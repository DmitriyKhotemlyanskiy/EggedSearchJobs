package main

import (
	"encoding/csv"
	"fmt"
	"io"
	"log"
	"os"
	"parser2/config"
	"parser2/entities"
	"strings"
)

func readFromPeulot(c chan entities.Job) {
	f1, err := os.Open("peulot.csv")
	if err != nil {
		log.Println("Error Opening file: shaaton1.csv ", err)
	}
	reader1 := csv.NewReader(f1)
	for {
		var peula strings.Builder

		row, err := reader1.Read()
		if err == io.EOF {
			fmt.Println("END OF peulot.csv FILE")
			break
		}
		//Next 3 lines build Job description from row[1] and row[7] to string
		peula.WriteString(row[1])
		peula.WriteString("\n")
		peula.WriteString(row[7])
		//____________________________________________________________________
		//Add a data to newJob
		newJob := entities.Job{
			Chapter:     row[3],
			Subchapter:  row[2],
			Code:        row[0],
			Description: peula.String(),
		}

		c <- newJob
		peula.Reset()
	}
}

func readFromShaaton(c chan entities.Job) {
	f, err := os.Open("shaaton.csv")
	if err != nil {
		log.Println("Error Opening file: shaaton.csv ", err)
	}
	var perek, tatperek string
	codeColNum := 0
	reader := csv.NewReader(f)
	for {
		var scania, mercedes, daf, man, golden, yutong, volvo, code string
		var teur strings.Builder
		var contain bool
		bus1, bus2, bus3, bus4, bus5, bus6, bus7 := "", "", "", "", "", "", ""
		row, err := reader.Read()
		if err == io.EOF {
			fmt.Println("END OF JOB SUCCESSFULLY")
			break
		}
		if err != nil {
			log.Println(err)
		}
		for _, col := range row {
			if strings.HasSuffix(col, ":קרפ תת") {
				tatperek = strings.Trim(col, ":קרפ תת")
				contain = true
				continue
			}
			if strings.HasSuffix(col, " קרפ") {
				perek = strings.Trim(col, " קרפ")
				contain = true
				continue
			}
		}
		if contain {
			continue
		}
		if row[0] == "הינקס ינוריע 5 ורוי" || row[0] == "הינקס ינוריע" || row[0] == "הינקס" {
			for colNum, col := range row {
				if col == "רפסמ" {
					codeColNum = colNum
				}
			}
		} else if !strings.HasSuffix(row[0], ":ףד") {

			for i := len(row); i > 10; i-- {
				if i == codeColNum {
					continue
				}
				if row[i-1] != "" {
					teur.WriteString(row[i-1])
					teur.WriteString(" ")
				}
			}
			if row[0] != "" {
				scania = row[0]
				bus5 = "5"
			}
			if row[2] != "" {
				yutong = row[2]
				bus7 = "7"
			}
			if row[3] != "" {
				golden = row[3]
				bus3 = "3"
			}
			if row[4] != "" {
				daf = row[4]
				bus2 = "2"
			}
			if row[6] != "" {
				volvo = row[6]
				bus6 = "6"
			}
			if row[8] != "" {
				man = row[8]
				bus4 = "4"
			}
			if row[9] != "" {
				mercedes = row[9]
				bus1 = "1"
			}

			code = row[codeColNum]
		} else {
			continue
		}
		if code == "" {
			continue
		}
		// BusId	Bus-Name
		// 1		Mercedes Benz
		// 2		DAF
		// 3		Golden Dragon
		// 4		MAN
		// 5		Scania
		// 6		Volvo
		// 7		Yutong
		var msg entities.Errors

		newJob := entities.Job{
			Chapter:     perek,
			Subchapter:  tatperek,
			Code:        code,
			Description: teur.String(),
		}
		teur.Reset()
		newJob.SetBusId(bus1, bus2, bus3, bus4, bus5, bus6, bus7)
		newJob.SetJobTime(&msg, mercedes, daf, golden, man, scania, volvo, yutong)
		c <- newJob
	}
}

func main() {
	msgFromPeulot := make(chan entities.Job)
	msgFromShaaton := make(chan entities.Job)
	var msg1 entities.Job
	var msg2 entities.Job
	var ok1, ok2 bool
	db := config.GetDB()
	defer db.Close()
	go readFromPeulot(msgFromPeulot)
	go readFromShaaton(msgFromShaaton)

	for {
		msg1, ok1 = <-msgFromPeulot
		if !ok1 {
			close(msgFromPeulot)
		}
		for {
			msg2, ok2 = <-msgFromShaaton
			if !ok2 {
				close(msgFromShaaton)
			}
			if msg1.Code != msg2.Code {
				fmt.Println(msg1.Code, " != ", msg2.Code)
				continue
			} else {
				fmt.Println(msg1.Code, " == ", msg2.Code)
				newJob := entities.Job{
					Chapter:     msg1.Chapter,
					Subchapter:  msg1.Subchapter,
					Code:        msg1.Code,
					Description: msg1.Description,
					BusId:       msg2.BusId,
					JobTime:     msg2.JobTime,
				}
				stmt, e := db.Prepare("INSERT INTO `egged`.`job_description` VALUES (?,?,?,?,?)")
				if e != nil {
					log.Println("Error Preparing: insert into egged.job_description ", e)
				}
				result, e := stmt.Exec(newJob.Code, newJob.Description, newJob.Chapter, newJob.Subchapter, nil)
				if e != nil {
					log.Println("Error stmt.Exec: egged.job_description ", e)
				}
				log.Println("Result stmt.Exec: egged.job_description ", result)
				stmt.Close()

				for i := 0; i < len(newJob.BusId); i++ {
					if newJob.BusId[i] != 0 {
						stmt, e := db.Prepare("INSERT INTO `egged`.`bus_job` VALUES (?,?,?,?)")
						if e != nil {
							log.Println("Error Preparing: insert into egged.bus_job ", e)
						}
						result, e := stmt.Exec(newJob.Code, newJob.JobTime[i], newJob.BusId[i], nil)
						if e != nil {
							log.Println("Error stmt.Exec: egged.bus_job ", e)
						}
						log.Println("Result stmt.Exec: egged.bus_job ", result)
						stmt.Close()
					}
				}
				insert, e := db.Query("UPDATE `egged`.`last_job` SET `last_job` = ? WHERE `id_last` = 1", newJob.Code)
				if e != nil {
					log.Println("Error db.Query: egged.last_job ", e)
				}
				fmt.Println("Last job code was added: " + newJob.Code)
				insert.Close()
				break
			}
		}
	}
}

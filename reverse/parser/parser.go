package main

import (
	"encoding/csv"
	"fmt"
	"io"
	"log"
	"os"
	"parser/config"
	"parser/entities"
	"strings"
	"unicode"
)

func isHebrew(r rune) bool {
	return r >= 'א' && r <= 'ת'
}

func reverseHebrewWords(s string) string {
	words := strings.Fields(s)
	sentense := make([]string, len(words))
	engSentense := make([]string, len(words))
	for i, word := range words {
		runes := []rune(word)
		if unicode.Is(unicode.Hebrew, runes[0]) && !unicode.IsPunct(runes[0]) {
			for i, j := 0, len(runes)-1; i < j; i, j = i+1, j-1 {
				runes[i], runes[j] = runes[j], runes[i]
			}
			words[i] = string(runes)
		} else if len(runes) > 1 {
			if unicode.Is(unicode.Hebrew, runes[1]) && !unicode.IsPunct(runes[1]) {
				for i, j := 0, len(runes)-1; i < j; i, j = i+1, j-1 {
					runes[i], runes[j] = runes[j], runes[i]
				}
				words[i] = string(runes)
			}
		}

	}
	for i, j, k := 0, len(words)-1, 0; i < len(words); i, j = i+1, j-1 {
		runes := []rune(words[i])
		if len(runes) <= 1 {
			if unicode.Is(unicode.Hebrew, runes[0]) {
				sentense[j] = words[i]
			} else {
				sentense[j] = ""
				fmt.Println("Not hebrew word: ", words[i])
				engSentense[k] = words[i]
				k++
			}
		} else {
			if unicode.Is(unicode.Hebrew, runes[1]) {
				sentense[j] = words[i]
			} else {
				sentense[j] = ""
				fmt.Println("Not hebrew word: ", words[i])
				engSentense[k] = words[i]
				k++
			}
		}

	}
	fmt.Println(engSentense)
	for i, j := 0, 0; i < len(sentense); i++ {
		if sentense[i] == "" {
			sentense[i] = engSentense[j]
			j++
		}
	}
	return strings.Join(sentense, " ")
}

func main() {
	f, err := os.Open("shaaton1.csv")
	if err != nil {
		log.Println("Error Opening file: shaaton1.csv ", err)
	}
	db := config.GetDB()
	defer db.Close()
	var perek, tatperek string
	codeColNum := 0
	//jobDescCol := 0
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
				tatperek = strings.Trim(reverseHebrewWords(col), ":קרפ תת")
				fmt.Printf("___>tatperek: %s\n", tatperek)
				contain = true
				continue
			}
			if strings.HasSuffix(col, " קרפ") {
				perek = strings.Trim(reverseHebrewWords(col), " קרפ")
				fmt.Printf("___>perek: %s\n", perek)
				contain = true
				continue
			}

		}
		if contain {
			continue
		}
		if row[0] == "הינקס ינוריע 5 ורוי" || row[0] == "הינקס ינוריע" {
			for colNum, col := range row {
				/*if col == "הלועפ רואת" {
					jobDescCol = colNum
				}*/
				if col == "רפסמ" {
					codeColNum = colNum
				}
			}
		} else if !strings.HasSuffix(row[0], ":ףד") {

			for i := 16; i > 10; i-- {
				if i == codeColNum {
					continue
				}
				if row[i] != "" {
					teur.WriteString(reverseHebrewWords(row[i]))
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
		if code == "" || teur.String() == "" {
			continue
		}
		/*		fmt.Printf("->\nperek: %s, tatperek: %s\nscania: %s, yutong: %s, golden: %s, daf: %s , volvo: %s, man: %s, mercedes: %s\n"+
				"teur peula: %s		code: %s\n", perek, tatperek, scania, yutong, golden, daf, volvo, man, mercedes, teur.String(), code)*/
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
		if newJob.Code == "" || newJob.Code == " " {
			msg.Append("Error: Enter the job code.")
		}
		if newJob.Description == "" || newJob.Description == " " {
			msg.Append("Error: Enter the job Description.")
		}
		if len(msg.Error) != 0 {
			log.Println(msg.Error)
		} else {
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
			//fmt.Println("Query added to job_description")
			insert, e := db.Query("UPDATE `egged`.`last_job` SET `last_job` = ? WHERE `id_last` = 1", newJob.Code)
			if e != nil {
				log.Println("Error db.Query: egged.last_job ", e)
			}
			fmt.Println("Last job code was added: " + newJob.Code)
			msg.LastJob = newJob.Code + " -> The last entered job code"
			insert.Close()
			//time.Sleep(1 * time.Second)
		}
	}
}

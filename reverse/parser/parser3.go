package main

import (
	"database/sql"
	"encoding/csv"
	"fmt"
	"io"
	"log"
	"main/entities"
	"os"
	"strconv"
	"strings"

	_ "github.com/go-sql-driver/mysql"
)

func GetDB() (db *sql.DB) {
	db, err := sql.Open("mysql", "root:Dimas7729981hot@tcp(92.205.131.156:3306)/egged")
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("Connected to MySQL database")
	return db
}

func readFromGoldenTimes(db *sql.DB) {

	f1, err := os.Open("GoldenTimesCSV.csv")
	if err != nil {
		log.Println("Error Opening file: GoldenTimesCSV.csv ", err)
	}
	reader1 := csv.NewReader(f1)
	for {
		var peula strings.Builder

		row, err := reader1.Read()
		if err == io.EOF {
			fmt.Println("END OF GoldenTimesCSV.csv FILE")
			break
		}

		//Next 3 lines build Job description from row[2] and row[3] to string
		peula.WriteString(row[1])
		peula.WriteString("\n")
		peula.WriteString(row[2])
		time, err := strconv.Atoi(row[3])
		if err != nil {
			fmt.Println("Has not time for this job.")
			break
		}
		//____________________________________________________________________
		//Add a data to newJob
		newJob := entities.Job{
			Chapter:     "לקוחות חוץ",
			Subchapter:  "גולדן דרגון",
			Code:        row[0],
			Description: peula.String(),
			BusId:       [7]int{0, 0, 0, 3, 0, 0, 0},
			JobTime:     [7]int{0, 0, 0, time, 0, 0, 0},
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

		if newJob.BusId[3] != 0 {
			stmt, e := db.Prepare("INSERT INTO `egged`.`bus_job` VALUES (?,?,?,?)")
			if e != nil {
				log.Println("Error Preparing: insert into egged.bus_job ", e)
			}
			result, e := stmt.Exec(newJob.Code, newJob.JobTime[3], newJob.BusId[3], nil)
			if e != nil {
				log.Println("Error stmt.Exec: egged.bus_job ", e)
			}
			log.Println("Result stmt.Exec: egged.bus_job ", result)
			stmt.Close()
		}
		insert, e := db.Query("UPDATE `egged`.`last_job` SET `last_job` = ? WHERE `id_last` = 1", newJob.Code)
		if e != nil {
			log.Println("Error db.Query: egged.last_job ", e)
		}
		fmt.Println("Last job code was added: " + newJob.Code)
		insert.Close()
	}
}

func main() {
	db := GetDB()
	defer db.Close()
	readFromGoldenTimes(db)
}

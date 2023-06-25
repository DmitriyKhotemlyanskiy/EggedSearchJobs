package main

import (
	"encoding/csv"
	"log"
	"os"
	"strconv"
)

type Line struct {
	Date   string
	Open   float64
	High   float64
	Low    float64
	Close  float64
	Volume int
	Adj    float64
}

func OpenCSV() [][]string {
	file, err := os.Open("table.csv")
	if err != nil {
		log.Println("Cannot open CSV file:", err)
	}
	defer file.Close()
	reader := csv.NewReader(file)
	rows, err := reader.ReadAll()
	if err != nil {
		log.Println("Cannot read CSV file:", err)
	}
	return rows
}

func main() {
	var Lines []Line
	rows := OpenCSV()
	for _, row := range rows {
		id, _ := strconv.ParseInt(row[0], 0, 0)
		user := User{Id: int(id),
			firstName: row[1],
			lastName:  row[2],
			email:     row[3],
		}
		users = append(users, user)
	}
}

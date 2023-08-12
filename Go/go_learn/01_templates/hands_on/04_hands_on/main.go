package main

import (
	"encoding/csv"
	"log"
	"os"
	"strconv"
	"text/template"
)

type Line struct {
	Date   string
	Open   float64
	High   float64
	Low    float64
	Close  float64
	Volume int64
	Adj    float64
}

var tpl *template.Template

func init() {
	tpl = template.Must(template.ParseFiles("tpl.html"))
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
		open, _ := strconv.ParseFloat(row[1], 64)
		high, _ := strconv.ParseFloat(row[2], 64)
		low, _ := strconv.ParseFloat(row[3], 64)
		close, _ := strconv.ParseFloat(row[4], 64)
		volume, _ := strconv.ParseInt(row[5], 64, 64)
		adj, _ := strconv.ParseFloat(row[6], 64)
		line := Line{
			Date:   row[0],
			Open:   open,
			Low:    low,
			High:   high,
			Close:  close,
			Volume: volume,
			Adj:    adj,
		}
		Lines = append(Lines, line)
	}
	err := tpl.Execute(os.Stdout, Lines)
	if err != nil {
		log.Fatalln(err)
	}
}

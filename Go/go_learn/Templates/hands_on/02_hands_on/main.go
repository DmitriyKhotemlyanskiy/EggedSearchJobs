package main

import (
	"log"
	"os"
	"text/template"
)

// Create a data structure to pass to a template which
// contains information about California hotels including Name, Address, City, Zip, Region
// region can be: Southern, Central, Northern
// can hold an unlimited number of hotels
type Hotel struct {
	Name, Address, City string
	Zip                 int64
	Region              string
}

var tpl *template.Template

func init() {
	tpl = template.Must(template.ParseFiles("tpl.html"))
}
func main() {
	hotels := []Hotel{
		{
			Name:    "5 Star hotel",
			Address: "public st. 5",
			City:    "California",
			Zip:     12345,
			Region:  "Southern",
		},
		{
			Name:    "Leonardo",
			Address: "Best st. 10",
			City:    "California",
			Zip:     1299876,
			Region:  "Central",
		},
		{
			Name:    "Plaza",
			Address: "Hilton st. 1",
			City:    "California",
			Zip:     1234500,
			Region:  "Northern",
		},
	}
	err := tpl.Execute(os.Stdout, hotels)
	if err != nil {
		log.Fatalln(err)
	}
}

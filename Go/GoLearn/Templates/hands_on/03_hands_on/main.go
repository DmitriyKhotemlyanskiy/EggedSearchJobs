package main

import (
	"log"
	"os"
	"text/template"
)

//Create a data structure to pass to a template which
//contains information about restaurant's menu including Breakfast, Lunch, and Dinner items

type Menu struct {
	Items []Item
}

type Item struct {
	Name         string
	Price        float32
	Availability bool
}
type Restauran struct {
	Breakfast, Lunch, Dinner Menu
}

var tpl *template.Template

func init() {
	tpl = template.Must(template.ParseFiles("tpl.html"))
}
func main() {
	restauran := Restauran{
		Breakfast: Menu{
			Items: []Item{
				{
					Name:         "Eggs",
					Price:        0.5,
					Availability: true,
				},
				{
					Name:         "Toasts",
					Price:        1.2,
					Availability: true,
				},
				{
					Name:         "Orange Juice",
					Price:        0.7,
					Availability: true,
				},
			},
		},
		Lunch: Menu{
			Items: []Item{
				{
					Name:         "Meat Steak",
					Price:        5.9,
					Availability: true,
				},
				{
					Name:         "Chicken Shnizel",
					Price:        3.5,
					Availability: true,
				},
				{
					Name:         "Humburger",
					Price:        4.7,
					Availability: false,
				},
				{
					Name:         "Home frice",
					Price:        0.7,
					Availability: true,
				},
			},
		},
		Dinner: Menu{
			Items: []Item{
				{
					Name:         "Pasta",
					Price:        2.5,
					Availability: true,
				},
				{
					Name:         "Pizza",
					Price:        4.5,
					Availability: true,
				},
				{
					Name:         "Salmon",
					Price:        5.7,
					Availability: false,
				},
			},
		},
	}

	err := tpl.Execute(os.Stdout, restauran)
	if err != nil {
		log.Fatalln(err)
	}
}

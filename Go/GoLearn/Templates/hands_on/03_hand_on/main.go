package main

import(
	"os"
	"log"
	"text/template"
)
//Create a data structure to pass to a template which
//contains information about restaurant's menu including Breakfast, Lunch, and Dinner items

type Menu struct{
	items []Item
}

type Item struct{
	Name string
	Price float32
	Availability bool
}
type Restauran struct{
	Breakfast, Lunch, Dinner Menu
}

var tpl *template.Template

func init(){
	tpl = template.Must(template.ParseFiles("tpl.html"))
}
func main(){
	restauran := []Restauran{
		Breakfast: []Menu{
			items: []Item{
				{
					Name: "Eggs",
					Price: 0.5,
					Availability:  true,
				},
				{
					Name: "Toasts",
					Price: 1.2,
					Availability: true,
				},
				{
					Name: "Orange Juice",
					Price: 0.7,
					Availability: true,
				},
			}


		},

	}
}
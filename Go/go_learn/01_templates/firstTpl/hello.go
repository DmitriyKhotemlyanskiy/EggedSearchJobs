package main

import (
	"log"
	"os"
	"text/template"
)

// type person struct {
// 	fname  string
// 	lname  string
// 	age    int64
// 	weight float64
// 	height float64
// }

func main() {
	tpl := template.Must(template.ParseGlob("*.html"))
	nf, err := os.Create("index2.html") // creating a new file named "index2.html"
	if err != nil {
		log.Println("error creating file", err)
	}
	defer nf.Close() //at the end of executing the programm close nf file

	err = tpl.Execute(nf, nil) //writing into a "index2.html" file
	if err != nil {
		log.Fatalln(err)
	}
	err = tpl.ExecuteTemplate(os.Stdout, "index3.html", "Passed data into the file") //passing data into a "index2.html" template
	if err != nil {
		log.Fatalln(err)
	}
	err = tpl.ExecuteTemplate(os.Stdout, "index4.html", "Pass data into a variable") //passing data into a "index2.html" template
	if err != nil {
		log.Fatalln(err)
	}
	//Passing SLICE or MAP in template:
	s := []string{"Dima", "Khotem", "Vyacheslav"}
	err = tpl.ExecuteTemplate(os.Stdout, "index5.html", s) //passing the slice/map into a "index5.html" template
	if err != nil {
		log.Fatalln(err)
	}
	//Passing Structure:
	type sage struct {
		Name  string
		Motto string
	}
	buddha := sage{
		Name:  "Buddha",
		Motto: "The blief of no beliefs",
	}
	err = tpl.ExecuteTemplate(os.Stdout, "index6.html", buddha) //passing the structure into a "index6.html" template
	if err != nil {
		log.Fatalln(err)
	}
	//Passing the slice of Struct:
	gandhi := sage{
		Name:  "Gandhi",
		Motto: " Be the change",
	}
	mlk := sage{
		Name:  "Martin Luter King",
		Motto: "Hatred never ceases...",
	}
	jesus := sage{
		Name:  "Jesus",
		Motto: "Love all",
	}
	muhammad := sage{
		Name:  "Muhammad",
		Motto: "To overcome evil with good is good...",
	}
	sages := []sage{
		buddha,
		gandhi,
		mlk,
		jesus,
		muhammad,
	}
	err = tpl.ExecuteTemplate(os.Stdout, "index7.html", sages)
	if err != nil {
		log.Fatal(err)
	}
	// me := person{
	// 	fname:  "Dmitriy",
	// 	lname:  "Khotemlyanskiy",
	// 	age:    31,
	// 	weight: 77.5,
	// 	height: 191.5,
	// }

	// fslice := []int{1, 5, 10, 3, 0, -5, 8, 4}

	// for i := range fslice {
	// 	fmt.Printf("%d \n", i)
	// }
	// for i, v := range fslice {
	// 	fmt.Printf("%d - %d \n", v, i)
	// }

	// myMap := map[string]int{
	// 	"di":  5,
	// 	"ma":  3,
	// 	"kho": 10,
	// }
	// fmt.Print(myMap)
	// fmt.Printf("\n")

	// for m := range myMap {
	// 	fmt.Print(m)
	// }
	// fmt.Printf("\n")
	// for s, i := range myMap {
	// 	fmt.Print(s, i)
	// }

}

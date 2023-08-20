package main

import (
	"html/template"
	"log"
	"net/http"
)

var tpl *template.Template

func init() {
	tpl = template.Must(template.ParseFiles("templates/index.html"))
}

func main() {
	fs := http.FileServer(http.Dir("public"))
	http.Handle("/pics/", fs)
	http.HandleFunc("/", dogs)
	http.ListenAndServe(":8080", nil)
}

func dogs(w http.ResponseWriter, req *http.Request) {
	err := tpl.Execute(w, tpl)
	if err != nil {
		log.Fatalln("template didn't execute: ", err)
	}
}

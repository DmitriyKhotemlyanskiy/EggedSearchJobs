package main

import (
	"html/template"
	"log"
	"net/http"
)

var tpl *template.Template

func init() {
	tpl = template.Must(template.ParseFiles("tpl.html"))
}

func slash(w http.ResponseWriter, r *http.Request) {
	err := tpl.Execute(w, "Slash endpoint")
	if err != nil {
		log.Fatalln(err)
	}
}

func dog(w http.ResponseWriter, r *http.Request) {
	err := tpl.Execute(w, "Dog endpoint")
	if err != nil {
		log.Fatalln(err)
	}
}

func me(w http.ResponseWriter, r *http.Request) {
	err := tpl.Execute(w, "My name is Dmitriy")
	if err != nil {
		log.Fatalln(err)
	}
}

func main() {
	http.HandleFunc("/", slash)
	http.HandleFunc("/dog/", dog)
	http.HandleFunc("/me/", me)

	http.ListenAndServe(":8080", nil)
}

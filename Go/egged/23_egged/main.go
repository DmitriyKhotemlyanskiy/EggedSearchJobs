package main

import (
	"html/template"
	"net/http"
)

func home_page(w http.ResponseWriter, r *http.Request) {
	tpl, _ := template.ParseFiles("index.html")
	tpl.Execute(w, nil)
}

func main() {
	http.HandleFunc("/", home_page)
	http.ListenAndServe(":8080", nil)
}

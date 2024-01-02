package main

import (
	"html/template"
	"main/config"
	"main/controllers"
	"main/entities"
	"net/http"
)

var tpl *template.Template

func init() {
	tpl = template.Must(template.ParseFiles("www/index.html"))
}

func home_page(w http.ResponseWriter, r *http.Request) {
	var result entities.Result
	result.Init()
	tpl.ExecuteTemplate(w, "index.html", result)
}

func main() {
	db := config.GetDB()
	defer db.Close()
	http.HandleFunc("/", home_page)
	http.HandleFunc("/search_bus_name", controllers.SearchControllers{}.SearchByBusName(db, tpl))
	http.HandleFunc("/search_job_desc", controllers.SearchControllers{}.SearchByDesc(db, tpl))
	http.HandleFunc("/search_job_code", controllers.SearchControllers{}.SearchByCode(db, tpl))
	http.HandleFunc("/search_chapter", controllers.SearchControllers{}.SearchByChapter(db, tpl))
	http.HandleFunc("/subsearch_chapter", controllers.SearchControllers{}.SearchBySubchapter(db, tpl))

	//подтягивать css файлы к сайту с помощъю слудующей функии:
	http.Handle("/css/", http.StripPrefix("/css/", http.FileServer(http.Dir("www/css"))))
	http.ListenAndServe(":8080", nil)
}

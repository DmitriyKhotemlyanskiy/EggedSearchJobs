package main

import (
	"database/sql"
	"fmt"
	"html/template"
	"log"
	"main/config"
	"main/entities"
	"net/http"
)

var tpl *template.Template

func init() {
	tpl = template.Must(template.ParseFiles("www/index.html"))
	//result.Init()
}

func home_page(w http.ResponseWriter, r *http.Request) {
	var result entities.Result

	/*res, err := db.Query("SELECT `last_job` FROM `egged`.`last_job` WHERE `id_last` = 1")
	if err != nil {
		log.Fatalln(err)
	}
	if res.Next() {
		err = res.Scan(&msg.LastJob)
		if err != nil {
			log.Fatalln(err)
		}
	}*/
	result.Init()
	fmt.Println(result.Options)
	tpl.ExecuteTemplate(w, "index.html", result)
}
func saveBases(w http.ResponseWriter, r *http.Request) {
	var msg entities.Errors
	db := config.GetDB()
	defer db.Close()
	newJob := entities.Job{
		Chapter:     r.FormValue("chapter"),
		Subchapter:  r.FormValue("subchapter"),
		Code:        r.FormValue("code"),
		Description: r.FormValue("op-description"),
	}
	if newJob.Code == "" || newJob.Code == " " {
		msg.Append("Error: Enter the job code.")
	}
	if newJob.Description == "" || newJob.Description == " " {
		msg.Append("Error: Enter the job Description.")
	}
	newJob.SetBusId(r.FormValue("bus1"), r.FormValue("bus2"), r.FormValue("bus3"), r.FormValue("bus4"), r.FormValue("bus5"), r.FormValue("bus6"), r.FormValue("bus7"))
	newJob.SetJobTime(&msg, r.FormValue("job-time1"), r.FormValue("job-time2"), r.FormValue("job-time3"), r.FormValue("job-time4"), r.FormValue("job-time5"), r.FormValue("job-time6"), r.FormValue("job-time7"))

	if len(msg.Error) != 0 {
		tpl.Execute(w, msg)
	} else {
		insert, e := db.Query("INSERT INTO `egged`.`job_description` VALUES (?,?,?,?)", newJob.Code, newJob.Description, newJob.Chapter, newJob.Subchapter)
		if e != nil {
			log.Fatalln(e)
		}
		defer insert.Close()

		for i := 0; i < len(newJob.BusId); i++ {
			if newJob.BusId[i] != 0 {
				insert, e := db.Query("INSERT INTO `egged`.`bus_job` VALUES (?,?,?)", newJob.Code, newJob.JobTime[i], newJob.BusId[i])
				if e != nil {
					log.Fatalln(e)
				}
				defer insert.Close()
			}
		}
		fmt.Println("Query added to job_description")
		insert, e = db.Query("UPDATE `egged`.`last_job` SET `last_job` = ? WHERE `id_last` = 1", newJob.Code)
		if e != nil {
			log.Fatalln(e)
		}
		fmt.Println("Last job code was added: " + newJob.Code)
		msg.LastJob = newJob.Code + " -> The last entered job code"
		insert.Close()
		tpl.ExecuteTemplate(w, "index.html", msg)
	}

}

func searchByBusName(w http.ResponseWriter, r *http.Request) {
	db := config.GetDB()
	defer db.Close()
	var result entities.Result
	var res *sql.Rows
	busId := r.FormValue("bus_ids")
	res, err := db.Query("SELECT `name`, `job_description`, `job_time`, `job_code`, `chapter`, `subchapter`"+
		"FROM `egged`.`job_description` AS `j_d`"+
		"JOIN `egged`.`bus_job` AS `b_j`"+
		"ON `j_d`.`j_code` = `b_j`.`job_code`"+
		"JOIN `egged`.`buses` AS `b`"+
		"ON `b_j`.`bus_id` = `b`.`id`"+
		"WHERE `b`.`id` LIKE ?", "%"+busId+"%")
	if err != nil {
		log.Fatalln(err)
	}
	for res.Next() {
		var search entities.Search

		err = res.Scan(&search.BusName, &search.Description, &search.JobTime, &search.Code, &search.Chapter, &search.Subchapter)
		if err != nil {
			log.Fatalln(err)
		}
		result.SearchRes = append(result.SearchRes, search)
	}
	result.Init()
	result.SetSelected(busId)
	fmt.Println(result.Options)
	tpl.ExecuteTemplate(w, "index.html", result)

}

func searchByDesc(w http.ResponseWriter, r *http.Request) {
	db := config.GetDB()
	defer db.Close()
	var res *sql.Rows
	var result entities.Result
	text := r.FormValue("job_description")
	busId := r.FormValue("bus_ids")
	res, err := db.Query("SELECT `name`, `job_description`, `job_time`, `job_code`, `chapter`, `subchapter`"+
		"FROM `egged`.`job_description` AS `j_d`"+
		"JOIN `egged`.`bus_job` AS `b_j`"+
		"ON `j_d`.`j_code` = `b_j`.`job_code`"+
		"JOIN `egged`.`buses` AS `b`"+
		"ON `b_j`.`bus_id` = `b`.`id`"+
		"WHERE `j_d`.`job_description` LIKE ? AND `b`.`id` LIKE ?", "%"+text+"%", "%"+busId+"%")
	if err != nil {
		log.Fatalln(err)
	}

	for res.Next() {
		var search entities.Search
		err = res.Scan(&search.BusName, &search.Description, &search.JobTime, &search.Code, &search.Chapter, &search.Subchapter)
		if err != nil {
			log.Fatalln(err)
		}
		result.SearchRes = append(result.SearchRes, search)
	}
	result.Init()
	result.SetSelected(busId)
	fmt.Println(result.Options)
	tpl.ExecuteTemplate(w, "index.html", result)
}

func searchByCode(w http.ResponseWriter, r *http.Request) {
	db := config.GetDB()
	defer db.Close()
	var result entities.Result
	jobCode := r.FormValue("job_codes")
	busId := r.FormValue("bus_ids")

	res, err := db.Query("SELECT `name`, `job_description`, `job_time`, `job_code`, `chapter`, `subchapter`"+
		"FROM `egged`.`job_description` AS `j_d`"+
		"JOIN `egged`.`bus_job` AS `b_j`"+
		"ON `j_d`.`j_code` = `b_j`.`job_code`"+
		"JOIN `egged`.`buses` AS `b`"+
		"ON `b_j`.`bus_id` = `b`.`id`"+
		"WHERE `b_j`.`job_code` LIKE ? AND `b`.`id` LIKE ?;", "%"+jobCode+"%", "%"+busId+"%")
	if err != nil {
		log.Fatalln(err)
	}
	for res.Next() {
		var search entities.Search
		err = res.Scan(&search.BusName, &search.Description, &search.JobTime, &search.Code, &search.Chapter, &search.Subchapter)
		if err != nil {
			log.Fatalln(err)
		}
		result.SearchRes = append(result.SearchRes, search)
	}
	result.Init()
	result.SetSelected(busId)
	fmt.Println(result.Options)
	tpl.ExecuteTemplate(w, "index.html", result)

}

func searchByChapter(w http.ResponseWriter, r *http.Request) {
	db := config.GetDB()
	defer db.Close()
	var result entities.Result
	chapter := r.FormValue("chapter_name")
	busId := r.FormValue("bus_ids")
	res, err := db.Query("SELECT `name`, `job_description`, `job_time`, `job_code`, `chapter`, `subchapter`"+
		"FROM `egged`.`job_description` AS `j_d`"+
		"JOIN `egged`.`bus_job` AS `b_j`"+
		"ON `j_d`.`j_code` = `b_j`.`job_code`"+
		"JOIN `egged`.`buses` AS `b`"+
		"ON `b_j`.`bus_id` = `b`.`id`"+
		"WHERE `j_d`.`chapter` LIKE ? AND `b`.`id` LIKE ?", "%"+chapter+"%", "%"+busId+"%")
	if err != nil {
		log.Fatalln(err)
	}
	for res.Next() {
		var search entities.Search
		err = res.Scan(&search.BusName, &search.Description, &search.JobTime, &search.Code, &search.Chapter, &search.Subchapter)
		if err != nil {
			log.Fatalln(err)
		}
		result.SearchRes = append(result.SearchRes, search)
	}
	result.Init()
	result.SetSelected(busId)
	fmt.Println(result.Options)
	tpl.ExecuteTemplate(w, "index.html", result)

}

func searchBySubchapter(w http.ResponseWriter, r *http.Request) {
	db := config.GetDB()
	defer db.Close()
	var result entities.Result
	subchapter := r.FormValue("subchapter_name")
	busId := r.FormValue("bus_ids")
	res, err := db.Query("SELECT `name`, `job_description`, `job_time`, `job_code`, `chapter`, `subchapter`"+
		"FROM `egged`.`job_description` AS `j_d`"+
		"JOIN `egged`.`bus_job` AS `b_j`"+
		"ON `j_d`.`j_code` = `b_j`.`job_code`"+
		"JOIN `egged`.`buses` AS `b`"+
		"ON `b_j`.`bus_id` = `b`.`id`"+
		"WHERE `j_d`.`subchapter` LIKE ? AND `b`.`id` LIKE ?", "%"+subchapter+"%", "%"+busId+"%")
	if err != nil {
		log.Fatalln(err)
	}
	for res.Next() {
		var search entities.Search
		err = res.Scan(&search.BusName, &search.Description, &search.JobTime, &search.Code, &search.Chapter, &search.Subchapter)
		if err != nil {
			log.Fatalln(err)
		}
		result.SearchRes = append(result.SearchRes, search)
	}
	result.Init()
	result.SetSelected(busId)
	tpl.ExecuteTemplate(w, "index.html", result)
}
func main() {
	db := config.GetDB()
	defer db.Close()
	http.HandleFunc("/", home_page)
	http.HandleFunc("/save_buses", saveBases)
	http.HandleFunc("/search_bus_name", searchByBusName)
	http.HandleFunc("/search_job_desc", searchByDesc)
	http.HandleFunc("/search_job_code", searchByCode)
	http.HandleFunc("/search_chapter", searchByChapter)
	http.HandleFunc("/subsearch_chapter", searchBySubchapter)

	//подтягивать css файлы к сайту с помощъю слудующей функии:
	http.Handle("/css/", http.StripPrefix("/css/", http.FileServer(http.Dir("www/css"))))
	http.ListenAndServe(":8080", nil)
}

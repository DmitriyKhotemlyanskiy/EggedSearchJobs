package controllers

import (
	"database/sql"
	"html/template"
	"log"
	"main/entities"
	"net/http"
)

type SearchControllers struct{}

func (s SearchControllers) SearchByBusName(db *sql.DB, tpl *template.Template) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
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
		tpl.ExecuteTemplate(w, "index.html", result)
	}
}

func (s SearchControllers) SearchByDesc(db *sql.DB, tpl *template.Template) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
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
		tpl.ExecuteTemplate(w, "index.html", result)
	}
}

func (s SearchControllers) SearchByCode(db *sql.DB, tpl *template.Template) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
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
		tpl.ExecuteTemplate(w, "index.html", result)
	}
}

func (s SearchControllers) SearchByChapter(db *sql.DB, tpl *template.Template) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
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
		tpl.ExecuteTemplate(w, "index.html", result)
	}
}

func (s SearchControllers) SearchBySubchapter(db *sql.DB, tpl *template.Template) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
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
}

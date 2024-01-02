package controllers

import (
	"database/sql"
	"fmt"
	"html/template"
	"log"
	"main/entities"
	"net/http"
)

type SaveController struct{}

func (s SaveController) SaveBases(db *sql.DB, tpl *template.Template) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		var msg entities.Errors
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
}

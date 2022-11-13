package controllers

//In this Controller, functions for GET Host requests
import (
	"database/sql"
	"examProg/entities"
	"examProg/utils"
	"github.com/gorilla/mux"
	"net/http"
)

type HostController struct{}

//Gets all hosts from DB table. This function takes pointer to DataBase
//and returns http.HandlerFunc
func (h HostController) GetAllHosts(db *sql.DB) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		var host entities.Host
		var hosts []entities.Host
		var errorMessage entities.Error
		rows, err := db.Query("SELECT * FROM hosts")
		if err != nil {
			errorMessage.Message = "Error: Get all hosts"
			utils.SendError(w, http.StatusInternalServerError, errorMessage)
			return
		}
		defer rows.Close()
		for rows.Next() {
			err := rows.Scan(&host.ID, &host.Uuid, &host.Name, &host.IPAddress)
			if err != nil {
				errorMessage.Message = "Error: (Get all hosts) Can't scan rows"
				utils.SendError(w, http.StatusInternalServerError, errorMessage)
				return
			}
			hosts = append(hosts, host)
		}
		////If hosts slice is empty -> no data in database
		if len(hosts) == 0 {
			errorMessage.Message = "No found hosts in database"
			utils.SendError(w, http.StatusNotFound, errorMessage)
			return
		}
		//Convert containers content to JSON representation
		w.Header().Set("Content-Type", "application/json")
		utils.SendSuccess(w, hosts)
	}
}

//Get host by ID from DB table. This function takes pointer to DataBase
//and returns http.HandlerFunc
func (h HostController) GetHostById(db *sql.DB) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		var host entities.Host
		var errorMessage entities.Error
		params := mux.Vars(r)
		rows, err := db.Query("SELECT * FROM hosts "+
			"WHERE id = ?", params["id"]) //Take id number from the endpoint <.../host/{id}>
		if err != nil {
			errorMessage.Message = "Error: Get host by ID"
			utils.SendError(w, http.StatusInternalServerError, errorMessage)
			return
		}
		defer rows.Close()
		for rows.Next() {
			err := rows.Scan(&host.ID, &host.Uuid, &host.Name, &host.IPAddress)
			if err != nil {
				errorMessage.Message = "Error: (Get host by ID) Can't scan rows"
				utils.SendError(w, http.StatusInternalServerError, errorMessage)
				return
			}
		}
		//If no found host with specific ID in DB, host.ID will equal to 0
		if host.ID == 0 {
			errorMessage.Message = "Not found host with this ID"
			utils.SendError(w, http.StatusNotFound, errorMessage)
			return
		}
		//Convert containers content to JSON representation
		w.Header().Set("Content-Type", "application/json")
		utils.SendSuccess(w, host)
	}
}

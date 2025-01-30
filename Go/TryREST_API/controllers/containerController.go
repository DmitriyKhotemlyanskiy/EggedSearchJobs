package controllers

//In this Controller, functions for GET,POST container requests
import (
	"database/sql"
	"encoding/json"
	"examProg/entities"
	"examProg/utils"
	"net/http"

	"github.com/google/uuid"
	"github.com/gorilla/mux"
)

type ContainerController struct{}

// Gets all containers from DB table. This function takes pointer to DataBase
// and returns http.HandlerFunc
func (c ContainerController) GetAllContainers(db *sql.DB) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Access-Control-Allow-Origin", "http://localhost:3000")
		w.Header().Set("Access-Control-Allow-Methods", "POST, GET, OPTIONS, PUT, DELETE, PATCH")
		w.Header().Set("Access-Control-Allow-Headers", "Accept, Content-Type, Content-Length, Accept-Encoding, X-CSRF-Token, Authorization")
		var container entities.Container
		var containers []entities.Container
		var errorMessage entities.Error
		rows, err := db.Query("SELECT * FROM containers;") //Get all rows from container table
		if err != nil {
			errorMessage.Message = "Error: Get all containers"
			utils.SendError(w, http.StatusInternalServerError, errorMessage)
			return
		}
		defer rows.Close()
		//Scan rows returned from SQL query
		for rows.Next() {
			err := rows.Scan(&container.ID, &container.HostId, &container.Name, &container.ImageName)
			if err != nil {
				errorMessage.Message = "Error: (Get all containers) Can't scan rows"
				utils.SendError(w, http.StatusInternalServerError, errorMessage)
				return
			}
			containers = append(containers, container)
		}
		//If containers slice is empty -> no data in database
		if len(containers) == 0 {
			errorMessage.Message = "No found containers in database"
			utils.SendError(w, http.StatusNotFound, errorMessage)
			return
		}
		//Convert containers content to JSON representation
		w.Header().Set("Content-Type", "application/json")
		utils.SendSuccess(w, containers)
	}
}

// Get container by there ID from DB table. This function takes pointer to DataBase
// //and returns http.HandlerFunc
func (c ContainerController) GetContainerById(db *sql.DB) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		var container entities.Container
		var errorMessage entities.Error
		params := mux.Vars(r)
		rows, err := db.Query("SELECT * FROM containers"+
			" WHERE id = ?;", params["id"]) //Take id number from the endpoint <.../container/{id}>
		if err != nil {
			errorMessage.Message = "Error: Get containers by ID"
			utils.SendError(w, http.StatusInternalServerError, errorMessage)
			return
		}
		defer rows.Close()
		for rows.Next() {
			err = rows.Scan(&container.ID, &container.HostId, &container.Name, &container.ImageName)
			if err != nil {
				errorMessage.Message = "Error: (Get containers by ID) Can't scan rows"
				utils.SendError(w, http.StatusInternalServerError, errorMessage)
				return
			}
		}
		//If no found container with specific ID in DB, container.ID will equal to 0
		if container.ID == 0 {
			errorMessage.Message = "Not found container with this ID"
			utils.SendError(w, http.StatusNotFound, errorMessage)
			return
		}
		//Convert containers content to JSON representation
		w.Header().Set("Content-Type", "application/json")
		utils.SendSuccess(w, container)
	}
}

// Add new container into DB. This function takes pointer to DataBase
// //and returns http.HandlerFunc
func (c ContainerController) AddContainer(db *sql.DB) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		var errorMessage entities.Error
		container := new(entities.Container)
		//Takes host_id and image_name from POST request and save into container variable
		err := json.NewDecoder(r.Body).Decode(&container)
		//If something wrong in POST request or
		//If at least one field missed information -> print Error and return from this function
		if container.HostId == 0 || container.ImageName == "" || err != nil {
			errorMessage.Message = "Error: Missing fields or wrong input"
			utils.SendError(w, http.StatusBadRequest, errorMessage)
			return
		}
		//Generate UUID and save it in container.Name
		uuidWithHyphen := uuid.New()
		uuid := uuidWithHyphen.String()
		container.Name = uuid
		_, err = db.Exec("INSERT INTO containers(host_id, name, image_name) "+
			"VALUES(?,?,?)", container.HostId, container.Name, container.ImageName)
		if err != nil {
			errorMessage.Message = "Error: Insert into container"
			utils.SendError(w, http.StatusInternalServerError, errorMessage)
			return
		}
		//Convert containers content to JSON representation
		w.Header().Set("Content-Type", "application/json")
		utils.SendSuccess(w, container)
	}
}

// Gets all containers for specific Host ID. This function takes pointer to DataBase
// //and returns http.HandlerFunc
func (c ContainerController) GetContainersByHostId(db *sql.DB) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		var container entities.ContainerByHost
		var containers []entities.ContainerByHost
		var errorMessage entities.Error
		params := mux.Vars(r)
		rows, err := db.Query("SELECT c.id, c.host_id, c.name, c.image_name, h.name "+
			"FROM containers c, hosts h "+
			"WHERE c.host_id = h.id AND h.id = ?;", params["host_id"]) //Take Host ID number from the endpoint <.../container/hosted/{host_id}>
		if err != nil {
			errorMessage.Message = "Error: Get containers by host ID"
			utils.SendError(w, http.StatusInternalServerError, errorMessage)
			return
		}
		defer rows.Close()

		for rows.Next() {
			err = rows.Scan(&container.ID, &container.HostId, &container.Name, &container.ImageName, &container.HostNAme)
			if err != nil {
				errorMessage.Message = "Error: (Get containers by host ID) Can't scan rows"
				utils.SendError(w, http.StatusInternalServerError, errorMessage)
				return
			}
			containers = append(containers, container)
		}
		//If containers slice is empty len(containers) will equal to 0
		if len(containers) == 0 {
			errorMessage.Message = "No found containers for this host"
			utils.SendError(w, http.StatusNotFound, errorMessage)
			return
		}
		//Convert containers content to JSON representation
		w.Header().Set("Content-Type", "application/json")
		utils.SendSuccess(w, containers)
	}
}

package main

import (
	"examProg/config"
	"examProg/controllers"
	"fmt"
	"github.com/gorilla/mux"
	_ "github.com/mattn/go-sqlite3"
	"log"
	"net/http"
)

func main() {
	db := config.GetDB() //Establishing connection to DBase
	router := mux.NewRouter()
	//Creates endpoints and connect them to relevant functions
	router.HandleFunc("/host", controllers.HostController{}.GetAllHosts(db)).Methods("GET")
	router.HandleFunc("/host/{id}", controllers.HostController{}.GetHostById(db)).Methods("GET")
	router.HandleFunc("/container", controllers.ContainerController{}.GetAllContainers(db)).Methods("GET")
	router.HandleFunc("/container/{id}", controllers.ContainerController{}.GetContainerById(db)).Methods("GET")
	router.HandleFunc("/container/hosted/{host_id}", controllers.ContainerController{}.GetContainersByHostId(db)).Methods("GET")
	router.HandleFunc("/container", controllers.ContainerController{}.AddContainer(db)).Methods("POST")
	//Informs at which port the server is running:
	fmt.Println("Server is running at port: 8080")
	log.Fatal(http.ListenAndServe(":8080", router))
}

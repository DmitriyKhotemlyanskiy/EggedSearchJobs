package utils

import (
	"encoding/json"
	"examProg/entities"
	"net/http"
)

//Prepares Error message for sending by http response
func SendError(w http.ResponseWriter, status int, err entities.Error) {
	w.WriteHeader(status)
	json.NewEncoder(w).Encode(err)
}

//Prepares Success message for sending by http response
func SendSuccess(w http.ResponseWriter, data interface{}) {
	json.NewEncoder(w).Encode(data)
}

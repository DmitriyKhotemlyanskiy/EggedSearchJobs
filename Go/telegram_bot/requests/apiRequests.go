package requests

import (
	"encoding/json"
	"fmt"
	"net/http"
	"telegram_bot/entities"
)

type Request struct {
	url string
}

func NewRequest() *Request {
	return &Request{url: "http://localhost:8080/api/v1/"}
}

func (r Request) GetAllAvailableTimes() *entities.AvailableTime {
	myUrl := r.url + "availableTimes"
	availableTimes := entities.NewAvailableTime()
	resp, err := http.Get(myUrl)
	if err != nil {
		fmt.Println("Request error: ", err)
	}

	defer resp.Body.Close()

	json.NewDecoder(resp.Body).Decode(availableTimes)
	return availableTimes
}

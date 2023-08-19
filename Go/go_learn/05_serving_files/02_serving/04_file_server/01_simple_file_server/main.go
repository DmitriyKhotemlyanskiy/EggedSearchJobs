package main

import (
	"io"
	"net/http"
)

func main() {
	http.Handle("/", http.FileServer(http.Dir("."))) //Use with "http.FileServer" -> "http.Handle" function!!!
	http.HandleFunc("/dog/", dog)
	http.ListenAndServe(":8080", nil)
}

func dog(w http.ResponseWriter, req *http.Request) {
	w.Header().Set("Content-Type", "text/html; charset=utf-8")
	io.WriteString(w, `<img src="toby.jpg">	`)
}

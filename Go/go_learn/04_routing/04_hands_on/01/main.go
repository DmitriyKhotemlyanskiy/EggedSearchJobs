package main

import (
	"io"
	"net/http"
)

func slash(w http.ResponseWriter, r *http.Request) {
	io.WriteString(w, "Slash endpoint")
}

func dog(w http.ResponseWriter, r *http.Request) {
	io.WriteString(w, "Dog endpoint")
}

func me(w http.ResponseWriter, r *http.Request) {
	io.WriteString(w, "My name is Dmitriy")
}

func main() {
	http.HandleFunc("/", slash)
	http.HandleFunc("/dog/", dog)
	http.HandleFunc("/me/", me)

	http.ListenAndServe(":8080", nil)
}

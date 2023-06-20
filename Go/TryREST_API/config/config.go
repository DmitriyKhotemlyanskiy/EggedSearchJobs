package config

import (
	"database/sql"
	_ "github.com/mattn/go-sqlite3"
	"log"
)

func GetDB() (db *sql.DB) {
	db, err := sql.Open("sqlite3", "./db/aqua.db")
	if err != nil {
		log.Fatal(err)
	}
	return db
}

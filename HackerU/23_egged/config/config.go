package config

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/go-sql-driver/mysql"
)

func GetDB() (db *sql.DB) {
	db, err := sql.Open("mysql", "root:Dimas7729981hot@tcp(127.0.0.1:3306)/egged")
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("Connected to MySQL database")
	return db
}

package main

import (
	"fmt"
	"log"
	"net"
)

func main() {
	li, err := net.Listen("tcp", ":8080")
	if err != nil {
		log.Fatal(err)
	}

	defer li.Close()

	for {
		conn, err := li.Accept()
		if err != nil {
			log.Fatal(err)
			continue
		}
		go handle(conn)
	}
}

func handle(conn net.Conn) {
	fmt.Fprintf(conn, "I see you connected.")
	conn.Close()
}

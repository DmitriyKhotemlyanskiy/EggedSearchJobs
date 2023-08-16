package main

import (
	"bufio"
	"fmt"
	"io"
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
	scan := bufio.NewScanner(conn)
	for scan.Scan() {
		ln := scan.Text()
		if ln == "" {
			break
		}
		fmt.Println(ln)
		io.WriteString(conn, "HTTP/1.1 200 OK\r\n")             //Status line
		io.WriteString(conn, ln+"	-> Connection established\n") //Write the message back to the connection
	}
	defer conn.Close()
	fmt.Println("Code got here.")
	io.WriteString(conn, "I see you connected.")
}

package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"time"
)

func main() {
	li, err := net.Listen("tcp", ":8080")
	if err != nil {
		log.Fatal(err)
	}

	defer li.Close()
	fmt.Println("Server started at port 8080. Try insert in your CMD -> telnet localhost 8080, and then write something to server")
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
	//Here we set how long the connection will be open.
	//In the example: 10 sec. And after that the connection will close.
	err := conn.SetDeadline(time.Now().Add(10 * time.Second))
	if err != nil {
		log.Println("***Connection timeout***")
	}
	scanner := bufio.NewScanner(conn)
	for scanner.Scan() {
		ln := scanner.Text()
		fmt.Println(ln)
		fmt.Fprintf(conn, "I heard you say: %s\n", ln)
	}
	defer conn.Close()

	fmt.Println("Code got here.")
}

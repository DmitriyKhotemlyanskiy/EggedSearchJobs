package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"strings"
)

func main() {
	li, err := net.Listen("tcp", ":8080")
	if err != nil {
		log.Fatalln(err.Error())
	}
	defer li.Close()

	for {
		conn, err := li.Accept()
		if err != nil {
			log.Fatalln(err.Error())
		}
		go handle(conn)
	}
}

func handle(conn net.Conn) {
	defer conn.Close()
	i := 0
	var m string
	var u string
	scanner := bufio.NewScanner(conn)
	for scanner.Scan() {
		ln := scanner.Text()
		fmt.Println(ln)
		if i == 0 {
			//request line
			m = strings.Fields(ln)[0] //method
			u = strings.Fields(ln)[1] //url
		}
		if ln == "" {
			//headers are done
			break
		}
		i++
	}
	body := `<!DOCTYPE html>
	<html lang="en">
		<head><meta charset="UTF-8">
			<title></title>
		</head>
		<body>
			<strong> Method*** ` + m + `</strong><br>
			<strong> URL*** ` + u + `</strong><br>
	 	</body>
	 </html>`

	fmt.Fprint(conn, "HTTP/1.1 200 OK\r\n")
	fmt.Fprintf(conn, "Content-Length: %d\r\n", len(body))
	fmt.Fprint(conn, "Content-Type: text/html\r\n")
	fmt.Fprint(conn, "\r\n")
	fmt.Fprint(conn, body)
}

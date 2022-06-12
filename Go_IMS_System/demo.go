package main

import (
	"flag"
	"io"
	"os"
)

var serverIp string
var serverPort int

func init() {
	flag.StringVar(&serverIp, "ip", "127.0.0.1", "设置服务器IP地址(默认是127.0.0.1)")
	flag.IntVar(&serverPort, "port", 8888, "设置服务器端口(默认是8888)")
}

func main() {
	// bytes := []byte{}
	// bytes = append(bytes, '\n')

	// fmt.Printf("%s", bytes)

	// flag.Parse()

	// fmt.Println(serverIp, serverPort)

	// var str string

	// fmt.Scan(&str)
	// fmt.Println(str)
	// fmt.Scanf("%s", &str)
	// fmt.Println(str)

	// reader := bufio.NewReader(os.Stdin)
	// res, _, err := reader.ReadLine()
	// if err != nil {
	// 	fmt.Println("reader Readline err: ", err)
	// 	return
	// }

	// fmt.Println(string(res))

	go print()

	// fmt.Println("Hi")

	for {

	}

}

func print() {
	// fmt.Println("Hello world")
	io.Copy(os.Stdout, os.Stdin)
}

package main

import (
	"flag"
	"fmt"
)

var serverIp string
var serverPort int

//Init函数会在main函数之前执行
func init() {
	flag.StringVar(&serverIp, "ip", "127.0.0.1", "设置服务器IP地址(默认是127.0.0.1)")
	flag.IntVar(&serverPort, "port", 8888, "设置服务器端口(默认是8888)")
}

func main() {

	//命令行解析
	flag.Parse()

	// client := NewClient("127.0.0.1", 8888)
	client := NewClient(serverIp, serverPort)

	if client == nil {
		fmt.Println(">>>>>>> Connect Server Fail .....")
		return
	}

	fmt.Println(">>>>>> Connect Success ......")

	go client.DealResponse()

	//启动客户端的业务
	// select {}
	client.Run()

}

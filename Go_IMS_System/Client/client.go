package main

import (
	"bufio"
	"fmt"
	"io"
	"net"
	"os"
	"time"
)

type Client struct {
	ServerIp   string
	ServerPort int
	Name       string
	conn       net.Conn
	flag       int //判断menu的类型,也就是区分是公聊还是私聊
}

func NewClient(serverIp string, serverPort int) *Client {

	//创建客户端对象
	client := &Client{
		ServerIp:   serverIp,
		ServerPort: serverPort,
		flag:       999,
	}

	//连接server
	conn, err := net.Dial("tcp", fmt.Sprintf("%s:%d", serverIp, serverPort))
	if err != nil {
		fmt.Println("net.Dial error: ", err)
		return nil
	}

	client.conn = conn

	return client
}

//处理server回应的消息，直接显示到标准输出即可
func (client *Client) DealResponse() {

	//一旦clien.conn有数据就直接拷贝到标准输出上，永久阻塞监听
	io.Copy(os.Stdout, client.conn)
}

func (client *Client) menu() bool {

	var flag int

	fmt.Println("1.public chat...")
	fmt.Println("2.private chat...")
	fmt.Println("3.update user name")
	fmt.Println("0.quit")

	fmt.Scanln(&flag)

	if flag >= 0 && flag <= 3 {
		client.flag = flag
		return true
	} else {
		// fmt.Println(">>>> 请输入合法范围内的数字 >>>>")
		fmt.Println("please input a valid number in 0-3")
		return false
	}

}

//查询在线用户
func (client *Client) SelectUsers() {
	sendMsg := "who\n"
	_, err := client.conn.Write([]byte(sendMsg))

	if err != nil {
		fmt.Println("conn Write err: ", err)
		return
	}

	return
}

//私聊模式
func (client *Client) PrivateChat() {

	var remoteName string
	var chatMsg string

	client.SelectUsers()

	// 等待一秒等控制台输出私聊之前自动查询的用户信息
	time.Sleep(time.Second * 1)

	// fmt.Println(">>>>请输入聊天对象[用户名], exit退出:")
	fmt.Println(">>> input the chat object [username], or exit quit")
	fmt.Scanln(&remoteName)

	reader := bufio.NewReader(os.Stdin)

	for remoteName != "exit" {
		// fmt.Println(">>>>请输入消息内容, exit退出")
		fmt.Println(">>>> input enter content, or exit to quit")
		line, _, err := reader.ReadLine()
		if err != nil {
			fmt.Println("reader Readline err:", err)
			return
		}
		chatMsg = string(line)

		for chatMsg != "exit" {
			if len(chatMsg) != 0 {

				sendMsg := "to|" + remoteName + "|" + chatMsg + "\n\n"

				_, err := client.conn.Write([]byte(sendMsg))
				if err != nil {
					fmt.Println("comm write err: ", err)
					break
				}
			}
			chatMsg = ""
			// fmt.Println(">>>> 请输入消息内容, exit退出")
			fmt.Println(">>>> input enter content, or exit to quit")
			// fmt.Scanln(&chatMsg)
			line, _, err = reader.ReadLine()
			if err != nil {
				fmt.Println("reader Readline err:", err)
				return
			}
			chatMsg = string(line)
		}

		client.SelectUsers()

		// 等待一秒让上面的函数将信息输出完毕
		time.Sleep(time.Second * 1)

		fmt.Println(">>>> intput Chat Object[username], or exit quit")
		fmt.Scanln(&remoteName)
	}

}

func (client *Client) PublicChat() {

	//提示用户输入消息
	var chatMsg string

	// fmt.Println(">>>> 请输入聊天内容，exit退出.")
	fmt.Println(">>>> input enter content, or exit to quit")

	reader := bufio.NewReader(os.Stdin)

	res, _, err := reader.ReadLine()
	if err != nil {
		fmt.Println("reader ReadLint err:", err)
		return
	}

	chatMsg = string(res)
	// fmt.Scanln(&chatMsg)

	for chatMsg != "exit" {
		// 发送给服务器,消息不为空则发送
		if len(chatMsg) != 0 {
			sendMsg := chatMsg + "\n"

			_, err := client.conn.Write([]byte(sendMsg))
			if err != nil {
				fmt.Println("comm write err: ", err)
				break
			}
		}

		chatMsg = ""
		// fmt.Println(">>> 请输入聊天内容, exit 退出")
		fmt.Println(">>>> input enter content, or exit to quit")
		// fmt.Scanln(&chatMsg)

		//考虑到带空格的字符串，不能使用Scan等函数
		// reader := bufio.NewReader(os.Stdin)
		res, _, err = reader.ReadLine()
		if err != nil {
			fmt.Println("reader ReadLint err:", err)
			return
		}

		chatMsg = string(res)
		// fmt.Println("hi", chatMsg)
	}

}

func (client *Client) UpdataName() bool {

	// fmt.Println(">>>> 请输入用户名: ")
	fmt.Println(">>>> input username: ")
	fmt.Scanln(&client.Name)

	sendMsg := "rename|" + client.Name + "\n"

	_, err := client.conn.Write([]byte(sendMsg))
	if err != nil {
		fmt.Println("UpdateName -> conn.Write err: ", err)
		return false
	}

	return true
}

//首次登录提醒用户修改名字
func (this *Client) First_Login_And_Updata_Name() bool {
	fmt.Scanln(&this.Name)

	sendMsg := "First Login" + this.Name + "\n"

	_, err := this.conn.Write([]byte(sendMsg))
	if err != nil {
		fmt.Println("conn.Write err:", err)
		return false
	}

	return true
}

func (client *Client) Run() {

	flag := client.First_Login_And_Updata_Name()
	if flag == false {
		fmt.Println("Login err!!!")
		return
	}

	//停顿一秒等待服务端输出用户登录信息(这个之后想办法替换掉)
	time.Sleep(time.Second)

	for client.flag != 0 {
		for client.menu() != true {
		}

		//根据不同的模式处理不同的业务即可
		switch client.flag {
		case 1:
			//公聊
			// fmt.Println("公聊模式选择...")
			client.PublicChat()
			break

		case 2:
			//私聊
			// fmt.Println("私聊模式选择...")
			client.PrivateChat()
			break

		case 3:
			//更新用户名
			// fmt.Println("更新用户名选择...")
			client.UpdataName()
			break

		default:
			//输入0退出
			break
		}
	}

}

/*
//在main函数之前执行

var serverIp string
var serverPort int

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
		fmt.Println(">>>>>>> 连接服务器失效 .....")
		return
	}

	fmt.Println(">>>>>> 连接服务器成功 ......")

	go client.DealResponse()

	//启动客户端的业务
	// select {}
	client.Run()

}
*/

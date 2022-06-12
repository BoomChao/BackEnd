package main

import (
	"fmt"
	"io"
	"net"
	"sync"
	"time"
)

type Server struct {
	Ip   string
	Port int

	//在线用户的列表
	OnlineMap map[string]*User

	//用于加锁互斥
	mapLock sync.RWMutex

	//消息广播的channel
	Message chan string
}

// 创建一个server的接口
func NewServer(ip string, port int) *Server {
	server := &Server{
		Ip:        ip,
		Port:      port,
		OnlineMap: make(map[string]*User),
		mapLock:   sync.RWMutex{},
		Message:   make(chan string),
	}

	return server
}

// 监听 Message 广播消息 channel 的 goroutine, 一旦有用户上线或者广播
// 消息就发送给全部的在线 user
func (this *Server) ListenMessager() {
	for {
		msg := <-this.Message

		//将msg发送给全部的在线User
		this.mapLock.Lock()
		for _, cli := range this.OnlineMap {
			cli.C <- msg
		}

		this.mapLock.Unlock()
	}
}

// 广播消息的方法
func (this *Server) BroadCast(user *User, msg string) {
	sendMsg := "[" + user.Addr + "]" + user.Name + ":" + msg

	this.Message <- sendMsg
}

func (this *Server) Handler(conn net.Conn) {
	// fmt.Println("连接建立成功")

	//创建用户
	user := NewUser(conn, this)

	//提示用户更改名字,设置成 [IP]:name 的格式
	msg := "please input username: "
	user.SendMsg(msg)

	//等待接受客户端发送过来的消息
	buf := make([]byte, 1024)

	//read会阻塞等待从socket中读取数据
	n, err := conn.Read(buf)
	if err != nil {
		fmt.Println("Handler -> Conn read err:", err)
		return
	}

	msg = string(buf[:n-1])
	if msg[:5] == "First" {
		user.Name = msg[11:]
	}

	//广播用户在线的消息
	user.Online()

	//监听用户是否活跃的channel
	isLive := make(chan bool)

	/*
		//用户上线,将用户加入到onlineMap中
		this.mapLock.Lock()
		this.OnlineMap[user.Name] = user
		this.mapLock.Unlock()

		//广播当前用户上线消息
		this.BroadCast(user, "已上线")
	*/

	//接受客户端发送的消息
	go func() {
		buf := make([]byte, 4096)
		for {
			n, err := conn.Read(buf)
			if n == 0 {
				// this.BroadCast(user, "下线")
				user.Offline()
				return
			}

			if err != nil && err != io.EOF {
				fmt.Println("Conn Read err: ", err)
				return
			}

			//提取用户消息(去除句尾的'\n')
			msg := string(buf[:n-1])

			/*
				//将得到的消息进行广播
				this.BroadCast(user, msg)
			*/
			//用户对msg进行处理
			user.DoMessage(msg)

			//用户的任意消息，代表当前用户是活跃的
			isLive <- true
		}
	}()

	for {
		//如果select中没有任何的通道准备好，那么当前select所在的协程会永远陷入等待
		//直到有一个case中的通道准备好为止
		select {

		//isLive能读取出东西就说明当前用户是活跃的,则不做任何处理
		case <-isLive:

		//超时强踢
		case <-time.After(time.Second * 100):
			user.SendMsg("Timeout auto offline !!!") //提示用户被踢
			close(user.C)                            //销毁使用的资源
			conn.Close()                             //关闭连接
			return
		}
	}

}

// 启动服务器的接口
func (this *Server) Start() {

	//设定socket
	listener, err := net.Listen("tcp", fmt.Sprintf("%s:%d", this.Ip, this.Port))
	if err != nil {
		fmt.Println("net.Listen err:", err)
		return
	}
	//关闭socket
	defer listener.Close()

	//启动监听 Mesage 的 goroutine
	go this.ListenMessager()

	//阻塞等待客户端发起连接
	for {
		//accept
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("listen accept err: ", err)
			continue
		}

		//do handler 异步处理
		go this.Handler(conn)
	}

}

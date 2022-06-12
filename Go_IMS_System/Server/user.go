package main

import (
	"net"
	"strings"
)

type User struct {
	Name string      //名字
	Addr string      //地址
	C    chan string //当前是否有数据回写给对应的客户端
	conn net.Conn    //socket通信的连接

	server *Server
}

//创建一个用户的API
func NewUser(conn net.Conn, server *Server) *User {
	userAddr := conn.RemoteAddr().String()

	user := &User{
		Name:   userAddr,
		Addr:   userAddr,
		C:      make(chan string),
		conn:   conn,
		server: server,
	}

	//启动监听当前 user channel 消息的 goroutine
	go user.ListenMessage()

	return user
}

//用户上线业务
func (this *User) Online() {

	//用户上线，将用户加入到 onlineMap 中
	this.server.mapLock.Lock()
	this.server.OnlineMap[this.Name] = this
	this.server.mapLock.Unlock()

	//广播当前用户上线消息
	this.server.BroadCast(this, "online")
}

//用户下线
func (this *User) Offline() {

	//用户下线，将客户从 OnlineMap 中删除
	this.server.mapLock.Lock()
	delete(this.server.OnlineMap, this.Name)
	this.server.mapLock.Unlock()

	//广播当前用户上线消息
	this.server.BroadCast(this, "offline")
}

//给当前 User 对应的客户端发送消息
//对应于 client 的 DealResponse 函数
func (this *User) SendMsg(msg string) {
	this.conn.Write([]byte(msg))
}

//用户处理消息的业务
func (this *User) DoMessage(msg string) {

	if msg == "who" {
		//私聊之前自动查询当前在线用户
		this.server.mapLock.Lock()
		for _, user := range this.server.OnlineMap {
			onlineMsg := "[" + user.Addr + "]" + user.Name + ":" + "online...\n"
			this.SendMsg(onlineMsg)
		}
		this.server.mapLock.Unlock()

	} else if len(msg) > 7 && msg[:7] == "rename|" {
		//消息格式: rename|张三
		newName := strings.Split(msg, "|")[1]

		//判断name是否存在
		if _, ok := this.server.OnlineMap[newName]; ok {
			// this.SendMsg("当前用户名被使用")
			this.SendMsg("The name already exist!!!")
		} else {
			this.server.mapLock.Lock()
			delete(this.server.OnlineMap, this.Name)
			this.server.OnlineMap[newName] = this
			this.server.mapLock.Unlock()

			//更新当前用户名
			this.Name = newName
			// this.SendMsg("您已经更新用户名" + this.Name + "\n")
			this.SendMsg("The user name update " + this.Name + "\n")
		}

	} else if len(msg) > 4 && msg[:3] == "to|" {

		//发送消息给对方
		//1.获取对方的用户名
		//2.根据用户名得到对方的User对象
		//3.获取消息内容，通过对方的User对象将消息内容发送出去

		remoteName := strings.Split(msg, "|")[1]

		remoteUser, ok := this.server.OnlineMap[remoteName]
		if !ok {
			this.SendMsg("user not exist!!!\n")
			return
		}

		content := strings.Split(msg, "|")[2]
		if content == "" {
			this.SendMsg("The content is empty, please try again!!!")
			return
		}

		remoteUser.SendMsg(this.Name + " speak to you: " + content)

	} else {
		this.server.BroadCast(this, msg)
	}

}

//监听当前 User channel 的方法, 一旦有消息就直接发送给客户端
func (this *User) ListenMessage() {
	for {
		msg := <-this.C

		this.conn.Write([]byte(msg + "\n"))
	}
}

/*
if remoteName == "" {
	this.SendMsg("消息格式不正确,请使用 \"to|张三|你好啊\"格式 ")
	return
}

this.SendMsg("无消息内容，请重发\n")

*/

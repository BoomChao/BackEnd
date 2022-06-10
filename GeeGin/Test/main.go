package main

import (
	"fmt"
)

type Animal struct {
	Cat
	addr string
}

type Cat struct {
	name string
	age  int
}

type Engine struct {
	RouterGroup             //写法1：这样写的话Engine结构体可以直接调用RouterGroup结构体实现的方法
	router      RouterGroup //写法2：这样写的话必须要使用Engine.router来调用RouterGroup实现的方法
}

type RouterGroup struct {
}

func (group RouterGroup) GET(relativePath string) string {
	return relativePath
}

func f() {
	g()
	fmt.Println("A")
}

func g() {
	defer func() {
		// if r := recover(); r != nil {
		// 	fmt.Println("Recovered in f", r)
		// }
		fmt.Println("hi")
	}()

	nums := []int{1, 2, 3}
	nums[3] = 40
	fmt.Println(nums[3])

	fmt.Println("hello world")
	// panic("hello wolrd")
}

func main() {
	s := "hello"
	prefix := ""

	fmt.Println(s[:len(prefix)] == prefix)

	// f()
	// fmt.Println("B")
	// s1, s2 := "/panic", ""
	// fmt.Println(strings.HasPrefix(s1, s2))
	// // f()
	// fmt.Println("B")
	// r := Engine{}
	// fmt.Println(r.RouterGroup.GET("/user"))
	// fmt.Println(r.GET("/user")) //Engine结构体可以直接调用RouterGroup实现的方法
}

/*
func main() {
	Cat := &Cat{name: "Tom", age: 14}

	ani := &Animal{
		Cat:  *Cat,
		addr: "England",
	}

	// fmt.Println(ani.cat.age)
	fmt.Println(ani.Cat.age)

	// mp := make(map[string]string)
	// mp["name"] = "world"

	// // fmt.Println(mp)
	// a, b := mp["name"]
	// fmt.Println(a, b)

	// str1, str2 := 1, 2
	// fmt.Print(str1, str2)
	// str := "/p/*name/"
	// fmt.Print(bytealg.CountString(str, '/'))
	// strs := strings.Split(str, "/")
	// fmt.Println(len(strs))
	// fmt.Println(strs)
}

*/

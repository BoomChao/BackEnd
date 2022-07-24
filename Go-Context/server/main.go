package main

import (
	"flag"
	"fmt"
	"net/http"
	"test/BackEnd/Go-Context/log"
	"time"
)

func main() {
	flag.Parse()
	http.HandleFunc("/", log.Decorate(handler))
	panic(http.ListenAndServe("127.0.0.1:8080", nil))
}

func handler(w http.ResponseWriter, r *http.Request) {
	ctx := r.Context()
	log.Println(ctx, "handle started")
	defer log.Println(ctx, "handler ended")

	//这个foo对应的value值是从客户端那边写入的，但是这里读不出来
	//如果想读出来需要在客户端那边将这个key-value写入到http的header里面才可以
	fmt.Printf("value for foo is %v\n", ctx.Value("foo"))

	select {
	//设置等待来模拟服务端处理客户端的请求
	case <-time.After(5 * time.Second):
		fmt.Fprintln(w, "hello")
	case <-ctx.Done():
		err := ctx.Err()
		log.Println(ctx, err.Error())
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}
}

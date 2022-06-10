package gee

import (
	"fmt"
	"log"
	"net/http"
	"runtime"
	"strings"
)

func Recovery() HandleFunc {
	return func(ctx *Context) {
		defer func() {
			if err := recover(); err != nil { //err不为nil代表有panic发生
				msg := fmt.Sprintf("%s", err)
				log.Printf("%s\n\n", trace(msg))
				ctx.Fail(http.StatusInternalServerError, "Internal Server Error")
			}
		}()
		ctx.Next() //这里一定要加
	}
}

func trace(msg string) string {
	var pcs [32]uintptr
	//Callers用来返回调用栈的程序计数器，第0个Caller是Callers本身
	//第1个是上一层trace
	//第2个是再上一层的defer func,为了日志简便跳过前三个Caller
	n := runtime.Callers(3, pcs[:])

	var str strings.Builder
	str.WriteString(msg + "\nTraceback:")
	for _, pc := range pcs[:n] {
		fn := runtime.FuncForPC(pc)
		file, line := fn.FileLine(pc)
		str.WriteString(fmt.Sprintf("\n\t%s:%d", file, line))
	}
	return str.String()
}

package main

import (
	gee "GeeGin/Gee"
	"fmt"
	"net/http"
	"time"
)

type student struct {
	Name string
	Age  int
}

func FormatAsDate(t time.Time) string {
	year, month, day := t.Date()
	return fmt.Sprintf("%d-%02d-%02d", year, month, day)
}

// 加上报错信息
func main() {
	r := gee.Default()

	// r.GET("/", func(ctx *gee.Context) {
	// 	ctx.String(http.StatusOK, "hello Geektutu\n")
	// })

	r.GET("/panic", func(ctx *gee.Context) {
		names := []string{"geektutu"}
		ctx.String(http.StatusOK, names[1000])
	})

	r.Run(":9999")
}

/*
//加上HTML渲染
func main() {
	r := gee.New()
	r.Use(gee.Logger())
	r.SetFunMap(template.FuncMap{
		"FormatAsDate": FormatAsDate,
	})
	r.LoadHTMLGlob("templates/*")
	r.Static("/assets", "./static")

	r.GET("/", func(ctx *gee.Context) {
		ctx.HTML(http.StatusOK, "css.tmpl", nil)
	})


	// stu1 := &student{Name: "Geektutu", Age: 20}
	// stu2 := &student{Name: "Jack", Age: 22}
	// r.GET("/", func(ctx *gee.Context) {
	// 	ctx.HTML(http.StatusOK, "css.tmpl", nil)
	// })
	// r.GET("/students", func(ctx *gee.Context) {
	// 	ctx.HTML(http.StatusOK, "arr.tmpl", gee.H{
	// 		"title":  "gee",
	// 		"stuArr": [2]*student{stu1, stu2},
	// 	})
	// })

	// r.GET("/date", func(ctx *gee.Context) {
	// 	ctx.HTML(http.StatusOK, "custom_func.tmpl", gee.H{
	// 		"title": "gee",
	// 		"now":   time.Date(2019, 8, 17, 0, 0, 0, 0, time.UTC),
	// 	})
	// })


	r.Run(":9999")
}
*/
/*
func onlyForv2() gee.HandleFunc {
	return func(ctx *gee.Context) {
		t := time.Now()
		log.Printf("[%d] %s in %v for group v2", ctx.StatusCode, ctx.Req.RequestURI, time.Since(t))
	}
}
//使用中间件
func main() {
	r := gee.New()
	r.Use(gee.Logger())
	r.GET("/", func(ctx *gee.Context) {
		ctx.HTML(http.StatusOK, "<h1>Hello Gee</h1>")
	})

	v2 := r.Group("/v2")
	v2.Use(onlyForv2())
	{
		v2.GET("/hello/:name", func(ctx *gee.Context) {
			ctx.String(http.StatusOK, "hello %s, you're at %s\n", ctx.Param("name"), ctx.Path)
		})
	}

	r.Run(":9999")
}
*/

/*
func main() {
	r := gee.New()
	r.GET("/index", func(ctx *gee.Context) {
		ctx.HTML(http.StatusOK, "<h1>Index Page</h1>")
	})

	v1 := r.Group("/v1")
	{
		v1.GET("/", func(ctx *gee.Context) {
			ctx.HTML(http.StatusOK, "<h1>Hello Gee</h1>")
		})
		v1.GET("/hello", func(ctx *gee.Context) {
			ctx.String(http.StatusOK, "hello %s, you're at %s\n", ctx.Query("name"), ctx.Path)
		})
	}

	v2 := r.Group("/v2")
	{
		v2.GET("/hello/:name", func(ctx *gee.Context) {
			ctx.String(http.StatusOK, "hello %s, you're at %s\n", ctx.Param("name"), ctx.Path)
		})
		v2.POST("/login", func(ctx *gee.Context) {
			ctx.JOSN(http.StatusOK, gee.H{
				"username": ctx.PostForm("username"),
				"password": ctx.PostForm("password"),
			})
		})

	}

	r.Run(":9999")
}
*/
/*
	// v2.GET("/assets/*filepath", func(ctx *gee.Context) {
	// 	ctx.JOSN(http.StatusOK, gee.H{"filepath": ctx.Param("filepath")})
	// })
	// r.POST("/login", func(ctx *gee.Context) {
	// 	ctx.JOSN(http.StatusOK, gee.H{
	// 		"username": ctx.PostForm("username"),
	// 		"password": ctx.PostForm("password"),
	// 	})
	// })
	// r.GET("/", func(w http.ResponseWriter, r *http.Request) {
	// 	fmt.Fprintf(w, "URL.Path = %q\n", r.URL.Path)
	// })

	// r.GET("/hello", func(w http.ResponseWriter, r *http.Request) {
	// 	for k, v := range r.Header {
	// 		fmt.Fprintf(w, "Header[%q] = %q\n", k, v)
	// 	}
	// })
type Engine struct{}

func (engine *Engine) ServeHTTP(w http.ResponseWriter, req *http.Request) {
	switch req.URL.Path {
	case "/":
		fmt.Fprintf(w, "URL.Path = %q\n", req.URL.Path)
	case "/hello":
		for k, v := range req.Header {
			fmt.Fprintf(w, "Header[%q] = %q\n", k, v)
		}
	default:
		fmt.Fprintf(w, "404 NOT FOUND: %s\n", req.URL)
	}
}

func main() {
	engine := new(Engine)
	log.Fatal(http.ListenAndServe(":9999", engine))
}
*/
/*
func main() {
	http.HandleFunc("/", indexHandler)
	http.HandleFunc("/hello", helloHandler)
	log.Fatal(http.ListenAndServe(":9999", nil))
}

func indexHandler(w http.ResponseWriter, req *http.Request) {
	fmt.Fprintf(w, "URL.Path = %q\n", req.URL.Path)
}

func helloHandler(w http.ResponseWriter, req *http.Request) {
	for k, v := range req.Header {
		fmt.Fprintf(w, "Header[%q] = %q\n", k, v)
	}
}
*/

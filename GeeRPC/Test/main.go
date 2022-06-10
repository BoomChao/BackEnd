package main

import (
	"fmt"
	"os"
)

func main() {

}

func init() {
	fmt.Println(os.Args[0])
}

/*
const (
	Ldate         = 1 << iota     // the date in the local time zone: 2009/01/23
	Ltime                         // the time in the local time zone: 01:23:23
	Lmicroseconds                 // microsecond resolution: 01:23:23.123123.  assumes Ltime.
	Llongfile                     // full file name and line number: /a/b/c/d.go:23
	Lshortfile                    // final file name element and line number: d.go:23. overrides Llongfile
	LUTC                          // if Ldate or Ltime is set, use UTC rather than the local time zone
	Lmsgprefix                    // move the "prefix" from the beginning of the line to before the message
	LstdFlags     = Ldate | Ltime // initial values for the standard logger

)

var defaultRPCPath = "/_geeprc_"

func worker(ctx context.Context, name string) {
	go func() {
		for {
			select {
			case <-ctx.Done():
				fmt.Println(name, "got the stop channel")
				return
			default:
				fmt.Println("still working")
				time.Sleep(time.Second)
			}
		}
	}()
}

func coroutine(ctx context.Context, duration time.Duration, id int, wg *sync.WaitGroup) {
	for {
		select {
		case <-ctx.Done():
			fmt.Printf("%d quit\n", id)
			wg.Done()
			return
		case <-time.After(duration):
			fmt.Printf("msg from %d\n", id)
		}
	}
}

type Test struct {
	n, m   int
	err    error
	expect error
}

func (w Test) Write(p []byte) (int, error) {
	// fmt.Println(w.m, w.n)
	// return len(p) * w.n / w.m, w.err
	return -1, errors.New("hi")
}

type Foo int

type Args struct{ Num1, Num2 int }

func (f Foo) Sum(args Args, reply *int) error {
	*reply = args.Num1 + args.Num2
	return nil
}

func (f Foo) Sleep(args Args, reply *int) error {
	time.Sleep(time.Second * time.Duration(args.Num1))
	*reply = args.Num1 + args.Num2
	return nil
}

func main() {
	var foo Foo
	register(&foo)
}

func register(rcvr interface{}) {
	typ := reflect.TypeOf(rcvr)
	// fmt.Println(typ.NumMethod())
	method := typ.Method(1)
	mType := method.Type
	replyType := mType.In(2)
	fmt.Println(replyType.Name(), replyType.PkgPath())

	fmt.Println(isExportedOrBuildinType(replyType))
	// for i := 0; i < typ.NumMethod(); i++ {
	// 	method := typ.Method(i)
	// 	mType := method.Type
	// 	argType := mType.In(1)
	// 	fmt.Println(argType.Name(), argType.PkgPath())

	// }
	// fmt.Println(typ.NumMethod())

	// fmt.Println(reflect.ValueOf(rcvr))
	// fmt.Println(reflect.Indirect(reflect.ValueOf(rcvr)))
	// fmt.Println(reflect.Indirect(reflect.ValueOf(rcvr)).Type().Name())
	// fmt.Println(reflect.TypeOf(rcvr))
}

func isExportedOrBuildinType(t reflect.Type) bool {
	return ast.IsExported(t.Name())
}


func main() {
	test := Test{}
	buf := bufio.NewWriter(test)
	n, e := buf.Write([]byte("hi"))
	fmt.Println(n)
	fmt.Println(e)

	// fmt.Println(time.Now())
	// wg := &sync.WaitGroup{}
	// ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	// defer cancel()

	// for i := 0; i < 3; i++ {
	// 	wg.Add(1)
	// 	go coroutine(ctx, time.Second, i, wg)
	// }

	// wg.Wait()

	// ctx, cancel := context.WithCancel(context.Background())

	// go worker(ctx, "node01")
	// go worker(ctx, "node02")
	// go worker(ctx, "node03")

	// time.Sleep(2 * time.Second)

	// cancel()

	// time.Sleep(time.Second * 2)

	// ctx, cancel := context.WithCancel(context.Background())

	// go func() {
	// 	for {
	// 		select {
	// 		case <-ctx.Done():
	// 			fmt.Println("got the stop channel")
	// 			return
	// 		default:
	// 			fmt.Println("still working")
	// 			time.Sleep(time.Second)
	// 		}
	// 	}
	// }()

	// time.Sleep(time.Second * 5)
	// cancel()
	// time.Sleep(time.Second)

	// var reply int
	// fmt.Println(reply)
	// ptr := &reply
	// fmt.Println(ptr)

	// var e error
	// if e == nil {
	// 	fmt.Println("hello")
	// }
	// fmt.Println(e)

	// hostport := ":0"
	// i := last(hostport, ":")
	// _, _ = net.Listen("tcp", ":0")

	// var m sync.Map
	// // m[1] = "hi"
	// m.Store(1, "hi")
	// key := 1
	// if v, ok := m.LoadAndDelete(key); ok {
	// 	fmt.Println("hello ", v)
	// }

	// if _, ok := m.Load(key); !ok {
	// 	fmt.Println("hei")
	// }

	// fmt.Println(m[1])

	// mp := make(map[int]string)
	// mp[1] = "hello"

	// delete(mp, 1)
	// if name, ok := mp[1]; ok {
	// 	fmt.Println(name)
	// }
	// ch1, ch2 := make(chan string), make(chan string)

	// go func(ch chan string) {
	// 	ch1 <- "hello"
	// }(ch1)

	// // ch1 <- "hello"
	// // ch2 <- "world"

	// select {
	// case msg1 := <-ch1:
	// 	fmt.Println(msg1)
	// case msg2 := <-ch2:
	// 	fmt.Println(msg2)
	// 	// default:
	// 	// 	fmt.Println("Receive nothing!!!")
	// }

	// str := fmt.Sprintf("CONNECT %s HTTP/1.0", defaultRPCPath)

	// // fmt.Println(str)

	// // str := "hello wolrd"

	// _, status, ok := strings.Cut(str, " ")
	// if !ok {
	// 	fmt.Println("error")
	// }

	// status = strings.TrimLeft(status, " ")
	// statudCode, _, _ := strings.Cut(status, " ")
	// fmt.Println(len(statudCode))

	// fmt.Println(proto)
	// fmt.Println(status)
	// fmt.Println(proto, status)
	// fmt.Println(proto, status, ok)

	// str := "CONNECT %s HTTP/1.0\n\n", defaultRPCPath

	// _, _ = io.WriteString(conn, fmt.Sprintf("CONNECT %s HTTP/1.0\n\n", defaultRPCPath))

	// log.SetFlags(0)
	// log.Println("hi")
}
*/

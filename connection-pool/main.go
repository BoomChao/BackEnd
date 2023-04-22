package connection_pool

import (
	"database/sql"
	"errors"
	"io"
	"log"
	"sync"
	"time"
)

// ConnPool 连接池结构体
type ConnPool struct {
	connections chan interface{}   // 连接池中的连接
	factory     func() interface{} // 创建连接的函数
	mu          sync.Mutex         // 互斥锁此(保证多个 goroutine 同时操作连接池的安全性)
}

// NewConnPool 创建一个新的连接池
func NewConnPool(factory func() interface{}, size int) (*ConnPool, error) {
	if size <= 0 {
		return nil, errors.New("pool size must be > 0")
	}
	pool := &ConnPool{
		connections: make(chan interface{}, size),
		factory:     factory,
	}
	for i := 0; i < size; i++ {
		pool.connections <- factory()
	}
	return pool, nil
}

// Get 从连接池中获取一个连接
func (pool *ConnPool) Get() (interface{}, error) {
	select {
	case conn := <-pool.connections:
		return conn, nil
	default:
		return pool.factory(), nil
	}
}

// Put 将连接放回连接池中(就是释放连接)
func (pool *ConnPool) Put(conn interface{}) {
	// 思考这里真的要加锁么？如果ConnPool没有记录当前的连接数,则这里是不用加锁的
	// 因为channel本身就是线程安全的
	pool.mu.Lock()
	defer pool.mu.Unlock()
	select {
	case pool.connections <- conn:
	default:
		// 如果连接池已满，直接关闭连接
		pool.Close(conn)
	}
}

// Close 关闭连接
func (pool *ConnPool) Close(conn interface{}) {
	if closer, ok := conn.(io.Closer); ok {
		closer.Close()
	}
}

// Len 获取连接池中的连接数量
func (pool *ConnPool) Len() int {
	return len(pool.connections)
}

func CreateDBConn() interface{} {
	db, err := sql.Open("mysql", "user:password@tcp(host:port)/dbname")
	if err != nil {
		log.Fatal(err)
	}
	// 设置连接的最大空闲时间
	db.SetConnMaxLifetime(time.Minute * 5)
	// 设置连接池的最大连接数
	db.SetMaxIdleConns(10)
	return db
}

func main() {
	// 然后，可以通过以下方式创建一个连接池:
	pool, err := NewConnPool(CreateDBConn, 20)
	if err != nil {
		log.Fatal(err)
	}

	// 获取连接
	conn, err := pool.Get()
	if err != nil {
		log.Fatal(err)
	}

	// 使用连接
	db := conn.(*sql.DB)
	rows, err := db.Query("SELECT * FROM table")
	if err != nil {
		log.Fatal(err)
	}
	defer rows.Close()
	for rows.Next() {
		// ...
	}

	// 使用完成后将连接放回连接池中
	pool.Put(conn)
}

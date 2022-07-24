package log

import (
	"context"
	"crypto/rand"
	"log"
	"math/big"
	"net/http"
)

type key int

const requestIDKey = key(42)

func Println(ctx context.Context, msg string) {
	id, ok := ctx.Value(requestIDKey).(int64)
	if !ok {
		log.Printf("[unknown] %s", msg)
		return
	}
	log.Printf("[%d] %s", id, msg)
}

func Decorate(f http.HandlerFunc) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		ctx := r.Context()
		n, _ := rand.Int(rand.Reader, big.NewInt(1000))
		id := n.Int64()
		ctx = context.WithValue(ctx, requestIDKey, id)
		f(w, r.WithContext(ctx))
	}
}

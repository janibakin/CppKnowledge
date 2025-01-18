package main

import (
	"fmt"
	"time"
)

func main() {
	// start timer
	start := time.Now()
	for i := 0; i < 100000000; i++ {
		// do nothing
	}
	// end timer
	elapsed := time.Since(start)
	fmt.Println("Time taken: ", elapsed)
}

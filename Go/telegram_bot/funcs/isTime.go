package funcs

import (
	"fmt"
	"time"
)

func IsTime(str string) bool {
	_, err := time.Parse("15:04", str)
	if err != nil {
		fmt.Println("Is not a time " + str)
		return false
	}
	fmt.Println("Is a Time ", str)
	return true
}

func IsDate(str string) bool {
	_, err := time.Parse("02 January 2006", str)
	if err != nil {
		fmt.Println("Is not a date " + str)
		return false
	}
	fmt.Println("Is a date " + str)
	return true
}

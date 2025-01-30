package funcs

import (
	"fmt"
	"reflect"
	"time"
)

func IsTime(str string) bool {
	t, err := time.Parse("15:04", str)
	if err != nil {
		fmt.Println("Is not a time")
		return false
	}
	fmt.Println(reflect.ValueOf(t))
	return true
}

func IsDate(str string) bool {
	t, err := time.Parse("02 January 2006", str)
	if err != nil {
		fmt.Println("Is not a date")
		return false
	}
	fmt.Println(reflect.ValueOf(t))
	return true
}

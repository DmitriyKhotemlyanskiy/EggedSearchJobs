package entities

import (
	"encoding/json"
	"fmt"
	"io"
	"os"
)

type JsonReader struct {
}

// Reads JSON file with menu in the bot.
func (j JsonReader) GetJsonFile() Lang {
	jsonFile, err := os.Open("config/txtmessages.json")
	if err != nil {
		fmt.Println("******Can't open file:", err)
	}

	defer jsonFile.Close()

	byteValue, _ := io.ReadAll(jsonFile)

	var res Lang
	json.Unmarshal([]byte(byteValue), &res)
	return res
}

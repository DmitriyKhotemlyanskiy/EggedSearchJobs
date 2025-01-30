package entities

import (
	"strconv"
	"telegram_bot/config"
)

type Admin struct {
	ID        int64  `json:"id"`
	FirstName string `json:"first_name"`
	LastName  string `json:"last_name"`
	UserName  string `json:"username"`
}

func GetAdmin() Admin {
	AdminID, _ := strconv.ParseInt(config.Config("ADMIN_ID"), 0, 64)
	admin := Admin{
		ID:        AdminID,
		FirstName: config.Config("ADMIN_NAME"),
		LastName:  config.Config("ADMIN_LASTNAME"),
		UserName:  config.Config("ADMIN_USERNAME"),
	}
	return admin
}

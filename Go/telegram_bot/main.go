package main

import (
	"telegram_bot/config"
	"telegram_bot/handlers"

	"github.com/gin-gonic/gin"
)

func main() {
	router := gin.Default()

	bot, updates := config.Bot{}.GetBot()
	handlers.HandleUpdates(bot, updates)
	router.Run(":8081")
}

package config

import (
	"log"

	tgbotapi "github.com/go-telegram-bot-api/telegram-bot-api/v5"
)

type Bot struct{}

func (b Bot) GetBot() (bot *tgbotapi.BotAPI, updates tgbotapi.UpdatesChannel) {
	bot, err := tgbotapi.NewBotAPI(Config("TELEGRAM_APITOKEN"))
	if err != nil {
		log.Print(err)
	}

	bot.Debug = false

	log.Printf("Authorized on account %s", bot.Self.UserName)

	u := tgbotapi.NewUpdate(0)
	u.Timeout = 60

	updates = bot.GetUpdatesChan(u)
	return bot, updates
}

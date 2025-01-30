package handlers

import (
	"telegram_bot/entities"

	tgbotapi "github.com/go-telegram-bot-api/telegram-bot-api/v5"
)

type UpdateHandler struct{}

func HandleUpdates(bot *tgbotapi.BotAPI, updates tgbotapi.UpdatesChannel) {
	var respMessage tgbotapi.Message
	lang := ""
	option := "1"
	arrFromUser := entities.SliceMsgsFromUser{}
	//var lang string
	for update := range updates {
		if update.Message == nil && update.CallbackQuery == nil {
			continue
		} else if update.Message != nil || update.CallbackQuery == nil {
			if !HandleMessage(bot, &update, &option, &arrFromUser, &respMessage) {
				continue
			}
		} else if update.Message == nil && update.CallbackQuery != nil {
			if !HandleCallback(bot, &update, &option, &lang, &arrFromUser, &respMessage) {
				continue
			}
		} else {
			continue
		}
	}
}

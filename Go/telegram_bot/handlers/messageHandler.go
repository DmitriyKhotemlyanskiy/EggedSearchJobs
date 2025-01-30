package handlers

import (
	"telegram_bot/builder"
	"telegram_bot/entities"

	tgbotapi "github.com/go-telegram-bot-api/telegram-bot-api/v5"
)

type MessageHandler struct{}

func HandleMessage(bot *tgbotapi.BotAPI, update *tgbotapi.Update, option *string, arrFromUser *entities.SliceMsgsFromUser, respMessage *tgbotapi.Message) bool {
	if update.Message.Text == "/start" { // If we got a message
		msg := builder.MsgBuilder{}.StartMsg(update.Message.Chat.ID)
		*respMessage, _ = bot.Send(msg)
		*option = "1"
		return false
	}
	arrFromUser.AppendMsgFromUser(*update.Message)
	return true
}

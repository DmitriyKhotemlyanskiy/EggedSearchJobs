package interfaces

import (
	tgbotapi "github.com/go-telegram-bot-api/telegram-bot-api/v5"
)

type Msg interface {
	GetNewMsg(*tgbotapi.Message) Msg
	AppendMsg(Msg)
	GetAllMessages() string
}

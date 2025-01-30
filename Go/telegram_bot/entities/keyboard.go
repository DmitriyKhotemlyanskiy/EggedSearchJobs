package entities

import (
	//"telegram_bot/entities"

	tgbotapi "github.com/go-telegram-bot-api/telegram-bot-api/v5"
)

type KeyBoard struct{}

func (k KeyBoard) GetKeyBoard(buttons []Button) tgbotapi.InlineKeyboardMarkup {
	var newKeyboard [][]tgbotapi.InlineKeyboardButton
	var row []tgbotapi.InlineKeyboardButton
	len := len(buttons)
	if len <= 2 {
		for _, button := range buttons {
			btn := tgbotapi.NewInlineKeyboardButtonData(button.GetText(), button.GetData())
			row = append(row, btn)
		}
		newKeyboard = append(newKeyboard, row)
	} else {
		for _, button := range buttons {
			btn := tgbotapi.NewInlineKeyboardButtonData(button.GetText(), button.GetData())
			row = append(row, btn)
		}
		size := 2
		var j int
		for i := 0; i < len; i += size {
			j += size
			if j > len {
				j = len
			}
			newKeyboard = append(newKeyboard, row[i:j])
		}
	}

	return tgbotapi.NewInlineKeyboardMarkup(newKeyboard...)
}

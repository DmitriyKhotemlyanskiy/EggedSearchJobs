package handlers

import (
	"telegram_bot/builder"
	"telegram_bot/entities"
	"telegram_bot/requests"

	tgbotapi "github.com/go-telegram-bot-api/telegram-bot-api/v5"
)

type CallbackHandler struct{}

func HandleCallback(bot *tgbotapi.BotAPI, update *tgbotapi.Update, option *string, lang *string, arrFromUser *entities.SliceMsgsFromUser, respMessage *tgbotapi.Message) bool {
	jsonFile := entities.JsonReader{}.GetJsonFile()

	if update.CallbackQuery.Data == "ru" || update.CallbackQuery.Data == "he" {
		*lang = update.CallbackQuery.Data
	} else {
		//If user randomly has clicked on old messages in bot then start dialog from start
		if *lang == "" {
			update.CallbackQuery.Data = "/start"
		}
		*option = update.CallbackQuery.Data
	}

	msg := builder.MsgBuilder{}.BuildMsg(arrFromUser, *lang, *option, jsonFile, update.CallbackQuery.Message.Chat.ID)
	// Respond to the callback query, telling Telegram to show the user
	// a message with the data received.
	callback := tgbotapi.NewCallback(update.CallbackQuery.ID, update.CallbackQuery.Data)
	if _, err := bot.Request(callback); err != nil {
		panic(err)
	}
	switch update.CallbackQuery.Data {
	case "0":
		if _, err := bot.Send(builder.MsgBuilder{}.BuildMsgToAdmin(*arrFromUser)); err != nil {
			panic(err)
		}
		builder.MsgBuilder{}.BuildPhotoToAdmin(bot, *arrFromUser)
		//Delete all old messages from the user and ready to next interaction with him
		var NewArr []tgbotapi.Message
		arrFromUser.AllMessages = NewArr
		msg = builder.MsgBuilder{}.BuildMsg(arrFromUser, *lang, *option, jsonFile, update.CallbackQuery.Message.Chat.ID)
		newRespMessage, _ := bot.Send(msg)
		//Delete message after user click on a button
		delMessage := tgbotapi.NewDeleteMessage(respMessage.Chat.ID, respMessage.MessageID)
		_, err := bot.Request(delMessage)
		if err != nil {
			panic(err)
		}
		*respMessage = newRespMessage
		*option = "1"
		return false
	case "/start":
		var NewArr []tgbotapi.Message
		arrFromUser.AllMessages = NewArr

		msg = builder.MsgBuilder{}.StartMsg(update.CallbackQuery.From.ID)
		newRespMessage, _ := bot.Send(msg)
		*respMessage = newRespMessage
		*option = "1"
		return false
	case "11111111":
		request := requests.NewRequest()
		availableTimes := request.GetAllAvailableTimes()
	}

	arrFromUser.AppendMsgFromCallback(update.CallbackQuery, jsonFile, *lang)

	// And finally, send a message containing the data received.
	newRespMessage, err := bot.Send(msg)
	if err != nil {
		panic(err)
	}
	//Delete message after user click on a button
	delMessage := tgbotapi.NewDeleteMessage(respMessage.Chat.ID, respMessage.MessageID)
	_, err = bot.Request(delMessage)
	if err != nil {
		panic(err)
	}
	*respMessage = newRespMessage
	return true
}

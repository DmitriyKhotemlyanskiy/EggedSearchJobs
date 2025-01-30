package entities

import (
	"strings"
	"time"

	tgbotapi "github.com/go-telegram-bot-api/telegram-bot-api/v5"
)

type SliceMsgsFromUser struct {
	AllMessages []tgbotapi.Message
}

// Adds User messages into slice
func (s *SliceMsgsFromUser) AppendMsgFromUser(msg tgbotapi.Message) {
	//if user sent more than two pictures/photos, clears MediaGroupID variable. This variable using for callback options in the bot
	if msg.MediaGroupID != "" {
		msg.MediaGroupID = ""
	}
	s.AllMessages = append(s.AllMessages, msg)
}

// Adds User callbacks into slice
func (s *SliceMsgsFromUser) AppendMsgFromCallback(callback *tgbotapi.CallbackQuery, jsonFile Lang, lang string) {
	var str string
	var opt string
	prevOption := len(s.AllMessages)
	//If a user return back to the start of the bot menu, delete all previous messages from user
	if callback.Data == "1" {
		var NewArr []tgbotapi.Message
		s.AllMessages = NewArr
		return
	}
	//If a user has selected only language, bot send him the first option menu.
	if prevOption == 0 {
		lastOption := jsonFile.Lng[lang].Opt["1"]
		for _, value := range lastOption.Btns {
			if value.GetData() == callback.Data {
				str = value.GetText()
				opt = value.GetData()
			}
		}
	} else {
		//If the last user's message not contain photos
		if s.AllMessages[prevOption-1].MediaGroupID == "" {
			for i := 1; i < prevOption; i++ {
				if s.AllMessages[prevOption-i].MediaGroupID != "" {
					lastOpt := jsonFile.Lng[lang].Opt[s.AllMessages[prevOption-i].MediaGroupID]
					for _, value := range lastOpt.Btns {
						if value.GetData() == callback.Data {
							str = value.GetText()
							opt = value.GetData()
						}
					}
					break
				}
			}
		} else {
			lastOpt := jsonFile.Lng[lang].Opt[s.AllMessages[prevOption-1].MediaGroupID]

			for _, value := range lastOpt.Btns {
				if value.GetData() == callback.Data {
					str = value.GetText()
					opt = value.GetData()
				}
			}
		}

	}
	//Save data in msg variable
	msg := tgbotapi.Message{
		MessageID:    callback.Message.MessageID,
		From:         callback.From,
		Date:         callback.Message.Date,
		Chat:         callback.Message.Chat,
		MediaGroupID: opt,
		Text:         str,
		Photo:        callback.Message.Photo,
		Caption:      "callback",
	}
	//Add msg only if recieved data not empty
	if str != "" {
		s.AllMessages = append(s.AllMessages, msg)
	}
}

// Get all recieved messages, callbacks and photos from user
func (s SliceMsgsFromUser) GetAllMessages() string {
	var str strings.Builder
	if len(s.AllMessages) > 1 {
		str.WriteString(
			"\nДанные клиента:\nUserName: @" + s.AllMessages[0].From.UserName +
				"\nName: " + s.AllMessages[0].From.FirstName +
				"\nLast Name: " + s.AllMessages[0].From.LastName +
				"\nДата и время: " + time.Unix(int64(s.AllMessages[0].Date), 0).Format("Jan 2, 2006 at 15:04:05") +
				"\nСодержание общения с ботом:\n")
		for _, msg := range s.AllMessages {
			if msg.Caption == "callback" {
				str.WriteString("\n" + msg.Text)
				continue
			}
			if msg.Photo != nil {
				str.WriteString("\nКлиент отправил фото " + msg.Text)

			}
			if msg.Text != "" {
				str.WriteString("\nКлиент: " + msg.Text)
			}
		}
		return str.String()
	}
	return "Клиент рандомно нажимал на кнопки. Не обращай внимания))))"
}

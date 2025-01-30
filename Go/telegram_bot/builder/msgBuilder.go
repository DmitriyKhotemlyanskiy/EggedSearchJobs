package builder

import (
	"telegram_bot/entities"

	tgbotapi "github.com/go-telegram-bot-api/telegram-bot-api/v5"
)

type MsgBuilder struct{}

// Builds start message to user (contain text and buttons for choose preferred language)
func (m MsgBuilder) StartMsg(chatID int64) tgbotapi.MessageConfig {
	msg := tgbotapi.NewMessage(chatID,
		"Доброго времени суток. Этот бот поможет вам узнать информацию "+
			"о тех услугах, которые я могу вам предоставить. А так же назначить "+
			"встречу со мной или телефонный разговор. "+
			"Чтобы бот сохранил ваши контактные данные и оповестил меня об этом\n"+
			"ВАЖНО закончить диалог с ним и нажать в конце на кнопку (ЗАКОНЧИТЬ).\n\n"+
			"בוט הזה יעזור לך למצוא מידע על השירותים שאני יכולה לספק לך. ניתן גם לקבוע איתי פגישה או שיחת טלפון. על מנת שהבוט ישמור את פרטי הקשר שלך ויודיע לי על כך, חשוב לסיים את הדיאלוג איתו וללחוץ על כפתור (לסיים) בסוף.\n\n"+
			""+
			"Выберте язык на котором вам удобнее общаться\n\n"+
			"תבחר\\י שפה שנוח לך לדבר איתי")
	newButtons := []entities.Button{}
	var btn entities.Button
	btn.NewButton("עברית", "he")
	newButtons = append(newButtons, btn)
	btn.NewButton("Русский", "ru")
	newButtons = append(newButtons, btn)
	keyboard := entities.KeyBoard{}.GetKeyBoard(newButtons)

	msg.ReplyMarkup = keyboard
	return msg
}

// Builds messages to user (msg contain text and buttons that taken from JSON file)
func (m MsgBuilder) BuildMsg(lang string, option string, jsonFile entities.Lang, chatID int64) tgbotapi.MessageConfig {
	msg := tgbotapi.NewMessage(chatID, jsonFile.Lng[lang].Opt[option].Msg)
	keyboard := entities.KeyBoard{}.GetKeyBoard(jsonFile.Lng[lang].Opt[option].Btns)
	msg.ReplyMarkup = keyboard
	//arr.AppendMsgFromBot(msg)
	return msg
}

func (m MsgBuilder) OrderQueueTime(available *entities.AvailableTime, lang string, option string, jsonFile entities.Lang, chatID int64) tgbotapi.MessageConfig {
	datetime := option
	option = "11111111"
	msg := tgbotapi.NewMessage(chatID, jsonFile.Lng[lang].Opt[option].Msg+"\n"+datetime)
	keyboard := entities.KeyBoard{}.GetKeyBoard(available.GetDatesButtons())
	keyboard = entities.KeyBoard{}.AppendButtons(keyboard, jsonFile.Lng[lang].Opt[option].Btns)
	msg.ReplyMarkup = keyboard

	return msg
}

// Builds message to admin with user information and his messages, clicks history in bot menu
func (m MsgBuilder) BuildMsgToAdmin(msgsFromUser entities.SliceMsgsFromUser) tgbotapi.MessageConfig {
	admin := entities.GetAdmin()
	msg := tgbotapi.NewMessage(admin.ID, msgsFromUser.GetAllMessages())
	return msg
}

// Forwards user's messages to admin if contains pictures or photo
func (m MsgBuilder) BuildPhotoToAdmin(bot *tgbotapi.BotAPI, msgsFromUser entities.SliceMsgsFromUser) {
	for _, message := range msgsFromUser.AllMessages {
		if message.Photo != nil {
			admin := entities.GetAdmin()
			msg := tgbotapi.NewForward(admin.ID, message.Chat.ID, message.MessageID)
			bot.Send(msg)
		}
	}
}

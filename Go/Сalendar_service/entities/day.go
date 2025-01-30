package entities

import (
	"calendar/config"
	"strconv"
)

type Day struct {
	Date            *DateTime
	WorkDayStart    string
	WorkDayEnd      string
	MeetingDuration int
	TimesArr        []string
}

func NewDay(dateUTC string) *Day {
	date := NewDateTime(dateUTC)
	dur, _ := strconv.ParseInt(config.GetFromEnv("MEETING_DURATION"), 0, 64)
	day := Day{
		Date:            date,
		WorkDayStart:    config.GetFromEnv("WORK_TIME_FROM"),
		WorkDayEnd:      config.GetFromEnv("WORK_TIME_TO"),
		MeetingDuration: int(dur),
	}
	for date.TimeBefore(day.WorkDayEnd) {

	}

}

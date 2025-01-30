package entities

import (
	"calendar/config"
	"strconv"

	"google.golang.org/api/calendar/v3"
)

type AvailableTime struct {
	DaysInterval    int    //DAYS
	MeetingDuration int    //MINUTES
	WorkTimeFrom    string //EXAMPLE -> "15:04"
	WorkTimeTo      string //EXAMPLE -> "18:00"
}

func getInt(str string) int {
	num, _ := strconv.Atoi(str)
	return num
}

func InitAvailableTime() *AvailableTime {
	return &AvailableTime{
		DaysInterval:    getInt(config.GetFromEnv("DAYS_INTERVAL")),
		MeetingDuration: getInt(config.GetFromEnv("MEETING_DURATION")),
		WorkTimeFrom:    config.GetFromEnv("WORK_TIME_FROM"),
		WorkTimeTo:      config.GetFromEnv("WORK_TIME_TO"),
	}
}

func (a *AvailableTime) GetAllAvailableTimes(items []*calendar.Event) []string {
	for _, item := range items {
			date := item.Start.DateTime
			end := item.End.DateTime
			if date == "" {
				date = item.Start.Date
				end = item.End.Date
			}
}

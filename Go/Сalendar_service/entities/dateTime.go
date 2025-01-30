package entities

import (
	"calendar/config"
	"strconv"
	"time"
)

type DateTime struct {
	Year     int            `json:"year"`
	Month    int            `json:"month"`
	Day      int            `json:"day"`
	Hour     int            `json:"hour"`
	Minute   int            `json:"minute"`
	Location *time.Location `json:"location"`
}

// Create and Init a new DateTime. Given date in "2024-08-04T23:04:00+03:00" format -> "YYYY-MM-DDThh:mm:ss+timezone"
func NewDateTime(dateUTC string) (newDate *DateTime) {
	date, _ := time.Parse(time.RFC3339, dateUTC)
	return &DateTime{
		Year:     date.Year(),
		Month:    int(date.Month()),
		Day:      date.Day(),
		Hour:     date.Hour(),
		Minute:   date.Minute(),
		Location: time.FixedZone(config.GetFromEnv("LOCATION"), 3*60*60),
	}
}

// Return the DateTime instance in time.Time representation from golang library
func (d DateTime) GetDate() (date time.Time) {
	return time.Date(
		d.Year,
		time.Month(d.Month),
		d.Day,
		d.Hour,
		d.Minute,
		0,
		0,
		d.Location,
	)
}

// Return DateTime instance in string representation
func (d DateTime) GetDateUTC() (date string) {
	return time.Date(
		d.Year,
		time.Month(d.Month),
		d.Day,
		d.Hour,
		d.Minute,
		0,
		0,
		d.Location,
	).Format(time.RFC3339)
}

func (d DateTime) GetTimeStr() (hour_minute string) {
	return d.GetDate().Format("15:04")
}
func (d DateTime) GetDayStr() (weekday_name string) {
	return d.GetDate().Weekday().String()
}
func (d DateTime) GetYearStr() (yyyy string) {
	return strconv.Itoa(d.GetDate().Year())
}
func (d DateTime) GetMonthStr() (month_name string) {
	return d.GetDate().Month().String()
}

// Set a new hour and minutes by sending "15:04" format string
func (d *DateTime) SetTime(hour_min string) {
	t, _ := time.Parse("15:04", hour_min)
	d.Hour = t.Hour()
	d.Minute = t.Minute()
}

// After(temp) – This function is used to check if given time is after the temporary time variable and return true if time variable comes after temporary time variable else false.
func (d DateTime) TimeAfter(hour_min string) bool {
	t1, _ := time.Parse("15:04", hour_min)
	t2, _ := time.Parse("15:04", d.GetTimeStr())
	return t2.After(t1)
}

// Before(temp) – This function is used to check if the given time is before the temporary time variable and return true if the time variable comes before the temporary time variable else false.
func (d DateTime) TimeBefore(hour_min string) bool {
	t1, _ := time.Parse("15:04", hour_min)
	t2, _ := time.Parse("15:04", d.GetTimeStr())
	return t2.Before(t1)
}

// Equal(temp) – This function is used to check if given time is equal the temporary time variable and return true if time variable equals temporary time variable else false.
func (d DateTime) TimeEqual(hour_min string) bool {
	t1, _ := time.Parse("15:04", hour_min)
	t2, _ := time.Parse("15:04", d.GetTimeStr())
	return t2.Equal(t1)
}
func (d *DateTime) AddTime(hour, minutes string) (hour_minute string) {
	h, _ := strconv.Atoi(hour)
	m, _ := strconv.Atoi(minutes)
	d.Hour += h
	d.Minute += m

	return d.GetTimeStr()
}

func (d *DateTime) TimeDifference(aboveDateTime DateTime) (hour int, minutes int) {
	if aboveDateTime.Hour == 0 {
		aboveHour := ((aboveDateTime.Hour + 24) * 60) + aboveDateTime.Minute
		lessHour := (d.Hour * 60) + d.Minute
		diff := aboveHour - lessHour
		return int(diff / 60), int(diff % 60)
	} else {
		aboveHour := (aboveDateTime.Hour * 60) + aboveDateTime.Minute
		lessHour := (d.Hour * 60) + d.Minute
		diff := aboveHour - lessHour
		return int(diff / 60), int(diff % 60)
	}
}

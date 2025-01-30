package entities

type AvailableTime struct {
	Days []Day `json:"days"`
}

type Day struct {
	Date     string            `json:"date"`
	TimesArr map[string]string `json:"timesarr"`
}

func NewAvailableTime() *AvailableTime {
	return &AvailableTime{}
}

func (a *AvailableTime) GetDatesButtons() []Button {
	var buttons []Button
	for _, day := range a.Days {
		button := Button{
			Text:  day.Date,
			Value: day.Date,
		}
		buttons = append(buttons, button)
	}
	return buttons
}

func (a *AvailableTime) GetTimesButtons(date string) []Button {
	var buttons []Button
	for _, day := range a.Days {
		if day.Date == date {
			for _, val := range day.TimesArr {
				button := Button{
					Text:  val,
					Value: val,
				}
				buttons = append(buttons, button)
			}
			break
		} else {
			continue
		}
	}
	return buttons
}

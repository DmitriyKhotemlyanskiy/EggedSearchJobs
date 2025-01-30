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

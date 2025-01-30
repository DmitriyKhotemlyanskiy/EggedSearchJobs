package entities

type Button struct {
	Text  string `json:"text"`
	Value string `json:"value"`
}

func (b *Button) NewButton(text, data string) {
	b.Text = text
	b.Value = data
}
func (b *Button) GetText() string {
	return b.Text
}
func (b *Button) GetData() string {
	return b.Value
}

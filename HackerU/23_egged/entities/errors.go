package entities

type Errors struct {
	Error   []string
	LastJob string
}

func (e *Errors) Append(s string) {
	e.Error = append(e.Error, s)
}

func (e Errors) String() string {
	var str string
	for _, err := range e.Error {
		str += err
	}
	return str
}

package entities

type Bus struct {
	Name           string //Brand name
	Model          string //Model name
	Euro           int32  //Ecological euro standart
	Type           string //Intercity or city bus
	JobCode        string //Job execution code
	JobDescription string //Description for the work
	JobTime        int32  //Work completion time
}

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

//func (b *Bus) setName(name string) {
//	b.Name = name
//}
//func (b *Bus) setModel(model string) {
//	b.Model = model
//}
//func (b *Bus) setEuro(euro int32) {
//	b.Euro = euro
//}
//func (b *Bus) setType(Type string) {
//	b.Type = Type
//}
//func (b *Bus) setJobCode(jobCode string) {
//	b.JobCode = jobCode
//}
//func (b *Bus) setDescription(description string) {
//	b.JobDescription = description
//}
//func (b *Bus) setJobTime(time int32) {
//	b.JobTime = time
//}
//func (b Bus) getName() string {
//	return b.Name
//}
//func (b Bus) getModel() string {
//	return b.Model
//}
//func (b Bus) getEuro() int32 {
//	return b.Euro
//}
//func (b Bus) getType() string {
//	return b.Type
//}
//func (b Bus) getJobCode() string {
//	return b.JobCode
//}
//func (b Bus) getDescription() string {
//	return b.JobDescription
//}
//func (b Bus) getJobTime() int32 {
//	return b.JobTime
//}

package entities

import (
	"fmt"
	"strconv"
	"strings"
)

// BusId	Bus-Name
// 1		Mercedes Benz
// 2		DAF
// 3		Golden Dragon
// 4		MAN
// 5		Scania
// 6		Volvo
// 7		Yutong
type Job struct {
	BusId       [7]int
	JobTime     [7]int
	Chapter     string
	Subchapter  string
	Code        string
	Description string
}

func (j *Job) SetBusId(arr ...string) {
	for i := 0; i < len(j.BusId); i++ {
		if arr[i] != "" {
			j.BusId[i], _ = strconv.Atoi(arr[i])
		} else {
			j.BusId[i] = 0
		}
	}
}

func (j *Job) SetJobTime(err *Errors, arr ...string) {
	var str strings.Builder
	for i := 0; i < len(j.JobTime); i++ {
		if arr[i] != "" && j.BusId[i] != 0 {
			j.JobTime[i], _ = strconv.Atoi(arr[i])
		} else if arr[i] != "" && j.BusId[i] == 0 {
			fmt.Fprintf(&str, " \nError %d -> Check bus or delete the job time. ", i+1)
			err.Append(str.String())
			str.Reset()
			continue
		} else if arr[i] == "" && j.BusId[i] != 0 {
			fmt.Fprintf(&str, " \nError %d -> Bus without job time, enter job time. ", i+1)
			err.Append(str.String())
			str.Reset()
			continue
		} else {
			j.JobTime[i] = 0
		}
	}
}
func (j Job) GetBusId() []string {
	var retString []string
	for bus := range j.BusId {
		retString = append(retString, strconv.Itoa(bus))
	}
	return retString
}

func (j Job) GetJobTime() []string {
	var retString []string
	for time := range j.JobTime {
		retString = append(retString, strconv.Itoa(time))
	}
	return retString
}

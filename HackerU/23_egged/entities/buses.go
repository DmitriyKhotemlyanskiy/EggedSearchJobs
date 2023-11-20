package entities

import (
	"fmt"
)

type Buses struct {
	BusesSlice []Bus //Container for buses
	Count      int32 //Count num of buses in slice
}

func (s *Buses) SliceInitial() {
	s.BusesSlice = make([]Bus, 5)
	s.Count = 0
}
func (s *Buses) AddNewBus(bus Bus) {
	s.BusesSlice = append(s.BusesSlice, bus)
	s.Count++
	fmt.Printf("\n%v -> Added successfuly\n", s.BusesSlice[s.Count-1])
}
func (s *Buses) GetBus() Bus {
	if s.Count == 0 {
		fmt.Printf("\nIs the last bus in the Slice: %v\n", s.BusesSlice[0])
		return s.BusesSlice[s.Count]

	} else {
		s.Count--
		return s.BusesSlice[s.Count]
	}

}

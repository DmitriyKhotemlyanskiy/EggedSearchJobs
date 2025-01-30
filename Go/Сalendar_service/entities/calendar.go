package entities

import (
	"calendar/config"
	"fmt"
	"log"
	"time"

	"google.golang.org/api/calendar/v3"
)

type Calendar struct{}

func (c Calendar) GetUpcomingEvents(srv *calendar.Service) []*calendar.Event {
	t := time.Now().Format(time.RFC3339)
	events, err := srv.Events.List(config.GetFromEnv("USER_EMAIL")).ShowDeleted(false).
		SingleEvents(true).TimeMin(t).MaxResults(10).OrderBy("startTime").Do()
	if err != nil {
		log.Fatalf("Unable to retrieve next ten of the user's events: %v", err)
	}
	fmt.Println("Upcoming events:")
	if len(events.Items) == 0 {
		fmt.Println("No upcoming events found.")
	}
	return events.Items
}

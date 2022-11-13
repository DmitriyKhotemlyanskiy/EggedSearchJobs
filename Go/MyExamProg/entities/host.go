package entities

//Host JSON representation
type Host struct {
	ID        int    `json:"id"`
	Uuid      string `json:"uuid"`
	Name      string `json:"name"`
	IPAddress string `json:"ip_address"`
}

package entities

//Container JSON representation
type Container struct {
	ID        int    `json:"id"`
	HostId    int    `json:"host_id"`
	Name      string `json:"name"`
	ImageName string `json:"image_name"`
}

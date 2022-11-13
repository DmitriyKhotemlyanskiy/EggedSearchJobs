package entities

//Container JSON representation for GET request for specific host id
type ContainerByHost struct {
	ID        int    `json:"id"`
	HostId    int    `json:"host_id"`
	Name      string `json:"name"`
	ImageName string `json:"image_name"`
	HostNAme  string `json:"hostName"`
}

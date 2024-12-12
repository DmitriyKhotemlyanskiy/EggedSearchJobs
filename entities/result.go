package entities

type Result struct {
	SearchRes []Search
	Options   []Option
}

func (r *Result) Init() {
	r.Options = []Option{
		{Value: "", Text: "הכל", Selected: false},
		{Value: "1", Text: "Mercedes OC500", Selected: false},
		{Value: "2", Text: "DAF", Selected: false},
		{Value: "3", Text: "Golden Dragon", Selected: false},
		{Value: "4", Text: "MAN", Selected: false},
		{Value: "5", Text: "Scania", Selected: false},
		{Value: "6", Text: "Volvo B12B", Selected: false},
		{Value: "7", Text: "Yutong", Selected: false},
	}
}

func (r *Result) SetSelected(opt string) {
	switch opt {
	case "":
		r.Options[0].Selected = true
	case "1":
		r.Options[1].Selected = true
	case "2":
		r.Options[2].Selected = true
	case "3":
		r.Options[3].Selected = true
	case "4":
		r.Options[4].Selected = true
	case "5":
		r.Options[5].Selected = true
	case "6":
		r.Options[6].Selected = true
	case "7":
		r.Options[7].Selected = true
	}
}

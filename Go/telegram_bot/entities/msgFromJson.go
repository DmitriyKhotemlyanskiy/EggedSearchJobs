package entities

type Lang struct {
	Lng map[string]Options `json:"lng"`
}

type Options struct {
	Opt map[string]MsgWithBtn `json:"opt"`
}

type MsgWithBtn struct {
	Msg  string   `json:"msg"`
	Btns []Button `json:"btns"`
}

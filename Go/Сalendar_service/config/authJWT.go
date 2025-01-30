package config

import (
	"context"
	"net/http"

	"golang.org/x/oauth2/google"
	"golang.org/x/oauth2/jwt"
)

type AuthJWT struct{}

func Auth() *http.Client {
	conf := &jwt.Config{
		Email:      GetFromEnv("EMAIL"),
		PrivateKey: []byte(GetFromEnv("PRIVATE_KEY")),
		Scopes: []string{
			GetFromEnv("SCOPE"),
		},
		TokenURL: google.JWTTokenURL,
	}

	return conf.Client(context.Background())
}

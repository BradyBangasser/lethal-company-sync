package models

import (
	"errors"
	"fmt"
)

var games = generateDebugGames(10)

type Game struct {
	Name             string `json:"name" xml:"Name"`
	Id               string `json:"id" xml:"Id"`
	ModPath          string `json:"modPath" xml:"ModPath"`
	SupportsProfiles bool   `json:"profiles" xml:"SupportsProfiles"`
}

func (game *Game) Save() {

}

func GetGames() []Game {
	return games
}

func GetGame(id string) (*Game, error) {
	for _, game := range games {
		if game.Id == id {
			return &game, nil
		}
	}

	return nil, errors.New("game not found")
}

func generateDebugGames(num int) []Game {
	g := []Game{}

	for i := 0; i < num; i++ {
		g = append(g, Game{
			Name: fmt.Sprintf("Game %d", i),
			Id: fmt.Sprintf("%06x", i + 100),
			ModPath: "/Here",
			SupportsProfiles: true,
		})
	}

	return g
}
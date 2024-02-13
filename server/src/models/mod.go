package models

import (
	"crypto/sha256"
	"errors"
	"fmt"
	"time"
)

var mods = generateDebugMods(games, 20)

type Mod struct {
	Name        string `json:"name" xml:"Name"`
	Description string `json:"des" xml:"Description"`
	DownloadUrl string `json:"durl" xml:"DownloadURL"`
	Version     string `json:"v" xml:"Version"`
	UploadTimeStamp time.Time `json:"ts" xml:"TimeStamp"`
	Id string `json:"id" xml:"Id"`
}

func generateModId(gameId string, name string) string {
	hash := sha256.Sum224([]byte(name))
	return fmt.Sprintf("%s:%x", gameId, string(hash[:]))
}

func (mod *Mod) Save() {

}

func GetMods() []Mod {
	return mods
}

func GetMod(id string) (*Mod, error) {
	for _, mod := range mods {
		if mod.Id == id {
			return &mod, nil
		}
	}

	return nil, errors.New("mod not found")
}

func generateDebugMods(games []Game, num int) []Mod {
	m := []Mod{}

	for i, game := range games {
		name := fmt.Sprintf("Mod %d", i)
		m = append(m, Mod{
			Name: name,
			Description: "Description",
			DownloadUrl: "Download URL",
			Version: "1.0.0",
			UploadTimeStamp: time.Now(),
			Id: generateModId(game.Id, name),
		})
	}

	return m
}
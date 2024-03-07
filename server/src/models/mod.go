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
	Hash string `json:"hash" xml:"Hash"`
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
			DownloadUrl: "http://849f90976f6f2afae5fb990635c67915.serveo.net/mod/000069:92038414a8a21b3f98b2a08c55e0201e9a7ebe8ac75d73dcee242f82/download/",
			Version: "1.0.0",
			UploadTimeStamp: time.Now(),
			Id: generateModId(game.Id, name),
			Hash: "f98fe137bb7047ac4e6f519a3db4b9fdc4bed0a16a778807a537295404df904dfdf48940d2796f8fc1b99e4d9e860f0b8c649afa71d36a78ccd4ed0168d934d9",
		})
	}

	return m
}
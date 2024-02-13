package main

import (
	"github.com/gin-gonic/gin"
	"lsc.bangasser.dev/src/routes"
)

func main() {
	engine := gin.Default()

	routes.CreateRouter(engine)

	engine.Run()
}
package routes

import (
	routes_ping "lsc.bangasser.dev/src/routes/ping"
	"github.com/gin-gonic/gin"
)

func CreateRouter(r *gin.Engine) {
	r_ping := r.Group("/ping"); {
		r_ping.GET("/", routes_ping.GET)
	}
}

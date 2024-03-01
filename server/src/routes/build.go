package routes

import (
	routes_game "lsc.bangasser.dev/src/routes/game"
	routes_game___id__ "lsc.bangasser.dev/src/routes/game/__id__"
	routes_mod "lsc.bangasser.dev/src/routes/mod"
	routes_mod___id___download "lsc.bangasser.dev/src/routes/mod/__id__/download"
	routes_mod___id__ "lsc.bangasser.dev/src/routes/mod/__id__"
	routes_ping "lsc.bangasser.dev/src/routes/ping"
	routes_report "lsc.bangasser.dev/src/routes/report"
	routes_report___id__ "lsc.bangasser.dev/src/routes/report/__id__"
	"github.com/gin-gonic/gin"
)

func CreateRouter(r *gin.Engine) {
	r_game := r.Group("/game"); {
		r_game.GET("/", routes_game.GET)
		r_game___id__ := r_game.Group("/:id"); {
			r_game___id__.GET("/", routes_game___id__.GET)
		}
	}
	r.GET("/", GET)
	r_mod := r.Group("/mod"); {
		r_mod.GET("/", routes_mod.GET)
		r_mod.POST("/", routes_mod.POST)
		r_mod___id__ := r_mod.Group("/:id"); {
			r_mod___id___download := r_mod___id__.Group("/download"); {
				r_mod___id___download.GET("/", routes_mod___id___download.GET)
			}
			r_mod___id__.GET("/", routes_mod___id__.GET)
		}
	}
	r_ping := r.Group("/ping"); {
		r_ping.GET("/", routes_ping.GET)
	}
	r_report := r.Group("/report"); {
		r_report.GET("/", routes_report.GET)
		r_report___id__ := r_report.Group("/:id"); {
			r_report___id__.POST("/", routes_report___id__.POST)
		}
	}
}

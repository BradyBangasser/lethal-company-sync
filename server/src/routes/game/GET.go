package game

import (
	"net/http"

	"github.com/gin-gonic/gin"
	"lsc.bangasser.dev/src/models"
)

func GET(c *gin.Context) {
	c.JSON(http.StatusOK, models.GetGames())
}
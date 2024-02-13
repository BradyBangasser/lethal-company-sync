package id

import (
	"net/http"

	"github.com/gin-gonic/gin"
	"lsc.bangasser.dev/src/models"
)

func GET(c *gin.Context) {
	id := c.Param("id")

	game, err := models.GetGame(id)

	if err != nil {
		if err.Error() == "game not found" {
			c.AbortWithError(http.StatusNotFound, err)
		} else {
			c.AbortWithError(http.StatusInternalServerError, err)
		}
	}

	c.JSON(http.StatusOK, game)
}
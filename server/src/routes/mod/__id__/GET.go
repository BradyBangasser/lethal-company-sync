package id

import (
	"net/http"

	"github.com/gin-gonic/gin"
	"lsc.bangasser.dev/src/models"
)

func GET(c *gin.Context) {
	id := c.Param("id")
	
	mod, err := models.GetMod(id)

	if err != nil {
		if err.Error() == "mod not found" {
			c.AbortWithError(http.StatusNotFound, err)
		} else {
			c.AbortWithError(http.StatusInternalServerError, err)
		}
	}

	c.JSON(http.StatusOK, mod)
}
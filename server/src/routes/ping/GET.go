package ping

import (
	"net/http"

	"github.com/gin-gonic/gin"
)

func GET(c *gin.Context) {
	c.String(http.StatusOK, "Pong")
}
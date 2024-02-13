package routes

import (
	"net/http"

	"github.com/gin-gonic/gin"
)

func GET(c *gin.Context) {
	// Change this to a 308 and not a redirect to google
	c.Redirect(http.StatusOK, "https://www.google.com")
}
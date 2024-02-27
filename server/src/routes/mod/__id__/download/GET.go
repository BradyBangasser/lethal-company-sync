package download

import "github.com/gin-gonic/gin"

func GET(c *gin.Context) {
	c.File("public/test.txt")
}
# !/usr/bin/env sh

python3 ./go-builder.py
go run ./src &
ssh -R "849f90976f6f2afae5fb990635c67915:80:localhost:8080" serveo.net
all: 
	gcc fetch.c play.c parse.c quiz.c -o quiz -ljson-c
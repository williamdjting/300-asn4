all: myls

main: myls.c
	gcc -g -Wall -o myls myls.c

clean: 
	$(RM) myls
all: p1 p2 
p1: monitor.c
	gcc -o monitor monitor.c
p2: hello.c
	gcc -o hello hello.c

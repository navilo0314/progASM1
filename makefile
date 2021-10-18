all: p1 p2 p3 p4 p5 p6
p1: monitor.c
	gcc -o monitor monitor.c
p2: hello.c
	gcc -o hello hello.c
p3: rusage.c
	gcc -o rusage rusage.c
p4: realtime.c
	gcc -o realtime realtime.c
p5: pipe.c
	gcc -o pipe pipe.c
p6: printdigits.c
	gcc -o pd printdigits.c
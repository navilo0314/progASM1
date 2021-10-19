all: p1 p2 p3 p4 p5 p7 p8 p9 p10
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
p9: playground.c
	gcc -o playground playground.c
p7: malloc.c
	gcc -o malloc malloc.c
p8: multiplyBy4.c
	gcc -o multiplyBy4 multiplyBy4.c
p10: monitor1.c
	gcc -o monitor1 monitor1.c
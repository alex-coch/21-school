clean:
	rm -rf ../../build/* *.o

all: chart.c graph.c parser.c
	gcc -std=c11 -Wall -Werror -Wextra chart.c graph.c parser.c -o ../build/graph

rebuild:
	$(MAKE) clean
	$(MAKE) all
PROGRAMS = main
CFLAGS = -g -std=c99 -Wall -Werror
programs: $(PROGRAMS)
main: main.o
	$(CC) -o $@ $^
clean: 
	-rm $(PROGRAMS) *.o
	-rm -rf $(PROGRAMS) main.dSYM


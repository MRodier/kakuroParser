parser: parser.o mainBT.c
	gcc -g3 -o $@ $^

%.o: %.c %.h
	gcc -g3 -c $<

clean:
	rm -f parser *.o

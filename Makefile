test:test.c
	gcc -o test test.c
.PHONY:clean
clean:
	rm -f test
	make clean




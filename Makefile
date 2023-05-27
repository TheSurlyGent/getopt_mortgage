all: mortgagepmt

mortgagepmt: mortgagepmt.c
	cc -o mortgagepmt mortgagepmt.c -lm

clean:
	rm *.o 

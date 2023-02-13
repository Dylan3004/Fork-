#makefile z poszczegolnych zadan


ZadanieA: zad3a.o 
	gcc zad3a.o -o zad3a.x
	./zad3a.x $(INT) $(INT2)
ZadanieB: zad3b.o zad3a.o
	gcc zad3b.o -o zad3b.x
	gcc zad3a.o -o zad3a.x
	./zad3b.x $(INT) $(INT2) 
ZadanieC: zad3c.o zad3c1.o zad3a.o
	gcc zad3a.o -o zad3a.x
	gcc zad3c1.o -o zad3c1.x
	gcc zad3c.o -o zad3c.x
	./zad3c.x $(INT) $(INT2)
	
%.o: %.c
	gcc -c $^
clean:
	rm *.o *.x

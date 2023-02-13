#makefile z poszczegolnych zadan


zad5a: zad5am.o zad5aprod.o zad5akons.o
	gcc zad5am.o -o zad5am.x
	gcc zad5aprod.o -o zad5aprod.x
	gcc zad5akons.o -o zad5akons.x
	./zad5am.x $(arg1) $(arg2) $(arg3) $(arg4) $(arg5)
zad5bprod:zad5aprod.o
	gcc zad5aprod.o -o zad5aprod.x
	./zad5aprod.x $(arg1) $(arg2) $(arg3)
zad5bkons:zad5akons.o
	gcc zad5akons.o -o zad5akons.x
	./zad5akons.x $(arg1) $(arg2) $(arg3)
%.o: %.c
	gcc -c $^
clean:
	rm *.o *.x

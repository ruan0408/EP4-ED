CC = gcc
CFLAGS = -ansi -Wall -pedantic -g

ep4: main.o t1.o t2.o Item_pal.o Item_lema.o Lista_pal.o Lista_sent.o getLine.o utils.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
main.o: main.c t1.h t2.h getLine.h
	$(CC) $(CFLAGS) -c $<
t1.o: t1enc.c t1.h utils.h
	$(CC) $(CFLAGS) -c $< -o $@
t2.o: t2enc.c t2.h utils.h
	$(CC) $(CFLAGS) -c $< -o $@
Item_pal.o: Item_pal.c Item_pal.h
	$(CC) $(CFLAGS) -c $<
Item_lema.o: Item_lema.c Item_lema.h
	$(CC) $(CFLAGS) -c $<
List_pal.o: Lista_pal.c Lista_pal.h utils.h
	$(CC) $(CFLAGS) -c $<
Lista_sent.o: Lista_sent.c Lista_sent.h utils.h
	$(CC) $(CFLAGS) -c $<
getLine.o: getLine.c getLine.h
	$(CC) $(CFLAGS) -c $<
utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f *.o *.gch ~*

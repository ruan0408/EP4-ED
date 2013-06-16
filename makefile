CC = gcc
CFLAGS = -ansi -Wall -pedantic

all: ep4encenc ep4enclp ep4lpenc ep4lplp

ep4encenc: main.o t1enc.o t2enc.o Item_pal.o Item_lema.o Lista_pal.o Lista_sent.o getLine.o utils.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
ep4enclp: main.o t1enc.o t2lp.o Item_pal.o Item_lema.o Lista_pal.o Lista_sent.o getLine.o utils.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
ep4lpenc: main.o t1lp.o t2enc.o Item_pal.o Item_lema.o Lista_pal.o Lista_sent.o getLine.o utils.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
ep4lplp: main.o t1lp.o t2lp.o Item_pal.o Item_lema.o Lista_pal.o Lista_sent.o getLine.o utils.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

main.o: main.c t1.h t2.h getLine.h
	$(CC) $(CFLAGS) -c $<
t1enc.o: t1enc.c t1.h utils.h
	$(CC) $(CFLAGS) -c $< -o $@
t2enc.o: t2enc.c t2.h utils.h
	$(CC) $(CFLAGS) -c $< -o $@
t1lp.o: t1lp.c t1.h utils.h
	$(CC) $(CFLAGS) -c $< -o $@
t2lp.o: t2lp.c t2.h utils.h
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

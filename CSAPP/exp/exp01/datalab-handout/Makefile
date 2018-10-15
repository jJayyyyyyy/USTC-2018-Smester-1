# Student's Makefile for the CS:APP Data Lab
TEAM = ac00
VERSION = 1
HANDINDIR = /afs/cs.cmu.edu/academic/class/15213-f01/L1/handin

CC = gcc
CFLAGS = -O -Wall -m64

btest: btest.c bits.c decl.c tests.c btest.h bits.h
	$(CC) $(CFLAGS) -o btest bits.c btest.c decl.c tests.c

handin:
	cp bits.c $(HANDINDIR)/$(TEAM)-$(VERSION)-bits.c

clean:
	rm -f *.o btest


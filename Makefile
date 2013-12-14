CC=g++
CFLAGS=-Wall -g
SRCS = $(wildcard *.cpp)
PROGS = $(patsubst %.cpp,%,$(SRCS)) # patten,replacement,text. % is the matching part

all: $(PROGS)

%: %.cpp
	$(CC) $(CFLAGS) -o $@ $<
# $@ is filename of target, $< is name of first dependency

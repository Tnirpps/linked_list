CC = gcc
LD = gcc
CFLAGS = -O2 -pedantic -std=c11 -Wall -Werror
LDFLAGS =#

SRC = main.c list.c
OBJ=$(SRC:.c=.o)
EXE=a.out

all: $(EXE)
	
$(EXE): $(OBJ)
	$(LD) $(LDFLAGS) -o $(EXE) $(OBJ)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf *.o a.out

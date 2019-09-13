BASIETYP= ../../basetyp.h
FSMBASE= $(wildcard ../*.c)
SRC=$(wildcard ./*.c)
SRC_H=$(patsubst *.c, *.h, $(SRC))
TAEGET=test
CC=gcc
ALL:
	$(CC) -o $(TARGET) -c $(SRC) $(SRC_H) $(BASETYP) $(FSMBASE)


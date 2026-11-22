BOOLE=/home/$$USER/github/boole
DIR = -DBASEDIR=\"/home/$$USER/boole/data/\"

ifeq (${MYHOST},dpt)
    BOOLE=/home/perso/langevin/github/boole
    DIR = -DBASEDIR=\"/home/perso/$$USER/github/boole/data/\"
endif
ifeq ($(DEBUG),1)
        OPTION = -Wall -g
else
    OPTION= -O3    -march=native   -Wno-unused-result
endif

CFLAGS = $(DIR) $(OPTION)  -I$(BOOLE)/src -L$(BOOLE)/src 
OFLAGS = $(DIR) $(OPTION)  -I$(BOOLE)/src -L$(BOOLE)/src

SRC = info.c select.c
EXE = $(SRC:.c=.exe)
OBJ = common.o



all: $(OBJ) $(EXE)

%.exe: %.c $(OBJ)
	gcc  $(CFLAGS) $^   -o $@ -lboole -lgmp

%.o: %.c
	gcc  $(CFLAGS) -c $< -o $@

debug :
	make DEBUG=1
clean:
	rm -f $(EXE) $(OBJ)


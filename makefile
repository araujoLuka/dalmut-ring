EXE = dalmut

SRC = $(wildcard ./SourceCode/*.c)
OBJ = $(SRC:.c=.o)

#--


all : $(EXE) clean
	@clear


#--


CFLAGS = -Wall
#LDLIBS =


#--


purge :	clean
	@rm -f $(EXE)
	@echo "terminado purge"

clean :
	@rm -f $(OBJ)
	@echo "terminado clean"


#--


$(EXE) : $(OBJ)


#--
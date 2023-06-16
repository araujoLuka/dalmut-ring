CFLAGS = -Wall -g
OBJECTS = libsocket.o
PROGRAM = main

# Regra para arquivos objeto
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

# Regras principais
all: $(PROGRAM)
$(PROGRAM): $(OBJECTS)

# Regra para excluir arquivos temporarios
clean:
	-rm -f $(OBJECTS) *.tar.gz

# Regra para excluir todos os arquivos gerado pelo make
purge: clean
	-rm -f $(PROGRAM)

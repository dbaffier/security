CFLAGS = -Wall -Werror -Wextra
STRACE := Colleen

all: $(STRACE)

$(COLLEEN): main.c
	$(CC) $(CFLAGS) -o $@ $^ 

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(COLLEEN) $(GRACE) $(SULLY)

re: fclean all
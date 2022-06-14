src = *.c

obj = $(src:.c=.o)

exec = pipex

flags = -Wall -Wextra -Werror

CC = gcc

$(exec) : $(obj)
	$(CC) $(flags) $(obj) -o $(exec)

clean : 
	rm -rf *.o


CPPFLAGS = -I/Users/hlachkar/.brew/opt/readline/include/
LDFLAGS = -L/Users/hlachkar/.brew/opt/readline/lib/

NAME = minishell

CFLAGS = -Wall -Wextra -Werror
		
SRC = *.c parse/*.c  exec/*.c

SANITIZE = -fsanitize=address

OBJ = $(SRC:.c=.o)


all : $(NAME)

$(NAME): $(SRC)
	@cc  $(CFLAGS) -g $(SRC) $(LDFLAGS) $(CPPFLAGS) -lreadline -o $(NAME)
	@echo "Mino ✅✅✅"

clean :
	@rm -f $(OBJ)
	@echo "🚮🚮🚮"

fclean : clean
	@rm -f $(NAME)
	@echo "🗑️ 🗑️ 🗑️"

re : fclean all
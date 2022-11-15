
CPPFLAGS = -I/Users/hlachkar/.brew/opt/readline/include/
LDFLAGS = -L/Users/hlachkar/.brew/opt/readline/lib/
# CPPFLAGS = -I/goinfre/hlachkar/homebrew/opt/readline/include
# LDFLAGS = -L/goinfre/hlachkar/homebrew/opt/readline/lib

NAME = minishell
NAME_BONUS = 

CFLAGS = -Wall -Wextra -Werror
SANITIZE = -fsanitize=address
		
SRC = *.c parse/*.c  exec/*.c
SRC_BONUS = 

SANITIZE = -fsanitize=address

OBJ = $(SRC:.c=.o)
OBJ_BONUS = 


all : $(NAME)

$(NAME): $(SRC)
	@cc  $(CFLAGS) -g $(SRC) $(LDFLAGS) $(CPPFLAGS) -lreadline -o $(NAME) $(SANITIZE)
	@echo "Mino ✅✅✅"

clean :
	@rm -f $(OBJ)
	@echo "🚮🚮🚮"

fclean : clean
	@rm -f $(NAME)
	@echo "🗑️ 🗑️ 🗑️"

re : fclean all
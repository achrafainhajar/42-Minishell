
CPPFLAGS = -I/Users/hlachkar/.brew/opt/readline/include/
LDFLAGS = -L/Users/hlachkar/.brew/opt/readline/lib/
# CPPFLAGS = -I/goinfre/hlachkar/homebrew/opt/readline/include
# LDFLAGS = -L/goinfre/hlachkar/homebrew/opt/readline/lib

NAME = minishell
NAME_BONUS = 

CFLAGS = -Wall -Wextra -Werror
SANITIZE =
		
SRC = *.c parse/*.c  exec/*.c
SRC_BONUS = 


OBJ = $(SRC:.c=.o)
OBJ_BONUS = 


all : $(NAME)

$(NAME):
	
	@cc  $(CFLAGS) -g $(SRC) $(LDFLAGS) $(CPPFLAGS) -lreadline  -o $(NAME) $(SANITIZE)
	@echo "Mino 👍👍👍"

$(NAME_BONUS) : 
	@gcc $(CFLAGS) -g $(SRC_BONUS) -o $(NAME_BONUS)
	@echo "🎁🎁🎁"

bonus: $(NAME_BONUS)

clean :
 
	@rm -f $(OBJ) $(OBJ_BONUS)
	@echo "🚮🚮🚮"

fclean : clean
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "🗑️ 🗑️ 🗑️"

re : fclean all
	@rm -r *.dSYM
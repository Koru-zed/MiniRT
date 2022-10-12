NAME := miniRT

FILES := get_next_line/get_next_line.c \
		 main.c

OBJES := ${FILES:.c=.o} 

CC := cc -g3

LIBFT := libft/libft

CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address

# FRAMWORK = -lmlx -framework OpenGL -framework AppKit

RM := /bin/rm -rf

#colors 

YELLOW = \033[1;93m
PURPLE = \033[1;95m
GREEN = \033[1;92m
WHITE = \033[1;97m
RED = \033[1;91m

all : ${NAME}

${NAME} : ${OBJES} ${LIBFT}
	 ${CC} ${CFLAGS} ${LIBFT} $^ -o $@
	@ echo "       ${YELLOW}}}}.....${GREEN}!Compile :-> fdf <-: Successe!${YELLOW}.....{{{${WHITE}"

%.o : %.c
	@ echo "${BLUE}Generating Minishell objects... ${PURPLE}" $@ "${WHITE}"
	@$(CC) $(CFLAGS) -c $< -o $@

claen : 
	@ ${RM} ${OBJES}
	@ echo "${YELLOW}-> ${PURPLE}Delete the object files.....${WHITE}"

fclean : clean
	@ ${RM} ${NAME}
	@ echo "${YELLOW}-> ${RED}fclean : Deleting executable done.${WHITE}\n"

re : fclean all

.PHONY : all clean fclean re
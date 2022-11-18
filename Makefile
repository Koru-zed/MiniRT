NAME := miniRT

FILES := get_next_line/get_next_line.c \
		 Parssing/fill_data.c \
		 Parssing/free_mini.c \
		 Parssing/fill_info.c \
		 Parssing/set_data.c \
		 Parssing/rt_last_node.c \
		 Parssing/get_data_part1.c \
		 Parssing/get_data_part2.c \
		 Draw/drawing.c \
		 Dowing/camera.c \
		 main.c \
		 math_operations.c rendring.c sphere.c \
		 cylinder.c

OBJES := ${FILES:.c=.o}

CC := cc -g3

LIBFT := libft/libft

CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address -g3

FRAMWORK = -lmlx -framework OpenGL -framework AppKit

RM := /bin/rm -rf

#colors 

YELLOW = \033[1;93m
PURPLE = \033[1;95m
GREEN = \033[1;92m
WHITE = \033[1;97m
RED = \033[1;91m

all : ${NAME}

${NAME} : ${OBJES} ${LIBFT}
	@ ${CC} ${CFLAGS} ${LIBFT} ${FRAMWORK} $^ -o $@
	@ echo "       ${YELLOW}}}}.....${GREEN}!Compile :-> ${NAME} <-: Successe!${YELLOW}.....{{{${WHITE}"

%.o : %.c
	@ echo "${BLUE}Generating Minishell objects... ${PURPLE}" $@ "${WHITE}"
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@ 

clean : 
	@ ${RM} ${OBJES}
	@ echo "${YELLOW}-> ${PURPLE}Delete the object files.....${WHITE}"

fclean : clean
	@ ${RM} ${NAME}
	@ echo "${YELLOW}-> ${RED}fclean : Deleting executable done.${WHITE}\n"

re : fclean all

do : all clean

.PHONY : all clean fclean re
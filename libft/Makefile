# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 01:39:45 by mait-jao          #+#    #+#              #
#    Updated: 2022/12/08 16:15:25 by mait-jao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft

FILES =	ft_atoi.c\
		ft_atod.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_arraylen.c\
		ft_itoa.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_putchar_fd.c\
		ft_free_array.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_split.c\
		ft_strchr.c\
		ft_strdup.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_str_begin_to_fin.c\
		ft_strjoin_free_s1.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strmapi.c\
		ft_strcmp.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_tolower.c\
		ft_toupper.c \
		ft_swap_double.c

BONUS = ft_lstnew_bonus.c\
		ft_lstadd_front_bonus.c\
		ft_lstsize_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstadd_back_bonus.c\
		ft_lstdelone_bonus.c\
		ft_lstclear_bonus.c\
		ft_lstiter_bonus.c\
		ft_lstmap_bonus.c

#colors 

YELLOW = \033[1;93m
PURPLE = \033[1;95m
GREEN = \033[1;92m
WHITE = \033[1;97m
RED = \033[1;91m

OBJECTS = ${FILES:.c=.o}

OBJS_BONUS = ${BONUS:.c=.o}

CC = cc -g3

CFLAGS = -Wall -Wextra -Werror

all : ${NAME}

${NAME}: ${OBJECTS}
	@ ar -rc ${NAME} ${OBJECTS}
	@ echo "       ${YELLOW}}}}.....${GREEN}!Create :-> ${NAME} <-: Successe!${YELLOW}.....{{{${WHITE}\n"

bonus: ${OBJECTS} ${OBJS_BONUS}
	@ ar -rc ${NAME} ${OBJECTS} ${OBJS_BONUS}
	
%.o : %.c
	@ echo "${BLUE}Generating Minishell objects... ${PURPLE}" $@ "${WHITE}"
	@ ${CC} ${CFLAGS} -c $< -o $@

clean :
	@ echo "${YELLOW}-> ${PURPLE}Delete the object files.....${WHITE}"
	@rm -f ${OBJECTS} ${OBJS_BONUS}

fclean : clean
	@ echo "${YELLOW}-> ${RED}fclean : Deleting executable done.${WHITE}\n"
	@ rm -f ${NAME} 

re : fclean all

do : all clean
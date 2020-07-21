# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: limartin <limartin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/21 21:07:36 by limartin      #+#    #+#                  #
#    Updated: 2020/07/21 22:37:13 by limartin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC_PATH = ./srcs/

INCL_PATH = ./srcs/

CC = gcc

FLAGS = -Wall -Wextra -Werror

SRCS	= $(SRC_PATH)ft_cub3dmain.c \
		$(SRC_PATH)ft_error_checker.c \
		$(SRC_PATH)ft_parser_part1.c \
		$(SRC_PATH)ft_parser_part2.c \
		$(SRC_PATH)ft_map.c \



# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: limartin <limartin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/29 18:20:12 by limartin          #+#    #+#              #
#    Updated: 2019/11/28 03:30:39 by limartin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_PATH = ./

INCL_PATH = ./

CC = gcc

FLAGS = -Wall -Wextra -Werror

SRC		= $(SRC_PATH)ft_memset.c \
		$(SRC_PATH)ft_bzero.c \
		$(SRC_PATH)ft_memcpy.c \
		$(SRC_PATH)ft_memccpy.c \
		$(SRC_PATH)ft_memmove.c \
		$(SRC_PATH)ft_memchr.c \
		$(SRC_PATH)ft_memcmp.c \
		$(SRC_PATH)ft_strlen.c \
		$(SRC_PATH)ft_isalpha.c \
		$(SRC_PATH)ft_isdigit.c \
		$(SRC_PATH)ft_isalnum.c \
		$(SRC_PATH)ft_isascii.c \
		$(SRC_PATH)ft_isprint.c \
		$(SRC_PATH)ft_toupper.c \
		$(SRC_PATH)ft_tolower.c \
		$(SRC_PATH)ft_strchr.c \
		$(SRC_PATH)ft_strrchr.c \
		$(SRC_PATH)ft_strncmp.c \
		$(SRC_PATH)ft_strlcpy.c \
		$(SRC_PATH)ft_strlcat.c \
		$(SRC_PATH)ft_strdup.c \
		$(SRC_PATH)ft_strnstr.c \
		$(SRC_PATH)ft_atoi.c \
		$(SRC_PATH)ft_calloc.c \
		$(SRC_PATH)ft_substr.c \
		$(SRC_PATH)ft_strjoin.c \
		$(SRC_PATH)ft_strtrim.c \
		$(SRC_PATH)ft_split.c \
		$(SRC_PATH)ft_itoa.c \
		$(SRC_PATH)ft_strmapi.c \
		$(SRC_PATH)ft_putchar_fd.c \
		$(SRC_PATH)ft_putstr_fd.c \
		$(SRC_PATH)ft_putendl_fd.c \
		$(SRC_PATH)ft_putnbr_fd.c

SRC_B	= $(SRC_PATH)ft_lstnew_bonus.c \
		$(SRC_PATH)ft_lstadd_front_bonus.c \
		$(SRC_PATH)ft_lstsize_bonus.c \
		$(SRC_PATH)ft_lstlast_bonus.c \
		$(SRC_PATH)ft_lstadd_back_bonus.c \
		$(SRC_PATH)ft_lstdelone_bonus.c \
		$(SRC_PATH)ft_lstclear_bonus.c \
		$(SRC_PATH)ft_lstiter_bonus.c \
		$(SRC_PATH)ft_lstmap_bonus.c

ADS		= #Additional functions go here

#Temporary files
SRCTEMP = ${SRC:%.c=%.c~}

SRCTEMB = ${SRC_B:%.c=%.c~}

ADSTEMP = ${ADS:%.c=%.c~}

#Object files
OBJ := ${SRC:%.c=%.o}

BOBJ := ${SRC_B:%.c=%.o}

ADSOBS	= ${ADS:%.c=%.o}

#Avoid relinking
ifdef WITH_BONUS
COMPILE_OBJECTS = $(OBJ) $(BOBJ)
else
COMPILE_OBJECTS = $(OBJ)
endif

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $< -I $(INCL_PATH)

$(NAME): $(COMPILE_OBJECTS)
	ar rc $(NAME) $(COMPILE_OBJECTS)

bonus:
	@ $(MAKE) WITH_BONUS=1 all

adds: $(OBJ) $(BOBJ) $(ADSOBS)
	ar rc $(NAME) $(OBJ) $(ADSOBS) $(BOBJ)

clean:
	rm -f $(OBJ) $(BOBJ) $(ADSOBS) $(SRCTEMP) $(SRCTEMB) $(ADSTEMP) \
	.DS_Store $(SRC_PATH).DS_Store $(INCL_PATH).DS_Store Makefile~ \
	test libft.h~ *.c#

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


-fsanitize=address -g
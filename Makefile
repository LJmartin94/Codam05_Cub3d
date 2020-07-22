# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: limartin <limartin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/21 21:07:36 by limartin      #+#    #+#                  #
#    Updated: 2020/07/22 21:54:21 by lindsay       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC_PATH = ./srcs/

INCL_PATH = ./srcs/

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

HEADER_FILES = $(INCL_PATH)ft_cub3d.h

SRC		= $(SRC_PATH)ft_cub3dmain.c \
		$(SRC_PATH)ft_error_checker.c \
		$(SRC_PATH)ft_parser_part1.c \
		$(SRC_PATH)ft_parser_part2.c \
		$(SRC_PATH)ft_map.c \
		$(SRC_PATH)ft_quit.c \
		$(SRC_PATH)get_next_line.c \
		$(SRC_PATH)utils_part1.c

SRC_B	= #BONUS .c FILES LISTED HERE

#Object files
OBJ := ${SRC:%.c=%.o}

BOBJ := ${SRC_B:%.c=%.o}

#Avoid relinking bonus
ifdef WITH_BONUS
COMPILE_OBJECTS = $(OBJ) $(BOBJ)
else
COMPILE_OBJECTS = $(OBJ)
endif

#Specify OS for MLX (Mac default)
ifdef FOR_LINUX
INCLUDE_MLX_HEADERS = -I/usr/include -Imlx_linux
LINK_LIBRARY = -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
else 
INCLUDE_MLX_HEADERS = -Imlx
LINK_LIBRARY = -Lmlx -lmlx -framework OpenGL -framework AppKit
endif

all: $(NAME)

$(NAME): $(COMPILE_OBJECTS)
	$(CC) -o $(NAME) $(COMPILE_OBJECTS) $(LINK_LIBRARY)

%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCL_PATH) $(INCLUDE_MLX_HEADERS) -O3

linux:
	@ $(MAKE) FOR_LINUX=1 all

bonus:
	@ $(MAKE) WITH_BONUS=1 all

clean:
	rm -f $(OBJ) $(BOBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

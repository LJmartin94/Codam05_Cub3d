# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: limartin <limartin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/21 21:07:36 by limartin      #+#    #+#                  #
#    Updated: 2020/07/23 01:51:27 by lindsay       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC_PATH = ./srcs/

INCL_PATH = ./srcs/

CC = gcc

CFLAGS = -Wall -Wextra -Werror 
#-fsanitize=address -g

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
INCLUDE_MLX_HEADERS = -I/usr/include
LINK_LIBRARY = -L/usr/lib -lXext -lX11 -lm -lz
MLX_DIR = mlx
#MLX_DIR = mlx_linux
#MLX_LIB = libmlx.dylib
else 
INCLUDE_MLX_HEADERS = -I. 
LINK_LIBRARY = -framework OpenGL -framework AppKit
MLX_DIR = mlx
#MLX_LIB = libmlx.a
endif

ifdef LIB_NAME
MLX_LIB = libmlx.dylib
else
MLX_LIB = libmlx.a
endif

all: $(NAME)

$(NAME): $(COMPILE_OBJECTS)
	$(CC) -o $(NAME) $(COMPILE_OBJECTS) -L$(MLX_DIR) -l$(MLX_DIR) -I$(MLX_DIR) $(LINK_LIBRARY)

%.o: %.c $(HEADER_FILES) $(MLX_LIB)
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCL_PATH) $(INCLUDE_MLX_HEADERS) -I$(MLX_DIR) -O3

$(MLX_LIB):
	make -C ./$(MLX_DIR)
	cp ./$(MLX_DIR)/$(MLX_LIB) $(MLX_LIB)
#both of these need to be silenced

bonus:
	@ $(MAKE) WITH_BONUS=1 all

linux:
	$(MAKE) FOR_LINUX=1 all
#silence this one too

opengl:
	rm -rf mlx
	mkdir mlx
	cp -r ./opengl/* mlx
	$(MAKE) linux

mms:
	rm -rf mlx
	mkdir mlx
	cp -r ./mms/* mlx
	$(MAKE) LIB_NAME=1 linux 

clean:
	@make clean -C ./mlx
	#@make clean -C ./mlx_linux
	rm -f $(OBJ) $(BOBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re opengl mms

# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: limartin <limartin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/21 21:07:36 by limartin      #+#    #+#                  #
#    Updated: 2020/10/19 13:46:57 by limartin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC_PATH = ./srcs/

INCL_PATH = ./srcs/

CC = gcc

CFLAGS = -Wall -Wextra -Werror -O3

HEADER_FILES = $(INCL_PATH)ft_cub3d.h

SRC		= $(SRC_PATH)ft_cub3dmain.c \
		$(SRC_PATH)ft_bmp.c \
		$(SRC_PATH)ft_constructors.c \
		$(SRC_PATH)ft_error_checker.c \
		$(SRC_PATH)ft_parser_part1.c \
		$(SRC_PATH)ft_parser_part2.c \
		$(SRC_PATH)ft_map.c \
		$(SRC_PATH)ft_floodfill.c \
		$(SRC_PATH)ft_window.c \
		$(SRC_PATH)ft_raycaster.c \
		$(SRC_PATH)ft_colourwixel.c \
		$(SRC_PATH)ft_sprites_part1.c \
		$(SRC_PATH)ft_sprites_part2.c \
		$(SRC_PATH)ft_keyhook.c \
		$(SRC_PATH)ft_movement.c \
		$(SRC_PATH)ft_mlx.c \
		$(SRC_PATH)ft_quit.c \
		$(SRC_PATH)get_next_line.c \
		$(SRC_PATH)utils_part1.c

#Object files
OBJ := ${SRC:%.c=%.o}

#Avoid relinking bonus
ifdef WITH_BONUS
COMPILE_OBJECTS = $(OBJ)
else
COMPILE_OBJECTS = $(OBJ)
endif

#Specify OS for MLX (Mac default)
ifdef FOR_LINUX
MLX_DIR = mlx_linux
MLX_LIB = libmlx.a
INCLUDE_MLX_HEADERS = /usr/include
LINK_LIBRARY = -L/usr/lib -lXext -lX11 -lm -lz
OS_FLAG = LINUX=1
endif

ifndef FOR_LINUX
MLX_DIR = mlx
MLX_LIB = libmlx.dylib
INCLUDE_MLX_HEADERS = .
LINK_LIBRARY = -framework OpenGL -framework AppKit
OS_FLAG = MAC=1
endif

all: $(NAME)

$(NAME): $(COMPILE_OBJECTS)
	$(CC) -o $(NAME) $(COMPILE_OBJECTS) -L$(MLX_DIR) -lmlx $(LINK_LIBRARY) \
	$(CFLAGS) -D $(OS_FLAG)

%.o: %.c $(HEADER_FILES) $(MLX_LIB)
	$(CC) -o $@ -c $< $(CFLAGS) -O3 -I$(INCLUDE_MLX_HEADERS) -I./$(MLX_DIR) \
	-I $(INCL_PATH) -D $(OS_FLAG)

$(MLX_LIB):
	@make -C ./$(MLX_DIR)
	@cp ./$(MLX_DIR)/$(MLX_LIB) $(MLX_LIB)

bonus:
	@ $(MAKE) WITH_BONUS=1

linux:
	@ $(MAKE) FOR_LINUX=1 all

clean:
	@make clean -C ./mlx
	@make clean -C ./mlx_linux
	@rm -f ./mlx_linux/Makefile.gen
	rm -f $(OBJ)
	rm -f libmlx.a
	rm -f snapshot.bmp

fclean: clean
	rm -f $(NAME)
	rm -f libmlx.dylib

re: fclean all

linuxre: fclean linux

.PHONY: all bonus linux linuxre clean fclean re

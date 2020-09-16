# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: limartin <limartin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/21 21:07:36 by limartin      #+#    #+#                  #
#    Updated: 2020/09/16 14:41:20 by lindsay       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC_PATH = ./srcs/

INCL_PATH = ./srcs/

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g 
#-fno-omit-frame-pointer

HEADER_FILES = $(INCL_PATH)ft_cub3d.h

SRC		= $(SRC_PATH)ft_cub3dmain.c \
		$(SRC_PATH)ft_constructors.c \
		$(SRC_PATH)ft_error_checker.c \
		$(SRC_PATH)ft_parser_part1.c \
		$(SRC_PATH)ft_parser_part2.c \
		$(SRC_PATH)ft_map.c \
		$(SRC_PATH)ft_window.c \
		$(SRC_PATH)ft_raycaster.c \
		$(SRC_PATH)ft_colourwixel.c \
		$(SRC_PATH)ft_keyhook.c \
		$(SRC_PATH)ft_movement.c \
		$(SRC_PATH)ft_mlx.c \
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
MLX_DIR = mlx_linux
MLX_LIB = libmlx.a
INCLUDE_MLX_HEADERS = /usr/include
LINK_LIBRARY = -L/usr/lib -lXext -lX11 -lm -lz
OS_FLAG = LINUX=1
#LINK_LIBRARY = -L/usr/lib -lXext -lX11 -lm -lz  -I./$(MLX_DIR) -lbsd
else 
MLX_DIR = mlx
MLX_LIB = libmlx.dylib
INCLUDE_MLX_HEADERS = . 
LINK_LIBRARY = -framework OpenGL -framework AppKit
OS_FLAG = LINUX=0
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
	@ $(MAKE) WITH_BONUS=1 all

linux:
	@ $(MAKE) FOR_LINUX=1 all

clean:
	@make clean -C ./mlx
	@make clean -C ./mlx_linux
	@rm -f ./mlx_linux/Makefile.gen
	rm -f $(OBJ) $(BOBJ)
	rm -f libmlx.dylib
	rm -f libmlx.a

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus linux clean fclean re

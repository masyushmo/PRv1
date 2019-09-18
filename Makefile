#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/17 17:51:05 by mmasyush          #+#    #+#              #
#    Updated: 2019/09/17 18:14:17 by mmasyush         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc

FLAGS = -Wall -Wextra -O3 -flto -Ofast -pipe #-g -fsanitize=address #-Werror

NAME = rtv

SRC = main.c math.c parser.c print.c raytrace.c \

INC = includes/

SRC_DIR = ./src/

OBJ_DIR = ./obj/

INC_DIR = ./includes/

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

FT = ./libft/

FT_LIB = $(addprefix $(FT), libft.a)

LINKS := -L$(FT) -l ft -lm -lSDL2
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
		LINKS += -lSDL2
endif

SDL_pATH = ./framework

INCLUDES := -I$(FT) -I$(INC_DIR)

ifeq ($(UNAME_S), Darwin)
INCLUDES += -I./frameworks/SDL2.framework/Headers \
				-I./frameworks/SDL2_image.framework/Headers \
				-F./frameworks
endif

FRAMEWORKS :=
ifeq ($(UNAME_S), Darwin)
FRAMEWORKS += -F./frameworks \
							-rpath ./frameworks \
							-framework AppKit -framework OpenGL \
							-framework SDL2 -framework SDL2_image
endif

all: obj_dir $(FT_LIB) $(NAME)
		@echo "\033[22;32mCOMPILATED! \033[22;35m^_^"
obj_dir:
		@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
		$(CC) $(FLAGS) $(FRAMEWORKS) $(OBJ) -o $(NAME) $(LINKS)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(INC)
		$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(FT_LIB):
		@make -C $(FT)

clean: clean
		@rm -rf $(OBJ_DIR)
		@make -C $(FT) clean

fclean: clean
		@rm -f $(NAME)
		@make -C $(FT) fclean

re: fclean all

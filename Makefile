INC=/usr/include
##
## Makefile for MiniLibX in /home/boulon/work/c/raytraceur/minilibx
## 
## Made by Olivier Crouzet
## Login   <ol@epitech.net>
## 
## Started on  Tue Oct  5 15:56:43 2004 Olivier Crouzet
## Last update Tue May 15 15:41:20 2007 Olivier Crouzet
##

## Please use configure script


VFLAGS		= --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt
UNAME		= $(shell uname)
CC			= gcc
ifeq ($(UNAME),FreeBSD)
	CC		= clang
endif

NAME		= test
LIBFT_DIR	= libft
LIBFTA		= libft/lib/libft.a

SRC			= test.c

OBJ_DIR 	= obj
OBJ	= $(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))
#CFLAGS		= -Wall -Wextra -Werror -g3 -O3 -I$(INC)
CFLAGS		= -g3 -O3 -I$(INC)

all: $(NAME)
	$(MAKE) -C mlx_linux

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFTA)
	$(CC) $(OBJ) $(LIBFTA) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(LIBFTA):
	$(MAKE) -C $(LIBFT_DIR)

check: all
	@test/run_tests.sh

show:
	@printf "NAME  		: $(NAME)\n"
	@printf "NAME_UNAME	: $(NAME_UNAME)\n"
	@printf "CC		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "SRC		:\n	$(SRC)\n"
	@printf "OBJ		:\n	$(OBJ)\n"

clean:
	rm -rf $(OBJ_DIR)/ $(NAME)

valgrind: $(NAME)
	valgrind VFLAGS ./$(NAME)

.PHONY: all check show clean

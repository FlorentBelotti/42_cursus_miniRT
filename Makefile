# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/17 14:17:45 by fbelotti          #+#    #+#              #
#    Updated: 2024/07/24 14:08:40 by fbelotti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
AUTHOR = Florent Belotti
AUTHOR2 = Jean-Baptiste Durand

CC = gcc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./Includes -I./Includes/42_cursus_libft -I./Includes/minilibx-linux -I/opt/homebrew/Cellar/readline/8.2.10/include
MLXDIR = ./Includes/minilibx-linux
MLXFLAGS = -L$(MLXDIR) -lmlx -L/usr/X11R6/lib -lX11 -lXext
LDFLAGS = -L./Includes/42_cursus_libft -lft -L/opt/homebrew/Cellar/readline/8.2.10/lib -lreadline -lhistory

SRCDIR = src
OBJDIR = obj

SRC = $(shell find $(SRCDIR) -name \*.c -type f -print)
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

DEPS = $(OBJ:.o=.d)

all: announce intro libft mlx $(NAME)

announce:
	@echo "\n===================================\n"
	@echo "Author: $(AUTHOR)"
	@echo "Author: $(AUTHOR2)\n"
	@echo "Project: $(NAME)\n"
	@echo "===================================\n"

intro:
	@echo "Starting the build process..."

$(NAME): $(OBJ)
	@echo "\nminiRT: Creating library..."
	@$(MAKE) -C ./Includes/42_cursus_libft > /dev/null
	@$(MAKE) -C $(MLXDIR) > /dev/null
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(MLXFLAGS) -lm -o $@
	@echo "miniRT: Executable $@ created."

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@echo "miniRT: Src: compiling file $@"
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

libft:
	@$(MAKE) -C ./Includes/42_cursus_libft > /dev/null

mlx:
	@$(MAKE) -C $(MLXDIR) > /dev/null

-include $(DEPS)

clean:
	@$(RM) $(OBJ)
	@$(MAKE) -C ./Includes/42_cursus_libft clean > /dev/null
	@$(MAKE) -C $(MLXDIR) clean > /dev/null
	@rm -rf $(OBJDIR)
	@echo "miniRT: Cleaned."

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C ./Includes/42_cursus_libft fclean > /dev/null
	@rm -rf $(OBJDIR)
	@echo "miniRT: Fully cleaned."

re: fclean all

debug: CFLAGS += $(DEBUG_FLAGS)
debug: re

.PHONY: all clean fclean re libft mlx announce intro

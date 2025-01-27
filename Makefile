# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yousong <yousong@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/03 02:40:33 by yousong           #+#    #+#              #
#    Updated: 2025/01/26 09:18:12 by yousong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c

LIBS_DIR = libs/
LIBFT_DIR = $(LIBS_DIR)libft/
LIBFT = $(LIBFT_DIR)libft.a

GNL_DIR = libs/get_next_line/
GNL_SRC = $(GNL_DIR)get_next_line.c \
				$(GNL_DIR)get_next_line_utils.c

OBJS = $(SRCS:%.c=%.o)
GNL_OBJS = $(GNL_SRC:%.c=%.o)

CC = gcc

DEBUG_FLAGS = -g3 -gdwarf-3 -fsanitize=address -fsanitize=undefined
ifdef DEBUG
	CFLAGS = -Wall -Wextra -Werror $(DEBUG_FLAGS)
else
	CFLAGS = -Wall -Wextra -Werror
endif

INCLUDES = -I$(LIBFT_DIR) -I$(GNL_DIR)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT) $(GNL_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(GNL_OBJS) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS) $(GNL_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
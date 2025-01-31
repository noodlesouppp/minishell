# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yousong <yousong@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/03 02:40:33 by yousong           #+#    #+#              #
#    Updated: 2025/01/31 14:48:23 by yousong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

LIBS_DIR = libs/
LIBFT_DIR = $(LIBS_DIR)libft/
LIBFT = $(LIBFT_DIR)libft.a

GNL_DIR = libs/get_next_line/
GNL_SRC = $(GNL_DIR)get_next_line.c \
				$(GNL_DIR)get_next_line_utils.c

PARSE_DIR = parse

SRCS = $(PARSE_DIR)/parser.c \
       $(PARSE_DIR)/parser_util.c \
       $(PARSE_DIR)/space_token.c \
       $(PARSE_DIR)/cmd_token.c \
       $(PARSE_DIR)/parse_error.c \
	   $(PARSE_DIR)/parse_path.c \
	   $(PARSE_DIR)/cmd_init.c \

OBJS = $(SRCS:.c=.o)
GNL_OBJS = $(GNL_SRC:%.c=%.o)
MAIN = main.c
MAIN_OBJ = $(MAIN:.c=.o)

DEBUG_FLAGS = -g3 -gdwarf-3 -fsanitize=address -fsanitize=undefined
ifdef DEBUG
	CFLAGS = -Wall -Wextra -Werror $(DEBUG_FLAGS)
else
	CFLAGS = -Wall -Wextra -Werror -Iincludes -I/usr/include/readline
endif

INCLUDES = -I$(LIBFT_DIR) -I$(GNL_DIR)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(MAIN_OBJ) $(LIBFT) $(GNL_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MAIN_OBJ) $(LIBFT) $(GNL_OBJS) -o $(NAME) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS) $(MAIN_OBJ) $(GNL_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
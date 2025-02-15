# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yousong <yousong@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/03 02:40:33 by yousong           #+#    #+#              #
#    Updated: 2025/02/15 07:48:03 by yousong          ###   ########.fr        #
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
UTILS_DIR = utils
ENV_DIR = env
SIGNAL_DIR = signal
EXEC_DIR = exec
BUILTINS_DIR = builtins

SRCS = $(PARSE_DIR)/parser.c \
       $(PARSE_DIR)/parser_util.c \
       $(PARSE_DIR)/space_token.c \
       $(PARSE_DIR)/cmd_token.c \
       $(PARSE_DIR)/parse_error.c \
	   $(PARSE_DIR)/parse_path.c \
	   $(PARSE_DIR)/cmd_init.c \
	   $(PARSE_DIR)/token_util.c \
	   $(UTILS_DIR)/utils.c \
	   $(ENV_DIR)/env_util.c \
	   $(ENV_DIR)/env.c \
	   $(SIGNAL_DIR)/signal_util.c \
	   $(SIGNAL_DIR)/signals.c \
	   $(EXEC_DIR)/process.c \
	   $(EXEC_DIR)/command.c \
	   $(EXEC_DIR)/here_doc.c \
	   $(EXEC_DIR)/set_fd.c \
	   $(EXEC_DIR)/redirect.c \
	   $(BUILTINS_DIR)/cd.c \
	   $(BUILTINS_DIR)/controller.c \
	   $(BUILTINS_DIR)/echo.c \
	   $(BUILTINS_DIR)/env.c \
	   $(BUILTINS_DIR)/exit.c \
	   $(BUILTINS_DIR)/export.c \
	   $(BUILTINS_DIR)/pwd.c \
	   $(BUILTINS_DIR)/unset.c

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
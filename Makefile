NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I.
LIBS = -lreadline

SRCS = \
		main.c executing/signals.c executing/pipeline.c executing/pipelinestatus.c executing/singlecmd.c \
		executing/singlecmd_builtins.c executing/singlecmd_child.c executing/pipehelpers.c \
		executing/execexternal.c executing/path.c executing/helpers.c executing/helpers2.c executing/cd.c \
		executing/cd_env.c executing/echo.c executing/env.c executing/exit.c executing/export.c \
		executing/unset.c executing/pwd.c executing/ft_split.c executing/utils.c executing/utils2.c\
		executing/export_utils.c executing/export_set.c parsing/lexer/expand_utils.c \
		parsing/lexer/expand.c parsing/lexer/expand_quotes.c parsing/lexer/lexer.c \
		parsing/lexer/lexer_utils.c parsing/lexer/operators.c parsing/lexer/word.c \
		parsing/parsing.c parsing/parsing_fill.c parsing/parsing_heredoc.c parsing/parsing_redirectors.c \
		parsing/parsing_utils.c parsing/syntax_validator.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

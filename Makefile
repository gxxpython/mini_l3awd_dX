NAME = minishell

SRC =	errors.c \
		pasring/main.c\
		pasring/parse.c\
		pasring/fill_shell.c\
		pasring/parse_qoutes.c\
		pasring/node_utils.c\
		pasring/node_utils_2.c\
		pasring/parsing_tool.c\
		pasring/parsing_tool_2.c\
		pasring/redirection.c\
		lexer/lexer_check.c\
		lexer/lexer_init.c \
		lexer/lexer_utils.c\
		minishell.c \
		pwd.c\
		cd.c\
		linked.c\
		unset.c\
		export.c\
		cmd_env.c\
		pipex_utils.c\
		cmd_excution.c\
		excution_util.c\
		her_doc.c\


RM		= rm -rf

CC		= cc

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g

OBJ	= ${SRC:.c=.o}

all	: ${NAME}

${NAME} : ${OBJ}
		make -C libft/
	${CC} ${CFLAGS} ${OBJ} libft/libft.a -o ${NAME} -lreadline

clean :
	make clean -C libft
	$(RM) $(OBJ) 
	
fclean	:	clean
		make fclean -C  libft
		$(RM) $(NAME)

re	:	fclean all
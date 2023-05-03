/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:31:44 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/03 11:50:20 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <errno.h>
# include <dirent.h>
# include <string.h>
# include <limits.h>
int	glob_exit;

enum t_token
{
	WORD = -1,
	WHITE_SPACE = 0,
	QOUTE = 1,
	DOUBLE_QUOTE = 2,
	ENV = 3,
	PIPE_LINE = 4,
	IN_RED = 5,
	OUT_RED = 6,
	MORE_RED = 7,
	LESS_RED = 8,
	LIMIT = 10,
	FILE_NAME = 11,
	TEMP = 12,
};

enum e_redirect{
	HEREDOC=7, /// here_doc
	LESS=8,  // infile
	GREAT=9,  // oufile
	EXPAND=10  // oufile expand
};
enum t_state
{
	IN_DQUOTE = 2,
	IN_QUOTE = 1,
	GENERAL = 0,
};

typedef struct s_elem		t_elem;
typedef struct s_redir_elem	t_redir_elem;
typedef union u_union		t_union;
typedef struct s_ast_node	t_ast_node;
typedef struct s_redir_list	t_redir_list;

/*
	@desc: a linked list element used to store
	a single token returned from the laxer/tokenizer
	(fshek).
*/
typedef struct s_elm
{
	char				*content;
	int					len;
	enum t_token		type;
	enum t_token		tmp;
	enum t_state		state;
    struct s_elm *next;
    struct s_elm *prev;
}	t_elm;
/*
	@desc: a doubly linked list to store the full command (lexer ouput).
*/
typedef struct l_list
{
	int		size;
	t_elm	*head;
	t_elm	*tail;
}	t_list;

typedef struct s_redirect
{
	int						my_redirect;
	char					*here_lim;
	int						here_doc_expand;
	char					*filename;
	struct s_redirect	*next;
}				t_redirect;

typedef struct s_data
{
	int					exit_status;

	int					pid;
	int					which;
	t_list				*lex;
	int					alloc;
	char				**env;
}	t_data;

t_data						g_data;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				here_doc;
	int				out_fd;
	int				in_fd;
	int				cheak_in;
	t_redirect		*list_of_red;
	int				in_of_next;
	int				sep;
	int				level;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_redir
{
	char			*arg;
	enum t_token	type;
	struct s_redir		*next;
}	t_redir;

////////////////////////////////////////////////////
typedef struct s_env
{
	int				cheak;
	char			*key;
	char			*value;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_val
{
	char *small;
	int fd;
}	t_val;

typedef struct s_global
{
	t_cmd	*all_cmd;
	t_env	*env_list;
}				t_global;

/* 			GENERAL STRUCT		*/
typedef struct pipe_ft
{
	char 	**args;
	t_redir	*reder;
	struct pipe_ft *next;
}cmd_pipe;

////////////////////////////////////////////////////
//////////// execution //////
void cmd_env(t_env *env,int fd);
void p_error(char *str);
t_env	*ft_lstnew_mini(char *content);
void	ft_lstadd_back_mini(t_env **lst, t_env *new);
//int	ft_strcmp(const char *str1, const char *str2);
char	*ft_strchr( const char *str, int c);
char **var_val(char *env);
void	del_node(t_env **head,char *key);
void cmd_unset(char** arg,t_env **env);
void cmd_export(t_env **env,char **arg,int fd);
void	cmd_cd(char **path,t_env **env);
char *cmd_pwd(int fd,int k);
int check_key(char *env);
void cmd_exit(char **str);
void cmd_echo(char **cmd,int fd);
char *get_env(t_env *env,char *s,char *s2);
void print_order(t_env *env, t_val *val ,t_env *ptr2 ,t_env *ptr3);
int	ft_lstsize_mini(t_cmd *lst);
//----------------------------------------
int her_doc(t_redirect *red);
void set_her_doc(t_cmd *cmd);
char	*my_path(char *cmd1, char **env);
void	free_all(char **str, char *str2);
void	check_error2(char *str);
void	ft_puterr(char *str);
void	check_error(char *str, int n);
void	set_red(t_cmd *cmd);
void cmd_excution(t_global *all, char **env);
int  cheackis_buil(char *cmd);
void exucute_builtine(t_global *all,t_cmd *cmds);
void execution_mini(t_global *all,char **env);
void handle_sig(int signum);

////////////////////////////////////////////////////


/*			PARSING FUCNTION				*/

void parse_cmd(t_elm **ptr,t_cmd **fcmd);
int				is_redir(enum t_token type);
t_ast_node		*create_cmd_node(char **args,t_redir_list *redir);
t_redirect 		*get_rednode(t_redir *ptr);
t_redir_list	*init_redir_list(t_redir_list *list);
t_redir_list 	*parse_redir(t_elm **ptr,t_redir_list *redir);
void			add_redir_tail(t_redir_list *list, t_redir *new);
t_redir			*new_redir_elem(char *arg, enum t_token type);
t_cmd 		*fix_red(t_elm **ptr,t_redir_list **redir,t_cmd **cmd);
t_redir 		*red_list(t_elm *ptr);
t_redirect 		*my_red(t_redir *red);
char			*parse_quotes(t_elm **ptr, enum t_token type);
char			*parse_quotes2(t_elm *ptr1, enum t_token type,enum t_token type2);
void			fille_cmd(t_cmd **fcmd,cmd_pipe *full_cmd);
char			**fill_arg(char **src);
int				count_args(t_elm *elem);
int	lunch_shell(char *line,t_global *all);
void parse1(t_elm *ptr,t_global *all);
/*					synatx  ERROR 			*/
t_elm	*check_unclosed_quotes(t_elm **ptr, enum t_token type);
t_elm	*skip_spaces(t_elm *ptr);
int		pipe_error(t_elm *ptr);
int		redir_error(t_elm *ptr);


/*				NODE UTILS 					*/
void		lstadd_back_red2( t_redirect  **lst,  t_redirect  *new);
cmd_pipe	*cmd_new();
t_cmd	*lstnew_cmd(cmd_pipe *cmds);
void		lstadd_back_cmd( t_cmd **lst,  t_cmd *new);
void		ft_lstadd_back1(cmd_pipe **lst, cmd_pipe *newnode);
void		lstadd_back_red( t_redir **lst,  t_redir *new);
t_redir		*lstnew_red(t_elm *ptr,int type);
t_redirect  *new_nodered(int red, char *lim ,int her_ex ,char *file);
void		lstadd_back_red2( t_redirect  **lst,  t_redirect  *new);
void		lstadd_back_red( t_redir **lst,  t_redir *new);
t_redir		*lstnew_red(t_elm *ptr,int type);
char		**fill_arg(char **src);

/* LEXER FUCNTIONS */
int 	check_operator(t_list *token,char *str,int i,enum t_state *state);
int 	env_check(t_list *token,char *str,enum t_state *state);
int		is_alpha(int c);
t_elm	*new_elem(char *content, int len, enum t_token type, enum t_state state);
int		ft_check_emp(t_list *list);
t_list 	*in_list(void);
int		is_space(char c);
void	add_link(t_list *list, t_elm *new);
int		ft_word(t_list *token, char *str, enum t_state state);
void	quotes(t_list *token, char *str, enum t_state *state, int flag);
int		is_char(char c);
int		toke_init(t_list *token, char *line, int i, enum t_state *state);
t_list	*lexer(char *line);

//// PROBELMES 


//// enpty string in quotes
//check pipe


#endif

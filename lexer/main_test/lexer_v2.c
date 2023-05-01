#include "../../minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\v'
		|| c == '\r' || c == '\f' || c == '\n');
}

int	is_char(char c)
{
	return (c == '\'' || c == '\"' || c == '<' || c == '>' || c == '|'
		|| c == '$' || is_space(c) || c == '\n' || c == '\0');
}

t_list *in_list(void)
{
    t_list *list = malloc(sizeof(t_list));
    if (list == NULL)
	{
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

t_elm *new_elem(char *content, int len, enum t_token type, enum t_state state)
{
    t_elm *elm = malloc(sizeof(t_elm));
    if (!elm)
    {
        return NULL;
    }
    char *content_copy = malloc(len + 1);
    if (!content_copy)
    {
        free(elm);
        return NULL;
    }
    ft_memcpy(content_copy, content, len);
    content_copy[len] = '\0';
    elm->content = content_copy;
    elm->len = len;
    elm->type = type;
    elm->state = state;
    elm->next = NULL;
    elm->prev = NULL;
    return (elm);
}
void add_link(t_list *list,t_elm *new)
{
    if (ft_check_emp(list))
        list->head = new;
    else
    {
        list->tail->next = new;
        new->prev = list->tail;
    }
    list->tail = new;
    list->size++;
}

int ft_word(t_list *token,char *str,enum t_state state)
{
    int i;

    i = 0;
    while (!is_char(str[i]))
        i++; 
    add_link(token, new_elem(str, i, WORD, state));
	return (i);
}

int ft_check_emp(t_list *list)
{
    if (list->head == NULL)
        return 1;
    else
        return 0;
}

void    quotes(t_list *tokens, char *str, enum t_state *state, int flag)
{
	enum t_state    e_state;
	enum t_token    e_type;

	if (flag == 1)
	{
		e_state = IN_QUOTE;
		e_type = QOUTE;
	}
    else
	{
		e_state = IN_DQUOTE;
		e_type = DOUBLE_QUOTE;
	}
	if (*state == GENERAL)
	{
		add_link(tokens, new_elem(str, 1, e_type, *state));
		*state = e_state;
	}
	else if (*state == e_state)
	{	
		*state = GENERAL;
		add_link(tokens, new_elem(str, 1, e_type, *state));
	}
	else
        add_link(tokens, new_elem(str, 1, e_type, *state));
}

int	is_alpha(int c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int env_check(t_list *token,char *str,enum t_state *state)
{
    int i = 1;
    while (is_alpha(str[i]) && str[i] != '\n' && str[i] != '\0')
        i++;
    add_link(token,new_elem(str,i,ENV,*state));
    return i;
}

int check_operator(t_list *token,char *str,int i,enum t_state *state)
{
    int j;

    j = i;
    if (str[i] == '<')
    {
        if (str[i + 1] == '<')
            add_link(token,new_elem(str + (i++), 2,LESS_RED, *state));
        else if (str[i] == '<')
            add_link(token,new_elem(str + (i++), 1,IN_RED, *state));
    }
    else if (str[i] == '>')
    {
        if (str[i + 1] == '>')
            add_link(token,new_elem(str + (i++), 2,MORE_RED, *state));
        else
            add_link(token,new_elem(str + (i++), 1,OUT_RED, *state));
        i++;
    }
    return (i - j);
}

// int	file_name(t_list *token,char *line,int i,	enum t_state state)
// {
// 	while (!is_space(line[i]))
// 	{
// 		i++;
// 	}
// 	add_link(token, new_elem(line, i, FILENAME, state));
// 	return (i);
// }

int	toke_init(t_list *token,char *line,int i,enum t_state *state)
{
	if (line[i] == '<' || line[i] == '>')
        i+=check_operator(token, line, i, state);
    else if (!is_char(line[i]))
		i += ft_word(token,line + i,*state);
	else if (line[i] == '\'')
		quotes(token, line + (i++), state, 1);
	else if (line[i] == '\"')
		quotes(token, line + (i++), state, 2);
	else if (line[i] == '|')
		add_link(token, new_elem(line + (i++), 1, PIPE_LINE, *state));
	else if (line[i] == ' ')
	{
		add_link(token, new_elem(line + (i++), 1, WHITE_SPACE, *state));
	}
	else if (line[i] == '$')
        i+=env_check(token, line ,state);
    return (i);
}

t_list *lexer(char *line)
{
	int i;
	t_list *token;
	enum t_state state;

	i = 0;
	state = GENERAL;
	token = in_list(); // Pass any required arguments here
	if (token)
	{
		while (line[i])
		{
			i = toke_init(token,line,i,&state);
		}
	}
	return (token);
}

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void print_tokens(t_list *token)
{
    const char *token_names[] = {
    "WORD",
    "WHITE_SPACE",
    "QOUTE",
    "DOUBLE_QUOTE",
    "ENV",
    "PIPE_LINE",
	"IN_RED",
	"OUT_RED",
	"MORE_RED",
	"LESS_RED",
    "LIMITE_DOC",
	"FILENAME"};
    const char *token_state[] = {
	    "GENERAL",
        "IN_QUOTE",
        "IN_DQUOTE",
    };
    enum t_state state;
    t_elm *curr = token->head;
    while (curr)
    {
        printf("%d %d\n", curr->type, curr->state);
        printf("content %s | type %s | state = %s\n",curr->content,token_names[curr->type + 1],token_state[curr->state]);
        curr = curr->next;
    }
}

int main(void)
{
    char *line;
    t_list *token;

    rl_bind_key('\t', rl_complete);
    while ((line = readline("> ")))
    {
        token = lexer(line);
        if (token)
        {
            print_tokens(token);
            free(token);
        }
        free(line);
    }
    return (0);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX_INPUT_LENGTH 1024

// int main(void) {
//     char input[MAX_INPUT_LENGTH];
//     t_list *tokens;
//     	const char *token_names[] = {
//     "WORD",
//     "WHITE_SPACE",
//     "QOUTE",
//     "DOUBLE_QUOTE",
//     "ENV",
//     "PIPE_LINE",
//     "NEW_LINE",
// };
//     enum t_state state = GENERAL;

//     while (1) {
//         printf("> ");
//         if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
//             // End of file or error occurred, exit the loop
//             break;
//         }
//         // Remove newline character from input
//         input[strcspn(input, "\n")] = '\0';
//         if (strcmp(input, "exit") == 0) {
//             // User entered "exit", exit the loop
//             break;
//         }
//         tokens = lexer(input);
//         printf("Tokens:\n");
//         for (t_elm *elm = tokens->head; elm != NULL; elm = elm->next) {
//             printf("Content: %s, Length: %d, Type: %s, State: %s\n",
//                    elm->content, elm->len, token_names[elm->type + 1], token_names[elm->state + 1]);
//         }
//         // Free memory used by tokens
//         while (tokens->size > 0) {
//             t_elm *elm = tokens->head;
//             tokens->head = elm->next;
//             tokens->size--;
//             free(elm->content);
//             free(elm);
//         }
//         free(tokens);
//     }

//     return 0;
// }


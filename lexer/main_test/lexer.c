#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_INPUT_LENGTH 1024
#define MAX_TOKEN_LENGTH 64
#define MAX_TOKEN_COUNT 16

typedef enum {
    TOKEN_TYPE_NONE,
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_ARGUMENT
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;

Token *lex(const char *input) {
    Token *tokens = malloc(MAX_TOKEN_COUNT * sizeof(Token));
    if (tokens == NULL) {
        return NULL;
    }

    const char *p = input;
    int token_count = 0;

    while (*p && token_count < MAX_TOKEN_COUNT) {
        Token *token = &tokens[token_count];
        token->type = TOKEN_TYPE_NONE;
        memset(token->value, 0, MAX_TOKEN_LENGTH);

        // Skip leading whitespace
        while (*p == ' ' || *p == '\t') {
            p++;
        }

        // Check for keyword or argument
        if (*p && (*p == '_' || isalpha(*p))) {
            token->type = TOKEN_TYPE_KEYWORD;
            int i = 0;
            while (*p && (i < MAX_TOKEN_LENGTH - 1) && (*p == '_' || isalnum(*p))) {
                token->value[i++] = *p++;
            }
        } else if (*p && strchr("><|", *p)) {
            token->type = TOKEN_TYPE_OPERATOR;
            token->value[0] = *p++;
            if (*p && (*p == '>' || *p == '|')) {
                token->value[1] = *p++;
            }
        } else {
            token->type = TOKEN_TYPE_ARGUMENT;
            int i = 0;
            while (*p && (i < MAX_TOKEN_LENGTH - 1) && (*p != ' ' && *p != '\t')) {
                token->value[i++] = *p++;
            }
        }

        token_count++;
    }

    // Add terminating token
    Token *token = &tokens[token_count];
    token->type = TOKEN_TYPE_NONE;
    token->value[0] = '\0';

    return tokens;
}

#include <stdio.h>
int main() {
    char *input = "ls -l | grep foo > output.txt | $USER";
    Token *tokens = lex(input);

    int i = 0;
    while (1) {
        if (tokens[i].type == TOKEN_TYPE_NONE) {
            break;
        } else if (tokens[i].type == TOKEN_TYPE_KEYWORD) {
            printf("Keyword: %s\n", tokens[i].value);
        } else if (tokens[i].type == TOKEN_TYPE_OPERATOR) {
            printf("Operator: %s\n", tokens[i].value);
        } else if (tokens[i].type == TOKEN_TYPE_ARGUMENT) {
            printf("Argument: %s\n", tokens[i].value);
        }
        i++;
    }

    free(tokens);
    return 0;
}

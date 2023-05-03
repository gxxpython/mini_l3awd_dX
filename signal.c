
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void handle_sig(int signum) {
    if (signum == SIGINT) {
        printf("\n");
        rl_clear_history();
        rl_on_new_line();
        printf("minishell> ");
        fflush(stdout);
    }
}

int main() {
    signal(SIGINT, handle_sig);

    while (1) {
        char *input = readline("minishell> ");
        add_history(input);
        // Process input and execute commands
        free(input);
    }

    return 0;
}

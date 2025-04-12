#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

void remove_newline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

int fakeshell(void) {
    char command[256];
    char dir[256];
    char user[256];
    char host[256];

    printf("C fakeshell user: ");
    if (fgets(user, sizeof(user), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    remove_newline(user);

    printf("C fakeshell host: ");
    if (fgets(host, sizeof(host), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    remove_newline(host);

    while (true) {
        if (getcwd(dir, sizeof(dir)) == NULL) {
            perror("getcwd() error");
            strcpy(dir, "?");
        }
        
        printf("%s@%s:%s$ ", user, host, dir);
        
        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n");
            break;
        }
        
        remove_newline(command);
        
        if (strcmp(command, "exit") == 0) {
            break;
        }
        
        system(command);
    }
    
    return 0;
}

int main(void) {
    return fakeshell();
}

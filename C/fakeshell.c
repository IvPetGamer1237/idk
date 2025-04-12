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

int fakeshell(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: there is no arguments\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        system(argv[i]);
    }
    
    return 0;
}

int main(int argc, char *argv[]) {
    return fakeshell(argc, argv);
}

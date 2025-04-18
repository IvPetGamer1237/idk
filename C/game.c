#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int min;
    int max;
    bool cheat;
    bool hard;
} config;


int start(void) {
    printf("write 'q' or 'exit' for exit\n\n");
    return 0;
}
int game(config cfg) {
    if (cfg.cheat) {
        printf("Cheater!\n");
    } else {
        srand(time(0));
    }
    char in[256];
    int num = 0, scr = 0, rnd = 0;

    while(true) {
        printf("%d choose (%d-%d): ", scr, cfg.min, cfg.max);
        if (fgets(in, sizeof(in), stdin) == NULL) {
            printf("EOF\n");
            break;
        }

        in[strcspn(in, "\n")] = '\0';

        if (strcmp(in, "q") == 0 || strcmp(in, "exit") == 0) {
            printf("exit\n");
            break;
        }
        if (strcmp(in, "bugreport") == 0) {
            printf("Make sure to report any bugs to /dev/null\n");
            continue;
        }
        if (strcmp(in, "segfault") == 0) {
            printf("You found a secret!\n");
            printf("For segfault write\n\n\n"
            "int main() {\n"
            "   int *i = NULL;\n"
            "   *i = 1;\n"
            "}\n\n\n"
            "in file with the '.c' extention and compile it\n");
            break;
        }
        if (sscanf(in, "%d", &num) != 1) {
            printf("Input is not a number or 'q'\\'exit' or 'bugreport'\n");
            continue;
        }

        if (num < cfg.min || num > cfg.max) {
            printf("Value out of range!\n");
            continue;
        }

        if (cfg.cheat) {
        } else {
            rnd = rand() % (cfg.max - cfg.min + 1) + cfg.min;
        }
        if (num == rnd) {
            if (cfg.hard) {
                scr++;
                printf("Your score is %d!\n", scr);
            } else {
                printf("Game over!\n");
                scr=0;
                printf("Your score is reset!\n");
            }
        } else {
            if (cfg.hard) {
                printf("Game over!\n");
                scr=0;
                printf("Your score is reset!\n");
            } else {
                scr++;
                printf("Your score is %d!\n", scr);
            }
        }

    }
    return 0;
}

int main(int argc, char *argv[]){
    config cfg = {
        .min = 1,
        .max = 3,
        .cheat = false,
        .hard = false
    };

        for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--cheat") == 0) {
            cfg.cheat = true;
        } else if (strcmp(argv[i], "--range") == 0 && i + 2 < argc) {
            cfg.min = atoi(argv[i+1]);
            cfg.max = atoi(argv[i+2]);
            i += 2;
        } else if (strcmp(argv[i], "--hard") == 0) {
            cfg.hard = true;
        }
    }

    start();
    game(cfg);
    return 0;
}

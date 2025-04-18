#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>

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

int help(void) {
    printf("Usage:\n");
    printf("    -c, --cheat     Turn on cheat mode (disables random)\n");
    printf("    -H, --hard      Turn on hard mode (incompatible with --cheat)\n");
    printf("    -r X-Y, --range X-Y Set custom max and min number\n");
    return 0;
}

int game(config cfg) {
    if (cfg.min > cfg.max) {
        printf("bad range\n");
        return 1;
    }

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

        if (!cfg.cheat) {
            rnd = rand() % (cfg.max - cfg.min + 1) + cfg.min;
        }

        if (num == rnd) {
            if (cfg.hard) {
                scr++;
                printf("Your score is %d!\n", scr);
            } else {
                printf("Game over!\n");
                scr = 0;
                printf("Your score is reset!\n");
            }
        } else {
            if (cfg.hard) {
                printf("Game over!\n");
                scr = 0;
                printf("Your score is reset!\n");
            } else {
                scr++;
                printf("Your score is %d!\n", scr);
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    config cfg = {
        .min = 1,
        .max = 3,
        .cheat = false,
        .hard = false
    };

    int opt;
    static struct option long_options[] = {
        {"cheat", no_argument, 0, 'c'},
        {"range", required_argument, 0, 'r'},
        {"hard", no_argument, 0, 'H'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "cHr:h", long_options, NULL)) != -1) {
        switch (opt) {
            case 'c':
                cfg.cheat = true;
                break;
            case 'H':
                cfg.hard = true;
                break;
            case 'r':
                if (sscanf(optarg, "%d-%d", &cfg.min, &cfg.max) != 2) {
                    fprintf(stderr, "Invalid range format. Use X-Y\n");
                    fprintf(stderr, "Example: %s -r 1-3\n", argv[0]);
                    return 1;
                }
                break;
            case 'h':
                help();
                return 0;
            case '?':
                return 1;
            default:
                fprintf(stderr, "Unknown error\n");
                return 1;
        }
    }

    start();
    game(cfg);
    return 0;
}

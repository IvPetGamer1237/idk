#include <stdio.h>      // standard input/output
#include <stdlib.h>     // standard library (used for rand in this code)
#include <time.h>       // used for initialization RNG
#include <string.h>     // for working with strings
#include <stdbool.h>    // for boolean true/false values
#include <getopt.h>     // for parsing command line arguments

// game congig structure
typedef struct {
    int min;        // minimal range value
    int max;        // maximal range value
    bool cheat;     // cheat mode
    bool hard;      // hard mode
} config;

// start function, outputs exit instructions
int start(void) {
    printf("write 'q' or 'exit' for exit\n\n");
    return 0;
}

// help function, outputs argument list
int help(void) {
    printf("Usage:\n");
    printf("    -c, --cheat     Turn on cheat mode (disables random)\n");
    printf("    -H, --hard      Turn on hard mode (incompatible with --cheat)\n");
    printf("    -r X-Y, --range X-Y Set custom max and min number\n");
    return 0;
}

int game(config cfg) {
    if (cfg.min > cfg.max) {
        printf("bad range\n");      // range validity check
        return 1;
    }

    if (cfg.cheat) {
        printf("Cheater!\n");       // if cheater mode, then output "Cheater!"
    } else {
        srand(time(0));             // else initializing RNG 
    }

    char in[256];                   // input buffer
    // num - user input, scr - score, rnd - random number
    int num = 0, scr = 0, rnd = 0;

    while(true) {
        printf("%d choose (%d-%d): ", scr, cfg.min, cfg.max); // command prompt
        if (fgets(in, sizeof(in), stdin) == NULL) {           // ^D check
            printf("EOF\n");
            break;
        }

        in[strcspn(in, "\n")] = '\0';   // deleting newline

        // if input equals 'q' or 'exit' then exit
        if (strcmp(in, "q") == 0 || strcmp(in, "exit") == 0) { 
            printf("exit\n");
            break;
        }

        // bugreport
        if (strcmp(in, "bugreport") == 0) {
            printf("Make sure to report any bugs to /dev/null\n");
            continue;
        }

        // secret input
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

        // creating number from input, if input invalid then outputs error
        if (sscanf(in, "%d", &num) != 1) {
            printf("Input is not a number or 'q' or 'exit'\n");
            continue;
        }

        // checking number validity
        if (num < cfg.min || num > cfg.max) {
            printf("Value out of range!\n");
            continue;
        }

        // checking for cheat mode, if user not a cheater then using random
        // else not using random
        if (!cfg.cheat) {
            rnd = rand() % (cfg.max - cfg.min + 1) + cfg.min;
        }

        if (num == rnd) { // if user guess number
            if (cfg.hard) {
                // in hard mode - reward for correct answer
                scr++;
                printf("Your score is %d!\n", scr);
            } else {
                // in normal - game over
                printf("Game over!\n");
                scr = 0; // reset score
                printf("Your score is reset!\n");
            }
        } else {
            if (cfg.hard) { // if user not guess number
                // in hard mode - game over
                printf("Game over!\n");
                scr = 0; // reset score
                printf("Your score is reset!\n");
            } else {
                // in normal mode - reward
                scr++;
                printf("Your score is %d!\n", scr);
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    // default config
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

    start();    // call start function
    game(cfg);  // call game function
    return 0;
}

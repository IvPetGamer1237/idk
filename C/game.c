#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int scr=0;

int start(void) {
    srand(time(0));
    printf("write 'q' or 'exit' for exit\n\n");
    return 0;
}
int game(void) {
    srand(time(0));
    char in[11];
    int num, rnd;

    while(true) {
        printf("Choose (1-3): ");
        scanf("%10s", in);

        if (strcmp(in, "q") == 0 || strcmp(in, "exit") == 0) {
            printf("exit\n");
            break;
        };
        if (strcmp(in, "bugreport") == 0) {
            printf("Make sure to report any bugs to /dev/null\n");
            continue;
        };
        if (sscanf(in, "%d", &num) != 1) {
            printf("Input is not a number or 'q'\\'exit' or 'bugreport'\n");
            continue;
        };

        if (num < 1 || num > 3) {
            printf("Value out of range!\n");
            continue;
        };

        rnd = rand() % 3 + 1;
        
        if (num == rnd) {
            printf("Game over!\n");
            break;
        }else{
            scr++;
            printf("Your score is %d!\n", scr);
        };

    };
    return 0;
}

int main(void){
    start();
    game();
    return 0;
}

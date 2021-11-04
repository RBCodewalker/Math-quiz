#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
// #include <sys/time.h>
#include <sys/types.h>

#include "quiz.h"

int main(int argc, char **argv)
{
    printf("Answer questions with numbers in the range[1..100].\n You score points for each correctly answered question.\n If you need multiple attempts to answer a question, the\n points you score for a correct answer go down.\n\n");
    quiz_t *qn = (quiz_t *)malloc(sizeof(quiz_t) * 1);
    qn->n = 1;
    qn->score = 0;
    qn->max = 8;
    while(1)
    {
        char *buffr;
        buffr = fetch(
            "http://numbersapi.com/random/math?min=1&max=100&fragment&json");
        if(!buffr) continue;

        int x = parse(buffr, qn);
        int errorno = 0;
        if(x == -1)
        {
            //three tries before ending the program throwing an error
            errorno += 1;
            if(errorno > 3)
            {
                perror("PARSE ERROR!!!");
                exit(3);
            }
            continue;
        }
        else
        {
            errorno = 0;
            play(qn);
        }
        fflush(stdout);
    }

    printf("Thanks for playing today.\n");
    printf("Your total score is %d/%d points.\n",
                 qn->score, ((qn->n) * 8));
            
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#include "quiz.h"

extern int play(quiz_t *quiz)
{
    printf("Q%d: What is %s?\n", quiz->n, quiz->text);

    int flag = 0;
    int try;
    int x = quiz->max;

    while(x && flag == 0)
    {
        printf("%d pt> ", x);
        char buffr[50];
        if(fgets(buffr, sizeof buffr, stdin) == NULL)
        {
            int total = (quiz->n - 1) * 8;
            printf("\nYour total score is %d/%d points.\n", quiz->score, total);
            exit(7);
        }
        // try = atol(buffr);
        if ((try = atol(buffr)) == 0L)
        {
            printf("Answer not valid\n");
            continue;
        }

        if(try < quiz->number)
        {
            x /= 2;
            if(x != 0)
            {
                printf("Too small, try again.\n");
            }
            else
            {
                printf(
                    "Too small, the correct answer was %d.\n", quiz->number);
            }
            continue;
        }
        else if(try > quiz->number)
        {
            x /= 2;
            if(x != 0)
            {
                printf("Too large, try again.\n");
            }
            else
            {
                printf(
                    "Too large, the correct answer was %d.\n", quiz->number);
            }
            continue;
        }
        else
        {
            quiz->score += x;
            printf("Congratulation, your answer %d is correct.\n", try);
            flag = 1;
        }   
    }
    printf("Your total score is %d/%d points.\n",
                 quiz->score, (quiz->n * 8));
    quiz->n += 1;
    quiz->max = 8;

    return 0;
}
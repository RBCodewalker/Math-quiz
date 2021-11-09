#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <json-c/json.h>

#include "quiz.h"

extern int parse(char *json, quiz_t *quiz)
{
    char buffr[1024];

    struct json_object *parsed;
    struct json_object *text;
    struct json_object *number;

    // size_t qns;

    strcpy(buffr, json);
    parsed = json_tokener_parse(buffr);

    json_object_object_get_ex(parsed, "text", &text);
    json_object_object_get_ex(parsed, "number", &number);

    strcpy(buffr, json_object_get_string(text));
    int no = json_object_get_int(number);

    quiz->text = buffr;
    quiz->number = no;

    return 0;
}

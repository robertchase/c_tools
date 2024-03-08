#include <stdlib.h>
#include <string.h>

#include "t_tokenizer.h"
#include "c_collection/c_array.h"

struct T_TOKENIZER {
    C_ARRAY *tokens;
    char delimiter;
    char escape;
    int null_columns;
};

T_TOKENIZER *
t_tokenizer_create (char delimiter, char escape, int null_columns) {
    T_TOKENIZER *t = (T_TOKENIZER *) malloc (sizeof (T_TOKENIZER));
    if (t) {
        t -> tokens = c_array_create(sizeof(char *));
        t -> delimiter = delimiter;
        t -> escape = escape;
        t -> null_columns = null_columns;
    }

    return t;
}

void
t_tokenizer_free (T_TOKENIZER *t) {
    c_array_free (t -> tokens);
    free (t);
}

void
t_tokenizer_parse (T_TOKENIZER *t, char *string) {
    c_array_clear(t -> tokens);

    int is_escaped = 0;
    int is_between = 1; // start off "between" tokens
    for (char *cur = string; *cur; cur++) {

        if (is_between) {

            if (is_escaped) {
                c_array_append (t -> tokens, &cur); // append the pointer (hence &)
                is_between = 0;
                is_escaped = 0;

            } else if (*cur == t -> delimiter && t -> null_columns) {
                *cur = 0x00;
                c_array_append (t -> tokens, &cur);

            } else if (*cur == t -> delimiter) {
                // ignore

            } else if (*cur == t -> escape) {
                is_escaped = 1;

            } else {
                c_array_append (t -> tokens, &cur);
                is_between = 0;
            }

        } else {

            if (is_escaped) {  // if we're in this mode, we'll take anything
                is_escaped = 0;

            } else if (*cur == t -> escape) {
                // shift buffer over the escape (include trailing NULL)
                memmove(cur, cur + 1, strlen(cur + 1) + 1);
                cur --; // account for buffer shift (re-incremented in for statement)
                is_escaped = 1;

            } else if (*cur == t -> delimiter) {
                *cur = 0x00;
                is_between = 1;
            }

        }

    }
}

int
t_tokenizer_count (T_TOKENIZER *t) {
    return c_array_length (t -> tokens);
}

char *
t_tokenizer_get (T_TOKENIZER *t, int index) {
    return * (char **) c_array_get (t -> tokens, index);
}

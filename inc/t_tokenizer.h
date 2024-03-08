#ifndef T_TOKENIZER_H
#define T_TOKENIZER_H

/*
 * A T_TOKENIZER breaks a null-terminated string into tokens.
 *
 * A token is any sequence of characters except for a NULL or a non-escaped
 * delimiting character. Sequential delimiting characters may be treated as a
 * single delimiter, or as one or more zero-length columns. When a delimiter
 * following a token is encountered, it is replaced with a NULL (the supplied
 * string is modified in-place).
 *
 * Create a T_TOKENIZER with the t_tokenizer_create function supplying the
 * delimiter character, the escape character and a flag indicating whether or
 * not sequential delimiter characters are treated as delimiting empty tokens.
 *
 * Parse a string with the t_tokenizer_parse function. After parsing, the
 * number of tokens is available with the t_tokenizer_count function, and
 * access to each token is available through the t_tokenizer_get function. The
 * t_tokenizer_parse function modifies the supplied string by placing NULL
 * characters at the end of each token--this prevents having to allocate
 * additional space for holding the tokens.
 *
 */

#include <stdio.h>
#include <sys/types.h>

typedef struct T_TOKENIZER T_TOKENIZER;

/*
 * Function  : t_tokenizer_create
 * Purpose   : creates a new T_TOKENIZER
 * Parameters: delimter character
 *             escape character
 *             flag indicating if null columns are allowed
 * Return    : pointer to T_TOKENIZER
 */
T_TOKENIZER *t_tokenizer_create (char delimiter, char escape, int null_columns);

/*
 * Function  : t_tokenizer_free
 * Purpose   : frees a T_TOKENIZER and all internal resources
 * Parameters: pointer to a T_TOKENIZER
 * Return    : none
 */
void t_tokenizer_free (T_TOKENIZER *);

/*
 * Function  : t_tokenizer_parse
 * Purpose   : parse a string into tokens
 * Parameters: pointer to a T_TOKENIZER
 *             pointer to a null terminated string
 * Return    : none
 * Notes     :
 *
 * 1. The string will be modified by the tokenizer so that each token
 *    ends with a NULL.
 */
void t_tokenizer_parse (T_TOKENIZER *, char *);

/*
 * Function  : t_tokenizer_count
 * Purpose   : return the number of tokens found in the last parse
 * Parameters: pointer to a T_TOKENIZER
 * Return    : the number of tokens
 */
int t_tokenizer_count (T_TOKENIZER *);

/*
 * Function  : t_tokenizer_get
 * Purpose   : return a pointer to one of the tokens from the last parse
 * Parameters: pointer to a T_TOKENIZER
 *             index of the token (zero is the first element)
 * Return    : the number of tokens
 * Notes     :
 *
 * 1. A negative index starts from the right (-1 == count - 1)
 *
 * 2. If the index is out-of-bounds, a NULL is returned.
 */
char *t_tokenizer_get (T_TOKENIZER *, int);

#endif

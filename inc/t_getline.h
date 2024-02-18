#ifndef T_GETLINE_H
#define T_GETLINE_H

/*
 * A T_GETLINE implements a safe (no buffer overflows) way to read lines from
 * a file. Lines read from the file can be trimmed of whitespace and simple
 * comments (everything on a line following a specified character). This might
 * be useful for reading program data from a text file.
 */

#include <stdio.h>
#include <sys/types.h>

typedef struct T_GETLINE T_GETLINE;

#define T_GETLINE_TRIM_LEFT    1 << 0
#define T_GETLINE_TRIM_RIGHT   1 << 1
#define T_GETLINE_TRIM_EOL     1 << 2
#define T_GETLINE_TRIM_COMMENT 1 << 3

/*
 * Function  : t_getline_create
 * Purpose   : creates a new T_GETLINE
 * Parameters: pointer to open file
 * Return    : pointer to T_GETLINE
 */
T_GETLINE *t_getline_create (FILE *);

/*
 * Function  : t_getline_free
 * Purpose   : frees a T_GETLINE and all internal resources
 * Parameters: pointer to a T_GETLINE
 * Return    : none
 */
void t_getline_free (T_GETLINE *);

/*
 * Function  : t_getline_set_comment
 * Purpose   : sets the comment charater (Note 1)
 * Parameters: pointer to a T_GETLINE
 *             character
 * Return    : none
 * Notes     :
 *
 * 1.  The comment character indicates the start of a comment, all of which
 *     will be trimmed if the T_GETLINE_TRIM_COMMENT flag is passed to the
 *     t_getline_next function. The trim includes the comment character itself.
 */
void t_getline_set_comment (T_GETLINE *, char comment);

/* 
 * Function  : t_getline_next
 * Purpose   : gets the next line from the T_GETLINE
 * Parameters: pointer to a T_GETLINE
 *             control flags (Note 1)
 * Return    : pointer to null terminated line
 *             0 on end of file or out of memory (see t_getline_error)
 * Notes     :
 *
 * 1. The flags can be logically added (using OR) to create combined effects.
 *
 *    These flags trim white space at the start or end of the line:
 *
 *      T_GETLINE_TRIM_LEFT
 *      T_GETLINE_TRIM_RIGHT
 *
 *    This flag removes the end of line character(s):
 *
 *      T_GETLINE_TRIM_EOL
 *
 *    This flag (in combination with t_getline_set_comment) trims single line
 *    comments by removing all characters including and after the specified
 *    comment character:
 *
 *      T_GETLINE_TRIM_COMMENT
 *
 * 2. On success, the t_getline_buffer function returns a pointer to a buffer
 *    containing the current line as a NULL-terminated string.
 */
char *t_getline_next (T_GETLINE *, u_char flags);

/*
 * Function  : t_getline_line_number
 * Purpose   : returns the current line count
 * Parameters: pointer to a T_GETLINE
 * Return    : line number of the last line returned by t_getline_next
 */
int t_getline_line_number (T_GETLINE *);

/*
 * Function  : t_getline_error
 * Purpose   : provide reason why last call to t_getline_next didn't work
 * Parameters: pointer to a T_GETLINE
 * Return    : 0 on end of file
 *             1 on out of memory
 *             else -1
 */
int t_getline_error (T_GETLINE *);

#endif

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "t_getline.h"
#include "c_collection/c_buffer.h"

struct T_GETLINE {
  FILE * file;
  C_BUFFER *buffer;
  char comment;
  int line_count;
  u_char eof;
  u_char out_of_memory;
};

T_GETLINE *
t_getline_create (FILE *file) {
  T_GETLINE *g = (T_GETLINE *) malloc (sizeof (T_GETLINE));

  if (g) {
    memset (g, 0x00, sizeof (T_GETLINE));
    g -> file = file;
    g -> buffer = c_buffer_create ();
    if (g -> buffer == NULL) {
      free (g);
      g = NULL;
    }
  }

  return g;
}

void
t_getline_free (T_GETLINE *g) {
  c_buffer_free (g -> buffer);
  free (g);
}

void
t_getline_set_comment (T_GETLINE *g, char comment) {
  g -> comment = comment;
}

char *
t_getline_next (T_GETLINE *g, u_char flags) {

  int dos = 0;
  int c;  /* this is an int so comparison to EOF will work consistently */
  char *ptr;
  size_t white;
  char *buffer;
  int length;

  /* no reason to continue */
  if (g -> eof || g -> out_of_memory)
    return 0;

  c_buffer_clear (g -> buffer);
  while (EOF != (c = getc (g -> file))) {

    /* buffer the character */
    c_buffer_append_char (g -> buffer, c);

    /* done if end-of-line */
    if (c == '\n') break;
  }

  buffer = c_buffer_get (g -> buffer);
  length = c_buffer_length (g -> buffer);

  /* EOF */
  if (c == EOF && length == 0) {
    g -> eof = 1;
    return 0;
  }

  /* DOS style line end */
  if (length > 1 && buffer [length - 2] == '\r')
    dos = 1;

  /* trim white space on left */
  if (flags & T_GETLINE_TRIM_LEFT) {
    for (white = 0, ptr = buffer;
      length > 1 && isspace (*ptr);
      white ++, ptr ++, length --);
    if (white)
      memmove (buffer, buffer + white, length);
  }

  /* trim comment */
  if (flags & T_GETLINE_TRIM_COMMENT && g -> comment) {
    for (white = 0; white < length; white ++) {
      if (buffer [white] == g -> comment) {
        if (dos) {
          buffer [white] = '\r';
          white ++;
        }
        buffer [white] = '\n';
        length = white + 1;
        break;
      }
    }
  }

  /* trim white space on right */
  if (flags & T_GETLINE_TRIM_RIGHT) {
    for (white = 0, ptr = buffer + length - 2;
      length > 1 && isspace (*ptr);
      white ++, ptr --, length --);
    if (white) {
      if (dos) {
        buffer [length - 1] = '\r';
        length ++;
      }
      buffer [length - 1] = '\n';
    }
  }

  /* trim end of line */
  if (flags & T_GETLINE_TRIM_EOL) {
    length --;
    if (dos)
      length --;
  }

  /* add the final null character */
  buffer [length] = 0x00;

  /* keep track of line number */
  g -> line_count ++;

  return buffer;
}

int
t_getline_line_number (T_GETLINE *g) {
  return g -> line_count;
}

int
t_getline_error (T_GETLINE *g) {

  if (g -> eof)
    return 0;

  if (g -> out_of_memory)
    return 1;

  return -1;
}

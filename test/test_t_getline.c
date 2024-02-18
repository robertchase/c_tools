#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "t_getline.h"

int main (int argc, char **argv) {
  FILE *f = fopen ("data/t_getline.txt", "r");
  T_GETLINE *g = t_getline_create (f);
  char *line;
  u_char flags = 0;

  assert (f);
  assert (g);
  assert (0 == t_getline_line_number (g));

  /* test simple next */
  line = t_getline_next (g, 0);
  assert (line);
  assert (0 == strcmp (line, "LINE 1\n"));
  assert (1 == t_getline_line_number (g));

  /* test trim EOL */
  flags = T_GETLINE_TRIM_EOL;
  line = t_getline_next (g, flags);
  assert (line);
  assert (0 == strcmp (line, "LINE 2"));
  assert (2 == t_getline_line_number (g));

  /* test trim LEFT */
  line = t_getline_next (g, flags);
  assert (line);
  assert (0 == strcmp (line, "  LINE 3"));
  flags |= T_GETLINE_TRIM_LEFT;
  line = t_getline_next (g, flags);
  assert (line);
  assert (0 == strcmp (line, "LINE 4"));

  /* test trim RIGHT */
  line = t_getline_next (g, flags);
  assert (line);
  assert (0 == strcmp (line, "LINE 5  "));
  flags |= T_GETLINE_TRIM_RIGHT;
  line = t_getline_next (g, flags);
  assert (line);
  assert (0 == strcmp (line, "LINE 6"));

  /* test trim COMMENT */
  line = t_getline_next (g, flags);
  assert (line);
  assert (0 == strcmp (line, "#LINE 7"));
  line = t_getline_next (g, flags);
  assert (line);
  assert (0 == strcmp (line, "LINE 8#LINE 8"));
  t_getline_set_comment (g, '#');
  flags |= T_GETLINE_TRIM_COMMENT;
  line = t_getline_next (g, flags);
  assert (line);
  assert (0 == strcmp (line, ""));
  line = t_getline_next (g, flags);
  assert (line);
  assert (0 == strcmp (line, "LINE 10"));

  /* test EOF */
  assert (-1 == t_getline_error (g));
  line = t_getline_next (g, 0);
  assert (!line);
  assert (0 == t_getline_error (g));

  t_getline_free (g);
  fclose (f);

  f = fopen ("data/t_getline.dos.txt", "r");
  assert (f);
  g = t_getline_create (f);
  assert (g);

  /* test simple next DOS EOL */
  line = t_getline_next (g, 0);
  assert (line);
  assert (0 == strcmp (line, "LINE 1\r\n"));

  /* test trim DOS EOL */
  flags = T_GETLINE_TRIM_EOL;
  line = t_getline_next (g, flags);
  assert (line);
  assert (0 == strcmp (line, "LINE 2"));

  t_getline_free (g);
  fclose (f);

  return 0;
}

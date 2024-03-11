#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../inc/t_tokenizer.h"

int main (int argc, char **argv) {

  T_TOKENIZER *t = t_tokenizer_create (' ', '\\', 0);
  assert (t);
  assert (NULL == t_tokenizer_get(t, 0));

  char line[] = "a b c";
  t_tokenizer_parse(t, line);
  assert (3 == t_tokenizer_count (t));
  assert (0 == strcmp ("a", t_tokenizer_get (t, 0)));
  assert (0 == strcmp ("b", t_tokenizer_get (t, 1)));
  assert (0 == strcmp ("c", t_tokenizer_get (t, 2)));
  assert (NULL == t_tokenizer_get(t, 4));

  char line_extra[] = "     a    b  c    ";
  t_tokenizer_parse(t, line_extra);
  assert (3 == t_tokenizer_count (t));
  assert (0 == strcmp ("a", t_tokenizer_get (t, 0)));
  assert (0 == strcmp ("b", t_tokenizer_get (t, 1)));
  assert (0 == strcmp ("c", t_tokenizer_get (t, 2)));

  char line_escape[] = "\\abc d\\ e\\\\f  gh\\i\\"; /* last escape ignored */
  t_tokenizer_parse(t, line_escape);
  assert (3 == t_tokenizer_count (t));
  assert (0 == strcmp ("abc", t_tokenizer_get (t, 0)));
  assert (0 == strcmp ("d e\\f", t_tokenizer_get (t, 1)));
  assert (0 == strcmp ("ghi", t_tokenizer_get (t, 2)));

  t_tokenizer_free (t);

  t = t_tokenizer_create (' ', '\\', 1);
  assert (t);

  char m_line[] = "a b c";
  t_tokenizer_parse(t, m_line);
  assert (3 == t_tokenizer_count (t));
  assert (0 == strcmp ("a", t_tokenizer_get (t, 0)));
  assert (0 == strcmp ("b", t_tokenizer_get (t, 1)));
  assert (0 == strcmp ("c", t_tokenizer_get (t, 2)));

  char m_line_extra[] = "     a    b  c    ";
  t_tokenizer_parse(t, m_line_extra);
  assert (15 == t_tokenizer_count (t));
  assert (0 == strcmp ("a", t_tokenizer_get (t, 5)));
  assert (0 == strcmp ("b", t_tokenizer_get (t, 9)));
  assert (0 == strcmp ("c", t_tokenizer_get (t, 11)));

  char m_line_escape[] = "\\abc d\\ e\\\\f  gh\\i\\";
  t_tokenizer_parse(t, m_line_escape);
  assert (4 == t_tokenizer_count (t));
  assert (0 == strcmp ("abc", t_tokenizer_get (t, 0)));
  assert (0 == strcmp ("d e\\f", t_tokenizer_get (t, 1)));
  assert (0 == strcmp ("", t_tokenizer_get (t, 2)));
  assert (0 == strcmp ("ghi", t_tokenizer_get (t, 3)));

  t_tokenizer_free (t);

  return 0;
}

BUILD c_tools.a

CFLAGS -g
#CFLAGS -O -Wuninitialized
CFLAGS -Werror -Wall -Wmissing-prototypes -Wmissing-declarations -Wstrict-prototypes -Wunused
CFLAGS -Wno-deprecated-declarations

LIBRARY c_collection

SOURCE t_getline.c

TEST test_t_getline.c

INSTALL t_getline.h

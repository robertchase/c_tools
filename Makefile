SRC := src
INC := inc
TEST := test
OBJ := obj
SHARED_LIB := $(HOME)/lib
SHARED_INC := $(HOME)/inc
SHARED_BIN := $(HOME)/bin

IFLAGS := -I $(INC) -I $(SHARED_INC)
CFLAGS := -g -Werror -Wall -Wmissing-prototypes -Wmissing-declarations -Wstrict-prototypes -Wunused -Wno-deprecated-declarations
LFLAGS := $(SHARED_LIB)/c_collection.a

c_tools.a: $(OBJ)/t_getline.o
	$(AR) ru c_tools.a $(OBJ)/t_getline.o
	ranlib c_tools.a

$(OBJ)/t_getline.o: $(SRC)/t_getline.c $(SHARED_INC)/t_getline.h \
  $(SHARED_INC)/c_collection/c_buffer.h
	gcc $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ)/test_t_getline.o: $(TEST)/test_t_getline.c $(SHARED_INC)/t_getline.h

	gcc $(CFLAGS) $(IFLAGS) -c $< -o $@

test_t_getline: $(OBJ)/test_t_getline.o c_tools.a
	gcc $(OBJ)/test_t_getline.o c_tools.a $(LFLAGS) -o $@

test: test_t_getline c_tools.a
	./test_t_getline
	rm test_t_getline

install: c_tools.a
	-mkdir $(SHARED_LIB) 2>/dev/null || true
	-cp c_tools.a $(SHARED_LIB)/
	-mkdir $(SHARED_INC) 2>/dev/null || true
	-cp $(INC)/t_getline.h $(SHARED_INC)/

clean:
	-rm -f c_tools.a
	-rm -f $(OBJ)/t_getline.o
	-rm -f $(OBJ)/test_t_getline.o
	-rm -f test_t_getline

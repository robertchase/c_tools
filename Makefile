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

c_tools.a: $(OBJ)/t_getline.o $(OBJ)/t_tokenizer.o
	$(AR) ru c_tools.a $(OBJ)/t_getline.o $(OBJ)/t_tokenizer.o
	ranlib c_tools.a

$(OBJ)/t_getline.o: $(SRC)/t_getline.c $(INC)/t_getline.h \
  $(SHARED_INC)/c_collection/c_buffer.h
	gcc $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ)/t_tokenizer.o: $(SRC)/t_tokenizer.c $(INC)/t_tokenizer.h \
  $(SHARED_INC)/c_collection/c_array.h \
  $(SHARED_INC)/c_collection/c_iterator.h
	gcc $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ)/test_t_getline.o: $(TEST)/test_t_getline.c $(INC)/t_getline.h

	gcc $(CFLAGS) $(IFLAGS) -c $< -o $@

test_t_getline: $(OBJ)/test_t_getline.o c_tools.a
	gcc $(OBJ)/test_t_getline.o c_tools.a $(LFLAGS) -o $@

$(OBJ)/test_t_tokenizer.o: $(TEST)/test_t_tokenizer.c $(TEST)/../inc/t_tokenizer.h

	gcc $(CFLAGS) $(IFLAGS) -c $< -o $@

test_t_tokenizer: $(OBJ)/test_t_tokenizer.o c_tools.a
	gcc $(OBJ)/test_t_tokenizer.o c_tools.a $(LFLAGS) -o $@

test: test_t_getline test_t_tokenizer c_tools.a
	./test_t_getline
	rm test_t_getline
	./test_t_tokenizer
	rm test_t_tokenizer

install: c_tools.a
	-mkdir -p $(SHARED_LIB)
	-cp c_tools.a $(SHARED_LIB)/
	-mkdir -p $(SHARED_INC)/c_tools
	-cp $(INC)/t_getline.h $(SHARED_INC)/c_tools/
	-cp $(INC)/t_tokenizer.h $(SHARED_INC)/c_tools/

clean:
	-rm -f c_tools.a
	-rm -f $(OBJ)/t_getline.o
	-rm -f $(OBJ)/t_tokenizer.o
	-rm -f $(OBJ)/test_t_getline.o
	-rm -f $(OBJ)/test_t_tokenizer.o
	-rm -f test_t_getline
	-rm -f test_t_tokenizer

IFLAGS = -I inc -I /Users/bob/inc
CFLAGS = -g -Werror -Wall -Wmissing-prototypes -Wmissing-declarations -Wstrict-prototypes -Wunused -Wno-deprecated-declarations -I /Users/bob/inc/c_collection
LFLAGS = /Users/bob/lib/c_collection.a

c_tools.a: obj/t_getline.o
	$(AR) ru c_tools.a obj/t_getline.o
	ranlib c_tools.a

obj/t_getline.o: src/t_getline.c inc/t_getline.h \
  /Users/bob/inc/c_collection/c_buffer.h
	gcc $(CFLAGS) $(IFLAGS) -c $< -o $@

obj/test_t_getline.o: test/test_t_getline.c inc/t_getline.h
	gcc $(CFLAGS) $(IFLAGS) -c $< -o $@

clean: 
	-rm -f c_tools.a
	-rm -f obj/t_getline.o
	-rm -f obj/test_t_getline.o
	-rm -f test_t_getline

test: test_t_getline c_tools.a
	./test_t_getline
	rm test_t_getline

test_t_getline: obj/test_t_getline.o c_tools.a
	gcc obj/test_t_getline.o c_tools.a $(LFLAGS) -o $@

install: c_tools.a 
	-cp c_tools.a $(HOME)/lib/
	-mkdir $(HOME)/inc/c_tools
	-cp inc/t_getline.h $(HOME)/inc/c_tools/

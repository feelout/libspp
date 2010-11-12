CC=gcc
CFLAGS=-fPIC -g
OBJECTS := Grammar.o Util.o rbtree.o Set.o

libspp.so: $(OBJECTS)
	$(CC) -shared -Wl,-soname,libspp.so.1 \
		-o libspp.so.1.0.1 $(OBJECTS)
	ln -f -s libspp.so.1.0.1 libspp.so.1
	ln -f -s libspp.so.1.0.1 libspp.so

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o libspp.so*

install:
	cp libspp.so* /usr/lib/

remove:
	rm -rf /usr/lib/libspp.so*

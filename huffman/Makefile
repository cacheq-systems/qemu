
huffman.a: huffman.o huffinterface.o
	ar rcs $@ $^

huffinterface.o: huffinterface.cpp huffinterface.h huffman.h
	gcc -g -c -o $@ $<

huffman.o: huffman.c huffman.h
	gcc -g -c -o $@ $<

clean:
	rm -f *.o *.a $(TARGET)
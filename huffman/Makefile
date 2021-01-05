
huffman.a: huffman.o huffinterface.o
	ar rcs $@ $^

huffinterface.o: huffinterface.cpp huffinterface.h huffman.h
	g++ -g -c -o $@ $<

huffman.o: huffman.c huffman.h
	g++ -g -c -o $@ $<

clean:
	rm -f *.o *.a $(TARGET)
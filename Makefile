SOURCES=$(wildcard src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

game: .depend $(OBJECTS)
	clang -lm -o game $(OBJECTS)

$(OBJECTS): %.o: %.c
	clang -c -o $@ $<

.depend: $(SOURCES)
	clang -MM $(SOURCES) | sed "s/\([A-Za-z0-9]\+\)\.o/src\/\1.o/g" > ./.depend

include .depend

clean:
	rm src/*.o
	rm .depend
	rm game


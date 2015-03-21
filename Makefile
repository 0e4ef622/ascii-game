SOURCES=$(wildcard src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

game: .depend $(OBJECTS)
	clang -lm -o game $(OBJECTS)

$(OBJECTS): %.o: %.c
	clang -c -o $@ $<
#obj/main.o: src/main.c src/screen.h
#	clang -c -o obj/main.o src/main.c
#
#obj/screen.o: src/screen.c
#	clang -c -o obj/screen.o src/screen.c
#
#obj/canonctrl.o: src/canonctrl.c
#	clang -c -o obj/canonctrl.o src/canonctrl.c
#
#obj/keyboard.o: src/keyboard.c
#	clang -c -o obj/keyboard.o src/keyboard.c
#
#obj/player.o: src/player.c
#	clang -c -o obj/player.o src/player.c

.depend: $(SOURCES)
	clang -MM $(SOURCES) | sed "s/\([A-Za-z0-9]\+\)\.o/src\/\1.o/g" > ./.depend

include .depend

clean:
	rm src/*.o


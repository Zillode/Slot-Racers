CXXFLAGS=-Wall -O2
LDFLAGS=`sdl-config --cflags --libs` -lSDL_gfx
CCFILES=CSpriteBase.C CSprite.C font.C game.C graphics.C main.C map.C player.C bullet.C movingobject.C
HFILES=CSpriteBase.h CSprite.h font.h game.h graphics.h main.h map.h player.h bullet.h movingobject.h
EXTRAFILES=data/* README COPYING
OFILES=$(CCFILES:%.C=%.o)

main: $(OFILES)
	g++ $(CXXFLAGS) $(LDFLAGS) -o slotracers $^

include make.depend

clean:
	rm -f main $(OFILES) make.depend gmon.out

make.depend: $(CCFILES) $(HFILES)
	g++ -M $(CCFILES) >$@

tar:
	rm atari-game.tar && tar cvf atari-game.tar $(CCFILES) $(HFILES) $(EXTRAFILES) Makefile

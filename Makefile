CXXFLAGS=-Wall -O2
LDFLAGS=`sdl-config --cflags --libs` -lSDL_gfx
CCFILES=CSpriteBase.C CSprite.C font.C game.C graphics.C main.C map.C player.C bullet.C movingobject.C
HFILES=CSpriteBase.h CSprite.h font.h game.h graphics.h main.h map.h player.h bullet.h movingobject.h
EXTRAFILES=data/* README COPYING
OFILES=$(CCFILES:%.C=%.o)
ALLFILES=$(CCFILES) $(HFILES) $(EXTRAFILES) Makefile

main: $(OFILES)
	g++ $(CXXFLAGS) $(LDFLAGS) -o slotracers $^

clean:
	rm -f main $(OFILES)

make.depend: $(CCFILES) $(HFILES)
	g++ -M $(CCFILES) >$@

tar:
	rm -f atari-game.tar
	rm -f atari-game.tar.gz
	rm -f atari-game.rar
	tar cvf atari-game.tar $(addprefix ../Atari-game/, $(ALLFILES))
	tar cvzf atari-game.tar.gz $(addprefix ../Atari-game/, $(ALLFILES))
	rar a atari-game.rar $(addprefix ../Atari-game/, $(ALLFILES))

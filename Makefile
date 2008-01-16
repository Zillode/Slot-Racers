CXXFLAGS=-Wno-deprecated -g
LDFLAGS=`sdl-config --cflags --libs`
CCFILES=CSpriteBase.C CSprite.C font.C game.C graphics.C main.C map.C player.C
HFILES=CSpriteBase.h CSprite.h font.h game.h graphics.h main.h map.h player.h
PICFILES=pics/*
OFILES=$(CCFILES:%.C=%.o)

main: $(OFILES)
	g++ $(CXXFLAGS) $(LDFLAGS) -o $@ $^

include make.depend

clean:
	rm -f main $(OFILES) make.depend

make.depend: $(CCFILES) $(HFILES)
	g++ -M $(CCFILES) >$@

tar:
	tar cvf atari-game.tar $(CCFILES) $(HFILES) $(TESTFILES) Makefile

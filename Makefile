CXXFLAGS=-Wno-deprecated -g
LDFLAGS=`sdl-config --cflags --libs`
CCFILES=main.C map.C graphics.C game.C CSpriteBase.C CSprite.C font.C
HFILES=$(CCFILES:%.C=%.h)
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

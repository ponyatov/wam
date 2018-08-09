wam.log: ./wam.exe wam.src
	./wam.exe < wam.src > $@ && tail $(TAIL) $@
C = wam.cpp wam.tab.cpp lex.yy.c
H = wam.hpp wam.tab.hpp
CXXFLAGS += -std=gnu++11 -DHEAPsz=0x10 -DXsz=0x04
./wam.exe: $(C) $(H) Makefile
	$(CXX) $(CXXFLAGS) -o $@ $(C)
wam.tab.cpp: wam.ypp
	bison $<
lex.yy.c: wam.lpp
	flex $<
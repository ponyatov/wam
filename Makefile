wam.log: ./wam.exe
	./wam.exe > $@ && tail $(TAIL) $@
C = wam.cpp
H = 
CXXFLAGS += -std=gnu++11 -DHEAPsz=0x10
./wam.exe: $(C) $(H) Makefile
	$(CXX) $(CXXFLAGS) -o $@ $(C)
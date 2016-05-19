wam.log: ./wam.exe
	./wam.exe > $@ && tail $(TAIL) $@
C = wam.c
H = 
CFLAGS += -DHEAPsz=0x10
./wam.exe: $(C) $(H) Makefile
	$(CC) $(CFLAGS) -o $@ $(C)
wam.log: ./wam.exe
	./wam.exe > $@ && tail $(TAIL) $@
C = wam.c
H = 
CFLAGS = -ansi
./wam.exe: $(C) $(H) Makefile
	$(CC) $(CFLAGS) -o $@ $(C)
CC            = arm-linux-gnueabi-gcc
DEST          = /opt/rootfs/root/
LIBS          = 
PROGRAM       = bmp_ss
OBJS          = $(PROGRAM).o bitmap.o
CFLAGS        = 

$(PROGRAM):	$(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(PROGRAM)
install:
	cp $(PROGRAM) $(DEST)
clean:
	rm -f *.o $(PROGRAM)

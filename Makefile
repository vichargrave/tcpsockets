# Makes the tcpsocket lib

all:
	make -f Makefile.client
	make -f Makefile.client_timeout
	make -f Makefile.server
	make -f Makefile.server_timeout
	make -f Makefile.server_pause

clean:
	make -f Makefile.client clean
	make -f Makefile.client_timeout clean
	make -f Makefile.server clean	
	make -f Makefile.server_timeout clean
	make -f Makefile.server_pause clean


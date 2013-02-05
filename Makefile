all:
	make -f Makefile.client
	make -f Makefile.server

clean:
	make -f Makefile.client clean
	make -f Makefile.server clean	

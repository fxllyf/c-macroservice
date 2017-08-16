all: libs src

libs:
	make -C ./libs all

src:
	make -C ./src all

tools:
	make -C ./tools all
	
clean:
	make -C ./libs clean
	make -C ./apps clean
	make -C ./tools clean

scan:
	make -C ./libs scan
	make -C ./apps scan
	make -C ./tools scan

.PHONY: all build clean scan libs apps tools
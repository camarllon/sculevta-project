install: 
	gcc -o SCULEVTA-BIN SCULEVTA.c

clean: 
	rm -rf SCULEVTA-BIN

all: clean install

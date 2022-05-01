run: Premier
	./Premier

Premier: Premier.c
	gcc  Premier.c -o Premier -Wall -lgmp



clean:
	rm -f Premier

NOMS="Premier"

zip:
	rm -rf ${NOMS}
	mkdir ${NOMS}
	cp Makefile ${NOMS}
	cp Premier.c ${NOMS}
	cp README.md ${NOMS}
	rm -f ${NOMS}.zip
	zip -r ${NOMS}.zip ${NOMS}
	rm -rf ${NOMS}

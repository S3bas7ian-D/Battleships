build:
	gcc battleships.c -o battleships -lm

pack:
	zip -FSr 311CB_DinuAndreiSebastian_Tema2.zip README Makefile *.c *.h

clean:
	rm -rf battleships
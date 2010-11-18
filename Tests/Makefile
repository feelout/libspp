all: tokenize productionParsing gramparsing lrm

tokenize: tokenize.c
	gcc -g -o tokenize -I../ -L../ -lspp tokenize.c

productionParsing: productionParsing.c
	gcc -g -o productionParsing -I../ -L../ -lspp productionParsing.c

gramparsing: gramparsing.c
	gcc -g -o gramparsing -I../ -L../ -lspp gramparsing.c

lrm: lrm.c
	gcc -g -o lrm -I../ -L../ -lspp lrm.c

clean:
	rm -rf tokenize productionParsing gramparsing lrm

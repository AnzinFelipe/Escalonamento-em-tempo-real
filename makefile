pasta_o = objects

pasta_s = source

rate: rate.o
	gcc $(pasta_o)/rate.o -o rate

edf: edf.o
	gcc $(pasta_o)/edf.o -o edf

rate.o: pasta $(pasta_s)/rate.c
	gcc -c $(pasta_s)/rate.c -o $(pasta_o)/rate.o

edf.o: pasta $(pasta_s)/edf.c
	gcc -c $(pasta_s)/edf.c -o $(pasta_o)/edf.o

pasta:
	mkdir -p $(pasta_o)

clean:
	rm -rf *$(pasta_o).o $(pasta_o) rate edf
pasta_o = objects

pasta_s = source

rate: rate.o saida.o atividade.o
	gcc $(pasta_o)/rate.o $(pasta_o)/saida.o $(pasta_o)/atividade.o -o rate

edf: edf.o saida.o atividade.o
	gcc $(pasta_o)/edf.o $(pasta_o)/saida.o $(pasta_o)/atividade.o -o edf

rate.o: pasta $(pasta_s)/rate.c $(pasta_s)/saida.h $(pasta_s)/atividade.h
	gcc -c $(pasta_s)/rate.c -o $(pasta_o)/rate.o

edf.o: pasta $(pasta_s)/edf.c $(pasta_s)/saida.h $(pasta_s)/atividade.h
	gcc -c $(pasta_s)/edf.c -o $(pasta_o)/edf.o

saida.o: pasta $(pasta_s)/saida.c $(pasta_s)/atividade.h
	gcc -c $(pasta_s)/saida.c -o $(pasta_o)/saida.o

atividade.o: pasta $(pasta_s)/atividade.c $(pasta_s)/atividade.h $(pasta_s)/saida.h
	gcc -c $(pasta_s)/atividade.c -o $(pasta_o)/atividade.o

pasta:
	mkdir -p $(pasta_o)

test_rate: rate
	./rate rate_test.txt

test_edf: edf
	./edf edf_test.txt

clean:
	rm -rf *$(pasta_o).o $(pasta_o) rate edf
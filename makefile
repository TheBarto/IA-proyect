CC=gcc
CCFLAGS = -Wall -Wextra -g
EXE = linkedList
#EXE2 = SerieTemporal

linkedListTest:
	rm -f core $(EXE)
	$(CC) $(CCFLAGS) pruebas_linkedList.c linkedList.c -o $(EXE) -lm

#apartado1: 
#	./Encoder -file alfabeto.txt -train 1 -tasaApren 0.01 -capaOculta 5 -fSalida salida_alfabeto.txt -tolerancia 0.00001 -apartado 1

#apartado2: 
#	./Encoder -file alfabeto.txt -train 1 -tasaApren 0.01 -capaOculta 5 -fSalida salida_alfabeto.txt -tolerancia 0.00001 -F 3 -apartado 2


#serietemporalcompile:
#	$(CC) $(CCFLAGS) main_serie_temporal.c particion.c linkedList.c serie_temporal.c -o $(EXE3) -lm

#serietemporal:
#	rm -f core $(EXE) $(EXE2) $(EXE3) 
#	$(CC) $(CCFLAGS) main_serie_temporal.c particion.c linkedList.c serie_temporal.c -o $(EXE3) -lm
#	./SerieTemporal -origen p3_serie2.txt -destino salida_p3_serie2.txt -train 0.7 -tasaApren 0.01 -capaOculta 10 -fSalida salida.txt -tolerancia 0.0000000000000001 -Na 5 -Ns 1 -predice 1 -pospredice 0 -Nf 400
#	Rscript scriptR.r p3_serie2.txt salida_test.txt salida_predice_recursivamente.txt salida.txt

PHONY: clean
clean:
	rm -f core $(EXE)

#valgrind --leak-check=full --track-origins=yes

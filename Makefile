sources = alelo.cpp loco.cpp individuo.cpp geracao.cpp populacao.cpp lz5.cpp 
objects = alelo.o loco.o individuo.o geracao.o populacao.o lz5.o

simulator: $(objects)
	g++ $(objects) -lgsl -lgslcblas -lm -g -static -o lz5
	echo "Makefile para Linux"

alelo.o: $(sources)
	echo "Compilando alelo.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings $(sources)

loco.o: $(sources)
	echo "Compilando loco.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings $(sources)

individuo.o: $(sources)
	echo "Compilando individuo.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings $(sources)

geracao.o: $(sources)
	echo "Compilando geracao.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings $(sources)

populacao.o: $(sources)
	echo "Compilando populacao.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings $(sources)

lz5.o: $(sources)
	echo "Compilando lz5.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings $(sources)


gdb: simulagdb

simulagdb:$(objects)
	g++ $(objects) -lgsl -lgslcblas -lm -o lz5
	echo "Makefile para Linux - GDB"

locusgdb.o: lz5.cpp
	echo "Compilando lz5.cpp"
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings  lz5.cpp



mc: simulamc

simulamc: $(objects)
	g++ $(objects) -lgsl -lgslcblas -lm -L/opt/local/lib -o lz5
	echo "Makefile para Mac OS"

locusmc.o: $(objects)
	echo "Compilando locus.cpp"
	g++ -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++  locus.cpp -I /opt/local/include



mcgdb: simulamcgdb

simulamcgdb: $(objects)
	g++ $(objects) -lgsl -lgslcblas -lm -L/opt/local/lib -o lz5
	echo "Makefile para Mac OS - GDB"

locusmcgdb.o: locus.cpp
	echo "Compilando locus.cpp"
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++  locus.cpp -I /opt/local/include

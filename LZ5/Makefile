sources = parameters.cpp locus.cpp chromosome.cpp genome.cpp individual.cpp population.cpp sel.cpp indSel.cpp ranSel.cpp tandem.cpp indSelRepo.cpp popRepo.cpp indRepo.cpp genomeRepo.cpp tandemRepo.cpp Lz5_Commands_db.cpp Lz5_Interpreter.cpp prompt.cpp repSim.cpp lz5.cpp parRepo.cpp
objects = parameters.o locus.o chromosome.o genome.o individual.o population.o sel.o ranSel.o indSel.o indSelRepo.o popRepo.o indRepo.o genomeRepo.o tandemRepo.o Lz5_Commands_db.o Lz5_Interpreter.o prompt.o repSim.o lz5.o baseReport.o parRepo.o

simulator: $(objects)
	g++ $(objects) -lgsl -lgslcblas -lm -g -static -o lz5
	echo "Makefile para Linux"

parameters.o: $(sources)
	echo "Compilando parameters.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

locus.o: $(sources)
	echo "Compilando locus.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

chromosome.o: $(sources)
	echo "Compilando chromosome.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

genome.o: $(sources)
	echo "Compilando genome.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

individual.o: $(sources)
	echo "Compilando individual.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

population.o: $(sources)	
	echo "Compilando population.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

sel.o: $(sources)
	echo "Compilando population.cpp"
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

ranSel.o: $(sources)	
	echo "Compilando ranSel.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

indSel.o: $(sources)	
	echo "Compilando indSel.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

tandem.o: $(sources)
	echo "Compilando tandem.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

baseReport.o: $(sources)		
	echo "Compilando baseReport.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

parRepo.o: $(sources)
	echo "Compilando parRepo.cpp"
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

indSelrepo.o: $(sources)		
	echo "Compilando indSelrepo.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

popRepo.o: $(sources)		
	echo "Compilando popRepo.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

indRepo.o: $(sources)		
	echo "Compilando indRepo.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

genomeRepo.o: $(sources)		
	echo "Compilando genomeRepo.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

tandemRepo.o: $(sources)		
	echo "Compilando tandemRepo.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

Lz5_Commands_db.o: $(sources)
	echo "Compilando Lz5_Commands_db.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

Lz5_Interpreter.o: $(sources)
	echo "Compilando Interpreter.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

prompt.o: $(sources)
	echo "Compilando prompt.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

repSim.o: $(sources)
	echo "Compilando repSim.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)

lz5.o: $(sources)
	echo "Compilando lz5.cpp" 
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++ $(sources)


gdb: simulagdb

simulagdb:$(objects)
	g++ $(objects) -lgsl -lgslcblas -lm -o lz5
	echo "Makefile para Linux - GDB"

locusgdb.o: lz5.cpp
	echo "Compilando lz5.cpp"
	g++ -g -c -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Weffc++  lz5.cpp



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

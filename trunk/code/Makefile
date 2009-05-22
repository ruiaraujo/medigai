CXX = g++
CXXFLAGS =  -c -Wall  -Wextra # -Weffc++ # -O2 

all:  pessoas.o consulta.o convencao.o hora.o data.o file.o especialidade.o mem.o horario.o gestaoteste.o
	$(CXX) hora.o data.o pessoas.o consulta.o convencao.o gestao.o file.o especialidade.o horario.o mem.o -o gestao

gestao:  pessoas.o consulta.o convencao.o hora.o data.o file.o especialidade.o mem.o horario.o gestao.o
	$(CXX) hora.o data.o pessoas.o consulta.o convencao.o gestao.o file.o especialidade.o horario.o mem.o -o gestao
	
gestao.o: gestao.cpp
	$(CXX) $(CXXFLAGS) gestao.cpp -o gestao.o
	
gestaoteste.o: gestaoteste.cpp
	$(CXX) $(CXXFLAGS) gestaoteste.cpp -o gestao.o
	
mem.o: classes/headers/MemoryHandling.h classes/MemoryHandling.cpp 
	$(CXX) $(CXXFLAGS) classes/MemoryHandling.cpp  -o mem.o
	
file.o: classes/headers/FileHandling.h classes/FileHandling.cpp 
	$(CXX) $(CXXFLAGS) classes/FileHandling.cpp  -o file.o
	
data.o: classes/headers/data.h classes/data.cpp
	$(CXX) $(CXXFLAGS) classes/data.cpp -o data.o
  
hora.o: classes/headers/hora.h classes/hora.cpp
	$(CXX) $(CXXFLAGS) classes/hora.cpp -o hora.o

especialidade.o: classes/headers/especialidade.h classes/especialidade.cpp
	$(CXX) $(CXXFLAGS) classes/especialidade.cpp -o especialidade.o

horario.o: classes/headers/horario.h classes/horario.cpp
	$(CXX) $(CXXFLAGS) classes/horario.cpp -o horario.o

convencao.o: classes/headers/convencao.h classes/convencao.cpp
	$(CXX) $(CXXFLAGS) classes/convencao.cpp -o convencao.o

pessoas.o: classes/headers/pessoas.h classes/pessoas.cpp
	$(CXX) $(CXXFLAGS) classes/pessoas.cpp -o pessoas.o
  
utente.o:  convencao.o utente.h utente.cpp
	$(CXX) $(CXXFLAGS) utente.cpp -o utente.o
  
medico.o: medico.h medico.cpp
	$(CXX) $(CXXFLAGS) medico.cpp -o medico.o

consulta.o: classes/headers/consulta.h classes/consulta.cpp
	$(CXX) $(CXXFLAGS) classes/consulta.cpp -o consulta.o

clean:
	rm -f *.o gestao

CXX = g++
CXXFLAGS = -Wall  -Wextra -c #-Weffc++ # -O2 

all: gestao.o tempo.o pessoas.o consulta.o convencao.o hora.o data.o
	$(CXX) hora.o data.o tempo.o pessoas.o consulta.o convencao.o gestao.o -o gestao
	
gestao.o: gestaoteste.cpp
	$(CXX) $(CXXFLAGS) gestaoteste.cpp -o gestao.o
  
data.o: classes/headers/data.h classes/data.cpp
	$(CXX) $(CXXFLAGS)  classes/data.cpp -o data.o
  
hora.o: classes/headers/hora.h classes/hora.cpp
	$(CXX) $(CXXFLAGS) classes/hora.cpp -o hora.o

tempo.o: classes/headers/tempo.h classes/tempo.cpp
	$(CXX) $(CXXFLAGS) classes/tempo.cpp -o tempo.o

convencao.o: classes/headers/convencao.h classes/convencao.cpp
	$(CXX) $(CXXFLAGS) classes/convencao.cpp -o convencao.o

pessoas.o: classes/headers/pessoas.h classes/pessoas.cpp
	$(CXX) $(CXXFLAGS) classes/pessoas.cpp -o pessoas.o
  
#utente.o:  convencao.o utente.h utente.cpp
	#$(CXX) $(CXXFLAGS) utente.cpp -o utente.o
  
#medico.o: medico.h medico.cpp
	#$(CXX) $(CXXFLAGS) medico.cpp -o medico.o

consulta.o: classes/headers/consulta.h classes/consulta.cpp
	$(CXX) $(CXXFLAGS) classes/consulta.cpp -o consulta.o

clean:
	rm -f *.o gestao

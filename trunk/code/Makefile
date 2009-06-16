CXX = g++
CX = i586-mingw32msvc-g++
CXXFLAGS =  -c -Wall  -Wextra -Weffc++ -O3 


all:  mem.o gestao.o
	$(CXX) hora.o data.o pessoas.o consulta.o convencao.o gestao.o file.o especialidade.o horario.o mem.o -o gestao

gestaoteste:  mem.o gestaoteste.o
	$(CXX) hora.o data.o pessoas.o consulta.o convencao.o gestaoteste.o file.o especialidade.o horario.o mem.o -o gestao
	
gestao.o: gestao.cpp
	$(CXX) $(CXXFLAGS) gestao.cpp -o gestao.o
	
gestaoteste.o: gestaoteste.cpp
	$(CXX) $(CXXFLAGS) gestaoteste.cpp -o gestaoteste.o

mem.o: horario.o file.o classes/headers/MemoryHandling.h classes/MemoryHandling.cpp
	$(CXX) $(CXXFLAGS) classes/MemoryHandling.cpp  -o mem.o
	
file.o: consulta.o classes/headers/FileHandling.h classes/FileHandling.cpp 
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

pessoas.o: hora.o especialidade.o convencao.o classes/headers/pessoas.h classes/pessoas.cpp 
	$(CXX) $(CXXFLAGS) classes/pessoas.cpp -o pessoas.o
  
utente.o:  convencao.o utente.h utente.cpp
	$(CXX) $(CXXFLAGS) utente.cpp -o utente.o
  
medico.o: hora.o especialidade.o medico.h medico.cpp
	$(CXX) $(CXXFLAGS) medico.cpp -o medico.o

consulta.o: pessoas.o data.o classes/headers/consulta.h classes/consulta.cpp
	$(CXX) $(CXXFLAGS) classes/consulta.cpp -o consulta.o


win32: memm.o gestaom.o
	$(CX) horam.o datam.o pessoasm.o consultam.o convencaom.o gestaom.o filem.o especialidadem.o horariom.o memm.o -o gestao.exe

gestaom.o: gestao.cpp
	$(CX) $(CXXFLAGS) gestaowin.cpp -o gestaom.o

memm.o: filem.o horariom.o classes/headers/MemoryHandling.h classes/MemoryHandling.cpp 
	$(CX) $(CXXFLAGS) classes/MemoryHandling.cpp  -o memm.o
	
filem.o: consultam.o classes/headers/FileHandling.h classes/FileHandling.cpp 
	$(CX) $(CXXFLAGS) classes/FileHandling.cpp  -o filem.o
	
datam.o: classes/headers/data.h classes/data.cpp
	$(CX) $(CXXFLAGS) classes/data.cpp -o datam.o
  
horam.o: classes/headers/hora.h classes/hora.cpp
	$(CX) $(CXXFLAGS) classes/hora.cpp -o horam.o

especialidadem.o: classes/headers/especialidade.h classes/especialidade.cpp
	$(CX) $(CXXFLAGS) classes/especialidade.cpp -o especialidadem.o

horariom.o: consultam.o classes/headers/horario.h classes/horario.cpp
	$(CX) $(CXXFLAGS) classes/horario.cpp -o horariom.o

convencaom.o: classes/headers/convencao.h classes/convencao.cpp
	$(CX) $(CXXFLAGS) classes/convencao.cpp -o convencaom.o

pessoasm.o: convencaom.o horam.o especialidadem.o classes/headers/pessoas.h classes/pessoas.cpp
	$(CX) $(CXXFLAGS) classes/pessoas.cpp -o pessoasm.o
  
utentem.o:  convencaom.o classes/headers/utente.h classes/utente.cpp
	$(CX) $(CXXFLAGS) classes/utente.cpp -o utentem.o
  
medicom.o: horam.o especialidadem.o classes/headers/medico.h classes/medico.cpp
	$(CX) $(CXXFLAGS) classes/medico.cpp -o medicom.o

consultam.o: datam.o pessoasm.o classes/headers/consulta.h classes/consulta.cpp
	$(CX) $(CXXFLAGS) classes/consulta.cpp -o consultam.o	

clean:
	rm -f *.o gestao

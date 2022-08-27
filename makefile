CC= g++
WFLAGS= -Wall -Wconversion -Werror -Wtype-limits -pedantic -O0

compilar:
	$(CC) garment.cpp laundry.cpp main.cpp -o lavados -g $(FLAGS) 

exe: compilar 
	./lavados

exe_valgrind: compilar
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lavados

compilar_gdb:
	$(CC) -g garment.cpp laundry.cpp main.cpp  $(FLAGS) -o lavados.exe

gdb: compilar_gdb
	gdb lavados.exe

clean:
	$(RM) -f lavados

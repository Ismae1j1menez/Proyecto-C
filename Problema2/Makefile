GNUcompiler := gcc
C_Files1 := shortest_path.c
C_Files2 := Problema2.c
Executable1 := exe1
Executable2 := exe2

all: compile_all

compile_all: p1 p2 p3

p1: $(C_Files1)
	$(GNUcompiler) $(C_Files1) -o $(Executable1)
	./$(Executable1)

p2: $(C_Files2)
	$(GNUcompiler) $(C_Files2) -o $(Executable2) -lm 
	./$(Executable2)

p3:
	# Comandos para compilar problem3

clean:
	rm -f $(Executable1) $(Executable2)
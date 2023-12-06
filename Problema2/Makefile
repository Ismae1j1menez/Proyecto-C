GNUcompiler := gcc
C_Files1 := shortest_path.c
C_Files2 := Problema2.c
Executable := exe

all: compile_all

compile_all: p1 p2 p3

p1: $(C_Files1)
	$(GNUcompiler) $(C_Files1) -o $(Executable)
	./$(Executable)

p2: $(C_Files2)
	$(GNUcompiler) $(C_Files2) -o $(Executable) -lm
	./$(Executable)

p3:
	# Comandos para compilar problem3

clean:
	rm -f $(Executable)
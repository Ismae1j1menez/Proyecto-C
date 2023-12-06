GNUcompiler := gcc
C_Files1 := proyecto1.c
C_Files2 := proyecto2.c
C_Files3 := proyecto3.c
Executable := exe

all: compile_all

compile_all: p1 p2 p3

p1: $(C_Files1)
	$(GNUcompiler) $(C_Files1) -o $(Executable)
	./$(Executable)

p2: $(C_Files2)
	$(GNUcompiler) $(C_Files2) -o $(Executable) -lm
	./$(Executable)

p3: $(C_Files3)
	$(GNUcompiler) $(C_Files3) -o $(Executable)
	./$(Executable)

clean:
	rm -f $(Executable)
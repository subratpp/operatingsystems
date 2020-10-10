all: prog1 prog2 prog3 prog4 prog5
	@echo ">> Change DEBUG to 1 in programs for debugging <<"

prog1: prog1.c
	 @gcc  prog1.c -o prog1.out
	 @echo "1. prog1 compiled. Run ./prog1.out <Number>"

prog2: prog2.c
	 @gcc  prog2.c -o prog2.out -lrt
	 @echo "2. prog2 compiled. Run ./prog2.out <Number>"

prog3: prog3.c
	 @gcc  prog3.c -o prog3.out
	 @echo "3. prog3 compiled. Run ./prog3.out"

prog4: prog4.c
	 @gcc  prog4.c -o prog4.out
	 @echo "4. prog4 compiled. Run ./prog4.out in.txt out.txt"

prog5: prog5.c
	 @gcc  prog5.c -o prog5.out
	 @echo "5. prog5 compiled. Run ./prog5.out segID"

clean: 
	rm -rfv *.out
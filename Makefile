all:
	gcc MT25092_Part_A_Program_A.c MT25092_Part_B_Workers.c -o programA -lm
	gcc MT25092_Part_A_Program_B.c MT25092_Part_B_Workers.c -o programB -lpthread -lm

clean:
	rm -f programA programB

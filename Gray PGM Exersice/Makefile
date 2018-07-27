PGM_PROJECT: main.o q1.o q2.o q3.o q4.o q5.o q6.o
	gcc -o PGM_PROJECT main.o q1.o q2.o q3.o q4.o -lm q5.o q6.o

main.o: main.c q1header.h q2header.h q3header.h q4header.h q5header.h q6header.h
	gcc -c main.c

q2.o: q2.c q2header.h q3header.h q4header.h q5header.h
	gcc -c q2.c

q3.o: q3.c q3header.h
	gcc -c q3.c

q4.o: q4.c q4header.h 
	gcc -c q4.c

q5.o: q5.c q2header.h q3header.h q4header.h q5header.h
	gcc -c q5.c 

q1.o: q1.c q1header.h q2header.h
	gcc -c q1.c

q6.o: q6.c q6header.h q5header.h
	gcc -c q6.c

CC = g++
OBJ = dictionary.o

dictionary: $(OBJ)
	$(CC) $(OBJ) -o $@


.cpp.o : 
	$(CC) -c $<


clean:
	rm *.o dictionary

archive:
	


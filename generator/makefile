CXX = g++
CXXFLAGS = -O3 -Wall -I./include -Os
OPT = -pedantic
EXEC = data_generator
OBJS = configuration.o generator.o main.o

ifeq ($(OS), Windows_NT)
$(EXEC) = data_generator.exe
endif

all : $(EXEC)

generator.o :
	$(CXX) $(CXXFLAGS) -c generator.cpp
	
configuration.o :
	$(CXX) $(CXXFLAGS) -c configuration.cpp
	
main.o : generator.o configuration.o
	$(CXX) $(CXXFLAGS) -c main.cpp
	
$(EXEC) : $(OBJS)
	$(CXX) -o $@ $^
	
clean :
	rm *.o $(EXEC) 
tar :
	tar cfv data_generation.tar configuration.h configuration.cpp generator.h generator.cpp main.cpp \
							calculate_average.py
							
stat :
	python3 calculate_average.py 100

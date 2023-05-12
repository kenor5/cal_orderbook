# Makefile of oddmap-demo

CC = g++
O = ./bin
# set O3 to avoid all optimization
OPT_LEVEL = -O3
COMPILE = $(CC) $(OPT_LEVEL) -std=c++11

SOURCE = src/calculate.cpp src/getbasic.cpp src/main.cpp

OBJS = $(patsubst %.cpp,$O/%.o,$(SOURCE))

INCS = $(wildcard include/*.h)


all : csob

csob : $(OBJS)  
	$(COMPILE) -o $@ $^ 

$O/main.o : src/main.cpp $(INCS)
	$(COMPILE) -c $< -o $@ 

$O/calculate.o : src/calculate.cpp $(INCS)
	$(COMPILE) -c $< -o $@

$O/getbasic.o : src/getbasic.cpp $(INCS)
	$(COMPILE) -c $< -o $@



#if you add any *.cpp to the project, you should add a line like lines upon and add the *.h to main.cpp
.PHONY : clean
clean : 
	rm -f $O/*.o ./store ./csob ./test *.o

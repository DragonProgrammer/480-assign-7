main.o .d/main.d : main.cpp table.hpp
main.bin: main.o table.o
	$(CXX) $(CXXFLAGS) $(LIBARYFLAGS) -o $@ $^

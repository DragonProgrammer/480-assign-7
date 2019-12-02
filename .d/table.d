table.o .d/table.d : table.cpp table.hpp
table.bin: table.o table.o
	$(CXX) $(CXXFLAGS) $(LIBARYFLAGS) -o $@ $^
table.bin: table.o table.o
	$(CXX) $(CXXFLAGS) $(LIBARYFLAGS) -o $@ $^

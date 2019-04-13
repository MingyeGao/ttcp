CXXFLAGS=-g

all:ttcp.cc
	g++ $(CXXFLAGS) -o ttcp ttcp.cc
clean:
	rm ttcp

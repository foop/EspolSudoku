CXXFLAGS=-I/opt/local/include
LDFLAGS=-L/opt/local/lib

all: test_all

test_all: testrunner.o testlibvalidate.o ../../lib/libvalidate.o
	      $(CXX) -o $@ $^ $(LDFLAGS) -lboost_unit_test_framework

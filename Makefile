CXX = g++
CXXFLAGS = -std=c++17 -I.

SOURCES = network.cpp
HEADERS = network.h types.h

all: reader

reader: main.cpp mainwindow.cpp $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o reader.exe main.cpp mainwindow.cpp $(SOURCES)

autotest:
	g++ -I. -I/usr/local/include -std=c++17 -o /repo/test_runner /tester.cpp /usr/local/lib/libgtest_main.a /usr/local/lib/libgtest.a $(SOURCES)

clean:
	rm -f reader.exe test_runner
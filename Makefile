# Makefile for GTFS Explorer project

# Variables
TARGET = gtfs_explorer
SOURCES = main.cpp mainwindow.cpp network.cpp CSVReader.cpp
HEADERS = mainwindow.h network.h types.h CSVReader.h

# Default rule - create project file and build
all: $(TARGET).pro
	qmake $(TARGET).pro
	make

# Create Qt project file
$(TARGET).pro:
	@echo "QT += core gui widgets" > $(TARGET).pro
	@echo "CONFIG += c++17" >> $(TARGET).pro
	@echo "TARGET = $(TARGET)" >> $(TARGET).pro
	@echo "SOURCES += $(SOURCES)" >> $(TARGET).pro
	@echo "HEADERS += $(HEADERS)" >> $(TARGET).pro

# Rule for building test runner (required by assignment)
test_runner: tester.cpp network.cpp
	g++ -I. -I/usr/local/include -std=c++17 -o test_runner /usr/local/lib/libgtest_main.a /usr/local/lib/libgtest.a tester.cpp network.cpp CSVReader.cpp

# Auto test target as required by the assignment
autotest: test_runner
	./test_runner

# Clean rule
clean:
	-rm -f $(TARGET) $(TARGET).pro Makefile.*
	-rm -f *.o moc_*.cpp ui_*.h qrc_*.cpp test_runner

.PHONY: all clean autotest
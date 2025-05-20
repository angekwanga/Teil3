# Makefile for GTFS Explorer project

# Include Qt build system
include $(shell qmake -query QT_INSTALL_PREFIX)/mkspecs/features/default_pre.mk

# Qt modules needed
QT = core gui widgets

# Files to include
SOURCES = main.cpp mainwindow.cpp network.cpp
HEADERS = mainwindow.h network.h types.h

# Target name
TARGET = gtfs_explorer

# Compiler flags
QMAKE_CXXFLAGS += -std=c++17

# Default rule
all: qmake_all
	$(MAKE) -f $(MAKEFILE)

# Build the application using qmake
qmake_all:
	qmake -o $(MAKEFILE) $(TARGET).pro

# Generate project file for qmake
$(TARGET).pro: 
	@echo "QT += $(QT)" > $(TARGET).pro
	@echo "SOURCES += $(SOURCES)" >> $(TARGET).pro
	@echo "HEADERS += $(HEADERS)" >> $(TARGET).pro
	@echo "TARGET = $(TARGET)" >> $(TARGET).pro
	@echo "CONFIG += c++17" >> $(TARGET).pro

# Clean rule
clean:
	-rm -f $(TARGET) $(TARGET).pro $(MAKEFILE)
	-rm -f *.o moc_*.cpp ui_*.h qrc_*.cpp

# Rule for running tests
test_runner: tester.cpp network.cpp
	g++ -I. -I/usr/local/include -std=c++17 -o test_runner /usr/local/lib/libgtest_main.a /usr/local/lib/libgtest.a tester.cpp network.cpp

# Auto test target as required by the assignment
autotest: test_runner
	./test_runner

.PHONY: all clean qmake_all autotest
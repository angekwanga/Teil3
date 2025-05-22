BEWERTUNG: 100

# Auswertung der Abgabe

- Status: Abgabe wurde bewertet
- Punkte: **100** von **100**

## Test 1

- Test: *Erforderliche Dateien sind vorhanden*
- Beschreibung: Das erforderliche Makefile muss vorhanden sein.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000017
##### Testschritte
- Makefile soll vorhanden sein: OK

## Test 2

- Test: *Qt-Projektdatei ist vorhanden*
- Beschreibung: Eine Projektdatei für das Qt-Projekt zum erstellen mit qmake ist vorhanden.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000252
- Punkte: **1**
##### Testschritte
- Für ./**/*.pro wurde ./gtfs_explorer.pro gefunden: OK

## Test 3

- Test: *Makefile-Target autotest existiert*
- Beschreibung: Das Makefile besitzt ein Target zum kompilieren der Tests.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000079
##### Testschritte
- Inhalt von Makefile prüfen: OK

## Test 4

- Test: *tester.cpp-Datei ist unverändert*
- Beschreibung: Die Datei tester.cpp wurde nicht verändert und ist genau so wie im Original-Repository.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000082
##### Testschritte
- Hash-Test von tester.cpp auf ['06a72f969e0658dace6443dcfb68581b671c51ab', 'e03f3983541ebbfe8db5cf60e44296e3c359619f']: OK

## Test 5

- Test: *Kompilieren der Tests*
- Beschreibung: Mit dem Befehl `make autotest` können die Tests kompiliert werden.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:43.395461
- Punkte: **1**
- Return-Code / Fehlercode: `0`
- Kommandozeile: `make autotest`
##### Testschritte
- Rückgabe-Code ist `0`: OK

##### Ausgabe

```g++ -I. -I/usr/local/include -std=c++17 -o test_runner /usr/local/lib/libgtest_main.a /usr/local/lib/libgtest.a tester.cpp network.cpp
./test_runner
Running main() from /usr/src/googletest/googletest/src/gtest_main.cc
[==========] Running 7 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 7 tests from Network
[ RUN      ] Network.getRoutes
[       OK ] Network.getRoutes (5827 ms)
[ RUN      ] Network.getRouteDisplayName
[       OK ] Network.getRouteDisplayName (5824 ms)
[ RUN      ] Network.getTripsForRoute
[       OK ] Network.getTripsForRoute (5789 ms)
[ RUN      ] Network.getTripDisplayName
[       OK ] Network.getTripDisplayName (5778 ms)
[ RUN      ] Network.getStopTimesForTrip
[       OK ] Network.getStopTimesForTrip (5789 ms)
[ RUN      ] Network.getStopById
[       OK ] Network.getStopById (5766 ms)
[ RUN      ] Network.searchStopTimesForTrip
[       OK ] Network.searchStopTimesForTrip (5798 ms)
[----------] 7 tests from Network (40575 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test suite ran. (40575 ms total)
[  PASSED  ] 7 tests.
```

## Test 6

- Test: *Ausführbare Anwendung der Unit-Tests wurde erstellt*
- Beschreibung: Die Anwendung wird mit Unit-Tests kompiliert und erzeugt die geforderte Datei `/repo/test_runner`.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000016
##### Testschritte
- test_runner soll vorhanden sein: OK

## Test 7

- Test: *Ausführbare Anwendung der Unit-Tests enthält die Testfälle*
- Beschreibung: Die geforderte Datei `/repo/test_runner` enthält die `tester.cpp`-Datei.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.208140
- Return-Code / Fehlercode: `0`
- Kommandozeile: `readelf -s --wide /repo/test_runner`
##### Testschritte
- Ausgabe ist korrekt: OK
- Rückgabe-Code ist `0`: OK

##### Ausgabe

```<AUSGABE WIRD NICHT ANGEZEIGT>
```

## Test 8

- Test: *QMake kann ausgeführt werden*
- Beschreibung: qmake erzeugt ein Makefile für die Anwendung
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.277218
- Punkte: **1**
- Return-Code / Fehlercode: `0`
- Kommandozeile: `/usr/bin/qmake6 /repo/./gtfs_explorer.pro`
##### Testschritte
- Rückgabe-Code ist `0`: OK

##### Ausgabe

```Info: creating stash file /repo/build/.qmake.stash
```

## Test 9

- Test: *Erzeugtes Makefile kann die Anwendung erstellen*
- Beschreibung: Das erzeugte Makefile für die Anwendung kann kompiliert werden.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:09.346854
- Punkte: **1**
- Return-Code / Fehlercode: `0`
- Kommandozeile: `make`
##### Testschritte
- Rückgabe-Code ist `0`: OK

##### Ausgabe

```g++ -c -pipe -O2 -std=gnu++1z -Wall -Wextra -fPIC -D_REENTRANT -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I/repo -I. -I/usr/include/x86_64-linux-gnu/qt6 -I/usr/include/x86_64-linux-gnu/qt6/QtWidgets -I/usr/include/x86_64-linux-gnu/qt6/QtGui -I/usr/include/x86_64-linux-gnu/qt6/QtCore -I. -I/usr/lib/x86_64-linux-gnu/qt6/mkspecs/linux-g++ -o main.o ../main.cpp
g++ -c -pipe -O2 -std=gnu++1z -Wall -Wextra -fPIC -D_REENTRANT -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I/repo -I. -I/usr/include/x86_64-linux-gnu/qt6 -I/usr/include/x86_64-linux-gnu/qt6/QtWidgets -I/usr/include/x86_64-linux-gnu/qt6/QtGui -I/usr/include/x86_64-linux-gnu/qt6/QtCore -I. -I/usr/lib/x86_64-linux-gnu/qt6/mkspecs/linux-g++ -o mainwindow.o ../mainwindow.cpp
g++ -c -pipe -O2 -std=gnu++1z -Wall -Wextra -fPIC -D_REENTRANT -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I/repo -I. -I/usr/include/x86_64-linux-gnu/qt6 -I/usr/include/x86_64-linux-gnu/qt6/QtWidgets -I/usr/include/x86_64-linux-gnu/qt6/QtGui -I/usr/include/x86_64-linux-gnu/qt6/QtCore -I. -I/usr/lib/x86_64-linux-gnu/qt6/mkspecs/linux-g++ -o network.o ../network.cpp
g++ -pipe -O2 -std=gnu++1z -Wall -Wextra -fPIC -dM -E -o moc_predefs.h /usr/lib/x86_64-linux-gnu/qt6/mkspecs/features/data/dummy.cpp
/usr/lib/qt6/libexec/moc -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB --include /repo/build/moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt6/mkspecs/linux-g++ -I/repo -I/usr/include/x86_64-linux-gnu/qt6 -I/usr/include/x86_64-linux-gnu/qt6/QtWidgets -I/usr/include/x86_64-linux-gnu/qt6/QtGui -I/usr/include/x86_64-linux-gnu/qt6/QtCore -I. -I/usr/local/include/c++/15.1.0 -I/usr/local/include/c++/15.1.0/x86_64-linux-gnu -I/usr/local/include/c++/15.1.0/backward -I/usr/local/lib/gcc/x86_64-linux-gnu/15.1.0/include -I/usr/local/include -I/usr/local/lib/gcc/x86_64-linux-gnu/15.1.0/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include ../mainwindow.h -o moc_mainwindow.cpp
g++ -c -pipe -O2 -std=gnu++1z -Wall -Wextra -fPIC -D_REENTRANT -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I/repo -I. -I/usr/include/x86_64-linux-gnu/qt6 -I/usr/include/x86_64-linux-gnu/qt6/QtWidgets -I/usr/include/x86_64-linux-gnu/qt6/QtGui -I/usr/include/x86_64-linux-gnu/qt6/QtCore -I. -I/usr/lib/x86_64-linux-gnu/qt6/mkspecs/linux-g++ -o moc_mainwindow.o moc_mainwindow.cpp
g++ -Wl,-O1 -Wl,-rpath-link,/usr/lib/x86_64-linux-gnu -o gtfs_explorer  main.o mainwindow.o network.o moc_mainwindow.o   /usr/lib/x86_64-linux-gnu/libQt6Widgets.so /usr/lib/x86_64-linux-gnu/libQt6Gui.so /usr/lib/x86_64-linux-gnu/libGLX.so /usr/lib/x86_64-linux-gnu/libOpenGL.so /usr/lib/x86_64-linux-gnu/libQt6Core.so -lpthread -lGLX -lOpenGL
```

## Test 10

- Test: *Testfälle werden korrekt ausgeführt*
- Beschreibung: Die Unit-Tests der Anwendung werden korrekt ausgeführt (max. Laufzeit 60 Sekunden).
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:40.696753
- Punkte: **96**
- Return-Code / Fehlercode: `0`
- Kommandozeile: `/repo/test_runner`
##### Testschritte
- Rückgabe-Code ist `0`: OK

##### Ausgabe

```Running main() from /usr/src/googletest/googletest/src/gtest_main.cc
[==========] Running 7 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 7 tests from Network
[ RUN      ] Network.getRoutes
[       OK ] Network.getRoutes (5780 ms)
[ RUN      ] Network.getRouteDisplayName
[       OK ] Network.getRouteDisplayName (5784 ms)
[ RUN      ] Network.getTripsForRoute
[       OK ] Network.getTripsForRoute (5777 ms)
[ RUN      ] Network.getTripDisplayName
[       OK ] Network.getTripDisplayName (5776 ms)
[ RUN      ] Network.getStopTimesForTrip
[       OK ] Network.getStopTimesForTrip (5793 ms)
[ RUN      ] Network.getStopById
[       OK ] Network.getStopById (5795 ms)
[ RUN      ] Network.searchStopTimesForTrip
[       OK ] Network.searchStopTimesForTrip (5785 ms)
[----------] 7 tests from Network (40492 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test suite ran. (40492 ms total)
[  PASSED  ] 7 tests.
```


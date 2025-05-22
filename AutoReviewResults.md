BEWERTUNG: 1

# Auswertung der Abgabe

- Status: Abgabe wurde bewertet
- Punkte: **1** von **100**

## Test 1

- Test: *Erforderliche Dateien sind vorhanden*
- Beschreibung: Das erforderliche Makefile muss vorhanden sein.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000023
##### Testschritte
- Makefile soll vorhanden sein: OK

## Test 2

- Test: *Qt-Projektdatei ist vorhanden*
- Beschreibung: Eine Projektdatei für das Qt-Projekt zum erstellen mit qmake ist vorhanden.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000258
- Punkte: **1**
##### Testschritte
- Für ./**/*.pro wurde ./project.pro gefunden: OK

## Test 3

- Test: *Makefile-Target autotest existiert*
- Beschreibung: Das Makefile besitzt ein Target zum kompilieren der Tests.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000150
##### Testschritte
- Inhalt von Makefile prüfen: OK

## Test 4

- Test: *tester.cpp-Datei ist unverändert*
- Beschreibung: Die Datei tester.cpp wurde nicht verändert und ist genau so wie im Original-Repository.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000101
##### Testschritte
- Hash-Test von tester.cpp auf ['06a72f969e0658dace6443dcfb68581b671c51ab', 'e03f3983541ebbfe8db5cf60e44296e3c359619f']: OK

## Test 5

- Test: *Kompilieren der Tests*
- Beschreibung: Mit dem Befehl `make autotest` können die Tests kompiliert werden.
- Status: ausgeführt
- Erfolgreich: **Nein**
- Laufzeit: 0:00:00.264935
- Punkte: **0**
- Return-Code / Fehlercode: `2`
- Kommandozeile: `make autotest`
##### Testschritte
- Rückgabe-Code ist `0`: fehlgeschlagen

##### Fehlerausgabe

```make: qmake: No such file or directory
Makefile:4: /mkspecs/features/default_pre.mk: No such file or directory
make: *** No rule to make target '/mkspecs/features/default_pre.mk'.  Stop.
```

##### Hinweise zur Behebung des Fehlers

- Stellen Sie sicher, dass der Kompilier-Befehl mit dem angegebenen Befehl aus dem Übungsblatt übereinstimmt.
- Sie dürfen in Ihren C++-Dateien, welche mit kompiliert werden, **keine** eigene main-Funktion haben. Kommentieren Sie diese ggf. aus.
- Entfernen Sie ggf. Dateien mit dem Namen `test_runner` aus Ihrem Repository.


## Test 6

- Test: *Ausführbare Anwendung der Unit-Tests wurde erstellt*
- Beschreibung: Die Anwendung wird mit Unit-Tests kompiliert und erzeugt die geforderte Datei `/repo/test_runner`.
- Status: nicht ausgeführt
- Erfolgreich: **Nein**
##### Hinweise zur Behebung des Fehlers

Der Test wurde nicht ausgeführt, da vorherige Tests fehlgeschlagen sind. Beheben Sie die vorherigen Probleme und versuchen Sie es dann erneut.

## Test 7

- Test: *Ausführbare Anwendung der Unit-Tests enthält die Testfälle*
- Beschreibung: Die geforderte Datei `/repo/test_runner` enthält die `tester.cpp`-Datei.
- Status: nicht ausgeführt
- Erfolgreich: **Nein**
##### Hinweise zur Behebung des Fehlers

Der Test wurde nicht ausgeführt, da vorherige Tests fehlgeschlagen sind. Beheben Sie die vorherigen Probleme und versuchen Sie es dann erneut.

## Test 8

- Test: *QMake kann ausgeführt werden*
- Beschreibung: qmake erzeugt ein Makefile für die Anwendung
- Status: nicht ausgeführt
- Erfolgreich: **Nein**
- Punkte: **0**
##### Hinweise zur Behebung des Fehlers

Der Test wurde nicht ausgeführt, da vorherige Tests fehlgeschlagen sind. Beheben Sie die vorherigen Probleme und versuchen Sie es dann erneut.

## Test 9

- Test: *Erzeugtes Makefile kann die Anwendung erstellen*
- Beschreibung: Das erzeugte Makefile für die Anwendung kann kompiliert werden.
- Status: nicht ausgeführt
- Erfolgreich: **Nein**
- Punkte: **0**
##### Hinweise zur Behebung des Fehlers

Der Test wurde nicht ausgeführt, da vorherige Tests fehlgeschlagen sind. Beheben Sie die vorherigen Probleme und versuchen Sie es dann erneut.

## Test 10

- Test: *Testfälle werden korrekt ausgeführt*
- Beschreibung: Die Unit-Tests der Anwendung werden korrekt ausgeführt (max. Laufzeit 60 Sekunden).
- Status: nicht ausgeführt
- Erfolgreich: **Nein**
- Punkte: **0**
##### Hinweise zur Behebung des Fehlers

Der Test wurde nicht ausgeführt, da vorherige Tests fehlgeschlagen sind. Beheben Sie die vorherigen Probleme und versuchen Sie es dann erneut.


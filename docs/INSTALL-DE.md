# Installation von Ultraschall 5

Das Open-Source-Projekt Ultraschall erweitert die kommerzielle Digital Audio Workstation (DAW) REAPER. Ultraschall 5 läuft nur mit der Version REAPER 6.25.

Eine Testversion von REAPER ist _uneingeschränkt 60 Tage lauffähig_, danach fallen einmalig 52 € Kosten an.

Ultraschall selbst ist kostenlos und Open-Source.

Die Installation von Ultraschall umfasst **zwei zwingend notwendige Schritte (Windows: 3)**.

--

# macOS ab 10.11

# 1.

## REAPER aktualisieren / installieren

 Seit Version 6 wird für REAPER eine spezielle Version angeboten, die für alle MacOS ab Catalina zusätzliche Lizensierungen enthält. Ferner gibt es eine hoch optimierte Version für Apple Silicon M1 Rechner (ARM). Es ist unbedingt die passende Version zu wählen: 

[**REAPER Version v6.25 OS X 64-bit herunterladen**](https://www.reaper.fm/files/6.x/reaper625_x86_64.dmg)  

[**REAPER Version v6.25 OS X 64-bit Catalina/Big Sur herunterladen**](https://www.reaper.fm/files/6.x/reaper625_x86_64_catalina.dmg)

[**REAPER Version v6.25 OS X 64-bit ARM für Apple Silicon herunterladen**](https://www.reaper.fm/files/6.x/reaper625-beta_arm64.dmg)


* Das `.dmg` laden und starten, dann REAPER installieren bzw. auf die Version 6.25 aktualisieren.
* Der Einsatz jeder anderen Version von REAPER führt dazu, dass das Ultraschall-Plugin nicht gestartet wird. Von einem manuellen Update von REAPER auf eine andere Version als 6.25 ist daher zwingend abzusehen.

# 2.

## Ultraschall laden und den Ultraschall-Installer starten.

Unsere Ultraschall 5 Distribution laden und das `.dmg` starten:

[**Ultraschall 4 herunterladen**](http://url.ultraschall-podcast.de/us5mac)

* Im sich öffnenden Fenster unser Installationsprogramm `Ultraschall-5.0.pkg` starten und durchlaufen lassen.
* **Achtung:** Sollte die Installation am Ende eine Fehlermeldung ausgeben, bitte einmal macOS neu booten und den Installer erneut durchlaufen lassen.
* Danach die REAPER App aus dem Program-Verzeichnis starten - Ultraschall 5 startet.

&nbsp;

---

## Erfolg der Installation kontrollieren

* Bei Fehlermeldungen bitte prüfen, ob wirklich die Version 6.25 von REAPER installiert wurde (Schritt 1). Im Zweifel REAPER noch einmal installieren.
* Es kann weiterhin helfen, den Rechner neu zu starten sowie die `Erste Hilfe` im Festplattendienstprogramm von macOS durchlaufen zu lassen.
* Falls immer noch Probleme auftreten oder eine sehr alte Installation (vor 3.0) aktualisiert werden soll, empfiehlt es sich, die im `.dmg` liegenden Skripte `Uninstall.command` sowie `Remove legacy audio devices.command` durchlaufen zu lassen und den Rechner neu zu starten. Danach die Schritte 1 und 2 wiederholen.
* Sollten _sämtliche dieser Maßnahmen_ nicht zum Erfolg führen, kann man Hilfe in unserem Anwender-Forum erbitten: [Ultraschall im Sendegate](https://sendegate.de/c/ultraschall)
* Zur Handhabung der neuen Funktionen empfehlen wir die Release-Screencast in unserem [Tutorial Bereich](http://ultraschall.fm/tutorials/).

---

## Optional - UltraschallHub installieren

Wenn man in Ultraschall eine rein in Software modellierte SKYPE N-1 Schaltung umsetzen möchte, ist die Installation unserer eigenen Ultraschall Devices Voraussetzung:

* Hierzu das `UltraschallHub.pkg` aus dem `.dmg` Fenster durchlaufen lassen.
* Den Rechner neu starten. Nun sollten die neuen Soundinterfaces in der Audio-Midi-Steuerung von macOS erscheinen.
* Für den Einsatz von StudioLink oder des Ultraschall-Soundboards ist dieser Schritt _nicht_ notwendig und kann ignoriert werden.

---

&nbsp;

# Windows ab Version 10

# 1.

## REAPER aktualisieren / installieren


[**REAPER v6.25 Windows 64-Bit herunterladen**](https://www.reaper.fm/files/6.x/reaper625_x64-install.exe)

* Die `.exe` laden und REAPER installieren bzw. auf die Version 6.25 aktualisieren.
* Der Einsatz jeder anderen Version von REAPER führt dazu, dass das Ultraschall-Plugin nicht gestartet wird. Von einem manuellen Update von REAPER auf eine andere Version als 6.25 ist daher zwingend abzusehen.


# 2.

## Ultraschall laden und den Ultraschall-Installer starten.

Unsere Ultraschall 5 Distribution laden und das `.msi` starten:

[**Ultraschall-5.msi (24.1 MB) herunterladen**](http://url.ultraschall-podcast.de/us5win)

* Den Installer starten und durchlaufen lassen.

# 3.

## StudioLink und das Ultraschall-Soundboard verbinden

* Unser integriertes Soundboard zum Einspielen von Jingles und Ähnlichem, sowie StudioLink (als Alternative zu Skype-Remoterecordings) und StudioLink OnAir wird automatisch installiert. Man muss dies jedoch REAPER einmalig nach der Installation mitteilen:
* Im Menü `Options | Preferences… | Plug-ins/VST` anwählen. Nun rechts oben den Button `Auto-detect` drücken und rechts unten mit `Apply` bestätigen. Die Einstellungen können nun wieder geschlossen werden.

&nbsp;

## Erfolg der Installation kontrollieren

* Bei Fehlermeldungen bitte prüfen, ob wirklich die Version 6.25 von REAPER 64-Bit installiert wurde (Schritt 1). Im Zweifel REAPER noch einmal installieren.
* Es kann weiterhin helfen, den Rechner neu zu starten.
* Sollten _sämtliche dieser Maßnahmen_ nicht zum Erfolg führen, kann man Hilfe in unserem Anwender-Forum erbitten: [Ultraschall im Sendegate](https://sendegate.de/c/ultraschall)
* Zur Handhabung der neuen Funktionen empfehlen wir die Release-Screencast in unserem [Tutorial Bereich](http://ultraschall.fm/tutorials/).

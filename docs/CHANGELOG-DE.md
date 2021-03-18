# Ultraschall Changelog

Die nachfolgenden Features werden ausführlich in unseren Ultraschall-Tutorial-Videos erklärt: [https://ultraschall.fm/tutorials/](https://ultraschall.fm/tutorials/)

## 5.0 Marianne Brandt - 2021-03-xx

## System

- REAPER: **Unterstützung der Version 6.25**  
_Ultraschall 5.0 ist für die Version 6.25 von REAPER optimiert. Alle anderen Versionen sind nicht lauffähig. Von einem manuellen Update von REAPER ist daher in Zukunft unbedingt abzusehen, die Ultraschall-Erweiterungen werden dann deaktiviert._

- Apple Silicon: **Optimiert für M1 Macs und MacOs Big Sur**  
_Ultraschall 5 ist bis in die Haarspitzen optimiert für die M1 Prozessoren von Apple. Sämtliche Komponenten laufen nativ auf der ARM-Architektur._

- StudioLink: **Aktuelle Versionen von StudioLink und StudioLink OnAir**

- API: **Update der Ultraschall API auf Version 4.2.003**  
_mit 1.385 LUA-Funktionen um Podcasting-Features in REAPER komfortabler programmieren zu können._

## Installer

- **1Klick Installer**  
_Der bisherige Schritt, die Theme-Datei in ein geöffnetes REAPER-Fenster fallen zu lassen, entfällt._

- **Sicherung von Profilen**  
_Während des Setups werden die alten Einstellungen gesichert - es ist damit grundsätzlich möglich, den Zustand einer vorherigen Installation wiederherzustellen oder auch nachträglich etwa Projektvorlagen zu kopieren. Unter MacOS sind sie in `~/Library/Application Support/Ultraschall/Backups`und unter Windows unter `%APPDATA%\Roaming\Ultraschall\Backups`_ 

## Theme

- Design: **Ultra Gray**  
_Die Ultraschall-Fenster Settings, Soundcheck, Marker-Dashboard und Export-Assistent folgen nun einer einheitlichen Bedien- und Formensprache. Noch grauer als Space Gray: ULTRA GRAY! (danke an @twittlik). Gleichzeitig wurde der Ressourcenverbrauch aller Fenster auf 10% des bisherigen Wertes reduziert - die Lüfter eurer Laptops bleiben nun aus._

- Theme: **Dark Mode für MacOS**  
_Der Dark Mode von MacOS wird nun unterstützt. Dies muss in den REAPER Settings unter `General/Advanced UI` aktiviviert werden. Achtung: ein Mischbetrieb ist leider nicht möglich, bei einem Wechsel zum Light-Theme muss das Setting wieder deaktiviert werden._

- Buttons: **Bereinigung der Buttons in der Export-Leiste**  
_Der oberste Button startet nun das Marker Dashboard , der Listen-Button startet den Export-Assistent._

- Buttons: **Konsistentz**  
_Gelbe Buttons sind nun den äußeren Kontrollflächen vorbehalten. Die FX-Buttons der Kanäle leuchten nun Blau. Aus den Mixer Control Panels (MCP) wurden die redundanten Solo- und Mute-Buttons entfernt._

## User Interface

- MacOS: **Optimierung der Fluppdizität**  
_Deutlich flüssigeres Scroll- und Zoomverhalten der Timeline sowie der Pegelanzeigen unter MacOS, sofern `Metal` unterstützt wird und ein hochauflösendes Trackpad eingesetzt wird._

- **Automatisches Layout und Einfärbung**  
_In den Settings sind zwei neue Komfort-Funktionen aktiv: automatische Spureinfärbung und automatische Trackhöhe_
  - _Die automatische Spureinfärbung funktioniert ähnlich wie der bekannte `Sonic Rainboom`, aber automagisch im Hintergrund. Normale Spuren erhalten Farben aus dem blauen Spektrum, Remote-Spuren (StudioLink) startet bei Orange. Das Soundboard wird Grau._
  - _Die automatische Trackhöhenanpassung passt die Höhe aller Spuren so an, dass immer alle Spuren sichtbar sind. Die Neuberechnung erfolgt, wenn sich die Spuranzahl ändert, Envelopes sichtbar/unsichtbar geschaltet werden oder man den Shortcut `alt`+`z` verwendet._

- **Dialoge mit Shortcuts schließen**  
_Alle Ultraschall-Dialoge wie Color-Picker oder Marker-Dashboard sind nun mit `Cmd`+`w` / `Alt`+`F4` schließbar. Alternativ kann auch die `esc` Taste verwendet werden._

- **Persistenz der Button-Zustände**  
_Die Buttons in den Bereichen Views, Routing, Mouse-Selection und Followmode zeigen nun immer korrekt den aktuellen Status auch - auch nach neu Laden eines Projektes oder dem Wechsel zwischen verschiedenen parallel geöffneten Projekten._

- **Direktverlinkungen im Welcome Screen**  
_Die auf dem Startscreen vorgestellten Features verlinken nun direkt auf die jeweilige Stelle im Kurz-Tutorial._

- **Erweitertes Podcast-Menü**  
_Das Podcast-Menü wurde um etliche neue Einträge erweitert, etwa solche, die sich auf selektierte Items oder Hilfe und Dokumentation beziehen._

- **Automatisches Speichern**  
_Auf vielfachen Wunsch wird nun alle 10 Minuten eine Sicherheitskopie der Projektdatei (nicht: der Audiofiles, die ohnehin nie verändert werden) im Projektordner abgelegt. Der Name enthält den Zeitstempel so dass man sich im Notfall schnell orientieren kann. Die Sicherheitskopien sind mit Zeitstempel im Namen versehen und im im Projektverzeichnis - Unterordner `backup` zu finden._

- **Ultraschall Workflows**  
_Zu nicht unbedingt selbsterklärenden, schrittweisen Abläufen gibt es im Podcast-Menü einen neuen Abschnitt `Workflows`, der als Erinnerungsstütze dienen kann. Derzeit werden angeboten:_
  - _Die neue Ultraschall **Automated Mixing Pipeline** (AMP)_
  - _Double-ender_

## Recording

- **Ripple Insert Recording**  
_Wenn man merkt, dass irgendwo in der bestehenden Aufnahme noch ein Satz fehlt, kann man diesen nun schnell hinzu fügen: den Edit-Cursor an die entsprechende Stelle setzen, die benötigten Spuren auf `arm` setzen und dann `cmd/strg`+`alt`+`i` drücken. Es wird sofort "Platz" in der Aufnahme gemacht für den neuen Take, so lange bis man die Aufnahme wieder stoppt. Alle Lücken werden danach automatisch geschlossen. An die Start-Endpositionen werden Edit-Marker gesetzt, damit man die Stelle für ein Finetuning besser wiederfindet._

- **Preroll-Recording**  
_Zuweilen möchte man eine Passage, die nicht perfekt war, neu aufnehmen bzw. "überschreiben". Hierfür bieten wir nun ein Preroll-Recording an: man platziert den Edit Cursor an die Stelle, ab der man neu aufnehmen möchte. Mit `cmd/strg`+`shift`+`r` wird nun um einige Sekunden zurückgesprungen und das Bisherige Audio abgespielt. Wird die zu verändernde Stelle erreicht, wird dort alles Folgende gelöscht und direkt ein neues Recording gestartet. Der Wert, um wieviel Sekunden zurückgesprungen wird, kann in den Ultraschall Settings angepasst werden. Mit `alt`+`shift`+`r` kann man den Cursor an eine beliebige Stelle setzen, von der aus das Vorhören beginnen soll. Letzteres Verhalten kann auch über einen `Soundcheck` gestartet werden: das Preroll-Recording wird angeboten, wenn man innerhalb einer bestehenden Aufnahme auf `Record` drückt._

- **SafeMode wieder eingeschaltet**  
_In der 4.0 ist die Sicherheitsabfrage beim Stoppen einer Aufnahme aus Versehen ausgeschaltet worden. Diese ist nun wieder aktiv und warnt, bevor eine Aufnahme beendet wird. Das Safemode Recording kann über die Ultraschall Settings eingestellt werden._

- **+18dB Check deaktiviert**  
_Der häufiger zu Problemen führende +18dB Check von REAPER (führte zum Auto-muten von Kanälen) ist nun standardmäßig deaktiviert._

- Actions: **togglemute, mute und unmute pro Track**  
_Die ersten 10 Tracks haben nun dedizierte Mute-Actions, die immer muten/unmuten, egal auf welchen Automationmode die Mutespur ist und egal, ob sie gerecarmed sind. Die entsprechenden Actions können über die Actions-Liste (`alt`+`,`) beispielsweise Midi-Noten zugewiesen werden für eine Steuerung über externe Controller._

## Editing

- **Einfache Lautstärkeanpassungen bei Items**  
_Mit dem neuen Shortcut `v` aktiviert man für selektierte Items einen Volume-Envelope, der direkt im Item angezeigt wird. Erstellt man nun innerhalb des Items mit gedrücktem Mauszeiger-Ziehen eine Zeitauswahl, kann man danach den Envelope-Abschnitt in der Mitte greifen und leicht anpassen. Das Ergebnis ist eine sehr schnelle Möglichkeit um komplexe Lautstärkeverläufe einstellen zu können, die auch garantiert stabil am Item verbleiben - vergleichbar zu Hindenburg._

- **Double-ender**  
_Ultraschall 5 bietet im neuen Untermenü `Workflows` des Podcast-Menüs zwei Varianten an, um Double-ender einfacher mit einer zeitlich auseinander laufenden lokalen Spur in Einklang zu bringen:_
  - _**Stretch Marker** können helfen, die Remote-Spur in der Länge an die lokale Spur anzupassen, wenn der Zeitversatz der Remote-Spur konstant ist - also etwa pro Minute der Sendung ein Versatz von einer Sekunde entsteht._
  - _Bei nicht gleichmäßigem Auseinanderlaufen kann der neue **Auto-matching** Workflow helfen, der darauf basiert beide Spuren entlang von Pausen in einzelne Items zu zerschneiden und diese dann auszurichten._

- Wellenformen: **Spektralansicht der Wellenformen**  
_Mit dem Shortcut `cmd`+`shift`+`h` kann nun eine Sprektralansicht der Wellenform umgeschaltet werden. Diese ist ebenso im Podcastmenü (Untermenü "View") sowie im Kontextmenü von Items zu finden. Diese Ansicht hilft dabei, störende Laute wie Poppen, Atmen oder Zischen farblich zu erkennen._

- **Prepare all tracks...**  
_Die nach jeder fertigen Aufnahme auszuführende `prepare all tracks for editing` Funktion setzt nun den neuen Ultraschall AMP Effekt (siehe oben) deaktiviert auf dem Master für das Tuning auf -16 LUFS und fordert ferner zum Speichern auf, sollte dies noch nicht erfolgt sein. Sind Studio-Link Effekte aktiv, wird dazu aufgefordert, zunächst im Webbrowser alle offenen Anrufe zu beenden._

- **Einfacher Ripple-Cut:**  
_Die Taste `Backspace` löst nun einen Ripple-Cut über alle Spuren aus (analog zu `cmd`+`x`), wenn eine Zeitselektion vorliegt. `Del` löscht die Inhalte aus einer Zeitselektion ohne die nachfolgenden Inhalte heranzuschieben._

- **Ripple-Cut mit Kontrolle:**  
_Der Shortcut `alt`+`cmd`+`x` macht einen Ripple-Cut mit nachgelagertem Preview des Schnittes._

- **Vereinfachte Schnittfunktionen mit Mausklick:**  
  - _`shift` + `cmd` + Linksklick auf Item: Kürzt Item unter Mousecursor am Ende_
  - _`shift` + `alt` + Linksklick auf Item: Kürzt Item unter Mousecursor am Anfang_
  - _`cmd` + Doppelklick: Normalisiert selektierte Items auf -23 LUFS_
  - _`cmd` + `alt` + Doppelklick: setzt alle Normalisierungen wieder zurück._

- Actions: **Neue Schnitt-Funktionen**  
_Über die Actions-Liste (`alt`+`,`) stehen neue Schnittfunktionen zur Verfügung, die man sich bei Bedarf auf Shortcuts legen kann:_
  - _Cut all items within time-selection in selected tracks_
  - _Ripple cut in selected tracks, markers stay at their position_
  - _Ripple cut in selected tracks, moving markers_

- **Magnetische Kanten**  
_Nach all den Jahren: endlich konsistente magnetische Snap-Settings für alle Itemkanten, Marker, Regionen. Wirkt sich erst bei in Ultraschall 5 neu erstellten Projekten aus._

## Mixing

- Ultraschall AMP: **Neue Effektkette für -16 LUFS Mastering**  
  - _Bisher wurde der Dynamics 2 Effekt so voreingestellt, das jede einzelne Spur auf - 16 LUFS Lautheit optimiert wurde. Dies konnte jedoch bei sich überlagernden Spuren - etwa bei gemeinsamen lauten Lachen - dazu führen, dass die Summe der Spuren verzerrt und zu laut wird. Zudem war es oft mühsam, für jede Spur den richtigen `Threshold` zwischen Sprache und unerwünschen Störunen (Atmen etc.) einzustellen._
  - _Daher wird nun eine neue, besser klingende unf einfacher zu handhabende Effektkette angeboten: **Ultraschall AMP** (Automated Mixing Pipeline):_
    - _**Schritt 1:** Alle Spuren die Sprache enthalten werden mit einer Automatisierung auf -23 LUFS gebracht_ (vergleichbar zu Hindenburg).
    - _**Schritt 2:** Der bekannte `Ultraschall Dynamics` Effekt kommt mit einem neuen Preset: `-23 input -20 output`, welches die Lautheit der Spursegmente auf -20 LUFS angleicht. Durch die vorherige Normalisierung in Schritt 1 kann in der Regel auf eine Anpassung des `Threshold` verzichtet werden._
    - _**Schritt 3**: Die fehlenden LUFS Lautheit auf das gewünschte Target (empfohlen für Podcasts: -16 LUFS) erreicht man, indem man den neuen `LUFS Loudness Metering` Effekt auf dem Masterkanal aktiviert. Dieser Effekt visualisiert zum einen die `integrated LUFS` im Zeitverlauf. Je länger die Messung andauert, desto genauer der Mittelwert. Mit `Reset` kann die Messung neu gestartet werden, mit der Auswahl `Target` können verschiedene Lautheits-Profile ausgewählt werden. Eine Umschaltung führt direkt zu einer Anhebung bzw. Absenkung der Lautheit. Ein Korridor von +/- 1 LUFS visualisiert, ob der Podcasts sich innerhalb des gewünschten Ziels bewegt. Blau bedeutet dabei zu leise, Grün genau richtig, Gelb etwas und Rot deutlich zu laut._
    - _**Schritt 4** (optional): sollte die Automatik doch einmal daneben liegen, kann die Lautheit über einen *Gain* Regler korrigiert oder mit einer `Match Gain` Funktion automatisch angepasst werden._

- Effekte: **Neue Effektsammlung für Spuren**  
_Bei neu angelegten Spuren werden nun standardmäßig diese Effekte in der richtigen Reihenfolge (deaktiviert) geladen:_
  - _DeNoise (der ReaFir Rauschfilter zum Anlernen von Rauschprofilen)_
  - _DeEsser (ein Multiband-Kompressor zum Reduzieren von Zischlauten)_
  - _ReaEQ (Multiband EQ mit verschiedenen Presets, etwa auch "Telefon-Sound"_
  - _Ambience (Ein Raumsimulator mit verschiedenen Presets, etwa Studio oder Kirche)_
  - _Ultraschall Dynamics 2 (Anpassung der Lautheit eines Tracks und Expander)_

  _Die Effekte sind zunächst deaktiviert. Sie sollten - mit Ausnahme des Dynamics 2 - nur maßvoll angewandt werden und nur dann, wenn auch wirklich Probleme zu beheben sind. Bei sehr gutem Ausgangsmaterial führen Filter ansonsten eher zu einer Verschlechterung der Klangqualität._

- Effekte: **Best-of-Breed Sammlung**  
_In einem neuen Ordner "Best-of-Breed" werden einige herausragende, freie Effekte angeboten:_
  - _**ReEQ** (Equalizer, der an Fabfilter angelehnt ist)_
  - _**Smooth Limiter** (Limiter der Extraklasse, der sehr anschaulich den Grad des Eingreifens visualisiert und auch im neuen LUFS Loudness Metering Effekt verbaut ist - pures Audio-Gold)_
  - _**Spectrum Matcher** (EQ mit Lernfunktion, um den Klang von Mikros aneinander anzupassen)_
  - _**TriLeveler2** (Gute Alternative zu unserem Dynamics 2 Effekt)_
  - _**ReaXcomp** (Grafischer Multiband-Kompressor der Spitzenklasse)_

## Export

- Assistent: **Erweiterter Export-Assistent**  
_Der Export-Assistent wurde um ein Ampel-System erweitert, das noch fehlende oder unvollständige Metadaten anzeigt. Wenn noch Edit-Marker im Projekt sind, wird dies mit einer gelben Warnlampe bei den Markern quittiert._

- Episodenbilder: **Drag-and-Drop**  
_Episodenbilder können nun im Export-Assistent direkt per Drag-and-Drop eingefügt werden. Es gibt ferner vier Speicherplätze, in denen man die Cover für unterschiedliche Podcasts hinterlegen kann - um diese dann mit einem Klick für den jeweilig aktuellen Podcast zu aktivieren._

- Rendering: **Ultraschall-Render-Presets nun im Menü auswählbar**  
_Man kann nun im File- und im Podcast-Menu ein Untermenü aufrufen, in welchem man den Render to File-Dialog gleich mit richtigem Render-Preset öffnen kann. Unterstützt werden unsere Standard-Render-Presets wie MP3 (mit Kapiteln, Kapitelbildern und - URLs), Auphonic Multichannel und m4a._

- Render Dialog: **Presets optimiert**  
  - _Auphonic Multichannel erhält das Namensschema `$project-$tracknumber-$track`, MP3 und M4A `$project` für die Dateien._
  - _Mono-Tracks werden immer als Mono gerendert._

- Routing-Check: **Umstellen des Routings**  
_Vor jedem Export wird geprüft, ob das Routing auf `Schnitt` steht, damit alle Spuren in den Export einfließen._

- Render Settings: **Optimierung für Apple Silicon**  
_Für den Rendering-Buffer wird der Wert 4096 gesetzt, was insbesondere auf Apple Silicon Macs die Rendergeschwindigkeit dramatisch anhebt (bis zu Faktor 5)_

## Shortcuts

- Global Shortcuts: **Etliche Tastaturshortcuts sind nun auf global gesetzt**  
_Je nach Tastaturfokus konnte es sein, dass Tastaturshortcuts nicht reagiert haben oder anders reagiert haben, als man es gewohnt war. Jetzt sind viele Shortcuts so eingestellt, dass sie auch dann funktionieren, wenn man z.B. etwas im Soundboard angeklickt hat. Dies sollte typische Probleme lösen, wie das nicht reagieren von Shortcuts fürs Marker setzen._

- **Übersicht sämtlicher Shortcuts**  
_Im neuen Menüpunkt "Help and Documentation" im Podcast-Menü ist eine automatisch generierte, durchsortierte Liste sämtlicher (!) aktiver Shortcuts und Maus-Modifier zu finden_

- **Aktuelles Projekttab schließen**  
_ist auf dem Mac nun mit `cmd`+`w` möglich._

- **Dynamic Split Items**  
_Die Funktion Dynamic Split Items ist nun wieder direkt über den Shortcut `cmd/strg`+`shift`+`d` zu erreichen._

- **Normalisierung**  
_Der Shortcut `opt`+`shift`+`n` normalisiert selektierte Items auf -23 LUFS. Mit `cmd` + `shift` + `n` wird jegliche Normalisierung aufgehoben._

- **Glue Items**  
_Der Shortcut `cmd`+`shift`+`g` führt nebeneinander liegende Items zu einem großen Item zusammen. Praktisch, wenn man etwa unterschiedlich laut aufgenommene Abschnitte einer Spur zerschnitten hat um sie separat auf -23 LUFS zu normalisieren, danach aber wieder als ein Item im Schnitt behandeln will. Es wird eine neue Audio-Datei im Format WavPack 32-Bit float geschrieben._

## Navigation

- **Optimierung der Trackpad-/Mausradfunktionen**  
_Trackpads und Mausrad kommen sich leider in den Belegungen in die Quere. Das Mausrad hat nun folgende Belegungen, die so auch in nahezu allen anderen Schnittprogrammen zu finden sind:_
`Scroll` - Verikales Scrollen des Arbeitsbereichs
`Scroll` + `Shift` - Horizontales Scrollen des Arbeitsbereichs
`Scroll` + `Alt` - Horizontaler Zoom
`Scroll` + `cmd/strg` - Vertikaler Zoom
`Klick`+ `Drag` - Freies Verschieben des Arbeitsbereichs
`Klick` - Setzt den Edit-Cursor ohne Auswahl von Spuren/items_

- **Schnitte Prüfen**  
_Die Shortcuts `alt`+`cmd`+`left` und `alt`+`cmd`+`right` springen zur nächsten Itemkante (bei ausgewählten Tracks nur auf ebendiesen), springen dann noch um den in den Ultraschall Sttings angegebenen Wert des Previews zurück und spielen den Schnitt dann ab. Perfekt zum schnellen Kontrollieren aller Schnitte in einem Projekt._

- **Zoom auf Auswahl und zurück**  
_Der Shortcut `shift`+`z` zoomt den Arrangeview auf eine Zeitauswahl oder auf selektierte Items. Die Auswahl wird dann aufgehoben. Bei nochmaligem Drücken wird auf die ursprüngliche Zoomstufe zurück gesprungen._

- **Zoom auf Edit-Cursor**  
_Mit `cmd/strg`+`Pinch` auf dem Trackpad wird nicht an die Position des Mauszeigers gezoomt, sondern an die des Edit-Cursors._

## Soundcheck 2

- Soundcheck: **Runderneuerung**  
_Der Ultraschall-Soundchek wurde im Vergleich zur 4er Version an viele Stellen optimiert: Es werden nur noch die akuten oder pausierten Problembereiche angezeigt, nicht mehr die unproblematischen; eine Erläuterung des jeweiligen Problems ist nun immer sichtbar; der `Ignore` Button wurde von den Buttons zur Problemlösung getrennt; die Fensterposition wird gespeichert; über die Ultraschall-Settings kann der Modus "Graceful Soundcheck" aktiviert werden: schließt man das Soundcheck-Fenster trotz offener Probleme, werden diese auf den Status `Ignored` gesetzt; die Logik hinter einigen Soundchecks wurde optimiert; Falsche Blocksize und unbekannte Soundinterfaces werden nun in der Titelzeile des entsprechenden Soundchecks angezeigt._

- Setup: **Automatische Zuweisung von Inputs**  
_Ein neuer Soundcheck prüft, ob:_
_a) mehrere Spuren denselben Input-Kanal eines Soundinterface nutzen und_
_b) bei einem angeschlossenen Zoom Interface (H4, H5, H6) die ersten beiden Stereo-Aufsatz-Kanäle verwendet werden._  
_Der Soundcheck schlägt an, sobald irgendein Kanal auf Recarm gesetzt wird. Es wird eine Autoassign-Funktion angeboten, die sämtlichen normalen, lokalen Spuren (nicht: Soundboard und StudioLink) aufsteigenden Input-Kanälen zuweist. Im Falle der Zoom-Interfaces starten diese mit Kanal 3. Die neue Autoassign-Funktion kann unabhängig vom Soundcheck auch im Bereich Setup des Podcast-Menüs aufgerufen werden._

## Marker

- Marker Dashboard 2: **Erweiterte Funktionen**  
_Das Marker Dashboard (`alt`+`shift`+`m`) kann nun in der Höhe verändert werden, so dass mehr Marker sichtbar sind. Ferner wurde eine Blätterlogik eingefügt, so dass beliebig viele Marker bearbeitet werden können. Ein selektierter Marker kann nun auch im Dashboard gelöscht werden. Kapitelbilder werden mit einer Vorschau angezeigt, ein Klick darauf startet die Vollansicht. Ein Hilfebutton erläutert eventuell auftretende Probleme. Die Funktion zum Speichern von Markern in einer Textdatei findet sich nun ebenfalls im Marker Manager._

- **Nächsten Marker auf "planned" setzen**  
_Im Podcast-Menü gibt es unter `Recording/Markers` den neuen Eintrag `Set next marker to planning stage`. Dieser setzt den nächsten normalen Kapitel-Marker rechts vom Cursor auf den Status "planned"._

- Settings: **Lautstärke der Kapitelglocke**  
_Die Lautstärke der Kapitelglocke in den Ultraschall Settings wird nun nicht mehr linear, sondern logarithmisch eingestellt - dies erleichtert die Einstellung von niedrigen Lautstärken._

- Settings: **Mehr Platz für Marker**  
_Mit der Option "Large marker manager" in den Ultraschall Settings wird der REAPER eigene marker manager im View recording groß an der rechten Fensterseite angezeigt._

- **Marker mit Namen**  
_Wenn mit `shift`+`m` Kapitelmarken mit Namen eingefügt werden, hat man deutlich mehr Platz den Namen zu editieren._

## Ultraschall Dashboard

- **Dashboard statt Ultraclock**  
_Die Ultracklock wurde umbenannt in Dashboard und zeigt nun erweiterte Funktionen an:_
  - _Im unteren Bereich immer den aktuellen Status der **Soundchecks** an (Passed, Ignored, Warning). Ein Klick darauf startet das Soundcheck-Fenster._
  - _Eine **Time Selection** wird im Dashboard standardmäßig angezeigt, aber nur wenn es auch eine gibt._
  - _Ist der neue **LUFS Metering** Effekt auf dem Masterkanal aktiv, so wird dessen aktueller Messwert im Dashboard angezeigt. Mit einem Klick kann der Effekt angezeigt werden._

## Magic Routing

- Routing: **Automagisches Umschalten**  
_Ist Magic Routing aktiviert, so springen die Routings-Presets nun automatisch um: Wird eine Aufnahme gestartet, wird das Preset `Recording` ausgewählt. Wird eine bereits erfolgt Aufnahme abgehört (Play), so wird das Preset `Schnitt` ausgewählt. Wurde das Preset `Preshow` ausgewählt, bleibt dieses erhalten bis man manuell auf `Recording` umschaltet._

- Bugfix: **Kein erneutes Setzen der Routing Matrix vor dem Rendern**  
_So bleiben Custom Routings (speicherbar unter dem Schriftzug-Button `Routing`) auch beim Rendern erhalten._

## Ultraschall Settings

- **Neues Layout**  
_Die Ultraschall-Settings werden nun in drei Tabs organisiert: `General`, `Soundcheck` und `Interfaces`_

- **Slider mit Werten**  
_Die Schieberegler in den Ultraschall Settings zeigen nun sinnvolle Werte - etwa Sekunden - an._

## Interfaces

- Stream Deck: **Support für das Elgato Stream Deck**  
_Ultraschall bietet nun umfassende Unterstützung für das Elgato Stream Deck zur Steuerung beliebiger Funktionen. Eine detailierte Dokumentation wird separat veröffentlicht._

## Bugfixes

- Plugin: **Fehlende Konvertierung des Projektverzeichnisses von UTF-8 nach Windows-1252 beim exportieren von Kapitelmarken**  
_Der Name des Projektverzeichnisses auf Windows wird jetzt richtig konvertiert._

- Button: **Projektordner öffnen erlaubt nun Projektordner mit Umlaut im Namen**  
_Bei Projektordnern, die Umlaut im Pfad oder eigenen Namen hatten, konnte es sein, dass diese mit dem "Open project folder"-Button nicht geöffnet wurden._

- Routing: **Ducking**  
_Im Routing-Preset `Preshow` ist nun das automatische Ducking des Soundboards durch alle anderen Spuren deaktiviert._

- Recording: **Setzen der Playrate**  
_Die Playrate wird erst bei einer realen Aufnahme automatisch auf 1x gesetzt, nicht wie bisher schon beim Scharfschalten ("arm") eines Tracks._

- FX: **Prepare all tracks for editing**  
_Die Funktion `Prepare all tracks for editing` löscht nun auch auf dem Mac zuverlässig den StudioLink OnAir Effekt aus dem Master-Kanal, und nicht mehr nur den ersten sichtbaren Effekt._

## 4.0 Aicher - 2020-03-09

### REAPER

- REAPER: **Unterstützung der Version 6.05**
_Ultraschall 4.0 ist für die Version 6.05 von REAPER optimiert. Alle anderen Versionen sind nicht lauffähig._ **Von einem manuellen Update von REAPER ist daher in Zukunft unbedingt abzusehen**, _die Ultraschall-Erweiterungen werden dann deaktiviert._

- SWS: **SWS Version 2.11**
_Ultraschall enthält nun die Version 2.11.0 des SWS Plug-ins._

### MagicRouting

- MagicRouting: **Automatisiertes Routing**
_Mit den neuen MagicRouting Buttons links im Bereich Routing entfällt das manuelle setzen der Routing-Matrix vollständig. Grundsätzlich bietet MagicRouting zwei verschiedene Modi: Vollautomatisch und Halbautomatisch.
Man schaltet den Modus um, indem man den Zauberstab aktiviert (vollautomatisch) oder deaktiviert (halbautomatisch). Der Standardwert für ein neues Projekt ist vollautomatisch, Routing-Preset: Recording.

    Es werden drei Routing-Presets ausgeliefert, die über die drei Buttons unter dem Zauberstab umgeschaltet werden können:

    **Preshow:** Macht dann Sinn, wenn über `StudioLink OnAir` gestreamt wird und ferner ein Ùltraschall Soundboard` aktiv ist. Dieses Preset bildet die Situation ab, dass vor Sendungsbeginn der Stream über das Soundboard schon mit Musik versorgt wird, die Stimmen der Podcaster jedoch noch nicht "OnAir" sind. Alle Podcastenden sollen sich jedoch schon untereinander hören, ebenfalls auf Wunsch leise die Musik. Im Detail:
  - Das Routing der StudioLink-Spuren wird automatisch eingestellt
  - Das Soundboard geht als einziger Track auf den Master und ist damit im Stream zu hören.
  - Alle anderen Spuren hören sich nur lokal, aber gehen nicht auf den Stream (kein Send auf den Master)
  - Man kann über die neuen Ultraschall-Settings (`shift`+`,`) einstellen, ob im lokalen Kopfhörer-Mix auch ein Anteil der Soundboard(Musik)-Spur zu hören sein soll um sich etwas einzustimmen.

  **Recording:** Die Normale Aufnahmesituation
  - Ist der Preset beim neu Anlegen eines Projektes
  - Alle Spuren gehen auf den Master und damit auf einen möglichen Stream
  - Das Routing der StudioLink-Spuren wird automatisch eingestellt
  - Abhängig davon, ob in den Ultraschall-Settings (`shift`+`,`) für das gerade aktive Soundinterface `Lokales Monitoring` aktiviert (Preset) oder deaktiviert ist, gehen die lokalen Spuren in den Kopfhörer-Mix oder nicht.

  **Editing**: Das Preset für Schnitt und Mastering der Aufnahme
  - Alle Spuren gehen auf den Master (wichtig für den Export)
  - Der Master geht in den Kopfhörer-Mix

  #### Umschaltung
    Folgende Wege gibt es, um die Presets umzuschalten:
  - Jederzeit per Drücken des jeweiligen Buttons
  - Wählt man `Prepare all tracks for editing` aus, wird automatisch auf den Preset `Editing` umgestellt

  #### Ducking
    Für die Presets `Preshow` und `Recording` kann die Sondboard-Spur mit einem Ducking versehen werden. Ist dies in den `Ultraschall-Settings` aktiviert (`shift`+`,`) so fadet das Soundboard automatisiert etwas runter, wenn irgendjemand spricht. Im Preset `editing` ist das Ducking immer deaktiviert.

    #### Manuell/Automatisch
    Ist der Zauberstab aktiviert (Preset), dann wird bei jeder Änderung der Anzahl der Spuren im Projekt die Routing-Matrix entsprechend des gerade ausgewählten Presets neu aufgebaut.
    Ist das Zahnrad deaktiviert, bleibt das Routing in seinem Status Quo - bis es entweder händisch geändert wird oder über einen der Preset-Buttons umgestellt wird.
    Man kann jederzeit zwischen Automatik oder Manuell umschalten.


### Soundcheck

- Soundcheck: **Warnhinweise für diverse Probleme**
_Um diverse Probleme zu vermeiden, gibt es jetzt den Ultraschall Soundcheck. Er meldet sich von selbst, wenn ein Problem vorliegt oder kann manuell über `alt`+`shift`+`,` angezeigt werden. Jeder Soundcheck kann entweder vorübergehend mit `Ignore` ignoriert werden oder in den neuen `Ultrachall Settings` dauerhaft deaktiviert werden. Bei jedem Problem helfen `Call to Action`-Buttons bei der schnellen Lösung des jeweiligen Problems._
_Folgende Situationen werden permanent im Hintergrund überwacht:_

    _**Echo-Warnung:** Wenn das gerade verwendete Soundinterface _kein_ `lokales Monitoring` beherrscht, muss die sogenannte `Block Size` kleiner eingestellt werden um ungewünschte Echo-Effekte zu vermeiden. Sinnvoll sind dann Werte von 64 oder 128, ansonsten empfehlen wir 512 um Verzerrungen zu vermeiden._

    _**Unbekanntes Soundinterface:** Wenn ein Soundinterface zum ersten mal an Ultraschall 4 angeschlossen wird bzw. es nicht in unserer mitgelieferten Datenbank erfasst ist, muss einmalig angegeben werden, ob es `Local Monitoring` unterstützt (siehe `Ultraschall Settings`)_

    _**Internes Mikrofon:** Hiermit wird verhindert, dass aus Versehen mit dem internen Mikro - etwa des Notebooks - aufgenommen wird anstatt mit dem ebenfalls angeschlossenem Soundinterface._

    _**Starte Aufnahme nur am Ende:** Verhindert, dass beim Fortsetzen einer Aufnahme ein bereits aufgenommener Teil überschrieben wird bzw. ein alternativer Take angelegt wird._

    _**Prepare all Tracks for Editing:** Nach jeder Aufnahme kann (und muss!) man hiermit den Modus von Ultraschall von Aufnahme auf Schnitt umschalten._

    _**48KHz Samplerate:** Wenn StudioLink Spuren aktiv sind oder ein StudioLink OnAir Streaming aktiv ist, muss die Samplerate auf 48KHz eingestellt sein um Klangstörungen zu vermeiden._

    _**Nicht gespeichertes Projekt:** So früh wie möglich, in jedem Fall aber vor Beginn der Aufnahme, sollte ein Projekt unter eigenem Namen gespeichert werden._

### Ultraschall Settings

- Settings: **eigene Ultraschall Settings**
_Es gibt jetzt eine zentrale Stelle für Ultraschall-Settings beheimatet im Podcastmenü oder mithilfe des Shortcuts `shift`+`,`. Dort können auf der linken Seite diverse Ultraschall spezifische Einstellungen gemacht werden. Darunter kann jedes Modul des neuen SoundChecks dauerhaft deaktiviert werden. In der rechten Spalte sind alle Soundinterfaces aufgeführt, die bisher an Ultraschall 4 angeschlossen wurden. Für diese kann (und muss! damit MagicRouting funktioniert) einmalig eingestellt werden, ob sie `lokales Monitoring` unterstützen. Einfache Regel: wenn Kopfhörer/Headset zum Abhören an dem Gerät angeschlossen ist, dann muss `local monitoring` aktiviert werden. Mit dem `x`-Button können überflüssige Interfaces aus der Liste gelöscht werden. Mit den richtigen Einstellungen zum lokalen Monitoring in dieser Liste ist es problemlos möglich, den Podcast mit einem dezidierten Soundinterface aufzunehmen, dann aber im Zug auf dem Laptop nur mit der eingebauten Soundkarte zu schneiden - ohne sich um das Routing Gedanken machen zu müssen._

### Soundboard

- Soundboard: **Kontrolle per Nummernblock und Playlist-Feature**
_Das Soundboard ist nun per Nummernblock auf der Tastatur steuerbar(auch mit externem Nummernblock):_
_`1` bis `9` - toggelt Play/Pause der entsprechenden Soundboard-Slots_
_`,` stoppt alle derzeitig spielenden Sounds (eine Art Not-Aus)_
_`+` erhöht die Lautstärke des Soundboards_
_`-` verringert die Lautstärke des Soundboards_
_`0` fährt die Lautstärke des Soundboards auf einen niedrigen Wert bzw. wieder auf den Ursprungswert (manuelles Ducking)_

- Soundboard: **Playlist-Feature**
_Es gibt nun auch ein einfaches Playlist-Feature. Es erlaubt die einzelnen Sounds durchzugehen und abzuspielen. Man kann sich so mehrere O-Töne ins Soundboard in der richtigen Reihenfolge packen und diese dann der Reihe nach abspielen._
_`*` spielt den nächsten Sound im Soundboard ab(zuerst 1, dann 2, dann 3, etc)_
_`/` spielt den vorherigen Sound im Soundboard ab_
_`Enter` pausiert/spielt den aktuellen Soundboard-Slot(nochmal) ab_
_`alt`+`Enter` stoppt derzeitigen Soundboard-Slot_
_`cmd/strg`+`Enter` zeigt den aktuellen Soundboard-Slot an, der mit Enter abgespielt würde_

    _Achtung: nicht alle Shortcuts funktionieren auf allen Tastaturen, insbesondere unter Windows. Die entsprechenden Aktionen können jedoch leicht manuell auf passende Tasten gemappt werden._

- Soundboard: **Anzeige des Soundboards**
_Mit der `TAB`-Taste wird das Soundboard angezeigt. Ist noch keine Soundboard-Spur im Projekt geladen, bekommt man die Möglichkeit direkt eine einzufügen._

- Soundboard: **Neues Layout**
_Das wichtige Ordner-Icon zum laden von Sounds ist ganz nach links gewandert, damit man es auch auf sehr kleinen Monitoren immer direkt erreichen kann._

- Soundboard: **Midi Aktionen**
_Alle relevanten Funktionen des Soundboards können nun direkt als Aktionen aufgerufen und auf eigene Midi-Interfaces gemappt werden._

### StudioLink

- StudioLink: **Version v20.03.3-stable**
_Ultraschall liefert nun die aktuellste StudioLink Version mit. Ebenso für das OnAir Live-Streamingmodul._

### Editing

- Editing: **Ripple Cut an/aus mit Modifier**
_`cmd/strg`+`x` macht nur noch einen Ripple-Cut auf Zeitselektionen. Item Selektionen werden ignoriert._
_`cmd/strg`+`delete` macht nun einen Ripple-Cut auf eines oder mehrere Items. das ganze unter Berücksichtigung von Envelopes, Undo etc._
_`alt`+`delete` löscht selektierte Items, ohne dass nachfolgende Items verschoben werden, selbst wenn Ripple global aktiv ist._
_`alt`+`x` löscht entsprechend selektierte Items aus einer Zeitauswahl, wobei Ripple global ignoriert wird. Ist kein Item selektiert, werden alle in der Auswahl gelöscht._

- Editing: **RippleCut kopiert Items ins Clipboard**
_Items, die mit `cmd/strg`+`x` per RippleCut herausgeschnitten werden, werden ins Clipboard kopiert. Somit kann man diese wieder neu einfügen._

- Editing: **Vorübergehender Ripple-All Modus beim Verschieben**
_Wird eine Item mit gedrückter `cmd/strg` -Taste bewegt, dann wird der Ripple All Modus für die Zeitdauer des Schiebens aktiviert. Ausgesprochen nützlich, um schnell Platz zu schaffen oder aber Lücken zu schließen._

- Editing: **Editcursor springt nach RippleCut an Schnittstelle**
_Wenn man Ripplecut anwendet, springt der Editcursor nun an die Stelle des Schnitts. So kann man dort schnell weiterarbeiten._

- Editing: **Schneller Schnitt**
_Mit `alt`+`Klick` wird das unter dem Mauszeiger befindliche Item geteilt und die rechte Hälfte ausgewählt. Mit `alt`+`cmd`+`Klick` wird das unter dem Mauszeiger befindliche Item geteilt und die linke Hälfte gelöscht. Diese beiden Shortcuts sind ausgesprochen mächtig für den schnellen Schnitt gebauter Beiträge._

- Editing: **Remove Silence**
_Im Kontextmenü von Items, im Podcast-Menü sowie über den Shortcut `shift`+`d` findet sich eine neue Funktion: Remove Silence. Zuerst werden selektierte Items auf -23LUFS normalisiert und danach entlang sehr stiller Passagen zerschnitten. Die stillen Passagen werden entfernt, jedoch nicht zusammengeschoben. Die übrig bleibenden Blöcke werden mit 500ms Dauer sanft ein- und ausgeblendet._
- Navigation: **Beschleunigung der Cursorbewegung mit Pfeiltasten**
_Wenn man mit den Pfeiltasten `links`/`rechts` den Edit-Cursor bewegt und die Taste gedrückt hält, so beschleunigt sich die Bewegung des Cursors mit der Zeit. Somit ist das Navigieren durch größere Teile des Projekts mit Hilfe der Pfeiltasten einfacher und effizienter._

- Editing: **Umbenennen von Takes**
_Takes können nun schnell mit dem Shortcut `alt`+`n` umbenannt werden. Das hilft auch dabei in der ProjectBay im Storyboard-View einen besseren Überblick zu bekommen, da Takes nicht mehr kryptisch _01_audio_002_ heißen, sondern z.B. _MeinBesterTake_

- Editing: **Kapitelglocke**
_Aktiviert man die Kapitelglocke in den neuen `Ultraschall Settings`, so ertönt ein Glockenklang, wenn der Playcursor an einer Kapitelmarke vorbeikommt. So kann man die Augen vom Bildschirm wenden (z.B. wenn man Shownotes schreibt) und bekommt trotzdem mit, wenn ein Kapitelwechsel ist. Der Klang ist unterschiedlich für Edit-Marker, noch unbenannte Marker und bereits mit Namen versehene Marker._

- Navigation: **Springen zu Kanten**
_Mit `alt`+`links`/`rechts` springt man zu den Kanten der Items. Wenn Spuren selektiert sind, werden nur die Items dieser Spur(en) angesprungen._

- Editing: **MediaItem Enden snappen jetzt in Projekttemplates**
_Wenn man die Ultraschall-Projekttemplates benutzt, kann man Items nicht nur an den Anfang "snappen" lassen, wenn man sie aneinander schiebt, sondern auch ans Ende._

- Navigation: **JKL-Shuttle**
Die drei Tasten `j`, `k` und `l` funktionieren wie ein Shuttle-Rad. Man kann damit mit drei Fingern auf der Tastatur sehr schnell in der Timeline navigieren. Die Geschwindigkeitsstufen sind: 1, 2, 3, 5, 8, 20, 40 und 100 -fach._
_`l` spielt vorwärts. Die Wiedergabegeschwindigkeit lässt sich durch mehrfaches Drücken erhöhen._
_`k` beendet den Shuttlemodus und stoppt die Wiedergabe._
_`j` verhält sich wie die l-Taste, aber rückwärts._

- Navigation: **Zoom-Tasten +/- funktionieren auch kombiniert mit CMD**
_Wenn der Keyboardfokus den Zoom per `+`/`-` nicht nutzbar macht, kann man sie nun kombinieren mit `cmd/strg`._

- Navigation: **Zoom auf aktuelle Region**
_Man kann jetzt auf die aktuelle Region zoomen mit `alt`+`ä`. Aktuelle Region ist diejenige, in der der Edit-Cursor gerade positioniert ist._

- Navigation: **Manueller Follow Mode**
_In der vorherigen Version gab es einen Automatismus, der den Follow Mode in bestimmten, sinnvollen Situationen ausgeschaltet hat. Dieser Automatismus funktionierte für Einige nicht und kann nun in den neuen `Ultraschall Settings` ausgeschaltet werden. Der Followmode bleibt dann solange eingeschaltet, bis man ihn dediziert ausschaltet._

- Navigation: **Belegung der Maus**
_Mit gedrückter Mausrad-Taste kann man die Inhalte des Editierfensters frei verschieben. Das Mausrad scrollt zur Mauszeiger-Position hinein und heraus. Mit `shift` und dem Mausrad scrollt die Timeline horizontal, mit `alt` und Mausrad vertikal._

- Zeitselektion: **Beschleunigung der Zeitselektion mit Shift+Pfeiltasten**
_Wenn man mit `shift`+`links`/`rechts` eine Zeitselektion erstellt und diese Tastenkombination gedrückt hält, so beschleunigt das Größer-werden der Zeitselektion. So kann man größere Zeitselektionen schneller per Tastatur auswählen._

- Mastering: **Shortcut für Normalisierung**
_Der Shortcut auf einem Item `shift`+`alt`+`Klick` startet nun eine Analyse der Lautheit des Items und normalisiert dann auf gemittelte -23 LUFS. Bei langen Spuren kann dies eine Weile dauern. Diese Normalisierung ist eine gute Grundlage für den `Dynamics 2`-Effekt sowie Bestandteil der neuen `Remove Silence` Funktion. Im Kontextmenü für Items gibt es ferner den Eintrag `Toggle normalize items` der eine Standard-Normalisierung (Maximierung der höchsten Spitze) vornimmt bzw. bei erneuter Auswahl wieder rückgängig macht. Auch eine -23 LUFS-Normalisierung kann hiermit rückgängig gemacht werden._

- Editing: **Fileinfo**
_Im Kontextmenü für Items gibt es einen neuen Eintrag `Open item path in explorer/finder' der die Quelldatei des Items im Dateisystem anzeigt._

- Mastering: **Vorlagen für Effektwege**
_In den Vorlagen von Tracks und Projekten (normale Spuren, StudioLink) werden jetzt immer `ReaEQ` und `Ultraschall Dynamics 2` mit eingerichtet - müssen aber händisch aktiviert werden._

- Shortcuts: **Tab schließen**
_`cmd/strg`+`w` schießt den aktuellen Projekte-Tab._

- Editing: **Abhören während man Items löscht**
_Wenn man das Projekt abspielt, `Ripple-All` eingeschaltet hat und man Items löscht, so springt die Abspielposition passend zurück, um nahtlos das Projekt weiter abhören zu können._

- Editing: **Doppelklick für Play**
_Ein Doppelklick in der Zeitleiste oder dem Editierfenster spielt wie bisher ab der angeklickten Position ab. Zusätzlich kann nun auch mit einem Doppelklick auf Leerstellen zwischen Items das Abspielen gestartet werden._

- Marker: **Marker mit Zeitstempel**
_Mit dem Shortcut `alt`+`cmd`+`m` setzt man eine Kapitelmarke, die als Namen den aktuellen Zeitstempel enthält im Format YYYY-MM-DD; HH:MM:SS_


### Theme

- Theme: **Retina Unterstützung**
_Alle relevanten Teile der Nutzeroberfläche werden unter MacOS nun auch in Retina-Auflösung angezeigt. Unter Windows ist dies bei einer HiDPI-Einstellung prinzipiell auch der Fall, jedoch sind hier noch nicht alle Abhängigkeiten zu REAPER erforscht._

- Startscreen: **Neuer Startscreen und Quick-Tutorial**
_Beim Start wird ein neuer Screen angezeigt, der die Neuerungen der 4.0 Release präsentiert. Hier lässt sich auch ein Quick-Tutorial starten, dass verschiedene Aspekte von Ultraschall kompakt erklärt._

- Theme: **Neues Iconset**
_Sämtliche Icons der Buttonleisten wurden als Vektoren neu gezeichnet und liegen nun auch in Retina-Auflösung vor._

- Ultraclock: **Immer sichtbar und Settings**
_Die stark erweiterte Ultracklock ist nun in allen Views voreingestellt. Über das Zahnrad können viele zusätzliche Informationen zur Uhr hinzugefügt werden, etwa: Zeitselektion, Länge des Projekts, letzter/nächster Marker und die Möglichkeit sich die Länge des restlichen Projekts anzuzeigen(aktuelle Position bis Ende des Projekts)._


### Export

- Export: **Rich Chapters mit Bildern und URLs**
_Das neue `Ultraschall Marker Dashboard` des Export-Assistenten - auch zu erreichen über `alt`+`shift`+`m` - erweitert Kapitelmarken: man kann nun dort direkt Kapitelmarken editieren sowie Kapitelbilder und -URLs verwalten. Um einem Kapitel ein Bild zuzuordnen, erstellt man in der Timeline eine leere Spur, in die man per Drag and Drop einfach beliebige Bilder positionieren kann. Jedes Bild muss dabei an derselben Position liegen wie eine klassische Kapitelmarke. Jeder Kapitelmarke kann ferner eine URL zugewiesen werden, die mit `http://` oder `https://` beginnen muss. Eine Ampel informiert über mögliche Probleme beim Export der erweiterten Kapitelmarken._

- Export: **Metadaten-Dialog**
_Im Eingabedialog für die MP3-Metadaten sind nun auch Kommas erlaubt, so dass man Kommas nun auch z.B. im Titel eines MP3 haben kann._

- Export: **Export Assistent**
_Das Episodenbild des Podcats wird alle 2 Sekunden abgefragt, so dass man das Fenster nicht mehr schließen muss um zu sehen, ob es richtig erkannt wurde. Die Positionierung der Texte ist nun robust gegenüber unterschiedlichen Schriften._

- Export: **Plausibilitätscheck vor dem rendern**
_Vor dem Export wird geprüft, ob Track stumm geschaltet sind und eine entsprechende Warnung ausgegeben._

### Sonstiges und Bugfixes

- Backend: **Ultraschall-API**
_Ultraschall verfügt nun über ein eigenes programmierbares API mit 1000+ Endpunkten, auf welchem zukünftig viele Features basieren werden. Informationen, wie man mit dem API eigene Features programmieren kann: ultraschall.fm/api_

- Update: **Ultraschall State-Inspector**
_Das Developertool Ultraschall StateInspector erhielt einige Bugfixes und Layoutkorrekturen._

- Fix: Die Zeit, nach der ein erneuter Update-Check ausgeführt werden soll, wird falsch berechnet. (Danke, [@343max](https://twitter.com/343max))
  [https://github.com/Ultraschall/ultraschall-portable/issues/26](https://github.com/Ultraschall/ultraschall-portable/issues/26)

- Fix: Absturz beim Import von Kapitelmarken, wenn die ausgewählte Datei fehlerhafte Zeiteinträge enthält. (Danke, [@moritzklenk](https://twitter.com/moritzklenk))
  [https://github.com/Ultraschall/ultraschall-portable/issues/111](https://github.com/Ultraschall/ultraschall-portable/issues/111)

- Fix: Beim Export von Chaptermarks werden auch Regions exportiert.
  [https://github.com/Ultraschall/ultraschall-portable/issues/46](https://github.com/Ultraschall/ultraschall-portable/issues/46)

- Fix: Der Export von Kapitelmarken schlägt fehl, wenn eine Kapitelmarke eine oder mehrere Nicht-ANSI-Zeichen enthält. (Danke, Marcus von [@diezugfunker](https://twitter.com/diezugfunker))
  [https://github.com/Ultraschall/ultraschall-portable/issues/110](https://github.com/Ultraschall/ultraschall-portable/issues/110)

- Fix: Der Export von Kapitelmarken schlägt fehl, wenn die Länge eines Kapitelmarkentitels 62 Zeichen überschreitet.
  [https://github.com/Ultraschall/ultraschall-portable/issues/109](https://github.com/Ultraschall/ultraschall-portable/issues/109)

- Fix: Der Zoomlimiter schlug bei zu kurzen/neuen Projekten zu heftig zu, so dass man sich keinen Überblick verschaffen konnte. [https://github.com/Ultraschall/ultraschall-portable/issues/1](https://github.com/Ultraschall/ultraschall-portable/issues/1)

- Fix: Wenn mehere Items ausgewählt waren und man auf eines geklickt hat, wurde es nicht mehr exklusiv ausgewählt. [https://github.com/Ultraschall/ultraschall-portable/issues/20](https://github.com/Ultraschall/ultraschall-portable/issues/20)

- Fix: Der Followmode schaltete sich manchmal aus, wenn man etwas in die Mutespur setzte und mit der Maus über die Mute-Spur fuhr. [https://github.com/Ultraschall/ultraschall-portable/pull/93](https://github.com/Ultraschall/ultraschall-portable/pull/93)

- Fix: Wenn man Enter oder Space gedrückt hielt, sprangen Reaper-Dialoge auf, die nicht für Endnutzende notwendig waren.
 [https://github.com/Ultraschall/ultraschall-portable/issues/69](https://github.com/Ultraschall/ultraschall-portable/issues/69) - Danke an [@timpritlove](https://twitter.com/timpritlove)

- Fix: Wenn man Umlaute im Userpace-Namen hatte (Björn), konnte funktionierten einige Ultraschall-Features nicht mehr.
 [https://github.com/Ultraschall/ultraschall-portable/issues/71](https://github.com/Ultraschall/ultraschall-portable/issues/71) Danke an [@HobbyQA](https://twitter.com/HobbyQS) und [@fairsein](https://twitter.com/fair_sein)

- Fix: Wenn es Punkte in der Mute-Spur gab und man RippleCut angewendet hat, konnte es sein, dass zuviel stummgeschaltet wurde. [https://github.com/Ultraschall/ultraschall-portable/issues/58](https://github.com/Ultraschall/ultraschall-portable/issues/58)

- Fix: Unter Umständen wurden Marker an falsche Stellen gesetzt, nicht an die Playposition. [https://github.com/Ultraschall/ultraschall-portable/issues/64](https://github.com/Ultraschall/ultraschall-portable/issues/64)

### Deprecated

- Ultraschall unterstützt nicht mehr das Metadaten-Tagging von MP4 Dateien. Es wird empfohlen, nun ausschließlich MP3 zu verwenden.

## 3.2 Miedinger - August 2019

- [UPDATE] Ultraschall enthält jetzt die Version 2.10.0 des SWS Plug-ins.
  [https://github.com/Ultraschall/ultraschall-portable/issues/112](https://github.com/Ultraschall/ultraschall-portable/issues/112)

- [FIXED] Die Zeit, nach der ein erneuter Update-Check ausgeführt werden soll, wird falsch berechnet. (Danke, [@343max](https://twitter.com/343max))
  [https://github.com/Ultraschall/ultraschall-portable/issues/26](https://github.com/Ultraschall/ultraschall-portable/issues/26)

- [FIXED] Absturz beim Import von Kapitelmarken, wenn die ausgewählte Datei fehlerhafte Zeiteinträge enthält. (Danke, [@moritzklenk](https://twitter.com/moritzklenk))
  [https://github.com/Ultraschall/ultraschall-portable/issues/111](https://github.com/Ultraschall/ultraschall-portable/issues/111)

- [FIXED] Beim Export von Chaptermarks werden auch Regions exportiert.
  [https://github.com/Ultraschall/ultraschall-portable/issues/46](https://github.com/Ultraschall/ultraschall-portable/issues/46)

- [FIXED] Der Export von Kapitelmarken schlägt fehl, wenn eine Kapitelmarke eine oder mehrere Nicht-ANSI-Zeichen enthält. (Danke, Marcus von [@diezugfunker](https://twitter.com/diezugfunker))
  [https://github.com/Ultraschall/ultraschall-portable/issues/110](https://github.com/Ultraschall/ultraschall-portable/issues/110)

- [FIXED] Der Export von Kapitelmarken schlägt fehl, wenn die Länge eines Kapitelmarkentitels 62 Zeichen überschreitet.
  [https://github.com/Ultraschall/ultraschall-portable/issues/109](https://github.com/Ultraschall/ultraschall-portable/issues/109)

### Bekannte Probleme

- [FEATURE] Exportierte Kapitelmarken in MP3-Dateien werden in der Apple Podcast-App (iOS) nicht angezeigt. (Danke, [@twittlik](https://twitter.com/twittlik))
  [https://github.com/Ultraschall/ultraschall-portable/issues/113](https://github.com/Ultraschall/ultraschall-portable/issues/113)

- [BUG] MP4-Dateien, die exportierte Ultraschall-Daten enthalten, werden in der iTunes-Vorschau nicht wiedergegeben. (Danke, [@schanzpaulifunk](https://twitter.com/schanzpaulifunk))
  [https://github.com/Ultraschall/ultraschall-portable/issues/114](https://github.com/Ultraschall/ultraschall-portable/issues/114)

## 3.1 Miedinger - 2018-Januar

- REAPER: **Unterstützung der Version 5.70**
  _Ultraschall 3.1 ist für die Version 5.70 von REAPER optimiert. Alle anderen Versionen sind nicht lauffähig._ **Von einem manuellen Update von REAPER ist daher in Zukunft unbedingt abzusehen**, _die Ultraschall-Erweiterungen werden dann deaktiviert._

- Theme: **Master-Kanal im Mixer immer sichtbar**
  _In allen Views ist nun auch der Master-Kanal direkt rechts im Mixer sichtbar und muss nicht mehr über einen Tab umgeschaltet werden. Der Master-Kanal ist in der Anzeige zweigeteilt: in der Mitte das normale aktuelle Signal, breiter links und rechts daneben eine RMS-Anzeige mit dem Mittel von 2000 Millisekunden. Dies ermöglicht in Kombination mit dem neuen Ultraschall Dynamics2 Effekt eine schnelle Einordnung, ob die gewünschen -16LUFS konstant erreicht oder über-/unterschritten werden. Die Messung erfolgt zwar nicht in LUFS sondern in RMS, was aber als Näherungswert in der Praxis für Sprachaufnahmen ausreicht. Farblich werden folgende Zustände unterschieden: Blau-bis -18 LUFS (Mix ist zu leise) Grün- -18 bis -14 LUFS Aufnahme ist perfekt in der Lautstärke Gelb- -14 bis -12 LUFS (Aufnahme ist zu laut, sollte nur selten erreicht werden) Orange: -12 bis 0 LUFS (Aufnahme ist deutlich zu laut). Gewünscht ist ein Mix, bei dem die Aussteuerung im Master nur selten die grüne Zone verlässt wenn gesprochen wird._

  [Video: Master Mix and RMS Display](https://ultraschall.fm/wp-content/uploads/2018/01/Master_Mix_and_RMS.gif)

- Mastering: **Ultraschall Dynamics2 Loudness Normalization**
  _Der Dynamics-Effekt zum Vereinheitlichen der Lautstärke von Spuren der 3.0 Release wurde erheblich erweitert: über drei Schieberegler lassen sich nun Target-Lautstärke (normalerweise: -16LUFS), Noisefloor (Trennwert, ab dem ein Signal als Rauschen/Störung interpretiert wird und nicht als Stimme) sowie Noisegate (steiler oder flacher bzw. aus) je nach Anforderung einstellen. Der Effekt hat zudem einen Limiter-Effekt eingebaut der digitales Clipping abfängt. Eigene Einstellungen können - auch pro Spur - als Preset gespeichert werden._

  [Video: Ultraschall Dynamics 2 Loudness Normalization](https://ultraschall.fm/wp-content/uploads/2018/01/dynamics2b.gif)

- Export (Mac): **Export und Tagging von m4a**
  _Es können nun auf macOS im Render-Assistenten auch m4a-Dateien generiert werden. Im Export-Assistenten werden diese genauso wie bisher MP3 mit Kapitelmarken, Metadaten und Epispodencover versehen._

  [Video: m4a Export](https://ultraschall.fm/wp-content/uploads/2018/01/m4a_export.gif)

- Theme: **Anzeige ausgewählter Items optimiert**
  _Nur echt mit der Goldkante: ausgewählte Items werden nicht mehr durch Helligkeit hervorgehoben, sondern durch eine gut sichbare goldene Umrahmung._

  [Video: Select Items](https://ultraschall.fm/wp-content/uploads/2018/01/Select_Items.gif)

- Theme: **Alternative Darstellung der Wellenform**
  _Mit dem Shortcut `alt`+`shift`+`h` kann die Darstellung der Wellenform so umgestellt werden, dass die Peaks nicht von der Mitte sondern der Grundlinie aus wachsen._

  [Video: Rectify Peaks](https://ultraschall.fm/wp-content/uploads/2018/01/Rectify_Peaks.gif)

- Theme: **Darstellung der Wellenform als Spektogramm**
  _Mit Hilfe der Peak Display Settings kann man sich ergänzend zur normalen Wellenform ein Spektrogramm anzeigen lassen - hilfreich, um etwa Brummgeräusche zu identifizieren._

  [Video: Spektogramm](https://ultraschall.fm/wp-content/uploads/2018/01/Spektrogramm.gif)

- Theme: **Lautstärke-Zoom der Wellenform**
  _Mit dem Shortcut `alt`+`h` wird die Ansicht der Wellenform vertikal in zwei Stufen gezoomt. Man kann damit auch sehr leise Passagen gut sichtbar und editierbar schalten._

  [Video: Toggle Peak Gain](https://ultraschall.fm/wp-content/uploads/2018/01/Toggle_Peak_Gain.gif)

- Editing: **Zoom zu Edit-Cursor**
  _Mit dem Shortcut `z` wird direkt zu einer für Feinschnitt passenden Zoomstufe zum Edit-Cursor hin gezoomt. Nochmaliges Drücken von `z` springt wieder in die vorherige Zoomstufe zurück._

  [Video: Toggle Arrange Zoom](https://ultraschall.fm/wp-content/uploads/2018/01/Toggle_Arrange_Zoom.gif)

- Theme: **Begrenzung des Zoom-Out**
  _Insbesondere bei einem `Pinch-Zoom` auf dem Trackpad konnte es leicht passieren, dass man viel zu weit herausgezoomt hat und sein Projekt nicht wieder gefunden hat. Der maximale Zoom-Out ist nun auf die Projektlänge begrenzt (ganzes Projekt sichtbar). Über `alt`+`Pinch-Zoom` erhält man die bisherige, unlimitierte Zoomfunktion._

  [Video: Zoom Limiter](https://ultraschall.fm/wp-content/uploads/2018/01/Zoom_Limiter.gif)

- Theme: **Zoom zu Cursor**
  _Mit dem `Pinch-Zoom` wird wie bisher immer an die Stelle gezoomt, an der sich der Mauszeiger befindet. Nutzt man hingegen die Zoomfunktion über die Tastatur `+` bzw. `-`, so wird zur Position des Cursors gezoomt. Der Shortcut `^` Springt ohne Zoom zum Edit-/Rec-/Play-Cursor._

  [Video: Zoom to Cursor](https://ultraschall.fm/wp-content/uploads/2018/01/Zoom_to_Cursor.gif)

- Theme: **Ultraclock**
  _Im View "Recording" wird eine erweiterte Uhr angezeigt - sie zeigt wie bisher die aktuelle Position des Play-/Record-/Edit-Cursors, jedoch zusätzlich den aktuellen Transport-Status (Stop, Pause, Play, Record, Loop) in Farbe. Darüber ist die aktuelle Uhrzeit zu sehen - nützlich, um Start oder Ende einer Live-Sendung perfekt zu timen. Mit der rechten Maustaste können über ein Kontextmenü die angezeigten Informationen angepasst werden._

  [Video: Ultraclock](https://ultraschall.fm/wp-content/uploads/2018/01/Ultraclock.gif)

- Theme: **Tooltips optimiert**
  _Alle Buttons haben jetzt aussagekräftige Tooltipps wenn man mit dem Mauszeiger länger darauf verweilt._

  [Video: Tooltips](https://ultraschall.fm/wp-content/uploads/2018/01/tooltipps.gif)

- Theme: **Anzeige des Recording-Formates**
  _In der Menüleiste wird nun rechts nicht nur der noch freie Speicherplatz angezeigt, sondern auch das verwendete Recording-Format. Als Standard ist für normal ausgesteuerte Aufnahmen FLAC (verlustfreie Kompression), 16Bit 48KHz eingestellt. Natürlich kann dies für anspruchsvollere Aufnahmesituationen etwa auf 24Bit angehoben werden._

  [Video: Recording Info](https://ultraschall.fm/wp-content/uploads/2018/01/Recinfo.gif)

- Theme: **Envelope-Spuren**
  _Bei Envelope Spuren werden nun deren Typnamen angezeigt - also etwa "Mute", "Volume" etc. Mit dem Shortcut `shift`+`h` kann ihre Höhe umgeschaltet werden - vergleichbar zum Umschalten der Trackhöhe mit `h`._

  [Video: Envelope Info](https://ultraschall.fm/wp-content/uploads/2018/01/Envelope_Info.gif)

- Theme: **RecArm Verhalten optimiert**
  _Wenn neue Tracks über das Podcast-Menü oder ober den Shortcut `cmd`+`t` angelegt werden, sind sie wie bisher direkt für die Aufnahme scharf geschaltet (RecArm). Legt man Tracks über Doppelklick im linken Spurbereich oder im Mixer an, oder über drag & drop, so sind sie nicht direkt scharfgeschaltet._

  [Video: Auto Arm new Tracks](https://ultraschall.fm/wp-content/uploads/2018/01/Auto_Arm_New_Tracks.gif)

- Theme: **Umschalten des RecArm-Status für alle Tracks**
  _Mit dem Shortcut `shift`+`a` können alle Tracks für eine Aufnahme scharfgeschaltet werden bzw. die Scharfschaltung aufgehoben werden. Das Umschalten funktioniert nur, wenn keine Aufnahme läuft._

  [Video: Toggle Arm all tracks](https://ultraschall.fm/wp-content/uploads/2018/01/Toggle_Arm_all_Tracks.gif)

- Theme: **Umschalten der Playrate**
  _Mit dem Shortcut `alt`+`j` kann die Playrate von 1.0 zu 1.5 und zurück geschaltet werden. Wem das zu schnell ist: man kann auch einen anderen Wert am Playrate-Schieber einstellen und ebenfalls per `alt`+`j` speichern/umschalten. Der Wert bleibt erhalten. Dank an leonidlezner!_

  [Video: Envelope Info](https://ultraschall.fm/wp-content/uploads/2018/01/Switch_Playrate.gif)

- Editing: **Folgen-Modus**
  _Mit `cmd`+`f`oder dem entsprechenden neuen Icon wird der Folgen-Modus aktiviert oder deaktiviert. Ein Aktivieren führt immer dazu, dass die Timeline zur aktuellen Position des Play- oder Record-Cursors springt und die Timeline ab dann mitscrollt. Ein deaktivieren entkoppelt die Timeline vom Abspielen oder Aufnehmen - man kann somit andere Stellen im Projekt bearbeiten, ohne dass Wiedergabe oder Aufnahme stoppt. Sämtliche Kapitelmarken-Funktionen beziehen sich ab dann auch auf die Position des Edit-Cursors, nicht wie sonst auf Play-/Record-Cursor._

  [Video: Follow Mode](https://ultraschall.fm/wp-content/uploads/2018/01/follow.gif)

- Editing: **Zeitauswahl editieren an Kanten**
  _Eine Zeitauswahl kann nun überall an den beiden äußeren Kanten angefasst und verschoben werden._

  [Video: Adjust Time Selection](https://ultraschall.fm/wp-content/uploads/2018/01/Adjust_Time_Selection.gif)

- Editing: **Zeitauswahl selektiert direkt auch Items**
  _Wenn das Zeitauswahl-Werkzeug aktiviert ist, und man damit über ein Item zieht um eine Zeitauswahl vorzunehmen, wird nun auch direkt das entsprechende Item ausgewählt. Zieht man über mehrere Items, werden diese gemeinsam mit ausgewählt._

  [Video: Select Items with Time Selection](https://ultraschall.fm/wp-content/uploads/2018/01/Select_Items_with_Time_Selection.gif)

- Editing: **Muten ausgewählter Items entlang der Zeitauswahl**
  _Mit `cmd`+`y` werden alle ausgewählten Items gemutet, und zwar über den Zeitraum der Zeitauswahl. Mit `cmd`+`shift`+`y` wird eine Zeitauswahl wieder unmuted._

  [Video: Mute Items with Time Selection](https://ultraschall.fm/wp-content/uploads/2018/01/Mute_Items_with_Time_Selection.gif)

- Editing: **Doppelklick für Play**
  _Ein Doppelklick in der Zeitleiste oder dem Editierfenster spielt ab der angeklickten Position ab._

  [Video: Double-Click to Play](https://ultraschall.fm/wp-content/uploads/2018/01/Double_Click_to_Play.gif)

- Editing: **Verschieben von Items über Tastatur**
  _Mit den Tasten `alt`+`links` bzw. `alt`+`rechts` können markierte items in der Timeline verschoben werden. Über die Taste `n` erreicht man ein Einstellungsfenster, mit dem man die Laufweite festlegen kann._

  [Video: Nudge Items](https://ultraschall.fm/wp-content/uploads/2018/01/Nudge_Items.gif)

- Kapitelmarken: **Importieren geplanter Kapitelmarken aus der Zwischenablage**
  _beliebige Texte können aus der Zwischenablage als geplante Kapitelmarken (grüne Farbe) in das Projekt eingefügt werden. Zeilenumbrüche definieren die einzelnen Marken._

  [Video: Import planned Markers from Clipboard](https://ultraschall.fm/wp-content/uploads/2018/01/Import_from_Clipboard.gif)

- Kapitelmarken: **Setzen geplanter Kapitelmarken**
  _Mit dem Shortcut `b` wird die jeweils nächste vorbereitete Marke an die aktuelle Position des Play-/Record-Cursors bzw des Edit-Cursors (abhängig vom Folgen-Modus (siehe oben)) gesetzt._

  [Video: Set planned Markers](https://ultraschall.fm/wp-content/uploads/2018/01/Set_Planned_Markers2.gif)

- Kapitelmarken: **Umwandeln aller Marker in geplante Kapitelmarken**
  _Alle im Projekt befindlichen Marker können in grüne vorbereitete Marker verwandelt werden; die bisherige Reihenfolge bleibt dabei erhalten._

  [Video: Set all Markers to Planning Stage](https://ultraschall.fm/wp-content/uploads/2018/01/Set_Markers_to_Planned.gif)

- Kapitelmarken: **Sichtbarkeit von Kapitelmarken beim Setzen**
  _Werden Kapitelmarken an Play- oder Edit-Cursor gesetzt, während diese außerhalb des sichtbaren Bereiches sind, wird die Timeline an die entsprechende Stelle verschoben so dass man sieht, wo die Marker gesetzt werden._

  [Video: Show Positioning of Markers](https://ultraschall.fm/wp-content/uploads/2018/01/Show_Positioning_of_Markers.gif)

- Kapitelmarken: **Kapitelmarken immer an Play-/Record-Cursor setzen**
  _Kapitelmarken können durch zusätzliche Verwendung von `cmd` immer an die Position des Play-/Record-Cursor gesetzt werden (also `cmd`+`m`, `cmd`+`e`, `cmd`+`b` sowie `cmd`+`shift`+`m`). Der Follow-Modus (siehe oben) wird dabei ignoriert und auch der Viewport ändert sich nicht. Diese Funktionen eignen sich gut, um sie etwa auf ein Midi-Interface zu legen._

  [Video: Set Markers always to Play/Rec Position](https://ultraschall.fm/wp-content/uploads/2018/01/Set_Markers_to_Play.gif)

- Kapitelmarken: **Kapitelmarkenverwaltung**
  _Um während des Abhörens in Ruhe bestehende Kapitelmarken editieren zu können, wurde das Auto-Play Feature der Kapitelmarken in der Kapitelmarkenliste deaktiviert. Das Abspielen läuft nun einfach weiter, egal wie man die Kapitelmarken bearbeitet. Um wie bisher schnell zu einer Kapitelmarke in der Timeline zu springen, klickt man doppelt rechts neben der Marke im freien Bereich der Liste. Die Marken sind nun zur besseren Orientierung durchnummeriert, die Nummern landen nicht in den Texten._

  [Video: Edit Markers](https://ultraschall.fm/wp-content/uploads/2018/01/Edit_markers.gif)

- Soundboard: **Sortierung unter macOS High Sierra**
  _Die Sortierung der einzelnen Sounds erfolgt nun auch unter macOS High Sierra wieder alphabetisch nach Dateinamen. Es wird nur noch der jeweils angegebene Ordner ausgelesen und in das Soundboard importiert, nicht wie bisher auch sämtliche Unterordner._

- Sonstiges: **Tastatur-Shortcuts überarbeitet**
  _Die Übersicht für alle relevanten [Tastatur-Shortcuts](https://url.ultraschall-podcast.de/keymap31) in Ultraschall wurde aktualisiert und erweitert._

- Easter Egg: **Wenns mal wieder länger dauert**
  _Ostern kommt plötzlich und unerwartet. Mit dem Shortcut `alt`+`cmd`+`shift`+`u` kann man sich die Wartezeit etwas verkürzen._

- Sonstiges: **Bugfixes und Optimierungen**
  _Diverse kleinere Optimierungen, insbesondere von Sonderfällen. Zuviele Details würden Sie nur beunruhigen._

## 3.0.3 Miedinger - 2017-April-6

- REAPER: **Festlegung auf eine exakte Versionsnummer**
  _Um die Konsistenz und Stabilität des Systems zu gewährleisten, wird bei jedem Start nun auf eine spezifische Version von REAPER geprüft (5.70). Zukünftige Releases werden dann jeweils mit neuen Versionen gekoppelt sein._ **Von einem manuellen Update von REAPER ist daher in Zukunft unbedingt abzusehen**, _die Ultraschall-Erweiterungen werden dann deaktiviert._

- Actions: **Überarbeitete Routing Snapshots**
  _Um während einer Live-Sendung - etwa mit Hilfe von Studio Link OnAir - verschiedene Routing-Situationen vorbereiten und abrufen zu können (etwa Preshow mit nur Musik auf dem Stream, Show mit allen Stimmen und Aftershow mit leisem Musikbett), wurde der Bereich der Routing-Snapshots komplett neu implementiert und mit einer eigenen Verwaltungsoberfläche versehen. Die Snapshots berücksichtigen nun auch Sends in Richtung Master sowie Hardware-Sends._

- Keymap: **Shortcuts für Routing-Snapshots**
  _Mit `F1` bis `F4` werden gesetzte Routing Snapshots abgerufen. Mit `shift` + `F1` bis `F4` wird die gerade eingestellte Routing-Matrix in den jeweiligen Snapshot-Slot geschrieben._

- Keymap Mac: **Anpassungen an Systemstandard**
  _Unter macOS wurden folgende Aktionen für Shortcuts an den Systemstandard angepasst: Drag&Copy von Items erfolgt nun über `alt` + `gedrückter Primärklick`. Der aktuelle Projekt-Tab wird mit `cmd` + `w` geschlossen._

- Streaming: **Update für Studio Link OnAir**
  _Eine neue Version von Studio Link OnAir wird ausgeliefert, die ein seltenes Stabilitätsproblem unter Windows behebt._

- Editing: **Weiter verbessertes Verhalten der `esc`-Taste**
  _Die "lösche jegliche Auswahl"-Funktion beinhaltet nun auch nicht-selektierte Envelope-Points. Erstaunlich._

- Editing: **Midi Actions für EQ-Regler**
  _Zwei neue Ultraschall-Midi Aktionen ermöglichen das leichte Verschieben des Inpoint und Outpoint über einen klassischen EQ-Regler auf einem Midi-Interface: In der Mittelstellung passiert nichts, ein Drehen nach Links oder Rechts bewirkt eine beschleunigte Bewegung in die jeweilige Richtung. Je weiter der Einschlag, desto schneller bewegt sich der In-/Outpoint. Die Skripte (`ultraschall_midi_move_start_of_time_slection.lua` und `ultraschall_midi_move_end_of_time_slection.lua`) müssen manuell einem Midi-Signal zugeordnet werden._

- Installer: **Update Check**
  _Der Update Check auf neue Versionen von Ultraschall kann nun jederzeit im neuen Startscreen ab- oder angeschaltet werden._

- Theme: **Ultraschall-Startscreen erweitert**
  _Der neue Startscreen enthält nun auch die Informationen des alten `About Ultraschall...` Menüeintrages, der somit entfällt. Die Versionsnummern aller installierten Komponenten sind nun im Startscreen unter dem `Details`-Button erreichbar._

- Soundboard: **Bugfix**
  _Das Soundboard stoppt nun nicht mehr die Wiedergabe, sobald ein Routing-Preset abgerufen wird._

- Soundboard: **Presets**
  _Das Soundboard funktioniert nun durchgängig mit Presets. Dadurch ist es möglich, beliebige Sound-Sets zu speichern und zu laden, auch während einer Aufnahme. Duch den fliegenden Wechsel von Presets während einer Aufnahme ist es nun auch leicht möglich, mehr als 24 Sounds in einer Sendung zu verwenden. Man kann die Presets den eigenen Projekt-Presets zuweisen, damit jede Sendung gleich mit den richtigen Einspielern geladen wird._

## 3.0.2 Miedinger - 2017-März-06

- Editing: **Shortcuts für In- und Outpoint**
  _Mit den Tasten `alt` + `i` sowie `alt` + `o` springt man zum Anfang bzw. Ende einer Zeitauswahl. Mit `shift` + `i` sowie `shift` + `o` wird ab der jeweiligen Position abgespielt._

- Editing: **Verbesserter Ripple-Cut**
  _Die neue Ripple-Cut Funktion (`cmd` + `x` sowie das entsprechende Icon) verhalten sich nun sinnvoller: ist nichts ausgewählt, passiert nichts. Ist eine Zeitauswahl markiert, wird nur diese geschnitten, unabhängig von eventuell zugleich ausgewählten Items. Ist keine Zeitauswahl markiert, aber genau ein Item, so wird anhand dessen Rändern ein Ripple-Cut vorgenommen (Tim's Ripple Cut). Ist keine Zeitauswahl markiert, sowie mehrere Items, passiert nichts._

- Editing: **Schneller Wechsel und Einfrieren der Trackhöhe**
  _Mit der Taste `h` schaltet man schnell zwischen zwei (einstellbaren) Trackhöhen hin und her, die dann ihre Höhe auch bei Verschieben der Fenster untereinander behalten. Das Umschalten wirkt auf alle markierten Spuren. Ist keine Spur markiert, werden alle Spuren verändert. Das Einfrieren der Höhe kann mit den Zoom-Schaltern wieder aufgehoben werden._

- Keymap: **Optimierung der Tastatur-Shortcuts und Mapping für Windows**
  _Die Belegung von Shortcuts von Windows wurde dem Verhalen auf macOS angepasst. Die PDF-Schablone funktioniert nun auf beiden Systemen gleich. Neue Shortcuts sind etwa: `shift` + `n` - Normalisierung ausgewählter Items sowie `alt` + `d` - ausschalten aller Docks für ablenkungsfreies Editieren._

- Theme: **FX Buttons im Master-Kanal**
  _Die Buttons zum Einstellen von FX sind nun auch im Master-Kanal in jeder Größe sichtbar._

- Actions: **Erweitertes Prepare all tracks for editing**
  _Die Funktion beinhaltet nun das Einschalten der Sends aller Spuren richtung Masterkanal - eine gängige Fehlerquelle für scheinbar fehlende Spuren im finalen Mix._

- Mastering: **Erweiterte Episodenbilder**
  _Im Projektordner sind für den MP3-Export nun auch Episodenbilder mit dem Namen `cover.jpg`, `cover.jpeg` sowie `cover.png` zugelassen um schnell ein Standardbild nachnutzen zu können. Danke an Mespotine für die Idee._

## 3.0.1 Miedinger - 2017-März-05

- Streaming: **Studio Link OnAir Streaming**
  _Durch die Unterstützung von Studio Link OnAir (Version 17.02.0.) kann mit einem Knopfdruck ein Live-Streaming der Sendung gestartet werden. Gestreamt wird immer das im Mastermix anliegende Signal, über ein sich öffnendes Web-Interface können Anpassungen der Streaming-Metadaten vorgenommen sowie die Streaming-URL publiziert werden._

- Installer: **Update Check**
  _Beim Starten von Ultraschall wird geprüft, ob eine neue Version vorliegt. Eine Validitäts-Check stellt sicher, dass zueinander passende Versionen von Plugin und Theme installiert sind und gibt gegebenenfalls Warnmeldungen._

- Installer: **LAME MP3 Encoder**
  _Der LAME MP3 Encoder wird in Version 3.98.3 automatisch installiert._

- Studio Link: **Update**
  _Ultraschall wird mit aktualisiertem StudioLink Plug-in in Version 16.12.0. ausgeliefert._

- Theme: **Ultraschall-Startscreen**
  _Ein neuer Startscreen informiert über die erfolgreiche Installation und gibt erste Hinweise sowie Links zu Hilfe-Ressourcen._

- Theme: **Anpassungen der Views**
  _Die Views-Umschalter oben links zeigen nun auch nach einem Reaper-Neustart den aktuellen Modus an (Stichwort: Persistenz-Schicht). Im Edit-View wird ganz oben jetzt das Navigator-Fenster über die gesamte Breite angezeigt.
  Zusätzlich gibt es unten links nun einen neuen Reiter für `Loudness`, mit dem sich die Lautstärke von Spuren oder einzelnen Items in LUFS messen lässt (siehe: Ultraschall-Dynamics)._

- Theme: **FX immer sichtbar im Mixerbereich**
  _Durch die stetig wachsende Bedeutung der Effekte (StudioLink, OnAir, Soundboard, Dynamics) sind nun die FX-Buttons im Mixerbereich der Spuren immer sichtbar, auch bei sehr verkleinertem Fenster._

- Theme: **Wellenform**
  _Ausgewählte Items werden in der Helligkeit klarer hervorgehoben. Schnitte innerhalb einer Wellenform werden deutlicher angezeigt._

- Theme: **User Interface**
  _Viele GUI-Elemente erhalten mehr Kontrast für bessere Sichtbarkeit._

- Theme: **Auswahlwerkzeug**
  _Mit einem neuen Icon-Schalter kann zwischen zwei Editier-Modi gewechselt werden: dem bisherigenen Modus, der einzelne Elemente auf der Timeline markiert und verschiebt, sowie einem neuen Auswahl-Modus ("TSB-Button"), der das Erstellen von Zeitauswahlen für schnellen Schnitt (Ripple-Cut) erheblich vereinfacht. Eine Zeitauswahl kann damit überall in der Timeline gesetzt werden, nicht mehr nur wie bisher am oberen Rand. Das Umschalten der Modi erfolgt entweder über das neue Icon oder über den Tastatur-Shortcut: `#`._

- Theme: **Hervorhebung 'Prepare all tracks for editing'**
  _Die nach jeder Aufnahme und vor dem Schnitt aufzurufende Menü-Aktion 'Prepare all tracks for editing' wird optisch hervorgehoben um die Sichtbarkeit zu erhöhen. Die Funktion selbst wurde neu implementiert und erweitert. Nach erfolgreichem Durchlauf wird ein neues Status-Fenster angezeigt._

- Theme: **Podcast-Menü**
  _Diverse Einträge im Podcast-Menü wurden aktualisiert und klarer angeordnet._

- Editing: **Volume-Editing**
  _Über das Menü oder den Shortcut `alt`+`v` kann für ausgewählte Spuren ein Lautstärke-Envelope (PRE-FX!) angezeigt werden. Mit diesem können komplexere Fadings oder Lautstärke-Verläufe realisiert werden. Ferner gibt es einen PRE-FX Gainregler links im Spurbereich, mit dem sich die Gesamtlautstärke einer Spur - mit visueller Rückmeldung durch die Wellenform - anpassen lässt. Die Sichtbarkeit der Spuren wird über das aus der Mute-Spur bekannte Icon oben umgeschaltet._

- Editing: **Einfacheres Envelope-Handling**
  _Der Modus, mit dem man in Envelopes (Mute oder Volume) Punkt setzen oder verschieben kann, ist überarbeitet worden. Man klickt nun einfach an die Stelle, an der der nächste Punkt gesetzt werden soll, bzw. verschiebt bestehende Punkte. Ein Mute-Bereich ist so mittels zweier Klicks einstellbar. Der alte Freihand-Malmodus kann jederzeit durch gedrückt halten der `cmd` Taste zurückgeholt werden._

- Editing: **Verbessertes Verhalten der `esc`-Taste**
  _Wir glauben an die Zukunft und die Notwendigkeit der `esc`-Taste. Daher haben wir die "lösche jegliche Auswahl"-Funktion erheblich erweitert - sie hebt nun Track-, Item-, Envelope- und Zeitmarkierungen auf._

- Editing: **Vorhören von Schnitten**
  _Mit dem Shortcut `p` kann man vorhören, wie sich ein Schnitt mittels Zeitmarkierung auswirken würde, ohne dass man diesen bereits durchführen muss. In Kombination mit den neuen Shortcuts zum Verschieben der In- und Outpoints einer Zeitauswahl `<`, `y`, `x` und `c` ist dadurch ein sehr effizienter und kontrollierter Schnitt möglich._

- Editing: **Play-Cursor auf Anfang von Zeitauswahlen**
  _Setzt man eine Zeitauswahl, so wird der Play-Cursor direkt auf den Inpoint dieser Auswahl gesetzt und man kann direkt mit `return` oder `space` die Auswahl anhören._

- Editing: **Erweiterter Ripple-Cut**
  _Mit dem Shortcut `cmd`+`x` wird ein Ripple-Cut über alle Spuren auch dann durchgeführt, wenn nur ein einzelnes Item ausgewählt wird. Schnittbereich ist dann Start- und Endpunkt dieses Items._

- Keymap: **Neues Layout für Tastatur-Shortcuts**
  _Eine Vielzahl an Shortcuts wurden überarbeitet und neu hinzugefügt um einen effizienteren Schnitt über die Tastatur zu ermöglichen. In einem [.PDF](https://url.ultraschall-podcast.de/keymap) sind die neuen Shortcuts ausgewiesen, eigene Anpassungen können in einer mitgelieferten PowerPoint-Datei vorgenommen werden._

- Mastering: **Ultraschall Dynamics**
  _Mit dem neuen Dynamics Effekt kann die Lautheit des Podcasts auf ca. -16 LUFS optimiert werden. Der Effekt ersetzt den bisher empfohlenen AU General Dynamic Effekt und ist auch unter Windows einsetzbar. Es werden Presets mitgeliefert mit und ohne weichem Noisegate zur Reduzierung leiser Störungen. Der Effekt kann sowohl auf Einzelspuren, einzelnen Items, als auch auf dem Master-Kanal eingesetzt und parametrisiert werden. Achtung: der Effekt ist weniger geeignet zur Reparatur von problematischem Material (Brummen, Hall etc.) - hier wird dringend nach wie vor der Einsatz von Auphonic empfohlen._

- Mastering: **Effektvorgaben bei neuen Spuren**
  _Beim Anlegen neuer Spuren werden automatisch die Effekte ReaEQ (Equalizer) und JS: General Dynamics hinzugefügt, jedoch noch nicht aktiviert._

- Mastering: **Neues EQ-Preset**
  _Ein neues Ultraschall 3 Preset für den EQ wird mitgeliefert. Es bietet weniger Bassanhebung als der Preset der 2er Version und ist ein guter Startpunkt für die Headsets [DT297](https://www.thomann.de/de/beyerdynamic_dt297pv80_mk_ii.htm?partner_id=60110) und [HMC660](https://sendegate.de/t/profi-klang-fuer-alle-das-hmc660-headset-richtig-einsetzen-fuer-unter-100/3076?u=rstockm) ist._

- Mastering: **Export Assistent**
  _Ein neuer Export-Assistent, links unten in der `Export` Iconleiste zu finden, hilft dabei, perfekte MP3-Dateien zu erzeugen. Die ID3V2 Elemente Metadaten (wie Titel, Podcast etc.), Episodenbild und Kapitelmarken werden in die produzierte MP3-Datei gespeichert._

- Mastering: **Rauschfilter verfügbar**
  _Zum Beheben gängiger Soundprobleme wie Rauschen oder Netzbrummen wurde der ReaFir-Effekt in die Effekt-Favoriten mit aufgenommen. Die Bedienung wird im [Video zu Ultraschall Dynamics](https://ultraschall.fm/tutorials/) erläutert._

- Mastering: **Bugfix: Projektordner öffnen**
  _Menübefehl und Icon für das Öffnen des Projektverzeichnisses öffnen nun wirklich das Projektverzeichnis - nicht wie bisher den Unterordner mit den Sounddateien._

- Actions: **Colorpicker**
  _Der neue nutzerfreundlicher Colorpicker (Shortcut: `alt`+`c`) hilft, Übersicht in komplexen Projekten zu erhalten: Spuren oder einzelnen Clips können Farben zugewiesen werden, mehrere Spuren über eine Auswahl auch Farbverläufe - entweder fließend, oder unter Nutzung eines sinnvollen Kontrast-Bereichs._

- Actions: **Import von Kapitelmarken aus WAV-Dateien**
  _Einige Aufnahmegeräte (z.B. Zoom H5 und H6) bieten die Möglichkeit, während der Aufnahme Kapitelmarken in die .WAV Datei zu schreiben. Mit dieser neuen Kapitelmarken-Aktion können sie ausgelesen und in Ultraschall-Kapitelmarken umgewandelt werden._

- Actions [Windows]: **Bugfix für Umlaute**
  _Es wurde ein Fehler behoben im Umgang mit Kapitelmarken, die Umlaute enthalten. Danke an @jalea and Nico Buch für das Aufspüren dieses Fehlers._

- Soundboard: **Bugfix**
  _Mit OSC kann das Abspielen von Sounds nicht angehalten werden. Danke an Bastian Boessl für den Bugreport._

## 2.2.2 Gropius - 2016-August-14

- Soundboard [Mac]: **Bugfix**
  _Bugfix: Aufgenommene Soundboard-Spuren werden jetzt abgespielt._

- Misc [Windows]: **Kompatibilität**
  _Updates für Windows 10 Version 1607 (Build 14393, Anniversary-Update)._

- StudioLink: **Update**
  _Ultraschall enthält jetzt die neue StudioLink-Version 16.04.1._

## 2.2.2 Gropius - 2016-August-14

- Soundboard [Mac]: **Bugfix**
  _Bugfix: Aufgenommene Soundbooard-Spuren werdem jetzt abgespielt._

- Misc [Windows]: **Kompatibilität**
  _Updates für Windows 10 Version 1607 (Build 14393, Anniversary-Update)._

- StudioLink: **Update**
  _Ultraschall enthält jetzt die neue StudioLink-Version 16.04.1._

## 2.2.1 Gropius - 2016-June-09

- Installer: **Bugfix**
  _Bugfix: Löschen von alten Dateien schlägt fehl. Danke an Marcus Schwarz für den Bugreport._

- Installer: **Bugfix**
  _Bugfix: Löschen von anderen alten Dateien schlägt fehl. Danke an Wolfgang Schulz für den Bugreport._

## 2.2 Gropius - 2016-Jun-05

- Theme: **Weiteres Feintuning des neuen Themes**
  _Die Scrollbalken sowie Zoom-Icons wurden vereinfacht, ebenso Schieberegler in AU/VST-Effekten._

- Actions: **Räuspertaste und Mute-Spur**
  _Komplette Neukonzeption der Räuspertasten- und Mute-Funktion. Der editierbare Mute-Envelope wird nun immer in einer Separaten Spur angezeigt und farblich besser hervorgehoben. Der Mute-Button in der Iconleiste funktioniert nun kontexabhängig: vor einer Aufnahme können ausgewählte Spuren für die Räuspertaste aktiviert werden. Während und nach der Aufnahme schaltet er die Sichtbarkeit der Mute-Spuren ein oder aus._

- Actions: **Auswahl von Spuren über Tastatur**
  _Über die Zahlentasten 1 bis 8 können die jeweiligen Spuren markiert oder unmarkiert werden. 9 markiert sämtliche Spuren, 0 hebt die Markierung sämtlicher Spuren auf._

- Actions: **Alle Spuren für Schnitt vorbereiten**
  _Die Befehlsfolge "Prepare all tracks for editing", die nach jeder Aufnahme aufgerufen werden sollte, wurde verbessert und stellt weitere Parameter für den Schnitt um._

- Actions: **Neuer Menü-Eintrag "Customize"**
  _Im Podcast-Menü sind unter dem neuen Eintrag "Customize" folgende Funktionen zusammengefasst: 'Shortcuts and action list' um Tastaturkürzel neu definieren zu können und neue Funktionen hinzuzufügen, 'Track: set track icon' um Spuren mit einem Symbol verzieren zu können, 'Show theme configuration window' um Farben des Theme anzupassen, 'Show theme element finder' um die Benamung von einzelnen Elementen der GUI zu finden sowie 'Auto color' um die Standardfarben von Spuren in Abhängigkeit ihres Namens festzulegen. Weitere Hinweise über die Anpassbarkeit von Ultraschall/Reaper zeigt dieser Vortrag: <FIXME: Link fehlt>_

- StudioLink: **Vollständige Integration des StudioLink Plugins**
  _Als qualitativ in Bezug auf Stabilität, Konstanz und Klangqualität weit überlegene Alternative zu Skype unterstützt Ultraschall nun StudioLink. Ohne den Aufbau einer N-1 Schaltung über die Routingmatrix ist es damit möglich, Ferngespräche mit bis zu 8 PartnerInnen zu führen, die in jeweils separaten(!) Spuren aufgezeichnet werden. Die PartnerInnen können dabei die schlanke Standalone-Version von StudioLink nutzen und benötigen keine eigene DAW. Die Einrichtung einer StudioLink-Schaltung wird im Release-Video erläutert._

- Soundboard: **Soundboard nun auch für Windows und als AU Version für den Mac**
  _Das Ultraschall-Soundboard steht nun mit vollem Funktionsumfang auch unter Windows zur Verfügung. Bei der Mac-Version wurde von VST auf AU Technik umgestellt._

- Installer: **StudioLink Plugin und standalone**
  _Ultraschall liefert im Installer die Version des StudioLink-Plugins aus. Externe GesprächspartnerInnen können sich die [Standalone-Fassung von StudioLink](https://doku.Studio Link.de/standalone/installation-standalone.html) laden._

- Preferences: **Stop Funktion überarbeitet**
  _Die Stop-Funktion bei Aufnahmen wurde so überarbeitet, dass der Aufnahme-Cursor nach Stop an das Ende der bisherigen Aufnahme gesetzt wird. Dies verhindert, dass bei einem erneuten Start der Aufnahme kein alternativer Take angelegt wird, sondern die eigentliche Aufnahme fortgesetzt wird._

- Preferences: **Neue Spuren werden direkt für die Aufnahme aktiviert**
  _Alle neu angelegten Spuren werden direkt auf "Record Arm" geschaltet und sind bereit für die Aufnahme - der zusätzliche Klick auf den roten Arm-Knopf kann damit oft entfallen._

- Misc: **Ultraschall 3 Preset für ReaEQ**
  _Standardmäßig wird bei Aktivierung des ReaEQ Equalizers das Preset Ultraschall 3 aktiviert, dass deutlich weniger Bassanhebung und damit Poltern mit sich bringt._

- Misc: **Ultraschall Presets für gebaute Beiträge**
  _Folgende Effekte werden als Ultraschall-Presets für die Verfremdung von Stimmen für gebaute Beiträge angeboten: Telephone (ReaEQ), Small Room, Large Room, Church (ReaVerbate)_

- Installer: **Bugfix**
  _Fehlerhafte Code-Signatur in Uninstall.command. Vielen Dank an Arnd Layer für den Bugreport._

## 2.1.1 Gropius - 2016-Feb-27

- Theme: **Weiteres Feintuning des neuen Themes**
- Windows: **Anpassung der Farbwerte für die Audiospuren**
  _Auch unter Windows stimmen nun die Zuordnungen von Bezeichnungen und Farbwerte_

## 2.1 Gropius - 2016-Feb-19

- Theme: **Umfangreiches Feintuning des neuen Themes**
  _Der Kontrast von nahezu allen Elementen wurde hoch gesetzt, um die Bedienbarkeit auch in ungünstigen Lichtsituationen zu verbessern. Gruppen von Icons werden optisch zusammengefasst. Einzelne Icons wurden neu gezeichnet um die Funktion klarer werden zu lassen. Die Anmutung aller Buttons wurde vereinheitlicht. Feintuning vieler Farbwerte, um sie der Ultraschall Farbpalette anzupassen. Die Farbpalette ist nun logisch entlang des Regenbogens angeordnet. Schnitte innerhalb eines Items sind durch abgerundete Kanten und eine feine Linie jetzt deutlicher zu erkennen._

- Preferences: **Snap Funktionen (Magnetisches Andocken)**
  _Alle Elemente wie Items, Marker und Regions unterstützen nun das magnetische Andocken, was komplexere Editings vereinfacht._

- Theme: **Routing Matrix enthält Anzeige über Eingangszuordnungen**
  _Im unteren Bereich der Routing-Matrix können nun die Zuordnungen der Input-Kanäle zu den Spuren vorgenommen werden. Somit können nun wirklch alle relevanten Zuordnungen übersichtlich an einer einzigen Stelle erfolgen._

- Misc: **SWS/S&M Extension 2.8.3**
  _Ultraschall wird nun mit der [SWS/S&M Extension 2.8.3](http://www.sws-extension.org/) ausgeliefert_

- Actions: **Neue Shortcuts für flüssiges Editing mit der Tastatur**
  _Mit den Tasten `i` und `o` können Anfang und Ende einer Zeitselektion gesetzt werden - analog zu vielen Videoschnittprogrammen. Mit den Tasten `1` und `2` können Anfang und Ende der Selektion angesprungen werden. Die Tastaturzuordnungen für das Springen zwischen Kapitelmarken wurde geändert, um nicht Kollisionen beim wortweisen Springen in Textabschnitten zu provozieren._

- Actions: **Start/Stop/Pause-Safemode für die Tastatur**
  _Um das unbeabsichtigte Beenden einer laufenden Aufnahme zu verhindern, werden die Tasten `RETURN` und `SPACE` während einer Aufnahme abgefangen. Es erscheint ein Dialog, ob die Aufnahme wirklich gestoppt werden soll._

- Actions: **Robustheit der Kapitelmarken-Funktionen**
  _Sämtliche Kapitelmarkenfunktionen wurden neu in Lua implementiert und interpretieren nun, ob a) eine Aufnahme läuft oder b) eine Aufnahme abgespielt wird oder c) keine Aktion stattfindet. Im Falle von a werden die Marken an die aktuelle Aufnahmeposition gesetzt, bei b) an die aktuelle Abspielposition und bei c) an die aktuelle Position des Edit-Cursors. Die Midi-Ansteuerung wurde so robust gestaltet, dass Kapitelmarken über Midi in jedem Zustand des Programmes gesetzt werden können - selbst während bestehende Marken editiert werden._

- Actions: **Benamung der Ultraschall-Actions**
  _Im über die Taste `?` zu erreichenden Actions-Dialog - in dem sich auch Tastatur-Zuordnungen editieren lassen - sind nun alle Ultraschall-Funktionen einheitlich mit dem Präfix `ULTRASCHALL:` benamst und verständlicher formuliert._

- Soundboard [Nur Mac]: **Bugfix**
  _REAPER stürzt nicht mehr ab, wenn der ins Soundboard zu importierende Ordner nur eine Datei enthält. Vielen Dank an Sven Wiegand für den Bugreport._

- Soundboard: **Bugfix**
  _REAPER stürzt nicht mehr ab, wenn eine der zu importierenden Sounddateien nicht decodiert werden kann. Danke an René Kurfürst für den Bugreport._

## 2.0 Gropius - 2015-Dec-09

- Misc: **Reaper 5 und OS X 10.11 El Capitan**
  _Die Ultraschall ist nun für Reaper 5 und OSX 10.11 El Capitan optimiert. Ältere Versionen werden nicht weiter untertützt._

- Installer [Nur Mac]: **User- statt Systemverzeichnis**
  _Der neue Installer schreibt seine Einträge in das User-Verzeichnis von OSX, nicht mehr nach System._

- Theme: **Komplettes Redesign des Theme**
  _Mehr Konsistenz, weniger Unordnung. Alle Icons und Funktionsbereiche wurden überarbeitet, Farben vereinheitlicht._

- Theme: **Responsiver Mixer**
  _In Abhängigkeit der Dock-Höhe blendet der neue Mixerbereich Bediehnelemente ein und aus._

- Theme: **Neue Ansicht: das Storyboard für gebaute Beiträge.**
  _Beliebige Bereiche einer Aufnahme - etwa einzelne Antworten - können mit Schlagworten versehen werden, nach denen - auch projektübergreifend - gesucht und gefiltert werden kann. Verwaltung beliebig vieler Clip-Datenbanken. Farben und Kommentare, um in komplexen Projekten den Überblick zu behalten. Gruppierungsfunktion für fertige Abschnitte und Regionen, um sie zusammen zu halten. Text-Elemente können frei im Schnittbereich verteilt werden, etwa um Shownotes oder Kommentare zu verwalten._

- Actions [Nur Mac]: **About Screen**
  _Neue Funktion: über einen About-Screen können die derzeit installierten Komponenten mit ihren Versionsnummern angezeigt werden_

- Theme: **Translation**
  _Die Menüs wurden ins Englische übersetzt._

- HUB [Nur Mac]: **Neuer Audiotreiber**
  _Soundflower gehört der Vergangenheit an: entlang der neuen CoreAudio APIs von OSX 10.11 El Capitan wurde die Audio-Engine für virtuelle Soundkomponenten von Grund auf neu geschrieben._

## Release 1.3 - 2015-Jul-05

- WICHTIG: **Bis auf weiteres ist diese Release nur unter Reaper 4.78 lauffähig.**
  _Wir arbeiten an einer Unterstützung der Reaper 5.0 Version, informiert Euch hierzu im <https://sendegate.de/c/ultraschall>._

- Installer: **Der Installer hat ein geschmackvolleres Hintergrundbild bekommen.**
  _Die aktuelle stable Version der SWS Extension (2.7) wird installiert._

- Theme: **Überarbeitung des Podcast-Menüs**
  _Viele Begrifflichkeiten wurden klarer gefasst und vereinheitlicht. Track Templates (Einspieler, Audio-Track) werden direkt im Menü angezeigt._

- Theme: **Größe der Fenster**
  _Die Default-Fenstergröße von Reaper wurde an ein 13" MBP Retina mit Standard-Auflösung optimiert._

- Actions: **Letzte Kapitelmarke löschen**
  _Neue Funktion im Podcast-Menü und als Shortcut: die erste, sich links vom Edit-Cursor (rote Linie) befindliche Kapitelmarke wird gelöscht. In 99% der Fälle ist dies die zuletzt gesetzte._

- Actions: **Setze eine Kapitelmarke 2 Minuten in die Vergangenheit**
  _Eine blaue Kapitelmarke mit der Bezeichnung "\_Past" wird zwei Minuten VOR der derzeitigen Position des Edit-Markers gesetzt. Die hilft beim Markeiren einer Stelle in der Art von "eigentlich sind wir schon längst beim nächsten Thema". Durch die Farbe und den Bezeichner kann die Marke im Schnitt schnell gefunden und an die exakte Position geschoben werden._

- Actions: **Kapitelmarken schreiben und lesen**
  _Das Handling zum Export und Import der Kapitelmarken wurde überarbeitet. Kapitelmarken werden nun im Stil projektname.chapters.txt gespeichert._

- Actions: **Textelement einfügen**
  _In eine leere Spur kann nun an der Position des Cursors ein Text-Element eingefügt werden, das man mit Klick auf die Sprechblase mit beliebigem Text versehen kann der sich dann wie ein Audio-Element verhält. Diese wenn man eine Folge eher "baut", also aus vielen Sequenzen zusammensetzt bei denen etwa die klassischen Kapitelmarken zu unflexibel sind._

- Presets: **Ein neues Einspieler-Track Preset wird mitgeliefert, bei dem bereits ein Ducking voreingestellt ist.**
  _Über die Routing-Matrix werden die Kanäle ausgewählt die das Ducking aktivieren. Die genaue Bediehnung wird im Release-Screencast demonstriert._

- Preferences: **Die Samplerate wird auf 48KHz gesetzt, die Buffer-Size auf 512. "Ignore running Change Notifications" wird gesetzt.**
  _Bis zur Releasde unseres eigenen Audio-Treibers scheint dies unter OSX die am stabilsten funktionierenden Werte zu sein um Knaksen zu verhindern._

- Soundboard: **Neuer Grid-View**
  _Die Ansicht des Soundboard lässt sich umschalten zwischen der bekannten Tabellenansicht und einer Grid-Ansicht_

- Soundboard: **Ein- Ausfaden**
  _Das Ein- und Ausfaden wird nun in sämtlichen Play-Modi unterstützt - etwa einfaden aus Pause etc._

- Soundboard: **Ducking**
  _Es gibt einen neuen Ducking-Schalter der sämtliche gerade laufenden Einspieler sanft auf eine zu definierende, geringere Lautstärke runterregelt über die man gut drübersprechen kann. Ein Ausschalten bewirkt wieder eine Anhebung der Einspieler. Die stärke des Ducking lässt sich in den Soundboard-Settings einstellen._

- Soundboard: **Master-Volume**
  _Die Gesamtlautstärke des Einspieler-Outputs kann über einen Schieberegler eingestellt werden_

- Soundboard: **Themes**
  _Man kann verschiedene Farbsets für das Soundboard einstellen_

- Soundboard: **Live-Mode**
  _Hat man alle Einstellungen im Soundboard wie Lautstärken einmal eingestellt, kann man diese nun für die Sendung in einen "Lock" Modus versetzen: egal welche Presets verwendet werden, die Soundboard Einstellungen bleiben unberührt._

- Misc: **Bugfixes in den Plugins**
  _Einige garstige Speicherlecks wurden in unseren Reaper-Plugins geschlossen. Damit sich diese jeh auswirken hätte man aber einige Tage aufnehmen müssen._

- HUB [Nur Mac]: **Die virtuellen Sound-Devices werden umbenannt, um die Zuordnung in SKYPE intuitiver zu gestalten.**
  _Stereo-Geräte werden vor Mono-Geräte gesetzt um Verschiebungen in der Routing-Matrix vorzubeugen._

## Release 1.2 - 2015-Jan-04

- Installer: **Unter Mac OSX können weite Teile der Distribution nun über einen einfachen Installer abgewickelt werden**
  _Soundflower Ultraschall-Edition, Startlogo, SWS-Extensions sowie das Ultraschall-Soundboard werden installiert. Manuell muss nur noch einmalig die Theme -Datei in Reaper gezogen werden._

- Theme: **Neuer Eintrag im Podcast-Menü: Navigation/Springe zu Play-Cursor (#-Taste)**
  _springt zur aktuellen Position des Play-Cursors (Orange)_

- Theme: **Neuer Eintrag im Podcast-Menü: Soundboard Spur anlegen \*Legt eine Spur an, in der bereits alle Einstellungen für das Ultraschall Soundboard gesetzt sind.**
  _Im sich öffnenden Auswahlfenster muss man einmalig "Soundboard.RTrackTemplate" anwählen. Zur Funktionalität des Soundboard s.U._

- Theme: **Neues Untermenü im Podcast-Menü: Selection**
  \*bieter verschiedene nützliche Aktionen um den Schnitt mittels Selections zu beschleunigen - insbesondere Ripple-Delete zum schnellen Löschen von ganzen Passagen über alle Spuren\*\*

- Theme: **Einheitliche Symbole für Chapters(Dreieck/Strick)**
  _Neue Icons für setze Kapitelmarke, Export Chapters und Audiodatei Schreiben_

- Theme: **Mute- und Solo-Buttons**
  _In der Spuranzeige links sind nun immer die jeweiligen Mute- und Solo-Buttons sichtbar._

- Actions: **Neue Menüpunkte und Kontext-Links für den Umgang**
  _mit der Mute-Spur (Räuspertasten). Separate Mute-Spur für ausgewählten Track an/Ausschalten, Sichtbarkeit aller Mute-Spuren an/ausschalten. In der separaten Mute-Spur kann direkt mit dem Mauscursor und der linken Maustaste ein Mute-Bereich gemalt werden_

- Actions: **Verbessertes Audiodatei schreiben**
  _Der Menüpunkt "Audiodatei Schreiben" und das entsprechende Icon links unten im Edit-View setzen zunächst die Playrate des Projektes auf 1.0 um dann das Render-Menü zu starten. Ferner werden zuvor sämtliche Spuren ausgewählt, so dass man direkt einen Multifrack Export für Auphonic (Stems Export) starten kann._

- Misc: **Das Ultraschall-Soundboard feiert seinen Einstand und ist als VST-Effekt-Plugin realisiert.**
  _Für die genaue Bedienung bitte den Release-Screencast schauen. Funktionen: Verwalten von verschiedenen Sets, Play, Pause, Stop, Loop, Fade, einstellbare Fade-Zeit, regelbare Lautstärke pro Einspieler, direkte OSC-Kopplung. Zur OSC-Steuerung - etwas über ein iOS Gerät oder die Wiimotes - kommt in Kürze ein weiterer Screencast_

- Presets: **Ultraschall-Presets für Expander und EQ**
  _als Ergebnis eine kleinen Workshops mit Michael Kummeth gibt es im EQ das "Ultraschall2" Preset, das einen sehr guten Ausgangspunkt für moderate EQ-Einstellungen bietet._

- Presets: **optimiertes Datei-Handling**
  _Alle Dateien einer Podcast-Folge (Projektdatei, Aufnahmedateien, Peak-Dateien, Kapitelmarken-Datei) werden übersichtlich im Projektordner und mit sinnvollen Unterordnern abgelegt. Details sind dem Screencast zu entnehmen._

- Presets: **Sinnvolle Presets zur Dateibenamung von Aufnahmen eingestellt**
  _(Tracknummer-Trackname-Folgenname)_

- Misc: **Für die Verlinkung des Projektes auf der eigenen Podcast-Seite**
  _werden zwei unauffällige Badges mitgeliefert._

- Misc: **Für Probleme, Anregungen etc.**
  _wurde auf sendegate.de ein Support-Forum eingerichtet das den bisherigen Patter-Raum ersetzt: <https://sendegate.de/c/ultraschall>_

## Release 1.1 - 2014-Jun-09

- Theme: **Es gibt ein neues Menü "Podcast" in dem nach Workflowschritten unterteilt sämtliche Podcast-Funktionen gesammelt sind.**
  _Die Funktionen gliedern sich nach den drei Workflow-Schritten "Setup, Aufnahme und Produktion" und sind auch innerhalb der Gruppen so angeordnet, dass man sie von oben nach unten durchgehen kann. Jede neue Aufnahme durchläuft somit die Einträge (oder zumindest Teile davon) des Menüs von oben nach unten. Die Details sind dem 1.1 Release-Screencast zu entnehmen_

- Actions: **Import von mp4chaps Kapitelmarken (etwa: Shownotes Export) als Marker**

- Actions: **Export von Kapitelmarken als mp4chaps für Podlove und Auphonic**

- Actions: **Mit "E" oder dem neuen Icon werden rote Edit-Marken gesetzt**

- Theme: **im Edit-View ist ein neues Icon verfügbar, das den aktuellen Projekt-Ordner öffnet.**
  _Der Aufnahme-View wurde im unteren Teil erweitert: es sind nun drei Dockbereiche nebeneinader angesiedelt um Spurenaussteuerung, große Uhr sowie Kapitelmarken gleichzeitig im Blick haben zu können._

- Actions: **im Podcast-Menü gibt es den Eintrag "ausgewählte Spuren für Räuspertasten aktivieren".**
  _Hiermit werden für ausgewählte Spuren die Mute-Enveopes aktiviert und die Automation der Spuren auf WRITE gesetzt. Dies beschleunigt den Einsatz von Räuspertasten ganz erheblich, die Hintergründe sind in der Ultrachall-Folge zu Räuspertasten per Wiimote nachzuschauen._

- Actions: **Alle Spuren für Schnitt vorbereiten**
  _mit diesem Eintrag im Podcast-Menü werden die Recording-Buttons aller Spuren ausgeschaltet und der Mute-Automationsmode auf Trim/Read geschaltet. Sollte nach jeder Aufnahme einmal aktiviert werden._

- Theme: **mit einem Rechtsklick auf dem Spurbereich können verschiedene geschmackvoll ausgewählte Preset-Farben ausgewählt werden**
  _kreiert von niemand Geringerem als @[graphorama](https://twitter.com/graphorama)!_

- Theme: **Legt man Spuren mit den Namen "Einspieler" oder "SKYPE" an so werden diese automagisch mit geschmackvollen Farben versehen.**

- Theme: **Diverse optische Anpassungen**
  _Der Headerbereich ist etwas heller gestaltet. Die Wellenformen werden passend zur Rest-GUI invertiert dargestellt, also hell auf dunkelfarbigem Grund. Die Anzeige, welche Bereiche einer Spur ausgewählt wurden, wurde erheblich klarer gestaltet._

- Theme: **Die Icons wurden mit einer tüchtigen Portion Feenstaub überschüttet.**
  _Dies bezieht sich sowohl auf die etwas wertigere Optik, als auch auf den "State" der nun sauber gehalten wird - man hat jederzeit den Überblick, welcher View aktiv ist, welches Routing-Preset, ob Ripple-Edit aktiv ist sowie ob die Mute-Spuren sichtbar/unsichtbar geschaltet sind._

## Release 1.0 "Rams" - 2014-Feb-09

- Theme: **Ultraschall-Logo und Versionsnummer eingebaut**
  _wird in Zukunft wichtig sein um schnell sehen zu können auf welcher Version man unterwegs ist_

- Actions: **Exportformat der Kapitelmarken von .csv auf .txt umgestellt**
  _Damit man Kapitelmarken einfacher per Cut&Paste in Podlove beim Anlegen einer Episode verwenden kann wurde das Dateiformat für den Export von .csv auf .txt geändert. Die Dateien funktionieren wie bisher ebenfalls millisekundengenau in Auphonic._

- Preferences: **Views speichern nicht mehr die Fensterposition**
  _Wenn man die Views anpasst, wird nicht mehr die Hauptfenster-Position mit gespeichert / verändert. Das sollte nun deutlich weniger verwirrend sein._

## RC4 - 2014-Feb-07

- Theme: **Playrate Regler eingebaut**
  _Oben rechts befindet sich nun ein Regler, mit dem man die Abspielgeschwindigkeit des Podcast beschleunigen kann. Faktor 1,5 kann man noch ganz gut hören - diese Funktion kann im Schnitt (Edit View) nützlich sein um sich zügiger durch eine Aufnahme zu arbeiten. Mit Rechtsklick auf dem Regler kann man den Range des Faders einstellen, ferner sollte dort immer "preserve pitch" aktiviert sein (wird beides über Project Templates gespeichert, nicht global)_

- Actions: **Tastatur-Shortcuts für Navigation durch Projekt**
  _um sich flüssiger im Projekt bewegen zu können wurden zwei Tastenbelegungen geändert: alt+links/rechts springt zur vorherigen/nächsten Kapitelmarke, alt+rauf/runter zur jeweils nächsten Itemkante. Letztere Funktion entfaltet großen Charme in Kombination mit "Stile entfernen", da man so schnell die einzelnen Einspieler durchlaufen kann._

- Preferences: **Master output auch als source in der Routing Matrix**
  _Aus Gründen - die nur die Reaper Entwickler kennen - werden in den famosen neuen Presets zwar die Sends für die Tracks gespeichert, nicht jedoch die Master-Sends. Um dennoch ein 1KlickRouting (tm) umsetzen zu können wandert die Masterspur wieder als Quelle in die Routingmatrix zurück. Das Setting ist damit: Send auf den Master ist immer aktiviert, dieser schickt aber nicht immer zurück in den Mixer. Ich muss dazu mal eine Screencastfolge machen da zu abstrakt, aber es wird alles gut._

## RC3 - 2014-Feb-06

- Preferences: **Menüleiste zeigt verfügbaren Speicher an**
  _in der Menüleiste wird nun angezeigt, wieviel freier Plattenplatz noch auf dem Laufwerk vorhanden ist, auf dem aufgezeichnet wird._

- Theme: **Bereichsbeschriftungen**
  _die beiden Icon-Bereiche Views und Routing-Presets haben Beschriftungen bekommen um die Funktionen etwas klarer zu machen. Die Beschriftungen selbst sind sinnvoll mit Links zu Preset-Fenstern belegt._

- Actions: **Automagische Kapitelmarkengenerierung**
  _Im Edit-View finden sich links zwei neue Icons: diese können radikal bei der Erstellung von Kapitelmarken helfen. Wenn man eine Spur für Einspieler verwendet und diese die Kapitelübergänge markieren, so kann man diese Spur auswählen und dann das erste Icon "Stille entfernen aktivieren - es startet ein Dialog der relativ lange läuft. Ist er bei 100% kann man mit "Split" die komplette Einspielerspur so zerschneiden lassen, dass nur die einzelnen Einspieler übrig bleiben und Stille komplett entfernt wird. Nun kann man das zweite Icon aktivieren: Kapitelmarken-Foo setzt an den Beginn jeden Einspielers automatisch eine Kapitelmarke. Diese muss man nun nur noch sinnvoll benennen, ein mühsames Marken durch die Gegend schieben ist nicht mehr notwendig (aber natürlich immer noch möglich)"_

- Theme: **Icon um die Mute-Spur ein- und auszublenden**
  _Ein gängiges Konzept im Podcasting ist die Räuspertaste. Wie in der entsprechenden Ultraschall-Folge erklärt wird diese optimaler Weise über eine Mute-Automation umgesetzt. Da diese Anzeige häufig etwas im Weg ist (besonders beim Schneiden) gibt es nun ein Icon dass die Spuren für alle Tracks ein- oder ausblenden._

## RC2 - 2014-Feb-03

- Preferences: **Menüs angepasst**
  _ein paar sinnvolle Einträge sind wieder zurück gewandert_

- Preferences: **Diverse Korrekturen**
  _einige Einträge wurden korrigiert: das vertikale Verschieben von Tracks erzeugt keine Automationspuren, das Verlängern von Tracks loopt nicht den Klanginhalt, ctrl-linke Maus erzeugt einen Maus-Rechtsklick, es wird wieder nur eine Datei to Spur geschrieben_

- Theme: **Track-Farbanpassungen**
  _Ein wenig mehr Farbe im Track-Bereich_

## RC1 - 2014-Feb-02

- Theme: **Diverse Farbanpassungen**
  _Die Soundspuren haben einen leichten Verlauf erhalten der die Anmutung noch edler macht. Der Hintergrund der großen Zeitanzeige im Aufnahme-View wurde an den Resthintergrund angepasst. Das Icon zur Anzeige des Ripple-Edit Status wurde an die anderen angepasst. Einige Icons wurden für bessere Verständlichkeit ausgetauscht - etwa zum Setzen von Kapitelmarken_

- Preferences: **Menüs gelichtet**
  _Viele Einträge in den Reaper-Menüs sind für Podcastproduzierende völlig nutzlos und verwirrend. Etliche Einträge wurden daher aus den Menüs entfernt. Die Originalmenüs mit allen Einträgen bleiben dabei als letzter Eintrag in den jeweiligen Menüs erhalten._

- Actions: **Ein weiteres Bedienkonzept wird eingeführt: Snapshots zum Speichern und Abrufen von Routing/Mixerpresets**
  _Schon mit den VProdunktions-Views (F7, F8, F9 oder die drei Icons links oben) wurde versucht den klassischen Podcastingworkflow klarer zu unterstützen. Neben diesen Views, die sich auf Fensteraufbau und sichtbare Werkzeuge konzentrieren, tritt nun das Konzept der Snapshots. Diese können im Setup-View (F7 oder Mixer-Icon) rechts unten im Dock als Reiter angesteuert werden und setzen zwingend die SWS-Extension voraus (siehe Installation). Der Ablauf ist simpel: man stellt sich für die verschiedenen Stadien einer Podcastfolge die benötigten Routing-Setups in der Routing-Matrix zusammen und speicher diese in den Snapshots, die sich dann bequem über die Icons links mittig abrufen lassen. Beispiel: während der Preshow können sch bereits alle vor Ort hören, auf den Stream geht aber nur die Fahrstuhlmusik bis die Sendung beginnt. Bevor man das eigentliche Intro abspielt, schaltet man das Preset um auf Produktion (Mikrophon-Icon) und schon gehen alle Sprachkanäle ebenfalls auf den Stream. In der Poshow (Tassebier) kann leise Musik im Hintergrund laufen, im Schnitt-Preset (Schere) ist für das Abhören nur der Kanal hin zur Abhöreinheit (DAW oder lokaler Kopfhörerausgang) aktiviert. Snapshots sind unabhängig von den Views. Man kann also während einer Sendung beliebig in den Views umherschalten. Die Spanshots hingegen greifen direkt in das Routing ein und sollten nur bewusst umgeschaltet werden - sonst ist etwa der Stream tot. Zur Release gibt es eine Ultraschall-Screencast Folge wie man damit produktiv arbeitet._

- Misc: **Auphonic verarbeitet nun unser neues Kapitelmarkenformat ohne Frames.**
  _Derzeit rundet Auphonic auf ganze Sekunden ab, man hat also etwas Sicherheitsspielraum nach vorn was eher ein Vorteil ist._

## BETA 4 - 2014-Jan-28

- Theme: **Diverse Farbanpassungen**
  _noch stärker als bisher werden Farben und Formen reduziert. Mit diesem Theme dürfte Reaper die reduzierteste DAW überhaupt sein - selbst die Buttonanmutungen wurden reduziert._

- Theme: **Neue Iconleiste**
  _dynamische Iconleisten sind in Reaper nicht vorgesehen, was uns nicht davon abhalten sollte mittels Windows Presets welche zu bauen. Man kann nun links neben den Spuren die drei Views Setup, Sendung und Nachbereitung umschalten und hat sogar eine Rücmeldung in welchem View man sich gerade befindet. Dazu gibt es ein erstes Experiment mit SWS Snapshots: links neben dem Mixerbereich finden sich drei frei belegbare Snapshots, mit denen man sämtliche Mixer- und Routingeinstellungen speichern und abrufen kann - etwa um in der Preshow Musik einzuspielen während die Podcaster sich zwar unterhalten können (auch mit einem Skype-Partner) aber nicht auf den Stream gehen, dann die Sendung und anschließend eine Aftershow mit leisem Musikteppich_

## BETA 3 - aka "Der Zeitvernichter" 2014-Jan-25

- Preferences: **File/Project Settings... 50 - "Project Framerate"**
  _sorgt für sauberen Export der Kapitelmarken ohne Zeitversatz über die Projektlänge. UNBEDINGT so einstellen, selbst wenn man die Distribution ansonsten nicht nutzen möchte, Hintergrund: <https://ultraschall.wikigeeks.de/2014/01/25/howto-zeitversatz-bei-kapitelmarken-beheben>_

- Preferences: **Umstellung der Zeiteinheit auf Minuten:Sekunden**
  _an diversen Stellen. Sorgt nachhaltig dafür, dass Kapitelmarken sauber bis auf die Millisekunde nach Auphonic exportiert werden Teil 2._

- Preferences: **Audio/Rendering - 0ms "Tail length when rendering project or stems, or freezing track"**
  _Eine Aufnahme ist nach dem Rendern exakt so lang wie vorher in der Timeline angezeigt. Der bisherige Presetwert von 1.000ms fügt eine stille Sekunde am Ende hinzu und verwirrt vielleicht._

- Misc: **Footprint der Distribution auf 1/3 reduziert.**

## BETA 2 - 2014-Jan-23

- Preferences: **Audio/Recording - OFF "Always show full track control panel on armed track"**
  _ermöglicht auch Spuren die für die Aufnahme scharfgeschaltet sind in der Höhe sehr klein zu schieben. Dieser Schalter hat im Ultraschall-DR Theme generell keine Funktion, da es hier über das Theme deaktiviert wird._

- Preferences: **Project/Track-Sends Defaults - Input 1 "Record config"**
  _Sorgt dafür, dass bei jeder neu angelegten Spur das Record Monitoring sofort aktiviert ist._

- Theme: **neuer VU-Meter Balken**
  _die Pegelanzeige ist nun dreigeteilt bei Aufnahme (Grün-Gelb-Orange) und Abspielen (Blau - Gelb - Orange) für die bessere Aussteuerung im Setup-View (F7): Grün (Blau) reicht von -60db bis -18, Gelbe von -18 bis -6db (gut gepegelter Durchschnitt) und Orange von -6 db bis 0 db (Headroom für Peaks wie lautes Lachen). Wenn man mit einem Hardware-Limiter arbeitet sollte dieser so konfiguriert werden, dass die Aussteuerung knapp in den Orangenen Bereich (-3db) hineinreicht._

## BETA 1 - 2014-Jan-21

- Actions: **Actions/Show Action List... - Mousewheel "View:Scroll vertically"**
  _Schaltet das Zoomen mit Zweifinger-Trackpad rauf/runter ab und ersetzt es durch vertical-Scrolling wie überall unter OSX_

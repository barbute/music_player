# project-music_player

A continuation of my music player project.

## Description

This origins of this project begin in my CE 1100 (Intro. to Computer/Electrical Engineering) class, where my lab partner and I had to build something with an Arduino. We settled on a crude iPod Shuffle clone.

With this project, myself and my new lab partner for CE 1202 need to modify and improve upon it. We have decided to add a volume control knob, the ability to go to the previous or next song in the playlist, and swap out the single-color status LED with an RGB one for a more polished status-light set.

Here is a screenshot of the circuit in the TinkerCAD simulator:
![Music Player Circuit TinkerCAD Screenshot](/attachments/music_player_tinkercad_screenshot.png)

If time permits I am also interested in the ability to write playlists to the Arduino whilst it is running the program via USB over Serial protocol.

### TODO

- [ ] Add schematic and pinouts
- [ ] Fix pot. not controlling volume logarithmically (see http://www.geofex.com/Article_Folders/potsecrets/potscret.htm)
- [ ] Start writing the actual logic
- [ ] Polish README (IE rewrite with my standard template)
- [ ] Continue potentiometer adjustment testing. Maybe add voltae-buffer (see https://sound-au.com/articles/followers.html#s1) since the current dataset suggests that something is not working

### Useful links

- [Buzzer as speaker article](https://projecthub.arduino.cc/SURYATEJA/use-a-buzzer-module-piezo-speaker-using-arduino-uno-cf4191)
- [`Serial.println()` | Arduino](https://docs.arduino.cc/language-reference/en/functions/communication/serial/println/)
- [`analogRead()` | Arduino](https://docs.arduino.cc/language-reference/en/functions/analog-io/analogRead/)
- [iPod Shuffle | Wikipedia](https://en.wikipedia.org/wiki/IPod_Shuffle)
- [C++ `struct` | W3](https://www.w3schools.com/cpp/cpp_structs.asp)
- [Intro to non-inverting amp](https://www.electronics-tutorials.ws/opamp/opamp_3.html)
- [Voltage followers](https://sound-au.com/articles/followers.html#s1)
- [Pots and audio](http://www.geofex.com/Article_Folders/potsecrets/potscret.htm)
- [Radio circuits](https://www.allaboutcircuits.com/textbook/semiconductors/chpt-9/radio-circuits/)
- [MD image sizing](https://www.markdownguide.org/hacks/#image-size)
- [Add to PATH](https://unix.stackexchange.com/questions/26047/how-to-correctly-add-a-path-to-path)
- [Bash `free` | W3](https://www.w3schools.com/bash/bash_free.php)
- [Bash Guide](https://guide.bash.academy/)
- [Change default shell on macOS](https://www.howtogeek.com/444596/how-to-change-the-default-shell-to-bash-in-macos-catalina/)


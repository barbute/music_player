# logs

Engineering logs of progress.

# 2026-04-22

Started on project. Created basic circuit and code. Found issue with using a pot as a volume control. 

We are using a "linear-taper" pot, meaning that resistance increases at a linear-rate (which makes sense in most cases). However human hearing is "logarithmic" meaning that if the pot is turned at halfway resistance, we would only notice ~20% of the epxected volume. Thus we have to improvise a workaround.

After some "research" I have found that adding a resistor to the wiper, then connecting it in series to the pot's ground, then taking the signal output after the resistor junction produces a taper that is roughly logarithmic.

I have not yet worked out the optimal resistor-to-pot resistance ratio, as I do not yet fully understand how it works (need to better understand [this article about pots and audio](http://www.geofex.com/Article_Folders/potsecrets/potscret.htm)). For now, the resistor is 1/10 the resistance of the pot (pot is 10k ohm, resistor is 1k ohm).

Unfortunately when simulating this workaround, the output signal values followed a doubly exponentially growing curve.

| Pot. Units Turned | Signal Output |
| ----------------- | ------------- |
| 1 | 58 |
| 2 | 69 |
| 3 | 85 |
| 4 | 109 |
| 5 | 159 |
| 6 | 273 |
| 7 | 944 |

One of the issues may be that the impedance of the speaker that I am using is too low, thus creating an almost virtual short when connecting it to the wiper (idek if what I just said was correct). Using a voltage buffer may be the solution to offering impedance whilst achieving the desired signal for the speaker (see [this article about voltage followers](https://sound-au.com/articles/followers.html#s1) and [this article about non-inverting op-amps](https://www.electronics-tutorials.ws/opamp/opamp_3.html)).

In all, there is still much research and work to be done.

# 2026-04-28

Setup `deploy.sh` and `test.sh` scripts for using the [`arduino-cli`](https://docs.arduino.cc/arduino-cli/) to deploy programs to the board. Need to write README on build-deploy process.

Built and tested the volume control portion of the circuit in an open lab.

Here is the data I collected:

Potentiometer: $10 \text{k} \Omega$
GND-to-wiper resistor: $1 \text{k} \Omega$
Output component impedance: 330 ohm

| Pot. Fractional Rotation | Signal Output (V) |
| ------------------------ | ----------------- |
| 0.2 | 2.05 |
| 0.4 | 2.09 |
| 0.6 | 2.17 |
| 0.8 | 2.41 |
| 1.0 | 9.25 |

The results somewhat mimic what was obtained in the simulation, with a *giant* jump in signal output between the last and second-to-last fractional rotation of the pot. I am still eluded by what is causing this issue.

Unfortunately, due to time constraints I do not believe I will be able to create a proper fix and may just have to settle for this.

# 2026-04-30

Wrote `Button.h` to abstract away interactions with buttons. Probably not the best idea to pass a ptr to a function as an arg but who cares. I tested the button logic in sim, and everything looks to be working. The polling should be non-blocking, and the debounce seems to work properly.

Also added `includepath` stuff (added `.vscode` confs). Might want to specify in the README that the paths are platofrm dependent. I'm still going to commit them mostly just for future reference.

Reorganize directory structure:

```
music_player/
├── data/
│   ├── Mario.h
│   └── Tetris.h/
├── src/
│   ├── input/
│   ├── output/
│   ├── player/
│   └── util/
├── test/
└── music_player.ino
```

The main idea is to have only the very high-level logic in `music_player.ino` which is then deployed to the Arduino. Everything else is moved into `src/`.

Moved RGBLED code into separate files. Had to use `constexpr` to prevent multiple definitions of same constant (for pre-defined colors). See [this](https://www.geeksforgeeks.org/cpp/understanding-constexper-specifier-in-cpp/) for more info about it.

Added script to deploy code and then view serial output.

# 2026-05-02

Ok, completely reworking objectives (panic mode).

New minimum specs are:

- [ ] Working play/pause, prev song, next song buttons
- [ ] Toggle "random song" button, where the next song that plays will not be in playlist order
- [ ] "Good-enough" volume control knob using potentiometer
- [ ] Songs hard-coded in header files
- [ ] Working multi-color RGB status light (or at least make it flash pretty colors)

Added songs and `Pitches.h` to project

Switch songs over to using `PROGMEM`. See [this article](https://docs.arduino.cc/language-reference/en/variables/utilities/PROGMEM/) for more about it.

Bind actions to buttons on construction. This way if multiple polls are called in the same state they don't overwrite each other. Besides, each button should realistically only be doing one thing regardless of the state (if we wanted to do something more advanced could use an [EventLoop](https://docs.wpilib.org/en/stable/docs/software/convenience-features/event-based.html#downcasting-booleanevent-objects)).
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
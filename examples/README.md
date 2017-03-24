# Example scripts to create "breathing LED" effect (something akin to Mac's sleep indicator light)

  * **linear.pl** uses simple incremental change in PWM cadence, one per time tick
  * **exponential.pl** provides a more "natural" pattern (Thanks to Sean Voisen, http://sean.voisen.org/blog/2011/10/breathing-led-with-arduino)

  **Use suitable resistor in series with an LED connected to PA05 (middle pin on the UART0 header)**

<pre>
> # Turn PWM on
> echo 1 > /sys/class/pwm-sunxi-opi0/pwm0/run
> ./linear.pl
</pre>

![OPI0 PWM Driver Demo](https://github.com/iboguslavsky/pwm-sunxi-opi0/blob/master/examples/00003.gif "Orange Pi Zero PWM LED Example" | width=400)
![OPI0 PWM Driver Demo](https://github.com/iboguslavsky/pwm-sunxi-opi0/blob/master/examples/00000.gif "Orange Pi Zero PWM LED Example" | width=400)

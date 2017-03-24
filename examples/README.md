# Example scripts to create "breathing LED" effect (something akin to Mac's sleep indicator light)

  * **linear.pl** uses simple incremental change in PWM cadence, one per time tick
  * **exponential.pl** provides a more "matural" pattern (Thanks to Sean Voisen, http://sean.voisen.org/blog/2011/10/breathing-led-with-arduino)

<pre>
> # Turn PWM on
> echo 1 > /sys/class/pwm-sunxi-opi0/pwm0/run
> ./linear.pl
</pre>

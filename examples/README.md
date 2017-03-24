# Example script to create "breathing" LED (something akin to Mac's sleep indicator light)

<pre>
> # Turn PWM on
> echo 1 > /sys/class/pwm-sunxi-opi0/pwm0/run
> ./pwm.pl
</pre>

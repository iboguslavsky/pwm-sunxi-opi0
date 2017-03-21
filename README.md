# pwm-sunxi-opi0

Loadable Kernel Module to support PWM on Allwinner H3 / H2+ SoC (sun8i / sun8iw7p1). Used in Orange Pi Zero.

Provides access to PWM configuration parameters from userspace. 

Once loaded, the following sysfs structure is created:

<pre>
-- pwm-sunxi-opi0
      |
      +----pwm0
               |
               +---run
               +---prescale
               +---entire_cycles
               +---active_cycles
               +---polarity
	</pre>

	
  Only supports PWM0. It's exposed via PA6, which is an Rx pin in the UART header (middle pin).

# pwm-sunxi-opi0

Loadable Kernel Module to support PWM on Allwinner H3 / H2+ SoC (sun8i / sun8iw7p1). Used in Orange Pi Zero.

Provides access to PWM configuration parameters from userspace. Only exposes PWM0 (PWM1 will be added once H2+ SoC documentation is available). PWM0 is on PA5, which is exposed as UART0_RX (middle pin on the UART header). Remap in FEX.

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
               +---freqperiod
               +---polarity
	</pre>

	
  Only supports PWM0. It's exposed via PA6, which is an Rx pin in the UART header (middle pin).

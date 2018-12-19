# pwm-sunxi-opi0

Loadable Kernel Module to support PWM on Allwinner H3 / H2+ SoC (sun8i / sun8iw7p1). Works with Orange Pi Zero.

**Tested on Kernel (4.14.X)**

Provides access to PWM configuration parameters from userspace. Only exposes PWM0 (PWM1 will be added once H2+ SoC documentation is available). PWM0 output is on PA05, which is exposed as UART0_RX (middle pin on the UART header). 

<img src="https://github.com/iboguslavsky/pwm-sunxi-opi0/blob/master/images/00000.gif" width="500">

Installation
------

Remap pins in FEX:
<pre>
; Disable debug UART0
[uart_para]
uart_debug_port = 0
uart_debug_tx = port:PA04<2><1><default><default>
uart_debug_rx = port:PA05<2><1><default><default>

; Enable PWM0 on PA05
[pwm0_para]
pwm_used = 1
pwm_positive = port:PA05<3><0><default><default>
</pre>

<pre>
> fex2bin orangepizero.fex orangepizero.bin
> shutdown -r now
</pre>

After the board comes back up:

<pre>
> git clone https://github.com/iboguslavsky/pwm-sunxi-opi0.git
> cd pwm-sunxi-opi0
> make
> insmod ./pwm-sunxi-opi0.ko
</pre>

Once loaded, the following sysfs directory structure will be created:

<pre>
/sys
  │
  └─ /class 
       │
       └─ /pwm-sunxi-opi0
	    │
	    └─ /pwm0
	         │
	         ├── run
	         ├── prescale
	         ├── entire_cycles
	         ├── active_cycles
	         ├── polarity
	         └── freqperiod
</pre>
---
**Positive Polarity PWM cadence diagram**
![PWM Cadence](https://github.com/iboguslavsky/pwm-sunxi-opi0/blob/master/images/pwm.png "PWM Cadence Diagram")

  * **run** (read / write) - **NOTE: This needs to be run  first before any other values are set**
  
    Enable / disable PWM0
    
    *Allowed values: 0, 1*
	
  
    <pre>
    echo 1 > /sys/class/pwm-sunxi-opi0/pwm0/run
    echo 0 > /sys/class/pwm-sunxi-opi0/pwm0/run
    </pre>
 
  * **prescale** (read / write)
  
    Divide 24MHz PWM clock by a specified prescaler 
  
    *Allowed Values: hex value from the table below*
    
    <pre>
    PRESCALE_DIV120  = 0x00, // Divide 24mhz clock by 120 => PWM clock: 200Khz, PWM single "cycle": 5us
    PRESCALE_DIV180  = 0x01,
    PRESCALE_DIV240  = 0x02,
    PRESCALE_DIV360  = 0x03,
    PRESCALE_DIV480  = 0x04,
    PRESCALE_INVx05  = 0x05, // Invalid prescaler setting
    PRESCALE_INVx06  = 0x06,
    PRESCALE_INVx07  = 0x07,
    PRESCALE_DIV12k  = 0x08,
    PRESCALE_DIV24k  = 0x09,
    PRESCALE_DIV36k  = 0x0a,
    PRESCALE_DIV48k  = 0x0b,
    PRESCALE_DIV72k  = 0x0c,
    PRESCALE_INVx0d  = 0x0d,
    PRESCALE_INVx0e  = 0x0e,
    PRESCALE_DIV_NO  = 0x0f
    </pre>
  
  
  * **entire_cycles** (read / write)
    
    Specify number of ticks in a complete PWM period
    
    *Allowed values 0..65534*
  
  
   * **active_cycles** (read / write)
     
     Specify number of active ticks in a PWM period  
     
     *Allowed values 0..65535*
  
 
  * **polarity** (read / write)
  
    Specify polarity of the duty cycle (positive / negative)
    
    *Allowed values: 0, 1*
      
  
  * **freqperiod** (read only)
    
    Show a calculated frequency of the PWM cycle (accounting for PWM clock divider and specified PWM period)
    

---
**Sample of frequency values**

|prescale (in decimal) | entire_cycles | Result in Hz (Prefix Hz) | active_cycles (Duty%)|
|-------|-------|----------------------|--------|
|15     | 1     | 12000000 Hz (12 MHz) | 1 (50%)|
|15     | 10    | 2400000 Hz (2.4 MHz) | 5 (50%)|
|15     | 100   | 240000 Hz (240 kHz)  | 50 (50%)|
|15     | 1000  | 24000 Hz (24 kHz)    | 500 (50%)|
|15     | 10000 | 2400 Hz (2.4 kHz)    | 5000 (50%)|
|0      | 1     | 100000 Hz (100 kHz)  | 1 (50%)|
|0      | 10    | 20000 Hz (20 kHz)    | 5 (50%)|
|0      | 100   | 2000 Hz (2 kHz)      | 50 (50%)|
|0      | 1000  | 200 Hz (0.2 kHz)     | 500 (50%)|
|0      | 10000 | 20 Hz (0.02 kHz)     | 5000 (50%)|

As you can see the **active_cycles** is always lower or equal to **entire_cycles**, and depends on the necessary duty/frequency you need is necessary to recalculate the **prescale**.

And be aware that the final result of the frequency may vary do to how things may get rounded.

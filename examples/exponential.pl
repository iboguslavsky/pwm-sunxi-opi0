#!/usr/bin/perl
# Implement more "natural" pattern
# Thanks to Sean Voisen
# http://sean.voisen.org/blog/2011/10/breathing-led-with-arduino/
#
use Time::HiRes qw /time alarm sleep clock_gettime/;

use constant PI => 3.1415926;
use constant ENTIRE_CYCLE => 255;

# PWM cadence change interval (in ms)
use constant INTERVAL => 0.005;

open ENTIRE, '> /sys/class/pwm-sunxi-opi0/pwm0/entirecycles'
  or die "Can't open entirecycles file ($!)\n";
print ENTIRE ENTIRE_CYCLE;
close ENTIRE;

open ACTIVE, '> /sys/class/pwm-sunxi-opi0/pwm0/activecycles'
  or die "Can't open activecycles file ($!)\n";

# Unbuffer file
$old_fh = select (ACTIVE);
$| = 1;
select ($old_fh);

while (1) {

  # Change brigtness every 10ms
  sleep (.01);
  print ACTIVE int((exp (sin ($cnt++ / 200*PI)) - 0.36787944) * 108.0);
}

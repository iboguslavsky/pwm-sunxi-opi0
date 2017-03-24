#!/usr/bin/perl
use Time::HiRes qw /time alarm sleep/;

use constant ENTIRE_CYCLE => 255;

# PWM cadence change interval (in ms)
use constant INTERVAL => 0.01;

open ENTIRE, '> /sys/class/pwm-sunxi-opi0/pwm0/entirecycles'
  or die "Can't open entirecycles file ($!)\n";
print ENTIRE ENTIRE_CYCLE;
close ENTIRE;

open ACTIVE, '> /sys/class/pwm-sunxi-opi0/pwm0/activecycles'
  or die "Can't open activecycles file ($!)\n";

$old_fh = select(ACTIVE);
$| = 1;
select($old_fh);

while (1) {
my $i;

  for ($i = 0; $i <= ENTIRE_CYCLE; $i++) {
     print ACTIVE "$i\n";
     sleep (INTERVAL);
  }

  sleep 0.5;

  for ($i = ENTIRE_CYCLE; $i >= 0; $i--) {
     print ACTIVE "$i\n";
     sleep (INTERVAL);
  }

  sleep 0.5;
}

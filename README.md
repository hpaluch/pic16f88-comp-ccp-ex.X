# PIC16F88 Comparator and CCP demo in XC8

The ultimate goal of this project is to use Comparator of PIC16F88
to detect period (or crossing the "middle") of any analog signal
and then use Comparator output to measure that period using capture/compare
module.

Because of complexity to projects is done in stages (called milestones).

## Milestone 1 (M1)

* Blinking LED on RA3 PIN2 (using trivial `__delay_ms()` function - just
  to know that PIC is running
* 1 MHz f_cy (CLK/4) out on RA6/OSC2/CLK0 PIN 15, to verify
  that internal oscillator is properly calibrated

You can see results in [milestones/m1-led-and-clock-1MHz][milestones/m1-led-and-clock-1MHz]


# Requirements

Hardware:
- [PICDEM Lab Development Kit][DM163045] with [PIC16F88][PIC16F88] (mine was included
  in package, but I'm not sure if it still there in current PICDEM version)
- in many cases you will need signal generator and scope and also logic
  analyzer - all three things are included in `Digilent Analog Discovery 2`

Software:

- MPLAB X IDE v5.45
- XC8 v2.32
- DFP 1.2.33 (Device Family Pack - can be updated in menu Tools -> Packs)

[DM163045]: http://www.microchip.com/Developmenttools/ProductDetails/DM163045 "PICDEM Lab Development Kit"
[PIC16F88]: https://www.microchip.com/wwwproducts/en/PIC16F88 "PIC16F88 Overview"


# PIC16F88 Comparator and CCP demo in XC8

The ultimate goal of this project is to use Comparator of PIC16F88
to detect period (or crossing the "middle") of any analog signal
and then use Comparator output to measure that period using capture/compare
module.

Because of complexity to projects is done in stages (called milestones).

## Milseton 2 (M2)

* Test Cvref (comparator Voltage reference values) and verify
  that they match Expected values

We tested values for CVRR=1 where following formula is valid `=5.08*$A2/24`
(for Vss = 5.08V, valid `$Ax` values are 0 to 15).

Theoretical values from spreadsheet are here:

```
CVR	Cvref Formula
0	0.000V =5.08*$A2/24
1	0.212V ...
2	0.423V
3	0.635V
4	0.847V
5	1.058V
6	1.270V
7	1.482V
8	1.693V
9	1.905V
10	2.117V
11	2.328V
12	2.540V
13	2.752V
14	2.963V
15	3.175V
```

Here are values measured using `Digilent Analog Discovery 2` scope:

![Testing Cvref 16 values](https://raw.githubusercontent.com/hpaluch/pic16f88-comp-ccp-ex.X/milestones/m2-test-Cvref/cvref-tests-cvrr1-scope.png)

NOTE: Some details are as usual in [comp_ccp_ex.c](comp_ccp_ex.c) source code.

## Milestone 1 (M1)

* Blinking LED on RA3 PIN2 (using trivial `__delay_ms()` function - just
  to know that PIC is running
* 1 MHz f_cy (CLK/4) out on RA6/OSC2/CLK0 PIN 15, to verify
  that internal oscillator is properly calibrated

You can see results in [milestones/m1-led-and-clock-1MHz](milestones/m1-led-and-clock-1MHz)

NOTE: To return back current project to this Milestone, just
copy [milestones/m1-led-and-clock-1MHz/comp_ccp_ex.c](milestones/m1-led-and-clock-1MHz/comp_ccp_ex.c) to this main project directory (overwriting current
version).


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


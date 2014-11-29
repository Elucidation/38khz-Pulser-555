38khz-Pulser-555
================

Basic circuit board to output a 38 Khz ~51% duty cycle signal using a
555 timer in astable mode. The reset allows an arduino to drive logic at a lower
rate for things such as sending 38KHz IR signals to a TSOP receiver (TV Remote).

![Board](http://i.imgur.com/V8HO4Cs.png)


Arduino Frequency Detector Script
---
The script counts the number of rising edge triggers on pin #2 and returns
the rate every second; the frequency in hertz.

As a secondary utility it also outputs PWM signals of roughly 1, 19 and 38 khz for testing.

Some example println's from the #3 pin:

```
38498
38508
38469
38508
38469
```

This is roughly 38,500 interrupts triggered per second, or 38.5 khz frequency.
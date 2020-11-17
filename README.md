# MaslowCNC-Due

### This is firmware to control a Maslow CNC-type machine.

Quick Installation:

_You can optionally watch a [video of the following steps](https://www.youtube.com/watch?v=WoopPgRBfx4)_.

- Download this repository (green button, above) and unzip it somewhere convenient.
- Make sure the shield is attached to your Arduino Due.
- If you are using the M2 shield (3 heatsinks), no changes to any downloaded files are required.
- If you have a shield with only 2 heatsinks, change from v2 to v1 at the top of `MaslowDue.h`.
- Open the `.ino` file (from the unzipped folder) in the Arduino IDE.
- Choose `Arduino Due` from `Tools` -> `Board: ...` (you might need to [install it](https://www.arduino.cc/en/Guide/ArduinoDue)).
- Choose the correct port from `Tools` -> `Port: ...` (it will likely say `Arduino Due (Programming Port)` in the menu).
- `Upload` the firmware to the Arduino (find it in the `Sketch` menu).
- You should see `Done uploading` and `Verify successful` near the bottom of the Arduino IDE.

Before moving on, open the `Serial Monitor` in the Arduino IDE and select a baud rate of `38400`. You should immediately see something like this (though the version number at the top will differ, it should be higher than the one shown here):

```
[VER:1.1g.20200909.MaslowDue:]
[OPT:VNM+H,35,255]

Grbl 1.1g ['$' for help]
```

If you see nothing, then your Arduino is not responding. You might have the wrong port or board. If you see gibberish (random, non-english characters), you have the wrong baud rate.

Otherwise, you're ready to [use Makerverse](http://makerverse.com).

.....

_:warning: Making your own shield can be cumbersome and expensive. Our partners at [Maker Made](https://makermade.com/) offer both [a complete kit](https://makermade.com/product/m2-automated-cutting-machine-kit/), and [just the shield](https://makermade.com/product/complete-m2-due-board-with-case/) for those interested._

# About this upgrade...

The [MaslowCNC firmware](https://github.com/MaslowCNC/Firmware) and [GroundControl](https://github.com/MaslowCNC/GroundControl) front end software work well, but common points of discussion in the community is that it is slow and doesn't move smoothly (no accel/decel or chaining of vectors).

The behavior of this revised setup will sound and act a bit different than what may have been experienced with a previous stock-Maslow CNC setup. This new [GRBL](https://github.com/gnea/grbl)-driven system will be faster overall due to the splining of vectors as the machine moves. The top speed will still be limited by the use of the original Maslow CNC gear motors which will only go to about 20RPM which is about 1000mm/min.

Please note that the chain configuration of this supplied software is for an 'under-sprocket' chain to a sled-ring system. The sled-ring keeps the math to a simple triangular system and that makes it easier to compensate out any errors over the working area.

## Setting up the Firmware Development Environment

First clone the Firmware repository, then install and setup the Arduino IDE.

### Using Arduino IDE
1. Download [Arduino IDE](https://www.arduino.cc/en/main/software) 1.8.1 or higher
2. Install Arduino IDE and run Arduino IDE
3. Navigate menus: **File -> Open**
4. In the file chooser navigate to the cloned repository and choose the `MaslowDue.ino` file to open
5. Navigate menu: **Tools -> Board**, change to **Arduino Due Programming Port**
6. Navigate menu: **Sketch -> Upload**

# Maslow-Due Electronics
The electronics which powers the Maslow-Due CNC Machine System is based on the original Maslow-CNC shield board. The Maslow-Due (DUE) requires that the Arduino Mega2560 board (standard to the MaslowCNC) be upgraded to an Arduino Due. Since the DUE runs at a lower power supply voltage (3.3V instead of 5V) **3.9K shunt resistors**, in parallel with each motor phase, **are required** to provide safe operating voltages from the encoders to the I/O pins of the DUE. Additional **0.01uF filter caps are also required** to prevent positioning errors from noise spikes on the encoder cables. An **EEPROM must be added** to store the non-volatile parameters (the firmware will not work without it).

![Circuit Adaptations](https://imgur.com/1lLRGGO.png)

**Note:** _the board ID pins in the lower-left corner of the motor shield should be removed or not allowed to pass 5V to the Arduino Due. Cutting the trace as shown below also stops the 5V from getting back to the I/O pins:_

![Cut 5V trace or remove pins..](https://imgur.com/uj6fcP6.png)

The TLE5206-based boards require the same attention to 5V ingress. There are 3 places that must be cut and one place where 3.3V is patched over as shown here. **Please note that all 5V cuts are important or the Due can be damaged**:
https://makermade.com/product/m2-automated-cutting-machine-kit/
![TEL5206 Shield Power Modifications](https://imgur.com/36tnS2x.png)

Modifications can be made using a prototype shield like the [RobotDyn - Mega Protoshield Prototype Shield for Arduino Mega 2560](https://smile.amazon.com/RobotDyn-Protoshield-Prototype-breadboard-Assembled/dp/B071JDRGGR/ref=sr_1_3?keywords=mega%202560%20proto%20shield&qid=1552842751&s=gateway&sr=8-3).  This prevents any cutting or patching made directly to the Maslow Motor Shield or the Arduino Due.

Both L298 and TLE5206 type shields are supported by the firmware. The shield can be selected by un-commenting one of the below listed board-types in the ***MaslowDue.h*** file:
```
#define DRIVER_L298P_12    /* Uncomment this for a L298P version 1.2 Shield */
//#define DRIVER_L298P_11    /* Uncomment this for a L298P version 1.1 Shield */
//#define DRIVER_L298P_10    /* Uncomment this for a L298P version 1.0 Shield */
//#define DRIVER_TLE5206       /* Uncomment this for a TLE5206 version Shield */
```

# User Interface
The Maslow Due system uses [GRBL](https://github.com/gnea/grbl) at its core therefore, any GRBL sender application will work with the Maslow Due firmware.  The default data rate is 38400 and mode is `GRBL1`.

The sender application, [bCNC](https://github.com/vlachoudis/bCNC) has been used with great success.

# System Setup
The machine used with this Maslow-Due firmware uses a Meticulous-Z-Axis like setup which is an expansion of the Maslow CNC "stock" Z-axis kit:    http://maslowcommunitygarden.org/The-Meticulous-Z-Axis.html      Therefore, Z-Axis scaling and direction defaults are preset to such a configuration.

Many of the parameters of GRBL are defaulted in the firmware and will not require adjustment, but some of the MaslowDue-specific parameters may require adjustment to fit your specific machine configuration.
```
$81=2438.400 (Bed Width, mm): This defines a 8-foot WIDE work surface
$82=1219.200 (Bed Height, mm): This defines a 4-foot HIGH work surface
```

## Machine Geometry
The MaslowCNC machine that the MaslowDue firmware was developed for has a configuration as shown below:

![MaslowCNC Due Configuration](https://imgur.com/nKiqUgj.png)

`$83=3021.013 (distBetweenMotors, mm)`: This is the measured distance from where the chain leaves the motor on the left to where the chain leaves the motor on the right. This was measured from the 8-o'clock position of the left sprocket to the 4-o'clock position on the right sprocket - at the center of the chain connecting pin.

![Distance Between Motors Measurement](https://imgur.com/pplOCz5.png)

`$84=577.850 (motorOffsetY, mm)`: This is the distance perpendicular and down from a line that would exist between the two chain-exit sprocket positions in parameter `$83` to the top edge of the work surface.

`$85=1.004 (XcorrScaling)`: For better overall accuracy, a test pattern can be cut and measured and a general scaling correction factor (%) can be applied to the X-axis. It is best to use a reference on the order of 1M or more in length.

`$86=0.998 (YcorrScaling)`: For better overall accuracy, a test pattern can be cut and measured and a general scaling correction factor (%) can be applied to the Y-axis. It is best to use a reference on the order of 1M in height.

### Machine Home  (`$HOME`, `$H`)
The MaslowDue firmware assumes that machine home is in the center of the work surface, and it is `0,0,0`.  To set machine home, the sled can be placed near the center -- adjusting the chains manually, and the **bCNC ->Home** button pressed (or the `$h` GRBL command can be issued.) Once the `$HOME` has been applied, jogging and homing repeatedly is okay. This is now the machine home. If you wish to work in a different area of the table, jog the sled to wherever the desired `0,0,0` for the part is to be located and apply a work offset. If `$HOME` is used instead, the machine calibration will be off. So, consider `$HOME` to be the calibrated origin for the machine. The machine's current positions are saved to EEPROM, but it is good to periodically check and reset `$HOME` to maintain the best possible accuracy,

### Encoder Scaling
```
$100=127.775 (x, step/mm)
$101=127.775 (y, step/mm)
$102=735.000 (z, step/mm)
```
These parameters make the conversion from encoder-counts to mm in the DUE configuration.

**Note:** _if the direction of a motor needs to be reversed, the motor direction can be set with the GRBL parameter $3 - *Direction Mask*:
```
$3 = 0  (Standard configuration)
$3 = 1  (Reverse LEFT motor)
$3 = 2  (Reverse RIGHT motor)
$3 = 4  (Reverse Z-axis motor)
$3 = 3  (Reverse LEFT and RIGHT motors)
```

### Spindle Control
The Arduino Due I/O point **16** outputs a PWM signal that corresponds to the currently programmed spindle speed. (S8000 for 8K RPM, M3 for spindle on, M5 for spindle off.) A converter such as this one from Amazon:  [PWM-to_Voltage Module](https://smile.amazon.com/gp/product/B0797NBC79/ref=ppx_yo_dt_b_asin_title_o03_s00?ie=UTF8&psc=1)
allows direct control of a VFD or other speed control with a 0-10VDC input.

### PID
The following parameters may require some adjustment depending on the weight of the sled/router system being used:
```
$40=25600 (X-axis Kp): This is the proportion constant scaled as xx.xxx
$41=17408 (X-axis Ki): This is the integral constant scaled as xx.xxx
$42=21504 (X-axis Kd): This is the derivative constant scaled as xx.xxx
$43=5000 (X-axis Imax): This is the maximum integer value that the integrator can build to

$50=25600 (Y-axis Kp): These are the PID constants for Y
$51=17408 (Y-axis Ki)
$52=21504 (Y-axis Kd)
$53=5000 (Y-axis Imax)

$60=22528 (Z-axis Kp): These are the PID constants for Z
$61=17408 (Z-axis Ki)
$62=20480 (Z-axis Kd)
$63=5000 (Z-axis Imax)
```

# Maslow-Due Shield Board

There is not yet a shield board for this solution package, but if there was, it might look like this:

![MaslowDue Shield Board Top View](https://imgur.com/yLPaE3y.png)

![MaslowDue Shield Board Bottom View](https://imgur.com/8rasmGJ.png)

Gerbers and Schematics can be found on this repo under [Electronics](https://github.com/ldocull/MaslowDue/tree/master/Electronics).

Peace!

___
Let us know that this work has been helpful to you.  Any proceeds will be used to offset expenses and further the art.
[![](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=GLAHSMYYJJJAU&source=url)

### Authors
- Larry O'Cull ([ldocull](https://github.com/ldocull), Father)
- Max O'Cull ([maxattax97](https://github.com/maxattax97), Son)

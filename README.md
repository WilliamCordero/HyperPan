# HyperPan Control Software
[William Cordero Photo](http://williamcordero.com) <[william.cordero@gmail.com](william.cordero@gmail.com)>

--

### Dependencies
- [bcm2835](http://www.airspayce.com/mikem/bcm2835/)

### Building
```
$ make
```

### Installing & Uninstalling
```
$ sudo make install
```
```
$ sudo make uninstall
```

### Usage
```
Usage: hyperpan [OPTION...]
            virtual|sphere|slave|35|6x45|45x6|6x6|6x7|7x6|6x8|8x6|6x9|9x6|6x17|17x6

 * HyperPan Control Software.
   William Cordero Photo
   http://williamcordero.com
   https://github.com/WilliamCordero/HyperPan

Actions:

   virtual      Custom size virtual sensor
   sphere       Cover the entire area
   slave        Slave mode
   35           Full Frame    24x36mm
   6x6          Medium Format 60x60mm
   6x45 45x6    Medium Format 60x45mm
   6x7   7x6    Medium Format 60x70mm
   6x8   8x6    Medium Format 60x80mm
   6x9   9x6    Medium Format 60x90mm
   6x17 17x6    Medium Format 60x170mm

Options:

  -a, --auto                 Auto Focus On
  -b, --delay=DELAY          Trigger delay
  -c, --fast                 High speed
  -d, --dummy                Dummy mode
  -f, --focal=FOCAL          Focal length(Def:50mm)
  -g, --save=FILE            Save to file
  -h, --height=HEIGHT        Sensor height(Def:23.5mm)
  -l, --load=FILE            Load file
  -m, --motion               No trigger
  -o, --overlap=OVERLAP      Overlap area(Def:0.375)
  -q, --quiet                Quiet output
  -s, --speed=SPEED          Trigger speed(Def:0.5s)
  -v, --verbose=LEVEL        Verbose level
  -w, --width=WIDTH          Sensor width(Def:15.6mm)
  -x, --vwidth=VWIDTH        Virtual sensor width(Def:60mm)
  -y, --vheight=VHEIGHT      Virtual sensor height(Def:60mm)
  -z, --slow                 Low speed
  -?, --help                 Give this help list
      --usage                Give a short usage message
  -V, --version              Print program version

Mandatory or optional arguments to long options are also mandatory
or optional for any corresponding short options.
```

#### Actions
<p align="justify">
There are three main action types:
</p>

##### virtual
<p align="justify">
Emulates a virtual sensor using one smaller, the arguments <code>-w WIDTH</code> and <code>-h HEIGHT</code> set the size of the native sensor on the camera and <code>-x WIDTH</code> and <code>-y HEIGHT</code> set the virtual sensor size.
</p>
<p align="justify">
Actions <code>35</code>, <code>6x45</code>, <code>45x6</code>, <code>6x6</code>, <code>6x7</code>, <code>7x6</code>, <code>6x8</code>, <code>8x6</code>, <code>6x9</code>, <code>9x6</code>, <code>6x17</code> and <code>17x6</code> are aliases to their respective sensor formats.
</p>

##### sphere
<p align="justify">
Cover the entire area. For virtual tours or 360° photography. More wide the lens, less number of shots.
</p>

##### slave
<p align="justify">
<code>-g FILE</code> save a sequence path into a file, the dummy mode(<code>-d</code>) could be useful in this cases.
</p>
```
$ hyperpan 35 -d -g path 
```
<code>slave</code> allows control through the standard input(<code>stdin</code>) or loading a file(<code>-l FILE</code>)
```
$ cat path | hyperpan slave
```
```
$ hyperpan slave -l path 
```
#### Control
<p align="justify">
In order to calculate the correct angles of view set <code>-f FOCAL</code> to the focal length on the camera.
</p>
<p align="justify">
<code>-o OVERLAP</code> set the overlap between shots, <code>0.375</code> by default.
</p>
<p align="justify">
<code>hyperpan</code> minimize vibration by limiting speed and acceleration, when you need speed and vibration is not a problem (e.g. flash photography) <code>-c</code> set the maximum speed available
</p>
<p align="justify">
For a smooth ride use <code>-z</code>, also <code>-b SEC</code> do a pause before every shot.
</p>
<p align="justify">
<code>-s SEC</code> set the trigger speed.
</p>
<p align="justify">
<code>-a</code> activate the AutoFocus before every shot, use <code>-b SEC</code> to allow the AutoFocus some time to work.
</p>
<p align="justify">
<code>-m</code> turn off the camera trigger.
</p>

#### Verbose

<code>-v LEVEL</code>

```
L_INFO 0B00000001 //1  Info
L_STPR 0B00000010 //2  Steppers
L_SPHR 0B00000100 //4  Sphere
L_CAMR 0B00001000 //8  Camera
L_TRGR 0B00010000 //16 Trigger
L_SLVE 0B00100000 //32 Slave
L_OUTP 0B01000000 //64 Output
```

#### Example

<p align="justify">
Using a 50mm lens, emulate a 60mm•60mm image sensor format with an APS-C sensor(23.5mm•15.6mm).
</p>

```
$ hyperpan 6x6 -v13 -f50 -h23.5 -w15.6 
```
> ![HyperPan](http://misc.williamcordero.com/zip/HyperPan_0.62.gif)
```
# α: 
# ο: ★:
# δ: ★:
# δ:     focal:  50.00 mm
# δ: υ: sensor:  23.50 •  15.60 mm
# δ: υ:      α:  26.45 •  17.73 °
# δ: υ:     α':  21.49 •  14.41 °
# δ: υ:      Ξ:  0.375
# δ: ν: sensor:  60.00 •  60.00 mm
# δ: ν:      α:  61.93 •  61.93 °
# ο: ↝: 0.00:ρ  -21.49:θ  -23.23:φ
# ο: ↝: 0.00:ρ  -21.49:θ   -7.74:φ
# ο: ↝: 0.00:ρ  -21.49:θ    7.74:φ
# ο: ↝: 0.00:ρ  -21.49:θ   23.23:φ
# ο: ↝: 0.00:ρ    0.00:θ   28.82:φ
# ο: ↝: 0.00:ρ    0.00:θ   14.41:φ
# ο: ↝: 0.00:ρ    0.00:θ   -0.00:φ
# ο: ↝: 0.00:ρ    0.00:θ  -14.41:φ
# ο: ↝: 0.00:ρ    0.00:θ  -28.82:φ
# ο: ↝: 0.00:ρ   21.49:θ  -23.23:φ
# ο: ↝: 0.00:ρ   21.49:θ   -7.74:φ
# ο: ↝: 0.00:ρ   21.49:θ    7.74:φ
# ο: ↝: 0.00:ρ   21.49:θ   23.23:φ
# ο: ↝: 0.00:ρ  -90.00:θ  -90.00:φ
# ω:
```

### Hardware Configuration
```
src/config.h
```

<p align="justify">
For each stepper motor there are a set of <code>#define</code> with the respective configuration. Which GPIO pins are connected at which pins on the stepper driver(<a href="https://www.pololu.com/file/0J617/drv8834.pdf" target="_blank">DRV8834</a>) and most important, the microstepping mode and the number of native steps per rotation, which is the product of the native motor steps by the gear multiplier, in this case the <a href="http://www.omc-stepperonline.com/download/pdf/17HS19-2004S1.pdf" target="_blank">motor</a> has 200 steps and we are using a 16T gear on the motor and a 128T what makes an 8X multiplier. For microstepping we are using 1/32-step mode.
</p>

```
THETA_SLEEP 12    //GPIO 12
THETA_STEP  6     //GPIO 6
THETA_DIR   5     //GPIO 5
THETA_M0    16    //GPIO 16
THETA_M1    13    //GPIO 13
THETA_MODE  32    //MICROSTEP MODE 1/32
THETA_STEPS 200*8 //STEPS PER ROTATION
```

<p align="justify">
In this file there are also some <code>#define</code> to control the motor's speed and movement, there are three sets; one for default mode(<code>_DEF</code>), another used with the argument <code>-c</code> for Fast Mode(<code>_FAST</code>) and the last one, used with the argument <code>-z</code> for Slow Mode(<code>_SLOW</code>).
</p>

- `MIN` is the minimum time in microseconds for the faster steps, this can't be lower to the time require by the combination of stepper/driver/raspberry to operate without losing steps.
- `MAX` is the maximum time in microseconds for the slower steps.
- `BORDER` is the part of each travel used to accelerate and decelerate(total_travel/`BORDER`).

<p align="justify">
Increasing the speed also increase vibrations, if you want a faster movement set a low value for <code>MAX</code>, as low as <code>MIN</code> and a high value for <code>BORDER</code>, or, if you want a smooth movement, set a high value for <code>MIN</code> and <code>MAX</code> and a low value for <code>BORDER</code>.
</p>

```
MIN_DEF     40
MAX_DEF     230
BORDER_DEF  14
MIN_FAST    40
MAX_FAST    40
BORDER_FAST 1000
MIN_SLOW    200
MAX_SLOW    400
BORDER_SLOW 2
```

<p align="justify">
In <code>src/config.h</code> you can also find some <code>#define</code> for the default arguments, for example:
</p>

```
D_FOCAL     50.0  //DEFAULT FOCAL LENGH 50mm
```


#### Spherical Coordinates Reference

<img height="200" width="200" src="http://misc.williamcordero.com/zip/spherical.svg">
<img height="200" width="200" src="http://misc.williamcordero.com/zip/phi_1.svg">
<img height="200" width="200" src="http://misc.williamcordero.com/zip/theta_1.svg">
<img height="200" width="200" src="http://misc.williamcordero.com/zip/sphere.svg">

*[Spherical Coordinate System](https://en.wikipedia.org/wiki/Spherical_coordinate_system)

#### Circuit diagram
> ![Schematics](http://misc.williamcordero.com/zip/hyperpan_schematics.svg)


### Bugs
---
Report bugs to William Cordero <<william.cordero@gmail.com>>.

### Open Source Licensing GPL V2
---
If you wish to use this software under Open Source Licensing, you must contribute all your source code to the open source community in accordance with the GPL Version 2 when your application is distributed. http://www.gnu.org/licenses/old-licenses/gpl-2.0.html.

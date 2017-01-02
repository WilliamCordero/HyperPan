# HyperPan Control Software

> •

> [William Cordero Photo](http://williamcordero.com)

> [william.cordero@gmail.com](william.cordero@gmail.com)

> •

### Dependencies
- [bcm2835](http://www.airspayce.com/mikem/bcm2835/)

### Build
```
$ make
```

### Install
```
$ sudo make install
```

### Uninstall
```
$ sudo make uninstall
```

### Example
```
$ ./hyperpan 6x6 -v13 -s0.008
```
Console | Video
------- | -------------
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
```|hola mundo

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
  -b, --delay=DELAY          Shutter delay
  -c, --fast                 High speed
  -d, --dummy                Dummy mode
  -f, --focal=FOCAL          Focal length(Def:50mm)
  -g, --save=FILE            Save to file
  -h, --height=HEIGHT        Sensor height(Def:23.5mm)
  -l, --load=FILE            Load file
  -m, --motion               No shutter
  -o, --overlap=OVERLAP      Overlap area(Def:0.375)
  -q, --quiet                Quiet output
  -s, --speed=SPEED          Shutter speed(Def:0.5s)
  -v, --verbose=LEVEL        Verbose level
  -w, --width=WIDTH          Sensor width(Def:15.6mm)
  -x, --vwidth=VWIDTH        Virtual sensor width(Def:60mm)
  -y, --vheight=VHEIGHT      Virtual sensor height(Def:60mm)
  -z, --slow                 Low speed
  -?, --help                 Give this help list
      --usage                Give a short usage message
  -V, --version              Print program version

Mandatory or optional arguments to long options are also mandatory or optional
for any corresponding short options.
```

### Schematics
<p align="center">
<!--<img width="600" src="https://rawgit.com/WilliamCordero/HyperPan/master/doc/hyperpan_schematics.svg" />-->
<img width="600" src="http://misc.williamcordero.com/zip/hyperpan_schematics.svg" />
</p>

### Verbose levels
```
L_INFO 0B00000001 //1  Generic Info
L_STPR 0B00000010 //2  Steppers
L_SPHR 0B00000100 //4  Sphere
L_CAMR 0B00001000 //8  Camera
L_TRGR 0B00010000 //16 Trigger
L_SLVE 0B00100000 //32 Slave
L_OUTP 0B01000000 //64 Output
```

### Bugs
Report bugs to William Cordero <william.cordero@gmail.com>.

### Open Source Licensing GPL V2
If you wish to use this software under Open Source Licensing, you must contribute all your source code to the open source community in accordance with the GPL Version 2 when your application is distributed. http://www.gnu.org/copyleft/gpl.html
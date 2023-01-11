
# Arduino-Makefile 

Are you fed up with using the arduino IDE 
here is a geeky way to build and compile projects 
using Makefile and linux terminal.

You need to follow these steps:

## 1-Install the Arduino-mk package
This is the program that's going to compile and upload the code
to the arduino board.
You don't need to change anything in the Arduino sketches.
[Arduino-mk](https://github.com/sudar/Arduino-Makefile)

To install: 
```bash
$sudo apt update
$sudo apt-get install arduino-mk
```
## 2-Create your Arduino project
In your home directory 

Create a directory
```bash
$mkdir test 
  ```
Create .ino file 

```bash
$cd test
$touch test.ino 
  ```
Then with your preferred text editor write your arduino code 
Example:
```c++
/*
This sketch will toggle the internal LED 
and print a string on the terminal each 1s
*/
void setup (){
Serial.begin(9600); 
pinMode (13,OUTPUT); 
}

void loop(){ 
Serial.print ("hello world "); 
digitalWrite (13,!digitalRead(13)); 
}
  ```

Save the file 
## 3-Create the Makefile
In this Makefile, we are going to specify certain 
features like:
- The baud rate. 
- Arduino board.
- Com port. 
- Libraries used in your code 
- The path where you installed the Arduino-mk Makefile. 
 
In the same directory create the Makefile
```bash
$touch Makefile
  ```
```Makefile
#this is the path where you installed the arduino-mk Makefile  
path = /usr/share/arduino # this is a variable 
ARDUINO_PORT  =   /dev/ttyACM0  
BOARD_TAG = uno # specify which arduino board you are using I am using Uno
include $(path)/Arduino.mk
  ```
For more info you can refer to the GitHub repo 
[Arduino-mk](https://github.com/sudar/Arduino-Makefile).

## 4-Check the com port 

In this stage, you need to identify which com port is the arduino is using.

Plug in your arduino board 

- Method 1: 
open terminal and type: 
```bash
$sudo dmesg | tail -f
  ```
you should see something like this: 

```bash
[85441.284838] sd 2:0:0:0: [sdb] Attached SCSI removable disk
[85455.454024] usb 1-4: USB disconnect, device number 59
[85455.499489] FAT-fs (sdb): unable to read boot sector to mark fs as dirty
[85483.054487] usb 1-1: new full-speed USB device number 60 using xhci_hcd
[85483.204949] usb 1-1: New USB device found, idVendor=2a03, idProduct=0043, bcdDevice= 0.01
[85483.204973] usb 1-1: New USB device strings: Mfr=1, Product=2, SerialNumber=220
[85483.204985] usb 1-1: Product: Arduino Uno
[85483.204993] usb 1-1: Manufacturer: Arduino Srl            
[85483.205001] usb 1-1: SerialNumber: 85439303233351608182
[85483.214608] cdc_acm 1-1:1.0: ttyACM0: USB ACM device

  ```
- Method 2: 
```bash
$ls -l /dev/ttyACM* /dev/ttyUSB*
  ```
you should see something like this
 ```
ls: cannot access '/dev/ttyUSB*': No such file or directory
crw-rw----+ 1 moktar dialout 166, 0 Jan 11 21:10  /dev/ttyACM0
 ```
This means that your board is located in ```/dev/ttyACM0``` and not in any ```/dev/ttyUSB*```.

if you get: 
```
ls: cannot access '/dev/ttyACM*': No such file or directory
ls: cannot access '/dev/ttyUSB*': No such file or directory
  ```
That means your board isn't detected. remove it and plug it in again.

## 5-Compile and upload code 

in the same directory where you created your arduino code 
open the terminal and type: 
```bash
$make  
  ```
this instruction will compile your arduino sketch
as a result a new folder will appear ```build-uno```
```bash
$ls  
  ```
  output:
```
build-uno  Makefile  test.ino
```
that folder will contain the binary file (.elf) which will be uploaded to the arduino board.

To upload type: 

```bash 
$make upload
```
you should see  
```
-------------------------
Arduino.mk Configuration:
- [AUTODETECTED]       CURRENT_OS = LINUX 
- [AUTODETECTED]       ARDUINO_DIR = /usr/share/arduino 
- [COMPUTED]           ARDMK_DIR = /usr/share/arduino (relative to Common.mk)
- [AUTODETECTED]       ARDUINO_VERSION = 1819 
- [DEFAULT]            ARCHITECTURE = avr 
- [DEFAULT]            ARDMK_VENDOR = arduino 
- [AUTODETECTED]       ARDUINO_PREFERENCES_PATH = /home/moktar/.arduino15/preferences.txt 
- [AUTODETECTED]       ARDUINO_SKETCHBOOK = /home/moktar/Arduino (from arduino preferences file)
- [BUNDLED]            AVR_TOOLS_DIR = /usr/share/arduino/hardware/tools/avr (in Arduino distribution)
- [COMPUTED]           ARDUINO_LIB_PATH = /usr/share/arduino/libraries (from ARDUINO_DIR)
- [COMPUTED]           ARDUINO_PLATFORM_LIB_PATH = /usr/share/arduino/hardware/arduino/avr/libraries (from ARDUINO_DIR)
- [COMPUTED]           ARDUINO_VAR_PATH = /usr/share/arduino/hardware/arduino/avr/variants (from ARDUINO_DIR)
- [COMPUTED]           BOARDS_TXT = /usr/share/arduino/hardware/arduino/avr/boards.txt (from ARDUINO_DIR)
- [DEFAULT]            USER_LIB_PATH = /home/moktar/Arduino/libraries (in user sketchbook)
- [DEFAULT]            PRE_BUILD_HOOK = pre-build-hook.sh 
- [USER]               BOARD_TAG = uno 
- [COMPUTED]           CORE = arduino (from build.core)
- [COMPUTED]           VARIANT = standard (from build.variant)
- [COMPUTED]           OBJDIR = build-uno (from BOARD_TAG)
- [COMPUTED]           ARDUINO_CORE_PATH = /usr/share/arduino/hardware/arduino/avr/cores/arduino (from ARDUINO_DIR, BOARD_TAG and boards.txt)
- [DETECTED]           MONITOR_BAUDRATE = 9600  (in sketch)
- [DEFAULT]            OPTIMIZATION_LEVEL = s 
- [DEFAULT]            MCU_FLAG_NAME = mmcu 
- [DEFAULT]            CFLAGS_STD = -std=gnu11 -flto -fno-fat-lto-objects 
- [DEFAULT]            CXXFLAGS_STD = -std=gnu++11 -fno-threadsafe-statics -flto 
- [COMPUTED]           DEVICE_PATH = /dev/ttyACM0  (from MONITOR_PORT)
- [DEFAULT]            FORCE_MONITOR_PORT =  
- [AUTODETECTED]       Size utility: AVR-aware for enhanced output
- [COMPUTED]           BOOTLOADER_PARENT = /usr/share/arduino/hardware/arduino/avr/bootloaders (from ARDUINO_DIR)
- [COMPUTED]           ARDMK_VERSION = 1.5 
- [COMPUTED]           CC_VERSION = 5.4.0 (avr-gcc)
-------------------------
mkdir -p build-uno
make reset
make[1]: Entering directory '/home/moktar/Arduino_makefiles/test'
/usr/bin/ard-reset-arduino  /dev/ttyACM0
make[1]: Leaving directory '/home/moktar/Arduino_makefiles/test'
make do_upload
make[1]: Entering directory '/home/moktar/Arduino_makefiles/test'
/usr/share/arduino/hardware/tools/avr/bin/avrdude -q -V -p atmega328p -C /usr/share/arduino/hardware/tools/avr/etc/avrdude.conf -D -c arduino -b 115200 -P /dev/ttyACM0 \
    -U flash:w:build-uno/test_.hex:i

avrdude: AVR device initialized and ready to accept instructions
avrdude: Device signature = 0x1e950f (probably m328p)
avrdude: reading input file "build-uno/test_.hex"
avrdude: writing flash (3824 bytes):
avrdude: 3824 bytes of flash written

avrdude: safemode: Fuses OK (E:00, H:00, L:00)

avrdude done.  Thank you.

make[1]: Leaving directory '/home/moktar/Arduino_makefiles/test'

```
by now, the internal Led should be blinking 
to remove the folder type 
```bash
$make clean 
```
## 6-Serial communication 
to see the serial data: 

- Method 1: 
Three commands are used for this: ```stty```, ```cat``` and ```echo```.

The ```stty``` command sets the parameters and speed of the COM port.
Its format is:
```
stty [-F DEVICE | --file=DEVICE] [SETTING]...
```
for our case:
```bash
$stty 9600 -F /dev/ttyACM0 raw -echo
```
The ```9600``` is the baud rate

The ```raw``` parameter establishes that the data is 
transferred to the computer byte-by-byte the same way,
as they arrive at the port without changes (more see ```man stty```).

To print the data on the terminal
```bash 
$cat /dev/ttyACM0 
```
To exit 
```
ctrl-c 
```
- Method 2:
using a program called ```screen```

To install it 

```bash 
$sudo apt-get install screen 
```
then to print the data, just type 

``` 
screen [COM_PORT]   [BAUD_RATE]
```
``` bash 
$screen /dev/ttyACM0 9600
``` 
To exit 
```
ctrl-a
k 
```
it will ask you ```Really kill this window[y/n]``` type ```y```  
## 7-Troubleshooting
when i tried to compile the sketch  
```bash
$make  
  ```
I got an error 
```
avrdude: can't open config file "/usr/share/arduino/hardware/tools/avr/etc/avrdude.conf": No such file or directory
avrdude: error reading system wide configuration file "/usr/share/arduino/hardware/tools/avr/etc/avrdude.conf"
make[1]: *** [/usr/share/arduino/Arduino.mk:1462: do_upload] Error 1
make[1]: Leaving directory '/home/joey/src/arduino-copilot/Examples/Blink'
make: *** [/usr/share/arduino/Arduino.mk:1455: upload] Error 2  
```
Solution : 

Link the ```avrdude.conf``` to ```/usr/share/arduino/hardware/tools/avr/etc/```.

The ```avrdude.conf``` is located in ```/etc/avrdude.conf```.
``` bash 
$cd /usr/share/arduino/hardware/tools/avr
$mkdir etc
$cd etc
$ln -s /etc/avrdude.conf
```
Try compiling your code again and it should work fine. 

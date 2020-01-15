Chuck Sommerville 2020

I made this to help transfer disks form my Apple II to the PC so I can run them
on emulators, instead of the real hardware.

This is based on Arme Leute Apple Disk Transfer by Sebastian Kienzl
https://knzl.at/poor-mans-adt/

pinouts between the Apple II game port and the Arduino

Apple  Arduino  
  2	  13		c061  (c061)
  8	  gnd		ground
  13	  10            data (c058 c059)
  14      11		ready (c05a c05b)
  15      9          	reset (c05c c05d)

His code lives at $c00-$cff.  I modified his code by patching two calls
The first call is when the error code is printed.  I redirect this to
'OR' the byte with a local variable so I can report at the end if ANY
erors occured.  That way, I can just see the final result and know if the
read was successful.
The second, call is where he calls the monitor routine to write the memory block
to tape.  At this point, I send the block out the bit banged serioal port as
hex strings, 16 bytes per line.  The PC captures the text.  The result is converted
back to binary, for the .DSK image.

Here is how I use the program:

Getting started:

I have a copy of the apple binary on an Apple disk now, so I just bload it.
If you dont have that yes, boot a disk on the apple.  Then call -151 to enter the monitor.
type B00.DFFR and send the program via audio using the tool a2audioup.bin provided here:
https://knzl.at/poor-mans-adt/
then save it to a disk so you can load it again.

Usage:

On apple:

boot a dos 3.3 disk
bload a2arduino.b
call 2816
This will print a '?'  At this point it is paused waiting to prep the PC

On the PC:

type com6: >file.hex   (may be different for you)
I have this in a batch file.  Com6 is the serial port that my arduino starts at.
The baudrate needs to be set at 230400. Do this however you need to.

on The Apple:

press a key.  This will read the disk in clocks and send them to the PC.  When
the Apple is done, it will beep 3 times, and print a hex value. This is the logical
'OR' or all the secor read results.  If it is 00, then the disk read correctly.

on the PC:

At this point there is probably a dos window up, but it didnt stop.  
Type ctrl-c and end the transfer.
At this point, I open file.hex to see if it looks reasonable.  It should be all
hex strings.

hextodsk file.hex file.dsk

This is my little converter that converts exactly the size of a disk image.

Put the dsk file into an emulator and test it out.  If all is good, delete the hex file,
you are done with it.

Disk Dumper used by permission

From the Sebastian Kienzl source:
; Apple ][ Disk Dumper
; Copyright (c) Sebastian Kienzl <seb at riot dot org>
; $Id: disk2cassette.asm 29 2008-09-15 20:26:26Z seb $
; This thing dumps a whole DOS 3.3 disk and sends it out the
; CASSETTE OUT-port of the Apple. The output can be decoded
; with my a2cassdecode-tool. If the output-file is given the DSK-extension
; it can be directly used with emulators.



# Hardware Libraries

## Creating library paths for Arduino
In order to have Arduino recognize the hardware libraries, symbolic links to the folders in the GTORHardwareLibraries repo must be created in the Arduino libraries folder.

Instructions for Windows:
* Run `symlinks_generator.bat` as administrator and enter path to the Arduino libraries (eg. C:\Users\USER\Documents\Arduino\libraries).

Instructions for Linux:
* Navigate to the folder containing `symlink_gen_linux.sh`.
* Use the terminal command `./symlink_gen_linux.sh` to execute the script to general symlinks.


## Troubleshooting
Sometimes you have to go to the Arduino libraries folder and delete all the symlinks that have been automatically generated.

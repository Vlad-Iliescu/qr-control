### Install quirc requirements
1. `sudo apt-get install libjpeg-dev libpng-dev libsdl1.2-dev` \
 **TODO:** Check if `libpng-dev` and `libsdl1.2-dev` are really necessary!
 2. `git clone https://github.com/dlbeer/quirc.git`
 3. `cd quirc`
 4. `make libquirc.a libquirc.so`
 5. `mkdir quirc` \
 `mv libquirc.so.* quirc/libquirc.so` 
 6. copy `quirc/` folder to your source
 7. optional: copy `libquirc.a` to source `/lib` folder
 8. copy `lib/quirc.h` to your source


### GDB
1. add `-g` option to build
2. install gdbserver
`sudo apt install gdbserver`
3. make project
`make clean && make`
4. run gdbserver 
`gdbserver :2345 ./face_control` 

tips: ` handle SIGILL nostop`

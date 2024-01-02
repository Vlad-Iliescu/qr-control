### GDB
1. add `-g` option to build
2. install gdbserver
`sudo apt install gdbserver`
3. make project
`make clean && make`
4. run gdbserver 
`gdbserver :2345 ./face_control` 

tips: ` handle SIGILL nostop`

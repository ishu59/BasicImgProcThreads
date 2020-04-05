# Simple Multithreaded WebCam Processor
Generates 2x2 window of processed web cam feed with various filters



## Overview


<BR></BR><img src = "./detector.png"/><BR></BR><BR></BR>
## Dependencies
- CMake (>= 3.12): For project building
- OpenCV (>= 4.1): Project dependency
- C++17


### Notice 
This requires OpenCV library.
For more installation instructions, please visit
https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html

### Build and run
This project contains cmake that allows you to make easy. 

```
mkdir build
cd build
cmake ..
make
./ImageProc
```
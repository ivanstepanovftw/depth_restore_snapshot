## Compiling
Works on WSL2 + gcc version 7.5.0 (Ubuntu 7.5.0-3ubuntu1~18.04) and MSVC on Windows 10.

```shell script
/usr/local/bin/cmake -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles" /mnt/c/Users/user/CLionProjects/untitled`

/usr/local/bin/cmake --build /mnt/c/Users/user/CLionProjects/untitled/cmake-build-debug-wsl --target DOM -- -j 12
```

## Running
Set working path to the project root before run.

### Example output:

GCC 7.5.0, WSL2:
```
/mnt/c/Users/user/CLionProjects/untitled/cmake-build-debug-wsl/DOM
Parsing log file: done in 0.642362 seconds
Latency: 0.00266716 ms per message
Parsing 92435 messages: done in 0.246561 seconds
Overall: done in 0.898944 seconds

Process finished with exit code 0
```

MSVC 16.0:
```
C:\Users\ashft\CLionProjects\untitled\cmake-build-release\DOM.exe
Parsing log file: done in 1.57987 seconds
Parsing 92435 messages: done in 0.406973 seconds
Latency: 0.00438915 ms per message
Overall: done in 2.00076 seconds

Process finished with exit code 0
```
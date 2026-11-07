# What it is?
Code from [this video](https://www.youtube.com/watch?v=pbkQG09grFw)
This is a demonstration of a concept of treating C++ pointers as a "lens" to the memory. The code is shown at (2:35)[https://youtu.be/pbkQG09grFw?si=Y375A6s9c1y5vk88&t=155] and the speaker says that in the end it should return 2 when inlined. I decide to check the concept and the results were not that simple...

## Is it true?
So. I compile and run the program... And the result is not the same! I was surprised and check twice if my code is __exactly__ the same as in video. It was. And so I started to dig. I realized, that, in the end, if it gets inlined - the result is actually 2 (as expected). But when not - it varies. I checked both gcc and clang. The result is: unoptimized build returns 0. Optimized returns 2. I also included `fixed.cpp` which to check what would happen if we treat `i` as a `std::int32_t` reference. And surprisingly it does not change depending on optimization. Unfortunately I'm not that familiar with C++ compiler internals, so I can't tell what is the mechanism behind that. But it is an interesting case of program behaviour changing depending on optimization level.

## How to run
I added the Makefile. You can specify `CC` - c++ compiler, and `STD` - the standard. To simply run all tests just call
``` sh 
	make
```
Here's how to re-run tests with compiler and standard specified
``` sh 
	make -B -E CC=clang++ -E STD=c++23
```
cleanup
``` sh
	make clear
```

## My results
``` sh
 $ make -B -E CC=g++
g++ --std=c++23 -O0 -o main main.cpp
main exit code: 0
g++ --std=c++23 -O2 -o main_opt main.cpp
optimized main exit code: 2
g++ --std=c++23 -O0 -o fixed fixed.cpp
fixed exit code: 3
g++ --std=c++23 -O2 -o fixed_opt fixed.cpp
optimized fixed exit code: 3

$ make -B -E CC=clang++
clang++ --std=c++23 -O0 -o main main.cpp
main exit code: 0
clang++ --std=c++23 -O2 -o main_opt main.cpp
optimized main exit code: 2
clang++ --std=c++23 -O0 -o fixed fixed.cpp
fixed exit code: 3
clang++ --std=c++23 -O2 -o fixed_opt fixed.cpp
optimized fixed exit code: 3

$ make -B -E CC=gcc
gcc --std=c++23 -O0 -o main main.cpp
main exit code: 0
gcc --std=c++23 -O2 -o main_opt main.cpp
optimized main exit code: 2
gcc --std=c++23 -O0 -o fixed fixed.cpp
fixed exit code: 3
gcc --std=c++23 -O2 -o fixed_opt fixed.cpp
optimized fixed exit code: 3

$ make -B -E CC=clang
clang --std=c++23 -O0 -o main main.cpp
main exit code: 0
clang --std=c++23 -O2 -o main_opt main.cpp
optimized main exit code: 2
clang --std=c++23 -O0 -o fixed fixed.cpp
fixed exit code: 3
clang --std=c++23 -O2 -o fixed_opt fixed.cpp
optimized fixed exit code: 3
```

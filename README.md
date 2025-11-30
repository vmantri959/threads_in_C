There are three small programs here. 
One demonstrates the use of a conditional variables, the other demonstrates an example of a race condition. The third can be run in two ways. If the compile option USE_ATOMICS is used, it correctly prints out 2000. Otherwise, it gives an incorrect output of 1000. The idea here is to demonstrate a use case for <stdatomic.h>
**Build Instructions:**

```bash
cmake -S . -G "Unix Makefiles" -B build
cmake --build build
./build/cnd_mutex_example
./build/race_condition_example
./build/non_atomic_example

```
To run the non_atomic_example using atomic variables, build as follows:

```bash
cmake -S . -G "Unix Makefiles" -B build -DCMAKE_C_FLAGS="-DUSE_ATOMICS"


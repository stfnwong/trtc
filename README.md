# RAY TRACER
Taking the Ray Tracer redpill. Working through "The Ray Tracer Challenge".

[![Build Status](https://travis-ci.com/stfnwong/trtc.svg?branch=main)](https://travis-ci.com/stfnwong/trtc)

### Requirements 
- C++17 
- Catch2 


## Quickstart 
This section will gradually contain more as more things to start quickly are implemented.
At the time of writing 

- Run `make all`. 
- That's it.

Tests are implemented with `Catch2` and test binaries will appear in `bin/test/`. The
shell script `test/run_tests.sh` will run every program under `${BIN_TEST_DIR}` 
(default: `bin/test`).

Sample programs are stored under `prog/` and are built as part of the `all` target.


### Notes on Matrix 
The implementation in the main branch is fairly straightforward. There is an unfinished
templated version in another branch that I would like to replace the current implementation
with.

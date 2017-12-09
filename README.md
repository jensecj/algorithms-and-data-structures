[![Build Status](https://travis-ci.org/jensecj/algorithms-and-data-structures.svg?branch=master)](https://travis-ci.org/jensecj/algorithms-and-data-structures)

# Usage
You can add it as a submodule to your project using git:

`git submodule add https://github.com/jensecj/algorithms-and-data-structures.git libs/dads`

Then include it in your CMakeLists.txt file:

`add_subdirectory(libs/dads)`

and link the built library against your target:

`target_link_libraries(build_target dads)`

Alternatively you can clone the repo, and build the library yourself by running `make`.

Tests and benchmarks are run with `make test && make bench`.

# Algorithms
-

# Data Structures
-

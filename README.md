[![Build Status](https://travis-ci.org/jensecj/algorithms-and-data-structures.svg?branch=master)](https://travis-ci.org/jensecj/algorithms-and-data-structures)

# Usage
You can add it as a submodule to your project using git:

`git submodule add https://github.com/jensecj/algorithms-and-data-structures.git libs/dads`

Then include it in your CMakeLists.txt file:

`add_subdirectory(libs/dads)`

and link the built library against your target:

`target_link_libraries(build_target dads)`

Alternatively you can clone the repo, and build the library yourself by running `make`.

Tests and benchmarks are run with `make test && make bench**.

# [Algorithms](https://github.com/jensecj/algorithms-and-data-structures/tree/master/src/algorithms)
## Graphs
- [Breadth First Search](https://github.com/jensecj/algorithms-and-data-structures/tree/master/src/algorithms/breadth_first_search.hpp)
- [Depth First Search](https://github.com/jensecj/algorithms-and-data-structures/tree/master/src/algorithms/depth_first_search.hpp)
- [Iterative Deepening Search](https://github.com/jensecj/algorithms-and-data-structures/tree/master/src/algorithms/iterative_deepening_search.hpp)


# [Data Structures](https://github.com/jensecj/algorithms-and-data-structures/tree/master/src/data-structures)
- [Binary Search Tree](https://github.com/jensecj/algorithms-and-data-structures/tree/master/src/data-structures/binary_search_tree.hpp)

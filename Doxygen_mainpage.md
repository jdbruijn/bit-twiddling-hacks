@file
@cond ignore
This file is only used for the Doxygen documentation.
It is not supposed to be read as a markdown file.
@endcond ignore

@mainpage BitOperations Index Page

@section intro_sec Introduction
The BitOperations project contains several bit operations and manipulations, also known as 'bit hacks'. These functions and function
macros can be used in code to easily perform operations on variables. A complete list of these functons and function macros can be found
on the [BitOperations.h](BitOperations_8h.html) documentation page.

@note A lot of the functions used in this project are based [Bit Twiddling Hacks](https://graphics.stanford.edu/~seander/bithacks.html)
by Sean Eron Anderson.
See the <a href="https://github.com/gibsjose/BitHacks/blob/master/BitHacks.md">Bit Twiddling Hacks</a> documentation for more information
about the operations and, for example, the amount of instructions needed for those functions.

@section unit_test Unit test
The purpose of this unit test is not to verify that the arithmetic is correct, because Sean Eron Anderson already tested that thoroughly.
The purpose of this unit test is to verify that the implementation of the code is correct.

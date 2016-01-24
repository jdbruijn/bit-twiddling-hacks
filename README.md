# BitOperations
[![License GPLv3][badge-license]][license]
[![AppVeyor build status][badge-appveyor]][appveyor]
[![Travis build status][badge-travis]][travis]
[![Coveralls coverage][badge-coveralls]][coveralls]

Several bit operations and manipulations, also known as 'bit hacks'.  

*Please note that the coverage results do not include the function macros, although those are tested in the unit tests.*

## Documentation
Documentation can be found in the [documentation page](http://vidavidorra.github.io/BitOperations/html/index.html), and for the
function macros and functions on the [BitOperations.h documentation 
page](http://vidavidorra.github.io/BitOperations/html/BitOperations_8h.html).  
For the functions that are based on Sean Eron Anderson's [Bit Twiddling Hacks](https://graphics.stanford.edu/~seander/bithacks.html)
the arithmetics are explained on Joe Gibson's [markdown version](https://github.com/gibsjose/BitHacks/blob/master/BitHacks.md) of
Sean Eron Anderson's Bit Twiddling Hacks.

## Usage
In order to use this code the only thing that you need to do is copy `BitOperations.h` and `BitOperations.c` to your project and
include `BitOperations.h` in the files where you intend to use the BitOperations. These two files can be found in every
[release](https://github.com/vidavidorra/BitOperations/releases) in the `source` and `source/src` folders respectively.

## Unit test
The unit tests use [greatest](https://github.com/silentbicycle/greatest/) by Scott Vokes. Greatest is licensed under a [custom
license](https://github.com/silentbicycle/greatest/blob/master/LICENSE).  
The purpose of this unit test is not to verify that the arithmetic is correct, because Sean Eron Anderson already tested that thoroughly.
This unit test verifies that the implementation is correct.  

All the functions and function macros are tested by the unit tests, of which the log can be found in every [travis
build](https://travis-ci.org/vidavidorra/BitOperations#L179-L257) or in every [AppVeyor
build](https://ci.appveyor.com/project/vidavidorra/bitoperations/build/artifacts).  

## Licensing
GNU General Public License version 3 or later, as published by the Free Software Foundation.
Modification and redistribution are permitted according to the terms of the GPL.
The license can be found in the `LICENSE` file.  

Pull [requests](https://github.com/vidavidorra/BitOperations/pulls) and [bug
reports/suggestions](https://github.com/vidavidorra/BitOperations/issues) are welcome!


[badge-license]:            https://img.shields.io/badge/license-GPLv3-blue.svg
[license]:                  https://github.com/vidavidorra/BitOperations/blob/master/LICENSE
[badge-appveyor]:           https://ci.appveyor.com/api/projects/status/730ef5s733aaoyyp?svg=true
[appveyor]:                 https://ci.appveyor.com/project/vidavidorra/bitoperations
[badge-travis]:             https://travis-ci.org/vidavidorra/BitOperations.svg
[travis]:                   https://travis-ci.org/vidavidorra/BitOperations
[badge-coveralls]:          https://coveralls.io/repos/vidavidorra/BitOperations/badge.svg?branch=master&service=github
[coveralls]:                https://coveralls.io/github/vidavidorra/BitOperations?branch=master

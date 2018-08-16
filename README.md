# BuildCounter
Console program for counting versions of program builds.

The program creates a file with a version number that can be changed
through pre-post build events in Visual Studio, for example.

The program is licensed under the zlib/libpng.

Uses C++03 and STL.


Always specify the project name as a parameter '-name'.

# Examples
This example sets all version numbers
BuildCounter -name test -major 1 -minor 3 -patch 74 -build 4627

In this example, when you run the program, the number of build will be increased by 1.
BuildCounter -name HelloWorld -build++

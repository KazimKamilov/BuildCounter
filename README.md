# BuildCounter
Console program for counting versions of program builds.

The program creates a file with a version number that can be changed
through pre-post build events in Visual Studio, for example.

The program is licensed under the zlib/libpng.

Uses C++03 and STL.

# Parameters list
'-help' - Print this info.
'-name' - Sets project name.
'-major' - Manually sets major version.
'-minor' - Manually sets minor version.
'-patch' - Manually sets patch version.
'-build' - Manually sets build version.
'-major++' - Increments major version.
'-minor++' - Increments minor version.
'-patch++' - Increments patch version.
'-build++' - Increments build version.

Always specify the project name as a parameter '-name'.

# Examples
This example sets all version numbers
```cmd
BuildCounter -name test -major 1 -minor 3 -patch 74 -build 4627
```

In this example, when you run the program, the number of build will be increased by 1.
```cmd
BuildCounter -name HelloWorld -build++
```

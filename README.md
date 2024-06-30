# KlemmUI project template

A project template for the [KlemmUI UI library](https://github.com/Klemmbaustein/KlemmUI)

| Directories      |                                      |
|------------------|--------------------------------------|
| src/             | Contains C++ source code             |
| ui/              | Contains .kui UI element definitions |
| dependencies/    | Contains dependency submodules       |
| app/             | Contains app files                   |


On Windows, this template uses the `Visual Studio 17 2022` generator by default. This is because ninja doesn't check for files to rebuild after running a custom command.
So the program would need to be rebuilt twice for any changes of the ui source code to show up.

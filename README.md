# conway

![Lines of code](https://img.shields.io/tokei/lines/github/bdreece/conway)

An implementation of Conway's Game of Life, written in C++ with SDL2 and OpenCL

## Table of Contents

- [Getting Started](#getting-started)
  - [Dependencies](#dependencies)
  - [Building](#building)
- [Usage](#usage)
- [Future Plans](#future-plans)

---

## Getting Started

### Dependencies

In order to run the game of life simulation, you must have the following packages installed on your system:

- SDL 2.0
- OpenCL 3.0 (with C++ wrapper).
- CMake
- A build system of your choice (e.g. Ninja, GNU Make, etc.)

### Building

This program is built using CMake. To generate Ninja build files for the project, use the following command:

```console
$ git clone https://github.com/bdreece/conway && cd conway
$ mkdir -p build && cd build
$ cmake -G Ninja ..
$ ninja
```

After compilation has finished, you should find an executable at `build/src/conway`!

---

## Usage

`conway` expects a number of command line arguments, as described below:

`./conway <width_px> <height_px> <nrows> <ncols> <seed> <delay>`

The `<seed>` value can be any valid unsigned integer, and the `<delay>` value can be any valid unsigned long integer representing milliseconds.

---

## Future Plans

I plan to flesh out the CLI for this program a little bit in the coming weeks, as well as fix the weird edge flashing glitches that appear on the window.

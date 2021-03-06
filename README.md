# conway

[![GitHub](https://img.shields.io/github/license/bdreece/conway)](https://github.com/bdreece/conway/blob/main/LICENSE.md)
[![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/bdreece/conway?include_prereleases)](https://github.com/bdreece/conway/releases)

An implementation of Conway's Game of Life, written in C++ with SDL2 and OpenCL

![Conway's Game of Life](conway.gif)

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
- OpenCL 2.2.0 (with C++ wrapper).
- CMake
- A build system of your choice (e.g. Ninja, GNU Make, etc.)

### Building

This program is built using CMake. To generate Ninja build files for the project, use the following command:

```bash
$ git clone https://github.com/bdreece/conway && cd conway
$ mkdir -p build && cd build
$ cmake -G Ninja ..
$ ninja
```

After compilation has finished, you should find an executable at `build/src/conway`!

---

## Usage

`conway` expects a number of command line arguments, as described below:

`./conway WIN_SIZE CELL_SIZE SEED DELAY`

The `WIN_SIZE` parameter refers to the width/height of the window. Windows will be square. This must be an unsigned integer greater than 1.

The `CELL_SIZE` parameter refers to the width/height of each cell. Cells will be square. This must be an unsigned integer greater than 0 and less than `WIN_SIZE`.

The `SEED` parameter refers to the RNG seed used for generating initial conditions. This can be any valid unsigned integer.

The `DELAY` parameter refers to the delay (in milliseconds) between frames. This can be any valid unsigned long integer.

---

## Future Plans

I plan to flesh out the CLI for this program a little bit in the coming weeks, and I'll work on other issues as they arise.

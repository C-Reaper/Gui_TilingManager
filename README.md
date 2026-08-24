## Overview
The project appears to be a simple file explorer implemented in C. It is designed to be platform-independent, supporting Linux, Windows, Wine, and WebAssembly environments.

## Features
- Basic navigation of directories.
- File selection and display of selected files' paths.
- Support for different input methods (keyboard for movement, mouse for selection).

## Project Structure

### Prerequisites
- C/C++ Compiler and Debugger (GCC, Clang)
- Make utility
- Standard development tools
- Libraries needed in specific projects:
  - `X11` for Linux GUI handling.
  - `user32`, `gdi32`, `winmm` for Windows API interactions.

## Build & Run

### Linux
To build and run the project on Linux, follow these steps:

1. **Build**:
   ```sh
   make -f Makefile.linux all
   ```
   To clean and rebuild:
   ```sh
   make -f Makefile.linux clean
   make -f Makefile.linux all
   ```

2. **Execute**:
   ```sh
   make -f Makefile.linux exe
   ```

### Windows
To build and run the project on Windows, follow these steps:

1. **Build**:
   ```sh
   make -f Makefile.windows all
   ```
   To clean and rebuild:
   ```sh
   make -f Makefile.windows clean
   make -f Makefile.windows all
   ```

2. **Execute**:
   ```sh
   make -f Makefile.windows exe
   ```

### Wine (Linux Cross Compile for Windows)
To build and run the project on Linux using Wine to compile for Windows, follow these steps:

1. **Build**:
   ```sh
   make -f Makefile.wine all
   ```
   To clean and rebuild:
   ```sh
   make -f Makefile.wine clean
   make -f Makefile.wine all
   ```

2. **Execute**:
   ```sh
   WINEPREFIX=~/wine64 WINEARCH=win64 wine $(TARGET)
   ```

### WebAssembly (Emscripten)
To build and run the project for the web using Emscripten, follow these steps:

1. **Build**:
   ```sh
   make -f Makefile.web all
   ```
   To clean and rebuild:
   ```sh
   make -f Makefile.web clean
   make -f Makefile.web all
   ```

2. **Execute**:
   ```sh
   make -f Makefile.web exe
   ```

Each of these commands will handle the necessary build configurations and produce executables or a web application that can be run in your environment.
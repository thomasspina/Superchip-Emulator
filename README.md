# Building the Web Version of the Chip-8 Emulator

This guide will help you download and set up [Emscripten](https://emscripten.org/), activate its compiler, and build the Chip-8 emulator for the web using the given `emcc` command.

## Prerequisites

- Ensure you have Python 3 installed on your system, as Emscripten requires it to run.

---

## Steps to Set Up and Compile

### 1. Download and Install Emscripten

1. Visit the [Emscripten download page](https://emscripten.org/docs/getting_started/downloads.html).
2. Follow the instructions to clone the Emscripten SDK:
   ```bash
   git clone https://github.com/emscripten-core/emsdk.git
   cd emsdk
   ```

3. Install and activate the latest Emscripten tools:
   ```bash
   ./emsdk install latest
   ./emsdk activate latest
   ```

4. For Windows users, use the `emsdk_env.bat` script to activate Emscripten in your environment. For other operating systems, adding it to your shell configuration (e.g., `.bashrc` or `.zshrc`) should not be too different.
   ```bash
   source ./emsdk_env.sh
   ```

---

### 2. Verify the Installation

1. Check if `emcc` is installed correctly:
   ```bash
   emcc --version
   ```
   You should see the version of Emscripten printed in the terminal.

---

### 3. Compile the Project

Once you have activated the Emscripten environment using `emsdk_env.bat` (Windows) or the appropriate command for your OS, navigate to your project directory and run the following `emcc` command to compile the emulator for the web:

```bash
emcc src/main.cpp src/chip8.cpp src/audio.cpp src/graphics.cpp -Iinclude -sUSE_SDL=2 -std=c++20 -o index.js --preload-file games -s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" -s EXPORTED_FUNCTIONS="['_invert','_loadROM', '_main']"
```

**Explanation of the command:**
- `src/main.cpp src/chip8.cpp src/audio.cpp src/graphics.cpp`: Specifies the source files to compile.
- `-Iinclude`: Includes the header files from the `include` directory.
- `-sUSE_SDL=2`: Enables SDL2 support.
- `-std=c++20`: Sets the C++ standard to C++20.
- `-o index.js`: Outputs the JavaScript/WASM files for the browser as `index.js`.
- `--preload-file games`: Includes the `games` directory in the output, making it accessible to the WASM environment.
- `-s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']"`: Exports specific runtime methods for JavaScript interaction.
- `-s EXPORTED_FUNCTIONS="['_invert','_loadROM', '_main']"`: Exports specific C++ functions for JavaScript interaction.

---

### 4. Move Output Files to the Correct Directory

After running the `emcc` command, move the generated files (`index.js`, `index.wasm`, etc.) to the desired directory for deployment, such as your web server root or the branch dedicated to the web build.

---

### Useful Sources
Compiling Chip8 to WASM:
- https://dominikrys.com/posts/compiling-chip8-to-wasm/#file-system-access-in-emscripten


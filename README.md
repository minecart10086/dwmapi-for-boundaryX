# DWMAPI Proxy Generator

This project is extracted from UE4SS and provides a standalone tool to generate proxy DLLs, specifically for `dwmapi.dll`.

## Project Structure

```
dwmapi-proxy-generator/
├── CMakeLists.txt          # Top-level CMake configuration
├── README.md               # This file
├── proxy_generator/        # Tool to generate proxy files
│   ├── CMakeLists.txt
│   ├── main.cpp           # Generator code
│   └── xmake.lua
├── proxy/                  # Proxy DLL target
│   ├── CMakeLists.txt
│   ├── proxy.rc           # Resource file
│   └── xmake.lua
├── exports/                # Export definition files
│   └── dwmapi.exports     # dwmapi.dll export definitions
└── deps/                   # Dependencies
    ├── Constructs/        # C++ utility constructs (header-only)
    ├── String/            # String utilities (header-only)
    ├── Helpers/           # Helper functions
    └── File/              # File handling library
```

## How It Works

1. **proxy_generator** reads an exports file (or directly analyzes a DLL) and generates:
   - `dllmain.cpp` - The main DLL entry point with UE4SS injection support
   - `dwmapi.asm` - Assembly stubs for function forwarding to original DLL
   - `dwmapi.def` - DLL export definitions

2. **proxy** target builds these generated files into the final `dwmapi.dll`

3. The generated proxy DLL:
   - Loads the original `dwmapi.dll` from System32
   - Forwards all function calls to the original DLL
   - Automatically loads UE4SS.dll (if present) for modding

## Features

- Pre-configured `dwmapi.exports` for all known dwmapi functions
- Supports both named exports and ordinal exports
- Automatic UE4SS injection via proxy DLL loading
- Command line arguments support (`--disable-ue4ss`, `--ue4ss-path`)
- Override file support for custom UE4SS paths

## Building

### Prerequisites

- CMake 3.22 or higher
- C++23 compatible compiler (MSVC 2022, MinGW-w64, etc.)
- Windows SDK (for Windows builds)

### Using CMake (Windows)

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### Cross-compiling for Windows on Linux (MinGW)

```bash
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=/path/to/mingw-toolchain.cmake
cmake --build .
```

## Usage

### Using pre-defined dwmapi.exports

```bash
# Build normally - uses exports/dwmapi.exports by default
cmake --build build
```

### Using custom DLL path (native Windows only)

```bash
cmake .. -DUE4SS_PROXY_PATH="C:\\Windows\\System32\\dwmapi.dll"
cmake --build .
```

### Using a different proxy DLL

```bash
# Create your own .exports file
cmake .. -DUE4SS_PROXY_PATH="path/to/your/exports/file.exports"
cmake --build .
```

## Output

After successful build, you'll find:
- `proxy_generator.exe` - The generator tool
- `dwmapi.dll` - The generated proxy DLL

## Deployment

To use the generated `dwmapi.dll`:

1. Place `dwmapi.dll` in your game executable directory
2. Place `UE4SS.dll` in a `ue4ss` subdirectory or same directory
3. Run the game - the proxy DLL will automatically load UE4SS

### Command Line Options

- `--disable-ue4ss` - Disable UE4SS loading (proxy only mode)
- `--ue4ss-path <path>` - Specify custom path to UE4SS.dll

### Override File

Create a file named `override.txt` in the same directory as the proxy DLL containing the path to your UE4SS installation:
```
path/to/custom/ue4ss/directory
```

## Creating Custom Export Files

To create an export file for a different DLL:

1. Run proxy_generator on the target DLL (Windows only):
   ```bash
   proxy_generator.exe "C:\Windows\System32\other.dll" output_dir
   ```

2. Or manually create a `.exports` file with:
   - First line: `Path: C:\Windows\System32\yourdll.dll`
   - Subsequent lines: `ordinal_number function_name` (or just ordinal for unnamed exports)

## Notes

- The generated DLL is specifically for Windows
- This is designed for game modding purposes
- Ensure you have the right to modify and distribute the target game
- Some anti-cheat systems may detect proxy DLLs

## License

This project retains the original licenses from UE4SS and its dependencies.
See individual LICENSE files in each dependency directory for details.

UE4SS is licensed under the MIT License.

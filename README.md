# UnauthScout C++

**UnauthScout** is an OSINT (Open Source Intelligence) tool for passive reconnaissance of users and repositories on version control platforms (GitHub and GitLab). Designed for developers, security researchers, and intelligence professionals, it provides modular and efficient data collection, normalization, and reporting.

---

## Features
- Fetches and normalizes user and repository data from GitHub and GitLab.
- JSON output for integration with other tools.
- Detailed reports and intelligence summaries.
- Flag support for output control (`--raw`, `--pretty`, `--save`).
- Modular architecture for easy extension.

## Requirements
Install the required dependencies on Debian/Ubuntu-based systems:

```bash
sudo apt-get update
sudo apt-get install -y g++ cmake libcurl4-openssl-dev
```

For the `nlohmann/json` library (header-only):

```bash
mkdir -p include/nlohmann
wget https://raw.githubusercontent.com/nlohmann/json/v3.11.2/single_include/nlohmann/json.hpp -O include/nlohmann/json.hpp
```

## Compilation

1. Create and enter the build directory:

```bash
mkdir -p build && cd build
```

2. Configure the project with CMake:

```bash
cmake ..
```

3. Compile:

```bash
make
```

## Usage

### Fetch user data:

```bash
./unauthscout torvalds
```

### Save response to JSON:

```bash
./unauthscout torvalds --save
```

Generates files in the format `output/torvalds_YYYY-MM-DD.json`.

### Raw mode (raw data):

```bash
./unauthscout torvalds --raw
```

### Intelligence summary:

```bash
./unauthscout torvalds --repos --summarize
```

### Help:

```bash
./unauthscout --help
```

## Example Output

Example files are available in `output/`:
- [torvalds_2026-02-07.json](output/torvalds_2026-02-07.json) (user data)
- [torvalds_repos_2026-02-07.json](output/torvalds_repos_2026-02-07.json) (repository data)

## Troubleshooting

### Compilation Errors
- Ensure all `.cpp` files are listed in `CMakeLists.txt`.
- Make sure `target_include_directories` is called after `add_executable`.
- Recompile from scratch if there are changes in headers:

```bash
rm -rf build && mkdir build && cd build
cmake ..
make
```

### Missing Dependencies
- Confirm `libcurl4-openssl-dev` is installed.
- Verify the presence of the file `include/nlohmann/json.hpp`.

---

## Contributing
Pull requests are welcome. For major changes, open an issue first to discuss what you would like to change.

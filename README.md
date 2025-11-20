#  Terminus Logging API

A small, header-only logging facade built on top of Boost.Log. It provides:

- Global logging functions like `tmns::log::trace`, `tmns::log::debug`, etc.
- Scoped loggers via `tmns::log::Logger` for component-specific scopes.
- Configurable backends through Boost.Log config files, including a custom `JsonFile` sink.

## Installation

Using Conan (example):

```bash
conan-build.sh -c --build-missing
```

On first build you may need `--build-missing` to build Boost and friends from source.

### Source location options

The library can be configured to use different `source_location` strategies via Conan options:

- `use_source_location=True` → use `<experimental/source_location>`
- `use_source_location_hack=True` → use the lightweight shim implementation
- neither → use standard `<source_location>` if available

These feed into the `TERMINUS_LOG_SOURCE_LOCATION_METHOD` macro in `Exports.hpp`.

### Example: simple console logging

```cpp
#include <terminus/log.hpp>

int main()
{
    tmns::log::configure(); // default console sink

    tmns::log::info("Hello, world!");

    tmns::log::Logger logger{"example"};
    logger.debug("Something happened");

    tmns::log::flush();
}
```

### Example: JSON file logging via config file

See `test/component/logging-json.conf` and `TEST_Boost_JSON_File_Logger.cpp` for a complete example. The key bits in the config:

```ini
[Sinks.Json]
Destination=JsonFile
FileName="Json.log"
TargetFileName="Json-%3N.log"
Asynchronous=true
```

This uses the custom `JsonFile` sink registered by `tmns::log::impl::sinks::configure()` and formats each record as JSON using the `tmns::log::impl::format::json` formatter.

## Using terminus-log from CMake

After installing via Conan, you can consume the package from another CMake project using the generated config files:

```cmake
find_package(terminus_log REQUIRED CONFIG)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE terminus_log::terminus_log)
```

Because `terminus-log` is header-only, linking the target mainly propagates include directories and Boost usage requirements.

## Running tests

If `with_tests=True` (the default) when building with Conan, the following test binaries are built:

- `terminus_log_test` (unit tests in `test/unit`)
- Component examples under `test/component` (each added as a small executable)

You can run the unit tests from the build tree with:

```bash
cd build
ctest -V
```

The component tests are normal executables and can be run directly from `build/test/component`.

[![CI](https://github.com/neurosuite/libneurosuite/actions/workflows/ci.yml/badge.svg)](https://github.com/neurosuite/libneurosuite/actions/workflows/ci.yml)

# libneurosuite

Library for shared functionality between Klusters, NeuroScope and NDManager
(formerly libklustersshared).

Developed by Lynn Hazan (main developer), Laurent Montel (Qt3 to Qt4/5 porting), David Faure
(Qt3 to Qt4/5 porting), Michaël Zugaro (plugins, maintenance), Florian Franzen (maintenance)
and Joscha Schmiedt (Qt5 to Qt6 porting), distributed under the GNU General Public License
v3 or later.

## Building

Requires CMake 3.16+, a C++17 compiler and Qt 6.4+ (Widgets, PrintSupport, and optionally
WebEngineWidgets for the handbook viewer).

```bash
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build
cmake --install build
```

See [BUILD.md](BUILD.md) for details and options, and [CHANGELOG.md](CHANGELOG.md) for changes.
With Nix: `nix build` or `nix develop`.

# Changelog

All notable changes to this project are documented in this file.
The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/).

## [3.0.0] - unreleased

### Changed
- Ported to Qt 6 (6.4 or newer). Qt4 and Qt5 are no longer supported. Port by Joscha Schmiedt.
- Requires CMake 3.16 and C++17. Sources reformatted with clang-format.
- The shared library is versioned (`libneurosuite.so.3`).
- The CMake package exports the namespaced target `neurosuite::neurosuite` and installs
  to the standard GNU directories.
- The handbook viewer uses QtWebEngine instead of QtWebKit. QtWebEngine is optional
  (`-DWITH_WEBENGINE=OFF` falls back to QTextBrowser).
- Licence file corrected to GPL-3.0-or-later, matching the source headers.

### Fixed
- Links inside the handbook stay in the viewer; only external links open the browser.
- Icon and cursor resources are compiled into the library again.
- Creating a backup no longer writes an empty file when the original cannot be read.

### Removed
- Qt4/Qt5 build paths, the QStandardPaths backport, and the DeployQt5,
  DeployNeurosuite and PackNeurosuite CMake modules.
- Travis CI and AppVeyor configuration.

Thanks to Joscha Schmiedt for the Qt6 port, to Théotime de Charrin (MOBS team) whose Qt6
work served as a checklist, and to Jean-Christophe Fillion-Robin for the Qt5 lookup fix.

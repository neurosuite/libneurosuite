{ lib
, stdenv
, src
, cmake
, ninja
, qtbase
, qtwebengine
, withWebEngine ? true
}:

stdenv.mkDerivation {
  pname = "libneurosuite";
  version = "3.0.0";
  inherit src;

  nativeBuildInputs = [ cmake ninja ];
  buildInputs = [ qtbase ] ++ lib.optional withWebEngine qtwebengine;

  cmakeFlags = [ (lib.cmakeBool "WITH_WEBENGINE" withWebEngine) ];

  # Library only; nothing to wrap.
  dontWrapQtApps = true;

  meta = {
    description = "Shared library for Klusters, NeuroScope and NDManager";
    homepage = "https://neurosuite.github.io";
    license = lib.licenses.gpl3Plus;
    platforms = lib.platforms.unix;
  };
}

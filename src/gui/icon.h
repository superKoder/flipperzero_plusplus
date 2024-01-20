#pragma once

#include <gui/icon_i.h>

#if !__cplusplus
#error Only include this header in a C++17 file (does it have the right file extension?)
#endif // !__cplusplus

// TODO: wrap
using CIconRawPtr = ::Icon*;
using CConstIconRawPtr = const ::Icon*;

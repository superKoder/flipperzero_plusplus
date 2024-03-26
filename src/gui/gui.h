#pragma once

#include <gui/gui.h>

#if !__cplusplus
#error Only include this header in a C++17 file (does it have the right file extension?)
#endif // !__cplusplus

namespace gui {

// TODO: wrap
using CGuiRawPtr = ::Gui*;

} // namespace gui

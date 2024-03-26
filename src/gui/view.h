#pragma once

#include <gui/view.h>

#if !__cplusplus
#error Only include this header in a C++17 file (does it have the right file extension?)
#endif // !__cplusplus

namespace gui {

// TODO: wrap
using CViewRawPtr = ::View*;

} // namespace gui

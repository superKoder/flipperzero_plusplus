#pragma once

#include <gui/modules/menu.h>

#if !__cplusplus
#error Only include this header in a C++17 file (does it have the right file extension?)
#endif // !__cplusplus

#include "view.h"
#include "icon.h"
#include "../input/input.h"

#include <functional>

namespace gui {

using namespace input;
using namespace std::placeholders;

class Menu {
public:
    using RawCPtr = ::Menu*;
    using Index = uint32_t;
    using Callback = void (*)(void*, Index);

    inline Menu()
        : raw_ptr_(::menu_alloc()){};

    inline ~Menu() {
        ::menu_free(raw_ptr_);
    }

    inline CViewRawPtr GetView() {
        return ::menu_get_view(raw_ptr_);
    }

    inline void AddItem(
        Index index,
        const char* label,
        Callback callback,
        void* context,
        const CIconRawPtr icon = nullptr) {
        ::menu_add_item(
            raw_ptr_, label, icon, index, reinterpret_cast<MenuItemCallback>(callback), context);
    }

    inline void Reset() {
        ::menu_reset(raw_ptr_);
    }

    inline void SetSelectedItem(Index index) {
        ::menu_set_selected_item(raw_ptr_, index);
    }

private:
    RawCPtr raw_ptr_;
};

} // namespace gui
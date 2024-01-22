#pragma once

#include <gui/modules/menu.h>

#if !__cplusplus
#error Only include this header in a C++17 file (does it have the right file extension?)
#endif // !__cplusplus

#include "view.h"
#include "icon.h"

namespace gui {

class Menu {
public:
    using RawCPtr = ::Menu*;
    using Index = uint32_t;
    using Callback = void (*)(void* context, Index index);

    inline Menu()
        : raw_ptr_(::menu_alloc()){};

    inline ~Menu() {
        ::menu_free(raw_ptr_);
    }

    inline CViewRawPtr GetView() {
        return ::menu_get_view(raw_ptr_);
    }

    inline void AddItem(
        const char* label,
        const CIconRawPtr icon,
        Index index,
        Callback callback,
        void* context) {
        ::menu_add_item(raw_ptr_, label, icon, index, callback, context);
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
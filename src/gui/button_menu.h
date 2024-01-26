#pragma once

#include <gui/modules/button_menu.h>

#include "../input/input.h"

#if !__cplusplus
#error Only include this header in a C++17 file (does it have the right file extension?)
#endif // !__cplusplus

#include "view.h"
#include "icon.h"

namespace gui {

using namespace input;

class ButtonMenu {
public:
    using RawCPtr = ::ButtonMenu*;
    using RawItemCPtr = ::ButtonMenuItem*;
    using Index = int32_t;
    using Callback = void (*)(void* context, Index index, Input::Type type);

    enum class ItemType : std::underlying_type_t< ::ButtonMenuItemType> {
        Common = ::ButtonMenuItemTypeCommon,
        Control = ::ButtonMenuItemTypeControl,
    };

    inline ButtonMenu()
        : raw_ptr_(::button_menu_alloc()){};

    inline ~ButtonMenu() {
        ::button_menu_free(raw_ptr_);
    }

    inline CViewRawPtr GetView() {
        return ::button_menu_get_view(raw_ptr_);
    }

    inline RawItemCPtr
        AddItem(ItemType type, Index index, const char* label, Callback callback, void* context) {
        return ::button_menu_add_item(
            raw_ptr_,
            label,
            index,
            reinterpret_cast< ::ButtonMenuItemCallback>(callback),
            static_cast< ::ButtonMenuItemType>(type),
            context);
    }

    inline RawItemCPtr AddItem(Index index, const char* label, Callback callback, void* context) {
        return AddCommonItem(index, label, callback, context);
    }

    inline RawItemCPtr
        AddCommonItem(Index index, const char* label, Callback callback, void* context) {
        return AddItem(ItemType::Common, index, label, callback, context);
    }

    inline RawItemCPtr
        AddControlItem(Index index, const char* label, Callback callback, void* context) {
        return AddItem(ItemType::Control, index, label, callback, context);
    }

    inline void Reset() {
        ::button_menu_reset(raw_ptr_);
    }

    inline void SetHeader(const char* header) {
        ::button_menu_set_header(raw_ptr_, header);
    }

    inline void SetSelectedItem(Index index) {
        ::button_menu_set_selected_item(raw_ptr_, index);
    }

    // Just making sure:
    static_assert(sizeof(ItemType) == sizeof(::ButtonMenuItemType));
    static_assert(alignof(ItemType) == alignof(::ButtonMenuItemType));

private:
    RawCPtr raw_ptr_;
};

} // namespace gui
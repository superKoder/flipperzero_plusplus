#pragma once

#include <gui/modules/popup.h>

#if !__cplusplus
#error Only include this header in a C++17 file (does it have the right file extension?)
#endif // !__cplusplus

#include "view.h"
#include "icon.h"

namespace gui {

/** C++17 wrapper around <gui/modules/popup.h> */
class Popup {
public:
    /** Popup result callback type
 * @warning    comes from GUI thread
 */
    using Callback = void (*)(void* context);

private:
    using RawCPtr = ::Popup*;
    RawCPtr raw_ptr_;

public:
    inline Popup()
        : raw_ptr_(::popup_alloc()) {
    }

    inline ~Popup() {
        ::popup_free(raw_ptr_);
    }

    inline CViewRawPtr GetView() {
        return ::popup_get_view(raw_ptr_);
    }

    inline void SetCallback(Callback callback) {
        ::popup_set_callback(raw_ptr_, callback);
    }

    inline void SetContext(void* context) {
        ::popup_set_context(raw_ptr_, context);
    }

    inline void
        SetHeader(const char* text, uint8_t x, uint8_t y, Align horizontal, Align vertical) {
        ::popup_set_header(raw_ptr_, text, x, y, horizontal, vertical);
    }

    inline void SetText(const char* text, uint8_t x, uint8_t y, Align horizontal, Align vertical) {
        ::popup_set_text(raw_ptr_, text, x, y, horizontal, vertical);
    }

    inline void SetIcon(uint8_t x, uint8_t y, const CConstIconRawPtr icon) {
        ::popup_set_icon(raw_ptr_, x, y, icon);
    }

    inline void SetTimeout(uint32_t timeout_in_ms) {
        ::popup_set_timeout(raw_ptr_, timeout_in_ms);
    }

    /// Convenience wrapper around EnableTimeout() & DisableTimeout()
    /// @param enabled
    inline void EnableTimeout(bool enabled) {
        if(enabled) {
            EnableTimeout();
            return;
        }
        DisableTimeout();
    }

    inline void EnableTimeout() {
        ::popup_enable_timeout(raw_ptr_);
    }

    inline void DisableTimeout() {
        ::popup_disable_timeout(raw_ptr_);
    }

    inline void Reset() {
        ::popup_reset(raw_ptr_);
    };
};

} // namespace gui

#pragma once

#include <gui/view_dispatcher.h>

#if !__cplusplus
#error Only include this header in a C++17 file (does it have the right file extension?)
#endif // !__cplusplus

#include "view.h"
#include "gui.h"

namespace gui {

class ViewDispatcher {
private:
    using RawCPtr = ::ViewDispatcher*;
    RawCPtr raw_ptr_;

public:
    enum class Type {
        Desktop = ::ViewDispatcherTypeDesktop,
        Window = ::ViewDispatcherTypeWindow,
        Fullscreen = ::ViewDispatcherTypeFullscreen,
    };

    using ViewId = uint32_t;
    using Event = uint32_t;

    using CustomEventCallback = bool (*)(void* context, Event event);

    using NavigationEventCallback = bool (*)(void* context);

    using TickEventCallback = void (*)(void* context);

    inline ViewDispatcher()
        : raw_ptr_(::view_dispatcher_alloc()) {
    }

    inline ~ViewDispatcher() {
        ::view_dispatcher_free(raw_ptr_);
    }

    inline void EnableQueue() {
        ::view_dispatcher_enable_queue(raw_ptr_);
    }

    inline void SendCustomEvent(Event event) {
        ::view_dispatcher_send_custom_event(raw_ptr_, event);
    }

    inline void SetCustomEventCallback(CustomEventCallback callback) {
        ::view_dispatcher_set_custom_event_callback(raw_ptr_, callback);
    }

    inline void SetNavigationEventCallback(NavigationEventCallback callback) {
        ::view_dispatcher_set_navigation_event_callback(raw_ptr_, callback);
    }

    inline void SetTickEventCallback(TickEventCallback callback, uint32_t tick_period) {
        ::view_dispatcher_set_tick_event_callback(raw_ptr_, callback, tick_period);
    }

    inline void SetEventCallbackContext(void* context) {
        ::view_dispatcher_set_event_callback_context(raw_ptr_, context);
    }

    inline void Run() {
        ::view_dispatcher_run(raw_ptr_);
    }

    inline void Stop() {
        ::view_dispatcher_stop(raw_ptr_);
    }

    inline void AddView(ViewId view_id, CViewRawPtr view) {
        ::view_dispatcher_add_view(raw_ptr_, view_id, view);
    }

    inline void RemoveView(ViewId view_id) {
        ::view_dispatcher_remove_view(raw_ptr_, view_id);
    }

    inline void SwitchToView(ViewId view_id) {
        ::view_dispatcher_switch_to_view(raw_ptr_, view_id);
    }

    inline void SendToFront() {
        ::view_dispatcher_send_to_front(raw_ptr_);
    }

    inline void SendToBack() {
        ::view_dispatcher_send_to_back(raw_ptr_);
    }

    inline void AttachToGui(CGuiRawPtr gui, ::ViewDispatcherType type) {
        ::view_dispatcher_attach_to_gui(raw_ptr_, gui, type);
    }

    inline void AttachToGui(CGuiRawPtr gui, Type type) {
        AttachToGui(gui, static_cast< ::ViewDispatcherType>(type));
    }
};

} // namespace gui
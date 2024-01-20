#pragma once

#include <gui/scene_manager.h>

#if !__cplusplus
#error Only include this header in a C++17 file (does it have the right file extension?)
#endif // !__cplusplus

namespace gui {

/**
 * In contrary to the other C++ classes, this one didn't really exist in C before and therefore has no 1-to-1 counterpart. 
 * It is roughly a grouping of the entry/event/exit callbacks.
*/
class Scene {
public:
    using Id = uint32_t;
    using State = uint32_t;

    struct Event {
        enum class Type {
            Custom = ::SceneManagerEventTypeCustom,
            Back = ::SceneManagerEventTypeBack,
            Tick = ::SceneManagerEventTypeTick,
        };
        using Number = uint32_t;

        Type type;
        Number event;
    };

    using OnEnterCallback = void (*)(void* context);
    using OnEventCallback = bool (*)(void* context, Event event);
    using OnExitCallback = void (*)(void* context);

    // Just for the typedefs above... for now.
    Scene() = delete;
};

} // namespace gui

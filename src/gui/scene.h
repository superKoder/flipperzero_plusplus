#pragma once

#include <gui/scene_manager.h>

#if !__cplusplus
#error Only include this header in a C++17 file (does it have the right file extension?)
#endif // !__cplusplus

#include <string>

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
        enum class Type : std::underlying_type_t< ::SceneManagerEventType> {
            Custom = ::SceneManagerEventTypeCustom,
            Back = ::SceneManagerEventTypeBack,
            Tick = ::SceneManagerEventTypeTick,
        };
        using Number = uint32_t;

        Type type;
        Number number;
    };

    using OnEnterCallback = void (*)(void* context);
    using OnEventCallback = bool (*)(void* context, Event event);
    using OnExitCallback = void (*)(void* context);

    // Just for the typedefs above... for now.
    Scene() = delete;

    // Just making sure:
    static_assert(sizeof(Event::type) == sizeof(::SceneManagerEvent::type));
    static_assert(alignof(Event::type) == alignof(::SceneManagerEvent::type));
    static_assert(sizeof(Event::number) == sizeof(::SceneManagerEvent::event));
    static_assert(alignof(Event::number) == alignof(::SceneManagerEvent::event));
    static_assert(sizeof(Event) == sizeof(::SceneManagerEvent));
    static_assert(alignof(Event) == alignof(::SceneManagerEvent));
};

static std::string ToString(Scene::Event::Number value) {
    return std::to_string(value);
}

static std::string ToString(Scene::Event::Type value) {
    switch(value) {
    case Scene::Event::Type::Custom:
        return "Custom";
    case Scene::Event::Type::Back:
        return "Back";
    case Scene::Event::Type::Tick:
        return "Tick";
    }
    FURI_LOG_E(
        TAG,
        "Unknown Scene::Event::Type: %d",
        static_cast<std::underlying_type_t<Scene::Event::Type> >(value));
    return "UNKNOWN";
}

// TODO: Make more efficient
static std::string ToString(Scene::Event const& value) {
    return std::string("Event{") + ToString(value.type) + ", " + ToString(value.number) + "}";
}

} // namespace gui
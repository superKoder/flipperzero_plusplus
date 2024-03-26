#pragma once

#include <input/input.h>

#if !__cplusplus
#error Only include this header in a C++17 file (does it have the right file extension?)
#endif // !__cplusplus

namespace input {

using Key = ::InputKey;
class Input {
public:
    enum class Type : std::underlying_type_t< ::InputType> {
        PressDown = ::InputTypePress,
        Release = ::InputTypeRelease,
        ShortPress = ::InputTypeShort,
        LongPress = ::InputTypeLong,
        Repeat = ::InputTypeRepeat,
        
        Count = ::InputTypeMAX,
    };

    static_assert(sizeof(Type) == sizeof(::InputType));
    static_assert(alignof(Type) == alignof(::InputType));

    struct Event {
        // TODO: Maybe a std::variant?
        union {
            uint32_t sequence;
            struct {
                uint8_t sequence_source : 2;
                uint32_t sequence_counter : 30;
            };
        };
        Key key;
        Type type;
    };

    static inline const char* GetName(Key key) {
        return ::input_get_key_name(static_cast< ::InputKey>(key));
    }

    static inline const char* GetName(Type type) {
        return ::input_get_type_name(static_cast< ::InputType>(type));
    }
};

} // namespace input

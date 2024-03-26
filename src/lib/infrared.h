#pragma once

#include <lib/infrared/encoder_decoder/infrared.h>
#include <lib/infrared/worker/infrared_transmit.h>

#if !__cplusplus
#error Only include this header in a C++17 file (does it have the right file extension?)
#endif // !__cplusplus

namespace lib {

class Infrared {
public:
    static constexpr uint32_t const COMMON_CARRIER_FREQUENCY = 38000;
    static constexpr float const COMMON_DUTY_CYCLE = 0.33;

    static constexpr uint32_t const RAW_RX_TIMING_DELAY_US = 150000;
    static constexpr uint32_t const RAW_TX_TIMING_DELAY_US = 180000;

    enum class Protocol : std::underlying_type_t< ::InfraredProtocol> {
        Unknown = InfraredProtocolUnknown,
        NEC = ::InfraredProtocolNEC,
        NECext = ::InfraredProtocolNECext,
        NEC42 = ::InfraredProtocolNEC42,
        NEC42ext = ::InfraredProtocolNEC42ext,
        Samsung32 = ::InfraredProtocolSamsung32,
        RC6 = ::InfraredProtocolRC6,
        RC5 = ::InfraredProtocolRC5,
        RC5X = ::InfraredProtocolRC5X,
        SIRC = ::InfraredProtocolSIRC,
        SIRC15 = ::InfraredProtocolSIRC15,
        SIRC20 = ::InfraredProtocolSIRC20,
        Kaseikyo = ::InfraredProtocolKaseikyo,
        RCA = ::InfraredProtocolRCA,

        Count = ::InfraredProtocolMAX,
    };
    static_assert(sizeof(Protocol) == sizeof(::InfraredProtocol));
    static_assert(alignof(Protocol) == alignof(::InfraredProtocol));

    struct Message {
        Infrared::Protocol protocol;
        uint32_t address;
        uint32_t command;
        bool repeat;
    };
    static_assert(sizeof(Message) == sizeof(::InfraredMessage));
    static_assert(alignof(Message) == alignof(::InfraredMessage));

    enum class Status : std::underlying_type_t< ::InfraredStatus> {
        Error = ::InfraredStatusError,
        Ok = ::InfraredStatusOk,
        Done = ::InfraredStatusDone,
        Ready = ::InfraredStatusReady,
    };
    static_assert(sizeof(Status) == sizeof(::InfraredStatus));
    static_assert(alignof(Status) == alignof(::InfraredStatus));

    /// Infrared::Decoder
    class Decoder {
    public:
        enum class Level {
            Low,
            High,
        };

        inline Decoder()
            : handler_(::infrared_alloc_decoder()) {
        }

        inline ~Decoder() {
            ::infrared_free_decoder(handler_);
        }

        /// Raw wrapper around infrared_decode(). But see the overload.
        inline Message const* Decode(bool level, uint32_t duration) const {
            return reinterpret_cast<Message const*>(::infrared_decode(handler_, level, duration));
        }

        /// Convenience overload.
        inline Message const* Decode(Level level, uint32_t duration) const {
            return reinterpret_cast<Message const*>(
                ::infrared_decode(handler_, (level == Level::High), duration));
        }

        inline Message const* CheckReady() const {
            return reinterpret_cast<Message const*>(::infrared_check_decoder_ready(handler_));
        }

        inline void Reset() {
            ::infrared_reset_decoder(handler_);
        }

    private:
        ::InfraredDecoderHandler* handler_ = nullptr;
    };

    /// Infrared::Encoder
    class Encoder {
    public:
        inline Encoder()
            : handler_(::infrared_alloc_encoder()) {
        }

        inline ~Encoder() {
            ::infrared_free_encoder(handler_);
        }

        /// Raw wrapper. See convenience overload.
        inline Status Encode(uint32_t* o_duration, bool* o_level) {
            return static_cast<Status>(::infrared_encode(handler_, o_duration, o_level));
        }

        /// Raw wrapper. See convenience overload.
        inline Status Encode(uint32_t& o_duration, bool& o_level) {
            return Encode(&o_duration, &o_level);
        }

        inline void Reset(Message const* message) {
            ::infrared_reset_encoder(
                handler_, reinterpret_cast< ::InfraredMessage const*>(message));
        }

        inline void Reset(Message const& message) {
            Reset(&message);
        }

    private:
        ::InfraredEncoderHandler* handler_ = nullptr;
    };

    static inline char const* GetName(Protocol protocol) {
        return ::infrared_get_protocol_name(static_cast< ::InfraredProtocol>(protocol));
    }

    /// Make sure `protocol_name` is either an std::string or nul-terminated!
    static inline Protocol GetProtocol(std::string_view protocol_name) {
        return static_cast<Protocol>(::infrared_get_protocol_by_name(protocol_name.data()));
    }

    static inline uint8_t GetAddressLength(Protocol protocol) {
        return ::infrared_get_protocol_address_length(static_cast< ::InfraredProtocol>(protocol));
    }

    static inline uint8_t GetCommandLength(Protocol protocol) {
        return ::infrared_get_protocol_command_length(static_cast< ::InfraredProtocol>(protocol));
    }

    static inline bool IsValid(Protocol protocol) {
        return ::infrared_is_protocol_valid(static_cast< ::InfraredProtocol>(protocol));
    }

    static inline uint32_t GetFrequency(Protocol protocol) {
        return ::infrared_get_protocol_frequency(static_cast< ::InfraredProtocol>(protocol));
    }

    static inline float GetDutyCycle(Protocol protocol) {
        return ::infrared_get_protocol_duty_cycle(static_cast< ::InfraredProtocol>(protocol));
    }

    static inline size_t GetMinRepeatCount(Protocol protocol) {
        return ::infrared_get_protocol_min_repeat_count(
            static_cast< ::InfraredProtocol>(protocol));
    }

    /// Raw wrapper. See convenience overload.
    static inline void Send(Message const* message, int times = 1) {
        ::infrared_send(reinterpret_cast<InfraredMessage const*>(message), times);
    }

    /// Convenience overload.
    static inline void Send(Message const& message, int times = 1) {
        Send(&message, times);
    }

    /// Raw wrapper. See convenience Send() overload.
    static inline void
        SendRaw(uint32_t const timings[], uint32_t timings_cnt, bool start_from_mark) {
        ::infrared_send_raw(timings, timings_cnt, start_from_mark);
    }

    /// Convenience overload 1 for SendRaw().
    static inline void Send(uint32_t const timings[], uint32_t timings_cnt, bool start_from_mark) {
        ::infrared_send_raw(timings, timings_cnt, start_from_mark);
    }

    /// Convenience overload 2 for SendRaw().
    static inline void Send(std::vector<uint32_t> const& timings, bool start_from_mark) {
        SendRaw(&(timings[0]), timings.size(), start_from_mark);
    }

    /// Raw wrapper. See convenience Send() overload.
    static inline void SendRawExt(
        uint32_t const timings[],
        uint32_t timings_cnt,
        bool start_from_mark,
        uint32_t frequency,
        float duty_cycle) {
        ::infrared_send_raw_ext(timings, timings_cnt, start_from_mark, frequency, duty_cycle);
    }

    /// Convenience overload 1 for SendRawExt().
    static inline void Send(
        uint32_t const timings[],
        uint32_t timings_cnt,
        bool start_from_mark,
        uint32_t frequency,
        float duty_cycle) {
        SendRawExt(timings, timings_cnt, start_from_mark, frequency, duty_cycle);
    }

    /// Convenience overload 2 for SendRawExt().
    static inline void Send(
        std::vector<uint32_t> const& timings,
        bool start_from_mark,
        uint32_t frequency,
        float duty_cycle) {
        SendRawExt(&(timings[0]), timings.size(), start_from_mark, frequency, duty_cycle);
    }
};

} // namespace lib
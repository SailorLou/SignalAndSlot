
#pragma once

#include <functional>
#include <vector>
#include <utility>

typedef INVALID_CALLBACKID 0;

/**
 * \brief thread unsafe
 * order unstable, don't depend on callback register order.
 */
template <class... CallbackArgs>
class EventCallbackHandler final
{
public:
    typedef std::function<void(CallbackArgs...)> Callback;
    typedef std::uint32_t CallbackId;

    EventCallbackHandler() = default;
    ~EventCallbackHandler() = default;

    /**
     * \brief same as connect method in signal and slot mechanism
     */
    CallbackId Register(Callback&& cb)
    {
        // valid check
        if (cb)
        {
            mCallbacks.emplace_back(++mCallbackID, std::move(cb));
            return mCallbackID;
        }
        return INVALID_CALLBACKID;
    }

    /**
     * \brief same as connect method in signal and slot mechanism
     */
    CallbackId Register(const Callback& cb)
    {
        // valid check
        if (cb)
        {
            mCallbacks.emplace_back(++mCallbackID, cb);
            return mCallbackID;
        }

        return INVALID_CALLBACKID;
    }

    /**
     * \brief pick last callback to replace remove one
     * pop last callback
     * same as disconnect method in signal and slot mechanism.
     */
    bool Unregister(CallbackId id)
    {
        auto iter = mCallbacks.begin();
        for (; iter != mCallbacks.end(); iter++)
        {
            if (iter->first == id)
            {
                // move last callback inplace
                if (iter + 1 != mCallbacks.end())
                {
                    *iter = std::move(*mCallbacks.rbegin());
                }

                mCallbacks.pop_back();
                return true;
            }
        }

        return true;
    }

    void Run(CallbackArgs... args) // same as emit method in signal and slot mechanism
    {
        for (const auto& [id, cb] : mCallbacks)
        {
            cb(std::forward<CallbackArgs>(args)...);
        }
    }

private:
    std::uint32_t mCallbackID{};
    std::vector<std::pair<int, Callback>> mCallbacks{};
};

#pragma once
#include <atomic>
#include <functional>
#include <unordered_map>
#include <utility>

template <class... CallbackArgs>
class EventCallbackHandler final
{
public:
	typedef std::function<void(CallbackArgs...)> Callback;
	typedef std::uint64_t CallbackId;

	EventCallbackHandler() = default;
	~EventCallbackHandler()
	{
		safe_delete(mCallbacks);
	}

	CallbackId Register(Callback cb) // same as connect method in signal and slot mechanism
	{
		if (mCallbacks == nullptr)
			mCallbacks = new std::unordered_map<CallbackId, Callback>;

		CallbackId id(nextId());

		mCallbacks->emplace(id, cb);

		return id;
	}

	bool Unregister(CallbackId id) // same as disconnect method in signal and slot mechanism
	{
		if (mCallbacks == nullptr)
			return false;

		if (auto it = mCallbacks->find(id) != mCallbacks->end())
		{
			mCallbacks->erase(it);
		}

		return false;
	}

	void Run(CallbackArgs... args) // same as emit method in signal and slot mechanism
	{
		if (mCallbacks == nullptr)
			return;

		for (const auto& [id, cb] : *mCallbacks)
		{
			cb(std::forward<CallbackArgs>(args)...);
		}
	}

private:
	std::unordered_map<CallbackId, Callback>* mCallbacks{ nullptr }; //save memory as soon as possible for basic class

	static CallbackId nextId()
	{
		static std::atomic<CallbackId> gId(0);
		return ++gId;
	}
};

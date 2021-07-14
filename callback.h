/*
 * libsig.h - Trivial signal/callback library.
 *
 * Copyright (c) 2015 Matthew Brush <mbrush@codebrainz.ca>
 * You can use this code under the MIT license as described here:
 *     https://opensource.org/licenses/MIT
 *
 * To create a signal, declare member variables of type
 * `libsig::signal<...>` in your class. The template parameter is the
 * argument types that will be passed to the callback functions.
 *
 * Here's a simple example with a class `MyClass` that has a single
 * signal `my_signal` which takes a single `int` argument:
 *
 *     class MyClass
 *     {
 *     public:
 *         libsig::signal<int> my_signal;
 *         ...
 *     };
 *
 * To connect to a signal, call its `connect()` member function,
 * passing a function (in the `std::function` sense) as the argument.
 * The function can be a function pointer, a functor object, or
 * an anonymous lambda function.
 *
 * Here's an example connecting to the above signal to a lambda function:
 *
 *     MyClass my_class;
 *     my_class.my_signal.connect([](int x) {
 *         cout << "value: " << x << endl;
 *     });
 *
 * The `connect()` function returns a unique ID of type `signal::id_type`
 * which can be used later to disconnect the callback function.
 *
 * Here's an example using the above code to then immediately disconnect
 * the signal connection with the `disconnect()` member function:
 *
 *     MyClass my_class;
 *     auto id = my_class.my_signal.connect([](int x) {
 *         cout << "value: " << x << endl;
 *     });
 *     my_class.my_signal.disconnect(id);
 *
 * The `disconnect()` function is passed the callback ID and will
 * return `true` if a callback was disconnected or `false` if the
 * ID wasn't found.
 *
 * To emit the signal, call its `emit()` member function passing
 * arguments matching the types of those in the signal variable
 * declaration.
 *
 * Using the above example code, here's an example showing how to
 * emit `my_signal`:
 *
 *     my_class.my_signal.emit(42);
 *
 * Since the signal was declared to take a single `int` argument, this
 * will cause any callbacks connected to the signal to be called,
 * passing the integer `42` as the only argument.
 *
 * Signals can not have any return value. If you need to pass a return
 * value from the callback functions to the emitter, use an "out"
 * reference parameter as one of the arguments.
 *
 * All callback functions are called in succession, in the order of
 * connection, until the last one has been called. There is no
 * mechanism builtin to allow stopping the signal emission before
 * all callbacks have been called. If you need to do this, use
 * a reference parameter to indicate whether the signal has been
 * handled and code the callback functions to guard for this case.
 *
 * Libsig requires a compiler with decent C++11 support since it uses
 * class like `std::atomic`, `std::function`, as well as "uniform
 * initialization" and "move semantics".
 *
 * To use libsig, simply include this header in your code and use it
 * as described above.
 *
 */

#ifndef LIBSIG_H_BA8D2F07F0444A9EB4B9BEC42EA6F4D3_
#define LIBSIG_H_BA8D2F07F0444A9EB4B9BEC42EA6F4D3_

#include <atomic>
#include <cstdint>
#include <functional>
#include <vector>

namespace libsig
{

template< class... Args >
class signal
{
public:
	typedef std::function<void(Args...)> handler_type;
	typedef std::uint64_t id_type;

	id_type connect(handler_type hnd)
	{
		id_type id(next_id());
		handlers.push_back(handler{ id, std::move(hnd) });
		return id;
	}

	bool disconnect(id_type id)
	{
		for (size_t i=0, n=handlers.size(); i < n; i++)
		{
			if (handlers[i].id == id)
			{
				handlers.erase(handlers.begin() + i);
				return true;
			}
		}
		return false;
	}

	void emit(Args... args)
	{
		for (auto& h : handlers)
			h.func(args...);
	}

private:

	struct handler
	{
		id_type id;
		handler_type func;
	};

	std::vector<handler> handlers;

	static id_type next_id()
	{
		static std::atomic<id_type> id(0);
		return ++id;
	}

};

} // namespace libsig

#endif // LIBSIG_H_BA8D2F07F0444A9EB4B9BEC42EA6F4D3_
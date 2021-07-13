#include "Signal.h"
/*
template<class ... ArgTypes>
class _connection_base1
{
public:
    virtual void emit(ArgTypes) = 0;
};

template<class dest_type, class ... ArgTypes>
class _connection1 : public _connection_base1<ArgTypes>
{
public:
    _connection1()
    {
        pobject = nullptr;
        pmemfun = nullptr;
    }

    _connection1(dest_type* pobject, void (dest_type::* pmemfun)(ArgTypes))
    {
        mSlotObject = pobject;
        mSlotFunction = pmemfun;
    }

    virtual void emit(ArgTypes a1)
    {
        (m_pobject->*m_pmemfun)(a1);
    }

    virtual has_slots<mt_policy>* getdest() const
    {
        return m_pobject;
    }

private:
    dest_type* m_pobject;
    void (dest_type::* m_pmemfun)(ArgTypes);
};

template<class ... ArgTypes>
class Signal
{
public:

    typedef std::list < _connection_base1<ArgTypes>  connections_list;

    typedef std::is_function<void(ArgTypes)> SlotFunction;
    typedef std::

        template<class desttype>
    void connect(desttype* slotClass, void (desttype::* slot)(ArgTypes))
    {
        lock_block<mt_policy> lock(this);
        _connection1<desttype, arg1_type, mt_policy>* conn =
            new _connection1<desttype, arg1_type, mt_policy>(pclass, pmemfun);
        m_connected_slots.push_back(conn);
        pclass->signal_connect(this);
    }

    void emit(arg1_type a1)
    {
        lock_block<mt_policy> lock(this);
        connections_list::const_iterator itNext, it = m_connected_slots.begin();
        connections_list::const_iterator itEnd = m_connected_slots.end();

        while (it != itEnd)
        {
            itNext = it;
            ++itNext;

            (*it)->emit(a1);

            it = itNext;
        }
    }

    void operator()(arg1_type a1)
    {
        lock_block<mt_policy> lock(this);
        connections_list::const_iterator itNext, it = m_connected_slots.begin();
        connections_list::const_iterator itEnd = m_connected_slots.end();

        while (it != itEnd)
        {
            itNext = it;
            ++itNext;

            (*it)->emit(a1);

            it = itNext;
        }
    }
};

template<class dest_type1, class arg1_type1>
class _connection1
{

};

template<class dest_type1, class arg1_type1> std::list<_connection1<dest_type1, arg1_type1>> tes;
*/

int main()
{
    DataWnd dataWnd;

    NetAdapter::GetInstance()->SetNetState(0);

    NetAdapter::GetInstance()->SetNetState(1);

    return 0;
}
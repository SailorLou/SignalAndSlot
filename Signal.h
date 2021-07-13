#pragma once

#include "sigslot.h"
#include <memory>
#include <iostream>

//The signal owner can be a signal manager and put all signals in this singleton class
class NetAdapter
{
    typedef sigslot::signal1 < const int32_t&> NetStateSignal;
public:
    static NetAdapter* GetInstance()
    {
        return s_instance.get();
    }

    NetStateSignal& GetNetStateSignal()
    {
        return net_state_signal_;
    }

public:
    void SetNetState(const int32_t& nState)
    {
        net_state_signal_.emit(nState);
    }

private:
    static std::shared_ptr<NetAdapter> s_instance;

    NetStateSignal net_state_signal_;
};
std::shared_ptr<NetAdapter> NetAdapter::s_instance(new NetAdapter);


//Slot 1: Main interface
class MainWnd : public sigslot::has_slots<>
{
public:
    MainWnd()
    {
        NetAdapter::GetInstance()->GetNetStateSignal().connect(this, &MainWnd::OnNetStateChanged);
    }
    ~MainWnd()
    {
        NetAdapter::GetInstance()->GetNetStateSignal().disconnect(this);
    }
public:
    void OnNetStateChanged(const int32_t& nState)
    {
        //The main interface handles the logic of network status changes
        std::cout << "MainWnd Signal Callback, State = " << nState << std::endl;
    }
};


//Slot 2: Data interface
class DataWnd : public sigslot::has_slots<>
{
public:
    DataWnd()
    {
        NetAdapter::GetInstance()->GetNetStateSignal().connect(this, &DataWnd::OnNetStateChanged);
    }
    ~DataWnd()
    {
        NetAdapter::GetInstance()->GetNetStateSignal().disconnect(this);
    }
public:
    void OnNetStateChanged(const int32_t& nState)
    {
        //The data interface handles the logic of network status changes
        std::cout << "DataWnd Signal Callback, State = " << nState << std::endl;
    }
};
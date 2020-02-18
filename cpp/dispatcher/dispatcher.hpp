// ver 1.0 18.2.2020 16:00
#ifndef _ILRD_OL734_DISPATCHER_HPP_
#define _ILRD_OL734_DISPATCHER_HPP_

#include <list>                  // list
#include <algorithm>

namespace ilrd
{

template<typename Event>
class CallbackBase;

template<typename Event>
class Dispatcher
{
public:

    ~Dispatcher(); // implement stop within
    void Subscribe(CallbackBase<Event>* callbackBase_);
    void UnSubscribe(CallbackBase<Event>* callbackBase_);
    void NotifyAll(Event event_);

private:
    Dispatcher(const Dispatcher& other_); // not implemented
    const Dispatcher& operator=(const Dispatcher& other_); // not implemented

    std::list<CallbackBase<Event>* > m_subscribers;

    class NotifySubscriber;
    class NotifyDeathSubscriber;
};

template<typename Event>
class CallbackBase
{
public:

    CallbackBase();
    virtual ~CallbackBase(); 
    virtual void Notify(Event event_) =0;
    virtual void NotifyDeath() =0;

    void Stop();

private:
    friend class Dispatcher<Event>;
    CallbackBase(const CallbackBase& other_); // not implemented
    const CallbackBase& operator=(const CallbackBase& other_); // not implemented

    Dispatcher<Event>* m_dispatcher;    
};


template<typename Type, typename Event>
class Callback : public CallbackBase<Event>
{
public:
    Callback(Type& instance_, 
            void (Type::*notify_)(Event), 
            void (Type::*notifyDeath_)(void));
    void Notify(Event event_);
    void NotifyDeath();

private:
    Callback(const Callback& other_); // not implemented
    const Callback& operator=(const Callback& other_); // not implemented

    Type& m_instance;
    void (Type::*m_notify)(Event);
    void (Type::*m_notifyDeath)();
};

template<typename Event>
Dispatcher<Event>::~Dispatcher()
{
    NotifyDeathSubscriber notify_death_subscriber;
    std::for_each(m_subscribers.begin(), m_subscribers.end(), notify_death_subscriber);  
}

template<typename Event>
void Dispatcher<Event>::Subscribe(CallbackBase<Event>* callbackBase_)
{
    m_subscribers.push_front(callbackBase_);
    callbackBase_->m_dispatcher = this;
}

template<typename Event>
void Dispatcher<Event>::UnSubscribe(CallbackBase<Event>* callbackBase_)
{
    m_subscribers.erase(callbackBase_);
}

template<typename Event>
void Dispatcher<Event>::NotifyAll(Event event_)
{
    NotifySubscriber notify_subscriber(event_);
    std::for_each(m_subscribers.begin(), m_subscribers.end(), notify_subscriber);
}

template<typename Event>
CallbackBase<Event>::~CallbackBase()
{
    Stop();
}

template<typename Event>
void CallbackBase<Event>::Stop()
{
    m_dispatcher->UnSubscribe(this);
    m_dispatcher = NULL;
}

template<typename Type, typename Event>
Callback<Type, Event>::Callback(Type& instance_, void (Type::*notify_)(Event), void (Type::*notifyDeath_)())
    : m_instance(instance_), m_notify(notify_), m_notifyDeath(notifyDeath_) {}

template<typename Event>
class Dispatcher<Event>::NotifySubscriber
{
public:
    NotifySubscriber(Event event_)
        : m_event(event_) {}

    void operator()(Subscriber &s)
    {
        s.Notify(m_event);
    }
private:
    Event m_event;
};

template<typename Event>
class Dispatcher<Event>::NotifyDeathSubscriber
{
public:
    void operator()(Subscriber &s)
    {
        s.NotifyDeath();
    }
};

#endif // _ILRD_OL734_DISPATCHER_HPP_
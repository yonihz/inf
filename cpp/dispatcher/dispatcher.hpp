// ver 1.0 18.2.2020 16:00
#ifndef _ILRD_OL734_DISPATCHER_HPP_
#define _ILRD_OL734_DISPATCHER_HPP_

#include <list>                  // list
#include <algorithm>

#include <boost/core/noncopyable.hpp>

namespace ilrd
{

template<typename Event>
class CallbackBase;

template<typename Event>
class Dispatcher : private boost::noncopyable
{
public:

    ~Dispatcher();
    void Subscribe(CallbackBase<Event>* callbackBase_);
    void UnSubscribe(CallbackBase<Event>* callbackBase_);
    void NotifyAll(Event event_);

private:
    std::list<CallbackBase<Event>* > m_subscribers;

    class NotifySubscriber;
    class NotifyDeathSubscriber;
};

template<typename Event>
class CallbackBase : private boost::noncopyable
{
public:
    CallbackBase();
    virtual ~CallbackBase(); 
    virtual void Notify(Event event_) =0;
    virtual void NotifyDeath() =0;

    void Stop();

private:
    friend class Dispatcher<Event>;

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
    Type& m_instance;
    void (Type::*m_notify)(Event);
    void (Type::*m_notifyDeath)();
};

/******************************************************************************/
/****** Dispatcher ************************************************************/
/******************************************************************************/

template<typename Event>
Dispatcher<Event>::~Dispatcher()
{
    std::for_each(m_subscribers.begin(), m_subscribers.end(), NotifyDeathSubscriber());  
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
    callbackBase_->m_dispatcher = reinterpret_cast<Dispatcher<Event> *>(0);
    m_subscribers.remove(callbackBase_);
}

template<typename Event>
void Dispatcher<Event>::NotifyAll(Event event_)
{
    std::for_each(m_subscribers.begin(), m_subscribers.end(), NotifySubscriber(event_));
}

template<typename Event>
class Dispatcher<Event>::NotifySubscriber
{
public:
    NotifySubscriber(Event event_)
        : m_event(event_) {}

    void operator()(CallbackBase<Event> *c)
    {
        c->Notify(m_event);
    }
private:
    Event m_event;
};

template<typename Event>
class Dispatcher<Event>::NotifyDeathSubscriber
{
public:
    void operator()(CallbackBase<Event> *c)
    {
        c->NotifyDeath();
        c->m_dispatcher = reinterpret_cast<Dispatcher<Event> *>(0);
    }
};

/******************************************************************************/
/****** CallbackBase **********************************************************/
/******************************************************************************/

template<typename Event>
CallbackBase<Event>::CallbackBase()
    : m_dispatcher(reinterpret_cast<Dispatcher<Event> *>(0)) {}

template<typename Event>
CallbackBase<Event>::~CallbackBase()
{
    Stop();
}

template<typename Event>
void CallbackBase<Event>::Stop()
{
    if (m_dispatcher != reinterpret_cast<Dispatcher<Event> *>(0))
    {
        m_dispatcher->UnSubscribe(this);
    }
}

/******************************************************************************/
/****** Callback **************************************************************/
/******************************************************************************/

template<typename Type, typename Event>
Callback<Type, Event>::Callback(Type& instance_, void (Type::*notify_)(Event), void (Type::*notifyDeath_)())
    : m_instance(instance_), m_notify(notify_), m_notifyDeath(notifyDeath_) {}

template<typename Type, typename Event>
void Callback<Type, Event>::Notify(Event event_)
{
    (m_instance.*m_notify)(event_);
}

template<typename Type, typename Event>
void Callback<Type, Event>::NotifyDeath()
{
    (m_instance.*m_notifyDeath)();
}

}
#endif // _ILRD_OL734_DISPATCHER_HPP_
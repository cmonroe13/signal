#ifndef SIGNAL_H
#define SIGNAL_H

#include <functional>
#include <list>

template<typename R, typename... Args>
class SignalCommon
{
public:
  using Slot = typename std::function<R (Args...)>;
  using SlotID = typename std::list<Slot>::const_iterator;

  inline const SlotID connect(const Slot& cbFn)
  {
    return slots.insert(slots.cend(), cbFn);
  }

  inline const SlotID disconnect(const SlotID& itr)
  {
    return slots.erase(itr);
  }

  inline void clear()
  {
    slots.clear();
  }

  inline void operator ()(const Args&... args)
  {
    auto itr = slots.cbegin();
    auto end = slots.cend();
    bool next = true;
    while (itr != end)
    {
      const Slot& fn = *itr++;
      fn(args...);
    }
  }

protected:
  SignalCommon() = default;

protected:
  std::list<Slot> slots;

};

template<typename R, typename... Args>
class Signal;

template<typename R, typename... Args>
struct Signal<R (Args...)> : SignalCommon<R, Args...>
{
  template<typename Ret>
  inline Ret emit(std::function<Ret (Ret, R)> op, const Args&... args)
  {
    auto itr = this->slots.cbegin();
    auto end = this->slots.cend();
    bool next = true;
    Ret ret;
    while (itr != end)
    {
      auto fn = *itr++;
      ret = op(ret, fn(args...));
    }
    return ret;
  }
};

template<typename... Args>
struct Signal<void (Args...)> : SignalCommon<void, Args...>
{
  inline void emit(const Args&... args)
  {
    this->operator()(args...);
  }
};

#endif // SIGNAL_H

#pragma once

#include <vector>
#include <functional>
#include <algorithm>
#include <mutex>

class ActionSubscribe
{
private:
    using UnsubscribeCallback = std::function<void()>;
    UnsubscribeCallback m_unsubscribeCallback;

public:
    ActionSubscribe() = default;
    ActionSubscribe(UnsubscribeCallback callback) : m_unsubscribeCallback{callback} {}
    ~ActionSubscribe() { m_unsubscribeCallback(); }
    ActionSubscribe(const ActionSubscribe&) = delete;
    ActionSubscribe& operator=(const ActionSubscribe&) = delete;

    ActionSubscribe(ActionSubscribe&& other) noexcept
    {
        m_unsubscribeCallback = other.m_unsubscribeCallback;
        other.m_unsubscribeCallback = []() {};
    }

    ActionSubscribe& operator=(ActionSubscribe&& other) noexcept
    {
        m_unsubscribeCallback = other.m_unsubscribeCallback;
        other.m_unsubscribeCallback = []() {};
        return *this;
    }
};

template <class... Args>
class Action
{
private:
    using ActionHandler = std::function<void(Args...)>;
    std::vector<ActionHandler> m_actionHandlers;
    std::mutex m_mutex;

public:
    ActionSubscribe add(ActionHandler actionHandler)
    {
        std::unique_lock lock{m_mutex};
        m_actionHandlers.push_back(actionHandler);
        int size = m_actionHandlers.size();
        return ActionSubscribe{[&, size]() { remove(size); }};
    }

    void remove(size_t actionHandlerID)
    {
        std::unique_lock lock{m_mutex};
        m_actionHandlers.erase(m_actionHandlers.begin() + actionHandlerID - 1);
    }

    void notify(Args... args)
    {
        std::unique_lock lock{m_mutex};
        std::for_each(m_actionHandlers.begin(), m_actionHandlers.end(), [&](ActionHandler& handler) { handler(args...); });
    }
};
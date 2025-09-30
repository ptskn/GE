//
// Created by ptskn on 29/09/2025.
//

#ifndef SAASCORE_SCHEDULEDTASK_H
#define SAASCORE_SCHEDULEDTASK_H
#include <chrono>
#include <thread>
#include <functional>

class ScheduledTask {
public:
    ScheduledTask(std::chrono::seconds interval, std::function<void()> task)
        : interval_(interval), task_(std::move(task)), stop_(false) {
        thread_ = std::thread([this]() {
            while (!stop_) {
                auto start = std::chrono::steady_clock::now();
                task_();
                auto end = std::chrono::steady_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start);
                if (elapsed < interval_) {
                    std::this_thread::sleep_for(interval_ - elapsed);
                }
            }
        });
    }

    ~ScheduledTask() {
        stop_ = true;
        thread_.join();
    }

private:
    std::thread thread_;
    std::chrono::seconds interval_;
    std::function<void()> task_;
    std::atomic<bool> stop_;
};



#endif //SAASCORE_SCHEDULEDTASK_H
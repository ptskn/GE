//
// Created by ptskn on 29/09/2025.
//

#ifndef SAASCORE_MESSAGEDISPATCHER_H
#define SAASCORE_MESSAGEDISPATCHER_H


#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <memory>
#include <mosquitto.h>
class MessageDispatcher {
public:
    MessageDispatcher(size_t threadCount = 4)
        : stop_(false) {
        for (size_t i = 0; i < threadCount; ++i) {
            workers_.emplace_back([this]() {  // Capture explicite de `this`
                while (true) {
                    std::unique_lock<std::mutex> lock(queueMtx_);
                    cv_.wait(lock, [this]() { return stop_ || !tasks_.empty(); });
                    if (stop_ && tasks_.empty()) return;
                    routeMessage(std::move(tasks_.front()));
                    tasks_.pop();
                }
            });
        }
    }
    void routeMessage(const mosquitto_message* message)
    {
        std::string topic(message->topic);
        std::string payload(static_cast<char*>(message->payload), message->payloadlen);
//ici on va faire le métier
/*
        try {
            txManager->executeInTransaction([this]() {
                // Logique de traitement (ex: sauvegarde en JSON)
                std::cout << "Message reçu sur " << topic << ": " << payload << std::endl;
                // Exemple: sauvegarder payload dans un fichier
            });
        } catch (const std::exception& e) {
            std::cerr << "Erreur: " << e.what() << std::endl;
        }
        */
    }
    ~MessageDispatcher() {
        {
            std::lock_guard<std::mutex> lock(queueMtx_);
            stop_ = true;
        }
        cv_.notify_all();  // Réveille tous les threads
        for (auto& worker : workers_) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }


    void enqueue(const mosquitto_message *msg ) {
        {

            std::lock_guard<std::mutex> lock(queueMtx_);

            tasks_.emplace(msg);
        }
        cv_.notify_one();  // Réveille un thread en attente
    }

private:
    std::vector<std::thread> workers_;
    std::queue<const mosquitto_message*> tasks_;
    std::mutex queueMtx_;
    std::condition_variable cv_;
    std::atomic<bool> stop_;
};



#endif //SAASCORE_MESSAGEDISPATCHER_H
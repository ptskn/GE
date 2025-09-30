//
// Created by ptskn on 29/09/2025.
//

#ifndef SAASCORE_MOSQUITTOASYNCCLIENT_H
#define SAASCORE_MOSQUITTOASYNCCLIENT_H


#include <mosquitto.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <iostream>
#include "MessageDispatcher.h"
#include <mosquitto.h>
#include <thread>
#include <mutex>
#include <condition_variable>

class MosquittoAsyncClient {
    std::unique_ptr<MessageDispatcher> dispatcher;
public:
    using MessageCallback = std::function<void(const std::string topic, const std::string payload)>;

    MosquittoAsyncClient(const std::string& clientId, const std::string& host, int port)
        : clientId_(clientId), host_(host), port_(port) {
        dispatcher=std::make_unique<MessageDispatcher>();
        mosquitto_lib_init();
        mosq_ = mosquitto_new(clientId.c_str(), true, this);
        mosquitto_connect_callback_set(mosq_, [](struct mosquitto*, void* obj, int rc) {
            static_cast<MosquittoAsyncClient*>(obj)->onConnect(rc);
        });
        mosquitto_message_callback_set(mosq_, [](struct mosquitto*, void* obj, const struct mosquitto_message* msg) {
            static_cast<MosquittoAsyncClient*>(obj)->onMessage(msg);
        });
    }

    ~MosquittoAsyncClient() {
        mosquitto_disconnect(mosq_);
        mosquitto_destroy(mosq_);
        mosquitto_lib_cleanup();
    }

    void connect() {
        std::lock_guard<std::mutex> lock(mtx_);
        mosquitto_connect_async(mosq_, host_.c_str(), port_, 60);
        mosquitto_loop_start(mosq_);  // Démarre le thread interne de Mosquitto
    }

    void subscribe(const std::string& topic) {
        mosquitto_subscribe(mosq_, nullptr, topic.c_str(), 1);
    }

    void publish(const std::string& topic, const std::string& payload) {
        mosquitto_publish(mosq_, nullptr, topic.c_str(), payload.size(), payload.c_str(), 1, false);
    }

    void setMessageCallback(MessageCallback cb) {
        messageCallback_ = std::move(cb);
    }

private:
    void onConnect(int rc) {
        if (rc == 0) {
            std::cout << "Connecté à " << host_ << ":" << port_ << std::endl;
        } else {
            std::cerr << "Échec de connexion: " << mosquitto_strerror(rc) << std::endl;
        }
    }

    void onMessage(const struct mosquitto_message* msg) {
        if (messageCallback_) {
            std::string topic(msg->topic);
            std::string payload(static_cast<char*>(msg->payload), msg->payloadlen);
            dispatcher->enqueue(msg );
         //   messageCallback_(topic, payload);
        }
    }

    struct mosquitto* mosq_;
    std::string clientId_, host_;
    int port_;
    MessageCallback messageCallback_;
    std::mutex mtx_;
};


#endif //SAASCORE_MOSQUITTOASYNCCLIENT_H
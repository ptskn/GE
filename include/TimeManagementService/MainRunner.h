//
// Created by ptskn on 30/09/2025.
//

#ifndef SAASCORE_MAINRUNNER_H
#define SAASCORE_MAINRUNNER_H
#include <memory>

#include "MosquittoAsyncClient.h"
#include "MessageDispatcher.h"
#include "TransactionManager.h"
#include "ScheduledTask.h"
class MainRunner
{
    std::unique_ptr<MosquittoAsyncClient> client;

    std::unique_ptr<TransactionManager> txManager;
    std::function<void(std::string topic, std::string payload)> lastTask;
public:
    MainRunner()
    {
        // 1. Initialiser le client Mosquitto
        client = std::make_unique<MosquittoAsyncClient>("client1", "localhost", 1883);
        client->connect();

        // 2. Configurer le dispatcher de messages

         txManager=std::make_unique<TransactionManager>();
        lastTask=std::function<void(std::string topic, std::string payload)>();
        // 3. Définir le callback pour les messages entrants
   /*     client->setMessageCallback([this]( std::function<void(std::string , std::string )> ) {
         //

        });*/

        // 4. Souscrire à un topic
        client->subscribe("sensor/data");

    //    // 5. Planifier une publication périodique
    //    std::chrono::seconds interval(60);
    //    ScheduledTask publisher(interval, std::function<void()>() {
    //        client->publish("sensor/status", "{\"status\":\"ok\",\"timestamp\":" + std::to_string(time(nullptr)) + "}");
    //    });
//
        // 6. Boucle principale (ou attendre un signal)
        std::this_thread::sleep_for(std::chrono::hours(1));
    }
};
#endif //SAASCORE_MAINRUNNER_H
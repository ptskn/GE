//
// Created by ptskn on 28/09/2025.
//
#include <string>
#ifndef SAASCORE_LIBIPC_H
#define SAASCORE_LIBIPC_H

namespace std
{
class LibIPC
{
public :
    void subscribe(string &topic);
    void publish(string &topic,string &data);
    void broadcast(string &topic, string &data);
    string getPayload(string &topic);
};
}

#endif //SAASCORE_LIBIPC_H
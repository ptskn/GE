//
// Created by ptskn on 26/09/2025.
//

#ifndef SAASCORE_MQTTMESSAGE_H
#define SAASCORE_MQTTMESSAGE_H
#include <cstddef>
#include <concepts>
#include <functional>
#include <string>

//un seul le + simple possible
template<typename T>
concept incrementable =  requires(T a)
{
    a.begin()++;
};

//nesting
template<typename T>
concept testConcept =
    incrementable<T>
    //&&other<T>
    ;

#endif //SAASCORE_MQTTMESSAGE_H
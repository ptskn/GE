//
// Created by ptskn on 27/09/2025.
//

#ifndef SAASCORE_MUTEX_H
#define SAASCORE_MUTEX_H

//std::mutex m;
typedef std::lock_guard<std::mutex> mutexLockGuard;
//mutexLockGuard guard(m);
//...

#endif //SAASCORE_MUTEX_H
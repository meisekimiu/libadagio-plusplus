#ifndef GL_ADAGIO_RENDERPOOL_IMPL_H
#define GL_ADAGIO_RENDERPOOL_IMPL_H

#include "RenderPool.h"
#include <iostream>

template<typename T>
RenderPool<T>::RenderPool() {
    current = 0;
    pool.reserve(64);
}

template<typename T>
void RenderPool<T>::createNew(int number) {
    for (int i = 0; i < number; i++) {
        pool.push_back(T());
    }
}

template<typename T>
T *RenderPool<T>::getNext() {
    T *obj;
    if (current < pool.size()) {
        obj = &pool[current];
    } else {
        pool.push_back(T());
        obj = &pool[current];
    }
    ++current;
    return obj;
}

template<typename T>
void RenderPool<T>::begin() {
    current = 0;
}

template<typename T>
void RenderPool<T>::debugInfo(std::string poolName) {
    std::cout << poolName << " Pool: " << std::endl;
    std::cout << "\tSize:" << pool.size() << std::endl;
    std::cout << "\tCurrent:" << current << std::endl;
    std::cout << "\tUsage:" << (current / static_cast<double>(pool.size()) * 100.0) << "%" << std::endl;
}

#endif //GL_ADAGIO_RENDERPOOL_IMPL_H

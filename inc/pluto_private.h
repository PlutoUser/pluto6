#ifndef PLUTO_PRIVATE_H
#define PLUTO_PRIVATE_H

#include <memory>

#if __cplusplus < 201402L
namespace std {
template <typename T, typename... Args> std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}
#else
// using std::make_unique;
#endif

#endif /* PLUTO_PRIVATE_H */

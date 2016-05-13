// File: utils.hpp
#ifndef _h_VFN_UTILS_
#define _h_VFN_UTILS_

#include <experimental/optional>

namespace vfn {

template <typename T>
using Maybe = std::experimental::optional<T>;

constexpr auto& Nothing = std::experimental::nullopt;

template <typename T>
Maybe<T> Just(T&& val)
{
    return std::experimental::make_optional(std::forward<T>(val));
}

// TODO: fix type safety of F
template <typename T, typename F>
Maybe<T> operator>>(const Maybe<T>& maybe, F fun)
{
    if (maybe) {
        return fun(*maybe);
    } else {
        return Nothing;
    }
}

template <typename T, typename F>
Maybe<T> operator>>(Maybe<T>& maybe, F fun)
{
    if (maybe) {
        return fun(*maybe);
    } else {
        return Nothing;
    }
}

// template <typename T>
// Maybe<T> operator>>(const Maybe<T>& maybe, Maybe<T>(*fun)(T))
// {
//     if (maybe) {
//         return fun(*maybe);
//     } else {
//         return Nothing;
//     }
// }

// template <typename T>
// Maybe<T> operator>>(Maybe<T>& maybe, Maybe<T>(*fun)(T&))
// {
//     if (maybe) {
//         return fun(*maybe);
//     } else {
//         return Nothing;
//     }
// }

// template <typename T>
// Maybe<T> operator>>(const Maybe<T>& maybe, Maybe<T>(*fun)(const T&))
// {
//     if (maybe) {
//         return fun(*maybe);
//     } else {
//         return Nothing;
//     }
// }

// template <typename T>
// Maybe<T> operator>>(const Maybe<T>& maybe, std::function<Maybe<T>(T)>)
// {
//     if (maybe) {
//         return fun(*maybe);
//     } else {
//         return Nothing;
//     }
// }

} // namespace vfn

#endif

#pragma once

#include <utility> // std::integer_sequence

template <std::size_t Head, std::size_t... Elems>
struct PopFrontT<std::index_sequence<Head, Elems...> > {
    using type = std::index_sequence<Elems...>;
};

template <std::size_t Head, std::size_t... Elems>
struct FrontT<std::index_sequence<Head, Elems...> > {
    using type = std::integral_constant<std::size_t, Head>;
};

template <std::size_t... Elems, std::size_t E>
struct PushBackT<std::index_sequence<Elems...>, std::integral_constant<std::size_t, E> > {
    using type = std::index_sequence<Elems..., E>;
};

template <std::size_t... Elems, std::size_t E>
struct PushFrontT<std::index_sequence<Elems...>, std::integral_constant<std::size_t, E> > {
    using type = std::index_sequence<E, Elems...>;
};

template <>
struct IsEmpty<std::index_sequence<>> {
    static constexpr bool value = true;
};

template <std::size_t... Integrals>
struct ListSizeT<std::index_sequence<Integrals...>> {
    static constexpr std::size_t size = sizeof...(Integrals);
};

template <std::size_t... Nums>
struct EmptyListT<std::index_sequence<Nums...>> {
    using type = std::index_sequence<>;
};

template <>
struct ContainsOne<std::index_sequence<>> {
    static constexpr bool value = false;
};

template <size_t... Ts, size_t... Us>
struct ConcatT<std::index_sequence<Ts...>, std::index_sequence<Us...>> {
    using type = std::index_sequence<Ts..., Us...>;
}; 

template <std::size_t... Ts>
struct ClearSequenceT<std::index_sequence<Ts...> > {
    using type = std::index_sequence<>;
};

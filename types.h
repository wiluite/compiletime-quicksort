#pragma once

template <class...>
class List {};

template <class Head, class... Elems>
struct PopFrontT<List<Head, Elems...> > {
    using type = List<Elems...>;
};

template <class Head, class... Elems>
struct FrontT<List<Head, Elems...> > {
    using type = Head;
};

template <class... Elems, class E>
struct PushBackT<List<Elems...>, E> {
    using type = List<Elems..., E>;
};

template <class... Elems, class E>
struct PushFrontT<List<Elems...>, E> {
    using type = List<E, Elems...>;
};

template <>
struct IsEmpty<List<>> {
    static constexpr bool value = true;
};

template <class... Elems, template <class...> class L>
struct ListSizeT<L<Elems...>> {
    static constexpr std::size_t size = sizeof...(Elems);
};

template <class... Elems>
struct EmptyListT<List<Elems...>> {
    using type = List<>;
};

template <>
struct ContainsOne<List<>> {
    static constexpr bool value = false;
};

template <class... Elems1, class... Elems2>
struct ConcatT<List<Elems1...>, List<Elems2...>> {
    using type = List<Elems1..., Elems2...>;
}; 

#pragma once

#include <cstddef>

template <class L>
struct PopFrontT;
template <class L>
using PopFront = typename PopFrontT<L>::type;

template <class L>
struct FrontT;
template <class L>
using Front = typename FrontT<L>::type;

template <class L, class E>
struct PushBackT;
template <class L, class E>
using PushBack = typename PushBackT<L,E>::type;

template <class L, class E>
struct PushFrontT;
template <class L, class E>
using PushFront = typename PushFrontT<L,E>::type;

template <class L>
struct IsEmpty {
    static constexpr bool value = false;
};

template <class L>
struct ListSizeT;
template <class L>
static constexpr std::size_t ListSize = ListSizeT<L>::size;

template <class L>
struct EmptyListT;
template <class L>
using EmptyList = typename EmptyListT<L>::type;

template <class L>
struct ContainsOne {
    static constexpr bool value = IsEmpty<PopFront<L>>::value;
};

template <class L1, class L2>
struct ConcatT;
template <class L1, class L2>
using Concat = typename ConcatT<L1, L2>::type;

template <class S>
struct ClearSequenceT;
template <class S>
using ClearSequence = typename ClearSequenceT<S>::type ;

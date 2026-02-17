#pragma once

#include "primaries.h"
#include <type_traits>

// Тип результата разделения вокруг порога
template <class L, class R>
struct PartitionResult {
    using left = L;
    using right = R;
};

// Алгоритм Разделения

// Первичный шаблон
template<template <class> class Cmp, class L, class Result, bool=IsEmpty<L>::value>
struct PartitionT;
// Шаблон псевдонима
template<template <class> class Cmp, class L, class Result = PartitionResult<ClearSequence<L>, ClearSequence<L> > >
using Partition = typename PartitionT<Cmp, L, Result>::type;

// Рекурсивный случай
template<template <class> class Cmp, class L, class Result>
struct PartitionT<Cmp, L, Result, false> : 
           PartitionT<
               Cmp, 
               PopFront<L>,
               std::conditional_t<
                   Cmp<Front<L> >::value,
                   PartitionResult< PushBack<typename Result::left, Front<L> >, typename Result::right>,
                   PartitionResult< typename Result::left, PushBack<typename Result::right, Front<L> > >
               >
           >{};

// Базовый случай
template<template <class> class Cmp, class L, class Result>
struct PartitionT<Cmp,L,Result, true> {
    using type = Result;
};

// Реализация главного алгоритма сортировки QuickSort

// Первичный шаблон
template <class L, bool = IsEmpty<L>::value or ContainsOne<L>::value >
struct QuickSortT;
// Шаблон псевдонима
template <class L>
using QuickSort = typename QuickSortT<L>::type;

// Объявление CT-предиката, захватывающего порог и участвующего в разделении вокруг него левой и правой половин
template <class T>
struct CMP_LESS_EQUAL_CT {
    template <class U>
    struct apply;
};

// Рекурсивный случай
template <class L>
struct QuickSortT<L, false> {
    using Piv = Front<L>;
    using LNoPiv = PopFront<L>;
    using partition_result = Partition<CMP_LESS_EQUAL_CT<Piv>::template apply, LNoPiv>;
    using type = Concat<
                     PushBack<QuickSort<typename partition_result::left>, Piv>,
                     QuickSort<typename partition_result::right> 
                 >;
};

// Базовый случай
template <class L>
struct QuickSortT<L, true> {
    using type = L;
};

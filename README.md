# Compile-time QuickSort

Модуль реализации.

```cpp
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
```

Модуль проверки.

```cpp
#include "quicksort.h"
#include "types.h"
#include "integrals.h"
#include <string>

using namespace std;

// Определения и специализации CT-предиката, захватывающего порог и участвующего в разделении вокруг него левой и правой половин
template <class T>
template <class U>
struct CMP_LESS_EQUAL_CT<T>::apply {
    static constexpr bool value = sizeof(U) <= sizeof(T);
};
template <class T>
template <std::size_t M>
struct CMP_LESS_EQUAL_CT<T>::apply<std::integral_constant<std::size_t, M> > {
    constexpr static bool value = (M <= T::value);
};

// Проверка алгоритма разделения

using partition_result_for_types = Partition<
                                       CMP_LESS_EQUAL_CT<float>::template apply, 
                                       List<float, double, bool, short, double, string> 
                                   >;
static_assert(std::is_same_v<typename partition_result_for_types::left, List<float, bool, short>>);
static_assert(std::is_same_v<typename partition_result_for_types::right, List<double, double, string>>);


using partition_result_for_nums = Partition<
                                      CMP_LESS_EQUAL_CT<integral_constant<size_t, 3>>::template apply, 
                                      index_sequence<3, 4, 1, 2, 4, 5> 
                                  >;
static_assert(std::is_same_v<typename partition_result_for_nums::left, index_sequence<3, 1, 2>>);
static_assert(std::is_same_v<typename partition_result_for_nums::right, index_sequence<4, 4, 5>>);


// Проверка алгоритма QuickSort.

static_assert(std::is_same_v<QuickSort<List<>>, List<>>);
static_assert(std::is_same_v<QuickSort<List<double>>,
                                       List<double>>);
static_assert(std::is_same_v<QuickSort<List<double, float>>,
                                       List<float, double>>);
static_assert(std::is_same_v<QuickSort<List<double, string, short, char, float>>, 
                                       List<char, short, float, double, string>>);
static_assert(std::is_same_v<QuickSort<index_sequence<4, 5, 2, 500, 1, 2, 3>>, 
                                       index_sequence<1, 2, 2, 3, 4, 5, 500>>);

int main() {}
```

#pragma once

#include "primaries.h"
#include <type_traits>

// Не совсем partition, а вычленение либо левого, либо правого подсписка от L по опорному P
// в зависимости от условия Cmp
template <class L, class P, template <class, class> class Cmp, bool = IsEmpty<L>::value>
struct PartitionByCompareT;

// Шаблон псевдонима
template <class L, class P, template <class, class> class Cmp>
using PartitionByCompare = typename PartitionByCompareT<L, P, Cmp>::type;

// Рекурсивный случай
template <class L, class P, template <class, class> class Cmp>
struct PartitionByCompareT<L, P, Cmp, false> 
    : std::conditional<
                        Cmp<Front<L>, P>::value,
                        PushFront<PartitionByCompare<PopFront<L>, P, Cmp>, Front<L> >,
                        PartitionByCompare<PopFront<L>, P, Cmp>
                      > {};

// Базовый случай
template <class L, class P, template <class, class> class Cmp>
struct PartitionByCompareT<L, P, Cmp, true> {
    using type = L;
};


// Реализация главного алгоритма сортировки QuickSort

// Первичный шаблон
template <class L, bool = IsEmpty<L>::value or ContainsOne<L>::value >
struct QuickSortT;
// Шаблон псевдонима
template <class L>
using QuickSort = typename QuickSortT<L>::type;

// Объявления CT-предикатов
template <class T, class U>
struct CMP_LESS_EQUAL;
template <class T, class U>
struct CMP_MORE;

// Рекурсивный случай
template <class L>
struct QuickSortT<L, false> {
    using Piv = Front<L>;
    using LNoPiv = PopFront<L>;
    using type = Concat<
                     PushBack<QuickSort<PartitionByCompare<LNoPiv, Piv, CMP_LESS_EQUAL>>, Piv>,
                     QuickSort<PartitionByCompare<LNoPiv, Piv, CMP_MORE>> 
                 >;
};

// Базовый случай
template <class L>
struct QuickSortT<L, true> {
    using type = L;
};

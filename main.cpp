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


#include "quicksort.h"
#include "types.h"
#include "integrals.h"
#include <string>

using namespace std;

// Compile-time предикаты сравнения элементов
template <class T, class U>
struct CMP_LESS_EQUAL {
    static constexpr bool value = sizeof(T) <= sizeof(U); 
};
template <size_t T, size_t U>
struct CMP_LESS_EQUAL<integral_constant<size_t, T>, integral_constant<size_t, U>> {
    static constexpr bool value = T <= U; 
};
template <class T, class U>
struct CMP_MORE {
    static constexpr bool value = sizeof(T) > sizeof(U); 
};
template <size_t T, size_t U>
struct CMP_MORE<integral_constant<size_t, T>, integral_constant<size_t, U>> {
    static constexpr bool value = T > U; 
};

// Проверка получения списков элементов меньших либо равных опорному, и больше опорного
static_assert(std::is_same_v<PartitionByCompare<List<float, double, bool, short, double, std::string>, 
                                                float, 
                                                CMP_LESS_EQUAL>,

                                                List<float, bool, short> >);

static_assert(std::is_same_v<PartitionByCompare<index_sequence<3, 4, 1, 2, 4, 5>, 
                                                integral_constant<size_t, 3>, 
                                                CMP_LESS_EQUAL>,

                                                index_sequence<3, 1, 2> >);


static_assert(std::is_same_v<PartitionByCompare<index_sequence<3, 4, 1, 2, 4, 5>, 
                                                integral_constant<size_t, 3>,
                                                CMP_MORE>,

                                                index_sequence<4, 4, 5> >);

static_assert(std::is_same_v<PartitionByCompare<List<float, double, bool, short, double, std::string>, 
                                                float, 
                                                CMP_MORE>,

                                                List<double, double, std::string> >);

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


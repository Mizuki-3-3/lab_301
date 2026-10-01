#include "dyn_arr.hpp"
#include "errors.hpp"
#include "test.hpp"
#include "assertions.hpp"
#include <utility>

TEST(dyn_arr_constructor_size){
    dyn_arr<int> a(5);
    expect_eq_scalar("size после конструктора с размером", 5u, a.size());
}

TEST(dyn_arr_index_operator_read_write){
    dyn_arr<int> a(3);
    a[0] = 10;
    expect_eq_scalar("значение записано и прочитано через operator[]", 10, a[0]);
}

TEST(dyn_arr_deep_copy_is_independent){
    dyn_arr<int> a(2);
    a[0] = 1;
    dyn_arr<int> b(a);
    b[0] = 999;
    expect_eq_scalar("оригинал не изменился после правки копии", 1, a[0]);
    expect_eq_scalar("копия содержит новое значение", 999, b[0]);
}

TEST(dyn_arr_copy_assignment_is_independent){
    dyn_arr<int> a(2);
    a[0] = 1;
    dyn_arr<int> b(1);
    b = a;
    b[0] = 999;
    expect_eq_scalar("оригинал не изменился после правки b", 1, a[0]);
    expect_eq_scalar("b содержит новое значение", 999, b[0]);
}

TEST(dyn_arr_move_constructor_empties_source){
    dyn_arr<int> a(2);
    a[0] = 5;
    dyn_arr<int> b(std::move(a));
    expect_eq_scalar("исходный массив опустел после move", 0u, a.size());
    expect_eq_scalar("новый массив получил значение", 5, b[0]);
}

TEST(dyn_arr_resize_grow_preserves_values){
    dyn_arr<int> a(2);
    a[0] = 1;
    a[1] = 2;
    a.resize(4);
    expect_eq_scalar("размер после resize вверх", 4u, a.size());
    expect_eq_scalar("старое значение сохранилось", 1, a[0]);
}

TEST(dyn_arr_resize_shrink_truncates){
    dyn_arr<int> a(4);
    a[0] = 1; a[1] = 2; a[2] = 3; a[3] = 4;
    a.resize(2);
    expect_eq_scalar("размер после resize вниз", 2u, a.size());
    expect_eq_scalar("первый элемент сохранился", 1, a[0]);
}

TEST(dyn_arr_out_of_range_throws){
    dyn_arr<int> a(3);
    bool threw = false;
    try {
        (void)a[3];
    } catch (const index_out_of_range&) {
        threw = true;
    }
    expected_true("operator[] за границей выбрасывает index_out_of_range", threw);
}

TEST(dyn_arr_const_out_of_range_throws){
    const dyn_arr<int> a(3);
    bool threw = false;
    try {
        (void)a[3];
    } catch (const index_out_of_range&) {
        threw = true;
    }
    expected_true("const operator[] за границей тоже выбрасывает", threw);
}

TEST(dyn_arr_initializer_list_constructor){
    dyn_arr<int> a{1, 2, 3, 4};
    expect_eq_scalar("размер после initializer_list", 4u, a.size());
    expect_eq_scalar("третий элемент", 3, a[2]);
}

TEST(dyn_arr_default_constructor_is_empty){
    dyn_arr<int> a;
    expect_eq_scalar("размер пустого массива", 0u, a.size());
}

TEST(dyn_arr_iterator_traversal_matches_index){
    dyn_arr<int> a{10, 20, 30};
    size_t i = 0;
    for (auto it = a.begin(); it != a.end(); ++it, ++i){
        expect_eq_scalar("значение по итератору совпадает с operator[]", a[i], *it);
    }
    expect_eq_scalar("итератор прошёл все элементы", 3u, i);
}

TEST(dyn_arr_iterator_distance_equals_size){
    dyn_arr<int> a{1, 2, 3, 4, 5};
    expect_eq_scalar("расстояние между begin и end равно size",
        static_cast<std::ptrdiff_t>(a.size()), a.end() - a.begin());
}

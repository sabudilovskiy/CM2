#include <gtest/gtest.h>
#include "state_machine.hpp"

class FooTest :
    public testing::TestParamInfo<std::pair<std::string_view, bool>> {
    // You can implement all the usual fixture class members here.
    // To access the test parameter, call GetParam() from class
    // TestWithParam<T>.
};

TEST_P(FooTest, MainTest){

};

// TEST_CASE("Factorials are computed", "[factorial]") {
//     auto sm = create_default();
//     std::vector<std::pair<std::string, bool>> params =
//     {
//         {"{}", true},
//         {"{{[]}}    ", true},
//         {"{ [ ] { } }", true},
//         {"{", false},
//         {"}", false},
//         {"{[}", false},
//         {"[}", false},
//         {"{]}", false},
//         {"{{{{}}}}", true},
//         {"{{{[[]]}}}", true},
//         {"{ { { } [ [ ] { } ] } }", true},
//         {"{{}]", false},
//         {"{[}}", false},
//         {"{{{}]}}", false},
//         {"{{{]}]", false},
//         {"{[}]", false},
//         {"{[(])}", false},
//         {"{[(])}", false},
//         {"{[[{{}}]]}", false},
//         {"{[}]", false},
//         {"{[{]}]", false}
//     };
//     for (auto [expr, result]: params) {
//         SECTION(expr) {
//             try {
//                 REQUIRE(sm.parse(expr) == result);
//             }
//             catch (const std::exception& e) {
//                 FAIL(e.what());
//             }
//         }
//     }
// }

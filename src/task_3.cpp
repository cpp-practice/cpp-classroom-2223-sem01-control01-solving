#include "network.hpp"
#include <cassert>
#include <cstring>
#include <iostream>

static void smoke_part_3() {
    Post* post1 = create_post("u1", "m1");
    Post* post2 = create_post("u1", "m2");
    Post* post3 = create_post("u1", "m2", post1);
    Post* post4 = create_post("u1", "m2", post2);

    assert(timestamp(post1) == 0);
    assert(timestamp(post2) == 1);
    assert(timestamp(post3) == 2);
    assert(timestamp(post4) == 3);

    Post* result = merge(post3, post4);

    assert(result == post4);
    assert(previous(result) == post3);
    assert(previous(previous(result)) == post2);
    assert(previous(previous(previous(result))) == post1);
    assert(previous(previous(previous(previous(result)))) == nullptr);

    destroy_posts(result);
}

static void test_merge_as_concat() {
    Post* post1 = create_post("u1", "m1");
    Post* post2 = create_post("u1", "m2");
    Post* post3 = create_post("u1", "m3", post2);

    assert(timestamp(post1) == 4);
    assert(timestamp(post2) == 5);
    assert(timestamp(post3) == 6);

    Post* result = merge(post1, post3);

    assert(result == post3);
    assert(previous(result) == post2);
    assert(previous(previous(result)) == post1);
    assert(previous(previous(previous(result))) == nullptr);

    destroy_posts(result);
}

int main() {
    smoke_part_3();
    test_merge_as_concat();
    std::cout << "Task 3 completed!" << std::endl;
    return 0;
}

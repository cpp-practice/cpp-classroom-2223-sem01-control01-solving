#include "network.hpp"
#include <cassert>
#include <cstring>
#include <iostream>

static void smoke_part_2() {
    // simple case
    {
        Post* post = create_post("u1", "m1");
        Post* result = remove_by_content(post, "1");

        assert(result == nullptr);

        destroy_posts(result);
    };

    // harder case
    {
        Post* post1 = create_post("u1", "my cow");
        Post* post2 = create_post("u2", "cow is so", post1);
        Post* post3 = create_post("u2", "is so my", post2);
        Post* result = remove_by_content(post3, "my");

        assert(result == post2);
        assert(previous(result) == nullptr);

        destroy_posts(result);
    };
}

static void regression_1() {
    {
        Post* post1 = create_post("u1", "my cow");
        Post* post2 = create_post("u2", "cow is so", post1);
        Post* post3 = create_post("u2", "is so my", post2);
        Post* post4 = create_post("u2", "is so so", post3);
        Post* result = remove_by_content(post4, "my");

        assert(result == post4);
        assert(previous(result) == post2);
        assert(previous(post2) == nullptr);

        destroy_posts(result);
    };
}

// Requirement: Если в ленте не осталось постов, то возвращается nullptr
static void test_remove_all_feed() {
    Post* post1 = create_post("u1", "my so cow");
    Post* post2 = create_post("u2", "cow is so", post1);
    Post* post3 = create_post("u2", "is so my", post2);
    Post* post4 = create_post("u2", "is so so", post3);
    Post* result = remove_by_content(post4, "so");
    assert(result == nullptr);  
}

int main() {
    smoke_part_2();
    regression_1();
    test_remove_all_feed();
    std::cout << "Task 2 completed!" << std::endl;
    return 0;
}

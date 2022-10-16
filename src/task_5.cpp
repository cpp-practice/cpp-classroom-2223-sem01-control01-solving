#include "network.hpp"
#include <cassert>
#include <cstring>
#include <iostream>

static void smoke_part_5() {
    {
      Post* post = create_post("u1", "This is so interesting post!");
      replace_with_stars(post, "interesting");
      assert(std::strcmp(get_text(post), "This is so *********** post!") == 0);
      destroy_posts(post);
    }

    {
      Post* post = create_post("u1", "aaaaaaaaa");
      replace_with_stars(post, "aa");
      assert(std::strcmp(get_text(post), "********a") == 0);
      destroy_posts(post);
    }
}

static void test_pattern_with_star() {
    Post* post = create_post("u1", "abc*defdefdef");
    replace_with_stars(post, "*def");
    assert(std::strcmp(get_text(post), "abc****defdef") == 0);
    destroy_posts(post);
}


int main() {
    smoke_part_5();
    test_pattern_with_star();
    std::cout << "Task 5 completed!" << std::endl;
    return 0;
}

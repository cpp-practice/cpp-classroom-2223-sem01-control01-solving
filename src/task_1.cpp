#include "network.hpp"
#include <cassert>
#include <cstring>
#include <iostream>

static void smoke_part_1() {
    // simple calls
    {
        Post* post1 = create_post("u1", "m1");
        Post* post2 = create_post("u2", "m2", post1);

        assert(previous(post2) == post1);
        assert(previous(post1) == nullptr);

        assert(std::strcmp(get_user(post1), "u1") == 0);
        assert(std::strcmp(get_text(post2), "m2") == 0);

        destroy_posts(post2);
    }

    // don't forget to copy
    {
        char buff[] = "Hello msg";
        Post* post = create_post("u1", buff);

        buff[0] = 'A';
        assert(std::strcmp(get_text(post), buff) != 0); // Hello != Aello

        destroy_posts(post);
    }
}

int main() {
    smoke_part_1();
    std::cout << "Task 1 completed!" << std::endl;
    return 0;
}

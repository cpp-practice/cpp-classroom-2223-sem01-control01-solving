#include "network.hpp"
#include <cassert>
#include <cstring>
#include <iostream>

static void smoke_part_4() {
    Post* post = create_post("u1", "m1");

    char new_text[] = "My awesome new text!";
    set_text(post, new_text);
    assert(std::strcmp(get_text(post), new_text) == 0);
    new_text[std::strlen(new_text) - 1] = '?';
    assert(std::strcmp(get_text(post), new_text) != 0);

    destroy_posts(post);
}

int main() {
    smoke_part_4();
    std::cout << "Task 4 completed!" << std::endl;
    return 0;
}

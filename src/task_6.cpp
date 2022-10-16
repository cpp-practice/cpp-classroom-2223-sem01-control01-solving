#include "network.hpp"
#include <cassert>
#include <cstring>
#include <sstream>
#include <vector>
#include <iostream>

static void smoke_part_6() {
    // simple calls
    {
        Post* post1 = create_post("u1", "m1");
        Post* post2 = create_post("u2", "m2", post1);

        assert(previous(post2) == post1);
        assert(previous(post1) == nullptr);

        like_post(post1);
        Post* head = sort_by_likes(post2);
        assert(head == post1);
        assert(previous(post1) == post2);
        assert(previous(post2) == nullptr);

        destroy_posts(head);
    }

    // don't forget to copy
    for (size_t posts_num = 3; posts_num < 50; posts_num++) {
        std::vector<Post*> posts(posts_num);
        posts[posts_num - 1] = create_post("u1", "m1");
        for (size_t i = 1; i < posts_num; i++) {
            std::ostringstream ss;
            ss << "u" << i;
            std::string user = ss.str();
            ss.str("");
            ss << "m" << i;
            std::string message = ss.str();
            posts[posts_num - i - 1] = create_post(
                user.c_str(), message.c_str(), posts[posts_num - i]);
        }

        for (size_t i = 0; i < posts_num; i++) {
            if (i < posts_num - 1) {
                assert(previous(posts[i]) == posts[i + 1]);
            } else {
                assert(previous(posts[i]) == nullptr);
            }
            for (size_t j = 0; j < i; j++) {
                like_post(posts[i]);
            }
        }

        Post* head = posts[0];
        head = sort_by_likes(head);

        {
            Post* cur = head;
            for (size_t i = 0; i < posts_num; i++) {
                assert(cur == posts[posts_num - i - 1]);
                cur = previous(cur);
            }
        }

        head = sort_by_timestamp(head);
        {
            Post* cur = head;
            for (size_t i = 0; i < posts_num; i++) {
                assert(cur == posts[i]);
                cur = previous(cur);
            }
        }

        destroy_posts(head);
    }
}

static void test_same_likes_order() {
    {
        Post* post1 = create_post("u1", "m1");
        Post* post2 = create_post("u2", "m2", post1);
        like_post(post1);
        like_post(post2);
        Post* head = sort_by_likes(post2);

        assert(head == post2);
        assert(previous(post2) == post1);
        assert(previous(post1) == nullptr);

        destroy_posts(head);
    }

    {
        Post* post1 = create_post("u1", "m1");
        Post* post2 = create_post("u2", "m2", post1);
        Post* post3 = create_post("u2", "m2", post2);
        like_post(post1);
        like_post(post2);
        Post* head = sort_by_likes(post3);

        assert(head == post2);
        assert(previous(post2) == post1);
        assert(previous(post1) == post3);
        assert(previous(post3) == nullptr);
        destroy_posts(head);
    }
}

int main() {
    smoke_part_6();
    test_same_likes_order();
    std::cout << "Task 6 completed!" << std::endl;
    return 0;
}
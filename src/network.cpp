#include <cstdint>
#include <cstring>
#include "network.hpp"

// TASK 1

struct Post {
    char const *user;
    char *text;
    Post *tail;
};

void deletePost(const Post *head);

char *copyText(char const* text) {
    size_t text_size = std::strlen(text) + 1;
    char *new_text = new char [text_size];
    std::memcpy(new_text, text, text_size);
    return new_text;
}

Post *create_post(
        char const *user,
        char const *text,
        Post *head
) {
    Post *new_post = new Post{};
    new_post->user = copyText(user);
    new_post->text = copyText(text);
    new_post->tail = head;
    return new_post;
}

void destroy_posts(const Post *head) {
    while (head != nullptr) {
        const Post *temp = head->tail;
        deletePost(head);
        head = temp;
    }
}

void deletePost(const Post *head) {
    delete[] head->user;
    delete[] head->text;
    delete head;
}

Post* previous(Post const* post) {
    return post->tail;
}

char const* get_user(Post const* post) {
    return post->user;
}

char const* get_text(Post const* post) {
    return post->text;
}

// for TASK_3
//static std::uint64_t get_current_time() {
//    static std::uint64_t current_time = 0;
//    return current_time++;
//}

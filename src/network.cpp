#include <cstdint>
#include <cstring>
#include "network.hpp"

// TASK 1

struct Post {
    char const *user;
    char *text;
    Post *tail;
    std::uint64_t ts;
};

void deletePost(const Post *head);

char *copyText(char const* text) {
    size_t text_size = std::strlen(text) + 1;
    char *new_text = new char [text_size];
    std::memcpy(new_text, text, text_size);
    return new_text;
}

// for TASK_3
static std::uint64_t get_current_time() {
    static std::uint64_t current_time = 0;
    return current_time++;
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
    new_post->ts = get_current_time();
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


Post* remove_by_content(Post* head, char const* content)
{
    // prev <- curr <- next
    Post* curr = head;
    Post* next = nullptr;

    while (curr != nullptr) {
        auto prev = curr->tail;

        if (std::strstr(get_text(curr), content)) {
            deletePost(curr);

            if (next) // prev <- curr <- next
                next->tail = prev;
            else      // prev <- [curr/head]
                head = prev;
        }
        else {
            next = curr;
        }

        curr = prev;
    }

    return head;
}

std::uint64_t timestamp(Post const* post) {
  return post->ts;
}

Post* merge(Post* head_1, Post* head_2) {
  Post* new_head = nullptr;
  Post* last = nullptr;
  if (head_1->ts >= head_2->ts) {
    new_head = last = head_1;
    head_1 = head_1->tail;
  } else {
    new_head = last = head_2;
    head_2 = head_2->tail;
  }
  while (head_1 && head_2) {
    if (head_1->ts >= head_2->ts) {
      last->tail = head_1;
      head_1 = head_1->tail;
    } else {
      last->tail = head_2;
      head_2 = head_2->tail;
    }
    last = last->tail;
  }

  if (head_1) {
    last->tail = head_1;
  } else {
    last->tail = head_2;
  }

  return new_head;
}

void set_text(Post* post, char const* new_text) {
  delete[] post->text;
  post->text = copyText(new_text);
}

void replace_with_stars(Post* post, char const* pattern) {
  while (post) {
    auto where = post->text;
    while((where = std::strstr(where, pattern))) {
      auto l = strlen(pattern);
      std::memset(where, '*', l);
      where += l;
    }
    post = post->tail;
  }
}

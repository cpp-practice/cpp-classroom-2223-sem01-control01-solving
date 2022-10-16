#pragma once

#include <cstdint>

struct Post;

Post *create_post(
        char const *user,
        char const *text,
        Post *head = nullptr
);

void destroy_posts(const Post *head);

Post* previous(Post const* post);

char const* get_user(Post const* post); // возвращает автора поста
char const* get_text(Post const* post); // возвращает сообщение в посте

Post* remove_by_content(Post* head, char const* content);

// возвращает время создания поста
std::uint64_t timestamp(Post const* post);

// сливает две ленты в одну так, чтобы посты шли в хронологическом порядке
// посты из аргументов надо переиспользовать (без копирования)
Post* merge(Post* head_1, Post* head_2);

#include <string>
#include <chrono>
#include <memory>
#include "../user/user.h"

#pragma once
struct alignas(4) Message {
    std::string text;
    std::string time;
    std::unique_ptr<User> user;
} 
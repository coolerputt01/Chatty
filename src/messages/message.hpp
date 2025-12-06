#include <string>
#include <chrono>
#include <memory>
#include "../user/user.h"

#pragma once
struct Message {
    std::string text;
    std::string time;
    std::string username;
};
// ./include/constants.hpp
#pragma once
#include <QString>

namespace AppConstants {
const QString APP_NAME = "Snake Game";
const QString APP_VERSION = "0.0.2";

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;
const QString WINDOW_TITLE = "Snake Game";
const QString DEVELOPER_INFO = "Developer: Ace606";

constexpr int MIN_SPEED = 50;
constexpr int MAX_SPEED = 1000;
constexpr int DEFAULT_SPEED = 300;
constexpr int BUTTON_WIDTH = 150;
constexpr int BUTTON_HEIGHT = 40;
}  // namespace AppConstants
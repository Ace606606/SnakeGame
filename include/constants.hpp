// ./include/constants.hpp
#pragma once
#include <QMap>
#include <QString>

namespace AppConstants {

namespace LanguageCodes {
inline const QString ENGLISH_US = "en_US";
inline const QString RUSSIAN_RU = "ru_RU";

inline const QString PATH_TO_RUS_QM = ":/translations/compiled/ru_RU.qm";

inline QMap<QString, QString> LANGUAGE_NAMES{
    {LanguageCodes::ENGLISH_US, "English (US)"},
    {LanguageCodes::RUSSIAN_RU, "Russian"}};
}  // namespace LanguageCodes

inline const QString APP_NAME = "Snake Game";
inline const QString APP_VERSION = "0.0.2";

inline const int WINDOW_WIDTH = 500;
inline const int WINDOW_HEIGHT = 500;
inline const QString WINDOW_TITLE = "Snake Game";
inline const QString DEVELOPER_INFO = "Developer: Ace606";

inline constexpr int MIN_SPEED = 50;
inline constexpr int MAX_SPEED = 1000;
inline constexpr int DEFAULT_SPEED = 300;
inline constexpr int BUTTON_WIDTH = 150;
inline constexpr int BUTTON_HEIGHT = 40;

}  // namespace AppConstants

// namespace OptionConstants {
// const int MIN_SPEED = 50;
// const int MAX_SPEED = 1000;
// const int DEFAULT_SPEED = 300;
// }  // namespace OptionConstants
// ./include/constants.hpp
#pragma once
#include <QMap>
#include <QMetaType>
#include <QPair>
#include <QString>

namespace AppConstants {

namespace AboutApp {
inline const QString APP_NAME = "Snake Game";
inline const QString VERSION = "0.0.3";
inline const QString DEVELOPER = "Ace606606";
inline const QString GITHUB_LINK = "https://github.com/Ace606606/SnakeGame";
}  // namespace AboutApp

namespace LanguageCodes {
inline const QString DEFAULT_LANGUAGE = "en_US";
inline const QString ENGLISH_US = "en_US";
inline const QString RUSSIAN_RU = "ru_RU";

inline const QString PATH_TO_RUS_QM = ":/translations/compiled/ru_RU.qm";

inline QMap<QString, QString> LANGUAGE_NAMES{
    {LanguageCodes::ENGLISH_US, "English (US)"},
    {LanguageCodes::RUSSIAN_RU, "Russian"}};
}  // namespace LanguageCodes

// ======================== config window ========================
// window
inline const int WINDOW_WIDTH = 500;
inline const int WINDOW_HEIGHT = 500;

// btn
inline constexpr int BUTTON_WIDTH = 200;
inline constexpr int BUTTON_HEIGHT = 60;

// ======================== end config window ========================

namespace GameSettings {

enum class Difficulty { Easy, Medium, Hard };

inline const QMap<Difficulty, int> DIFFICULTY_SPEEDS = {
    {Difficulty::Easy, 250}, {Difficulty::Medium, 150}, {Difficulty::Hard, 75}};

inline const QMap<Difficulty, QString> DIFFICULTY_NAMES = {
    {Difficulty::Easy, "Easy"},
    {Difficulty::Medium, "Medium"},
    {Difficulty::Hard, "Hard"}};

inline const Difficulty DEFAULT_DIFFICULTY = Difficulty::Medium;

const bool DEFAULT_WALL_CROSSING = false;

}  // namespace GameSettings

}  // namespace AppConstants

Q_DECLARE_METATYPE(AppConstants::GameSettings::Difficulty)
// ./include/settings_manager.hpp

#include <QObject>
#include <QSettings>

#include "constants.hpp"

class QString;

// Q_DECLARE_METATYPE(AppConstants::GameSettings::Difficulty)

class SettingsManager : public QObject {
    Q_OBJECT
   public:
    static SettingsManager& instance();

    SettingsManager(const SettingsManager&) = delete;
    SettingsManager& operator=(const SettingsManager&) = delete;

    AppConstants::GameSettings::Difficulty getDifficulty() const;
    bool getWallCrossingAllowed() const;
    QString getLanguageCode() const;

    void setDifficulty(AppConstants::GameSettings::Difficulty difficulty);
    void setWallCrossingAllowed(bool allowed);
    void setLanguageCode(const QString& languageCode);

    QString getLogLevelName() const;
    bool getLogToFileEnabled() const;
    bool getLogToConsoleEnabled() const;

    void setLogLevelName(const QString& levelName);
    void setLogToFileEnabled(bool enabled);
    void setLogToConsoleEnabled(bool enabled);

   private:
    explicit SettingsManager(QObject* parent = nullptr);
    QSettings m_settings;
};
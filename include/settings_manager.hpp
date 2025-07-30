// ./include/settings_manager.hpp

#include <QObject>
#include <QSettings>

#include "constants.hpp"

class QSettings;
class QString;

class SettingsManager : public QObject {
    Q_OBJECT
   public:
    static SettingsManager& instance();

    SettingsManager(const SettingsManager&) = delete;
    SettingsManager& operator=(const SettingsManager&) = delete;

    void setLanguageCode(const QString& languageCode);
    void setDifficulty(AppConstants::GameSettings::Difficulty difficulty);
    void setWallCrossingAllowed(bool allowed);

    QString getLogLevelName() const;
    bool getLogToFileEnabled() const;
    bool getLogToConsoleEnabled() const;
    QString getConsoleLogLevelName() const;
    QString getFileLogLevelName() const;

    QString getLanguageCode() const;

    AppConstants::GameSettings::Difficulty getDifficulty() const;
    bool getWallCrossingAllowed() const;

    void resetToDefaults();

   private:
    QSettings m_settings;
    explicit SettingsManager(QObject* parent = nullptr);
    void initializeFileConfig();

    void setLogLevelName(const QString& levelName);
    void setLogToFileEnabled(bool enabled);
    void setLogToConsoleEnabled(bool enabled);
    void setConsoleLogLevelName(const QString& levelName);
    void setFileLogLevelName(const QString& levelName);
};
#ifndef JOURNALMANAGER_H
#define JOURNALMANAGER_H

#include <QObject>
#include <QString>

    class JournalManager : public QObject
{
    Q_OBJECT // Mandatory macro for any class talking to QML

public:
    explicit JournalManager(QObject *parent = nullptr);

    // Q_INVOKABLE allows QML to call these C++ functions directly
    Q_INVOKABLE void saveDatabase(const QString &jsonString);
    Q_INVOKABLE QString loadDatabase();
};

#endif // JOURNALMANAGER_H
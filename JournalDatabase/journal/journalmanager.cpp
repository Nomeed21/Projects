#include "journalmanager.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>

JournalManager::JournalManager(QObject *parent) : QObject(parent) {}

void JournalManager::saveDatabase(const QString &jsonString)
{
    // Creates a file in your app's current directory
    QFile file("journal_data.json");

    // Open the file in WriteOnly mode, erasing anything that was there before
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << jsonString;
        file.close();
        qDebug() << "Database saved successfully!";
    } else {
        qDebug() << "Failed to save database.";
    }
}

QString JournalManager::loadDatabase()
{
    QFile file("journal_data.json");

    // If the file doesn't exist yet (e.g., first time running), return empty brackets
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return "[]";
    }

    QTextStream in(&file);
    QString jsonString = in.readAll();
    file.close();

    return jsonString;
}
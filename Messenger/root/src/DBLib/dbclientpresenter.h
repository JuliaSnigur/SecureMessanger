#pragma once

#include <QVariantList>

namespace DB {
    class DBClientPresenter: public DBPresenter
    {
    public:
        DBClientPresenter();
        DBClientPresenter(const QString& nameDB);
        virtual  ~DBClientPresenter();
        bool insertDialog(const int& id );
        bool insertFile(QString filename, qlonglong size);
        QVariantList searchFile(const int& id);
        int searchID(const QString& login);
        int searchIdDialog(const int& id);
        bool insertMessage(const int& idDialog, const bool& recipient, const QString& mess, const QString& time);
        QQueue<QString> showDialog(const int& idDialog);
        void createDB(const QString& nameDB);

    protected:
        virtual void createTables();

    private:
        QString m_tabDialogs;
        QString m_tabMessages;
    };
}

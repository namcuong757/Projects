#ifndef DISPLAYMESSAGE_H
#define DISPLAYMESSAGE_H

#include <QtWidgets>

struct DisplayMessage
{

public:

    static void info(const QString& header, const QString& info)
    {
        QMessageBox msg;
        msg.setText(header);
        msg.setInformativeText(info);
        msg.setIcon(QMessageBox::Information);
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setBaseSize(600,120);
        msg.exec();
    }

    static void warning (const QString& header, const QString& info)
    {
        QMessageBox msg;
        msg.setText(header);
        msg.setInformativeText(info);
        msg.setIcon(QMessageBox::Warning);
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setBaseSize(600,120);
        msg.exec();
    }


};

#endif // DISPLAYMESSAGE_H

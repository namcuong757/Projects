#pragma once

#include <QtWidgets>

// Notifies an error
class ErrorNotification : public ::QMessageBox
{

public:

    // Constructors
    explicit ErrorNotification(QWidget& window, const QString& text) noexcept;

};

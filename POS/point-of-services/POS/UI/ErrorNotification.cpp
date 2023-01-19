#include <POS/UI/ErrorNotification.hpp>


///////////////////////////////////////////////////////////////////////////
ErrorNotification::ErrorNotification( QWidget& window,const QString& text) noexcept
    : QMessageBox{ &window }
{
    this->setText(text.toStdString().c_str());
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
    this->setStyleSheet(
                "background-color: #FFFFFF; "
                "color:rgb(255,0,0); "
                "font-size: 15px; "
                "QMessageBox { border-color: rgb(0, 0, 0); "
                "border-style: none; "
                "border-width: 0px; }"
                );
    this->setModal(false);
    this->setStandardButtons(QMessageBox::StandardButton::NoButton);
    this->show();
    QTimer::singleShot(1500, this, SLOT(hide()));
    window.setFocus();
}

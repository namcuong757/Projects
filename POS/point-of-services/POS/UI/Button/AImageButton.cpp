#include <POS/UI/Button/AImageButton.hpp>
#include <iostream>

// Constructors

///////////////////////////////////////////////////////////////////////////
AImageButton::AImageButton(
        QWidget& window, const QString& filename,
        int xPos, int yPos, int xSize, int ySize ) noexcept
    : QPushButton{ &window }
{
    this->setIcon(::QIcon{ (":icons/" + filename).toStdString().c_str() });
    this->setIconSize(QSize{ xSize, ySize });
    this->move(xPos, yPos);
    this->resize(xSize, ySize);
    this->show();
}

///////////////////////////////////////////////////////////////////////////
AImageButton::AImageButton(
        QWidget& window, const QString& filename, const QString& tooltip,
        int xPos, int yPos,int xSize, int ySize) noexcept
    : AImageButton{ window, filename, xPos, yPos, xSize, ySize }
{
    this->setToolTip(tooltip.toStdString().c_str());
    this->setIcon(::QIcon{ (":icons/" + filename).toStdString().c_str() });
    this->setIconSize(QSize{ xSize, ySize });
}

///////////////////////////////////////////////////////////////////////////
/// Constructor 3
///////////////////////////////////////////////////////////////////////////
/*
AImageButton::AImageButton(
        QWidget& window, const QString& filename, const QString& tooltip,
        const QString& label, int xPos, int yPos, int xSize, int ySize) noexcept
    : AImageButton{window, filename, tooltip, label, xPos, yPos, xSize, ySize }
{
    this->setToolTip(tooltip.toStdString().c_str());
    this->setIcon(::QIcon{ (filename).toStdString().c_str() });
    this->setIconSize(QSize{ xSize, ySize });
    this->setText(label.toStdString().c_str());
}
*/
///////////////////////////////////////////////////////////////////////////
AImageButton::~AImageButton() noexcept = default;

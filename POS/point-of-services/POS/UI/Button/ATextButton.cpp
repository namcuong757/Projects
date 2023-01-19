#include <POS/UI/Button/ATextButton.hpp>

///////////////////////////////////////////////////////////////////////////
ATextButton::ATextButton( QWidget& window, const QString& text,
    int xPos, int yPos,
    int xSize, int ySize) noexcept
    : QPushButton{ QString{ text.toStdString().c_str() }, &window }
{
    this->move((xPos), (yPos));
    this->resize((xSize), (ySize));
    this->show();
}

///////////////////////////////////////////////////////////////////////////
ATextButton::~ATextButton() noexcept = default;

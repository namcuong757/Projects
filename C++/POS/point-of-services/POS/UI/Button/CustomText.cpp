#include <POS/UI/Button/CustomText.hpp>

///////////////////////////////////////////////////////////////////////////
CustomText::CustomText(QWidget& window, const QString& text,
    int xPos, int yPos, int xSize, int ySize,
    std::function<void()> callback) noexcept
    : ATextButton{ window, text, xPos, yPos, xSize, ySize }, m_callback{ std::move(callback) }
{}

///////////////////////////////////////////////////////////////////////////
bool CustomText::hitButton(const QPoint &pos) const
{
    m_callback();
    return false;
}

#include <POS/UI/Button/CustomImage.hpp>
#include <POS/UI/ErrorNotification.hpp>

///////////////////////////////////////////////////////////////////////////
CustomImage::CustomImage( QWidget& window, const QString& filepath,
                          int xPos, int yPos,
                          int xSize, int ySize,
                          std::function<void()> callback) noexcept
    : AImageButton{ window, filepath, xPos, yPos, xSize, ySize }, m_window{ window }, m_callback{ std::move(callback) }
{}

CustomImage::CustomImage( QWidget& window, const QString& filepath, const QString& tooltip,
        int xPos, int yPos, int xSize, int ySize,
        std::function<void()> callback ) noexcept
    : AImageButton{ window, filepath, tooltip, xPos, yPos, xSize, ySize } , m_window{ window } , m_callback{ std::move(callback) }
{}
/*
CustomImage::CustomImage(QWidget& window, const QString& filepath,
                     const QString& tooltip, const QString& label,
                     int xPos, int yPos, int xSize, int ySize,
                     std::function<void()> callback) noexcept
    : AImageButton{window, filepath, tooltip, label, xPos,yPos,xSize,ySize}, m_window{ window } , m_callback{ std::move(callback)}
{}
*/
//Override

///////////////////////////////////////////////////////////////////////////
bool CustomImage::hitButton(const QPoint &pos) const
{
    try {
        m_callback();
    } catch (const std::exception& e) {
        new ErrorNotification{ m_window, e.what() };
    }
    return false;
}

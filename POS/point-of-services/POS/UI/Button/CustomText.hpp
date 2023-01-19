#pragma once

#include <POS/UI/Button/ATextButton.hpp>

// Simplifies the usage of a Qt button with an image
class CustomText : public ATextButton
{

public:

    // Constructors

    // The filename is searched within the ./assets/ directory
    explicit CustomText(QWidget& window, const QString& text, int xPos,
                        int yPos, int xSize, int ySize,
                        std::function<void()> callback) noexcept;

    // Override

    // Behavior on button click
    // Remove the selected row
    bool hitButton(const QPoint &pos) const override;

private:

    std::function<void()> m_callback;

};

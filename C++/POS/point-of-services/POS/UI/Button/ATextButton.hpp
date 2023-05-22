#pragma once

#include <QtWidgets>

// Simplifies the usage of a Qt button with an image
class ATextButton : public QPushButton
{

public:

    // Constructors
    // The filename is searched within the ./assets/ directory
    explicit ATextButton(QWidget& window, const QString& text,
                         int xPos, int yPos, int xSize, int ySize) noexcept;

    // Copy constructor
    ATextButton(const ATextButton& other) noexcept = delete;

    // Move constructor
    ATextButton(ATextButton& that) noexcept = delete;

    virtual ~ATextButton() noexcept;

    // Copy assign operator
    ATextButton& operator=(const ATextButton& other) noexcept = delete;

    // Move assign operator
    ATextButton operator=(ATextButton& that) noexcept = delete;

private:

    std::vector<QString> m_lines;

};

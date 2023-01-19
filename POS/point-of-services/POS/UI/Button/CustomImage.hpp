#pragma once

#include <POS/UI/Button/AImageButton.hpp>

// Simplifies the usage of a Qt button with an image
class CustomImage: public AImageButton
{

public:

    // Constructors

    //The filename is searched within the ./assets/ directory
    explicit CustomImage(QWidget& window, const QString& filepath,
                         int xPos, int yPos, int xSize, int ySize,
                         std::function<void()> callback) noexcept;

    // Constructor with tooltip
    // The filename is searched within the ./assets/icon directory
    explicit CustomImage(QWidget& window, const QString& filepath, const QString& tooltip,
                         int xPos, int yPos, int xSize, int ySize,
                         std::function<void()> callback) noexcept;
/*
    explicit CustomImage(QWidget& window, const QString& filepath,
                         const QString& tooltip, const QString& label,
                         int xPos, int yPos, int xSize, int ySize,
                         std::function<void()> callback) noexcept;
                         */
    // Override

    // Behavior on button click
    // Remove the selected row
    bool hitButton(const QPoint &pos) const override;

private:

    QWidget& m_window;
    std::function<void()> m_callback;

};

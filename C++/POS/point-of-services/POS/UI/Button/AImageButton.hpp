#pragma once

#include <QtWidgets>

//Simplifies the usage of a Qt button with an image
class AImageButton: public QPushButton
{

public:

    // Constructors

    //The filename is searched within the ./assets/icon directory
    explicit AImageButton(QWidget& window, const QString& filename,
                          int xPos, int yPos, int xSize, int ySize) noexcept;

    // Constructor with tooltip
    //The filename is searched within the ./assets/icon directory
    explicit AImageButton(QWidget& window, const QString& filename, const QString& tooltip,
                          int xPos, int yPos, int xSize, int ySize) noexcept;
    // Constructor with label and tooltip
    //The filename is searched within the ./ directory
    /*
    explicit AImageButton(QWidget& window, const QString& filepath,
                         const QString& tooltip, const QString& label,
                         int xPos, int yPos, int xSize, int ySize) noexcept;
                         */

    // Copy constructor
    AImageButton(const AImageButton& other) noexcept = delete;

    // Move constructor
    AImageButton(AImageButton& that) noexcept = delete;

    // Destructor
    virtual ~AImageButton() noexcept;

    // Operators

    // Copy assign operator
    AImageButton& operator=(const AImageButton& other) noexcept = delete;

    // Move assign operator
    AImageButton operator=(AImageButton& that) noexcept = delete;

private:

    std::vector<QString> m_lines;

};

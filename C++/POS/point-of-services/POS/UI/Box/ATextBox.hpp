#pragma once

#include <QtWidgets>

// Simplifies the usage of a Qt text box to write read only text
class ATextBox : public QTextEdit
{

public:

    // Constructors

    // forward to the other constructor while passing null valuesa
    explicit ATextBox(QWidget& window) noexcept;

    //Sets all variables except the string
    explicit ATextBox(QWidget& window,int xPos,
                      int yPos, int xSize, int ySize, bool readOnly = true) noexcept;

    //Destructor
    virtual ~ATextBox() noexcept;

    //Copy constructor
    ATextBox(const ATextBox& other) noexcept = delete;

    // Copy assign operator
    ATextBox& operator=(const ATextBox& other) noexcept = delete;

    //Move constructor
    ATextBox(ATextBox& that) noexcept = delete;

    //Move assign operator
    ATextBox operator=( ATextBox& that) noexcept = delete;

    // Accessors
    // add text at the end of the line
    void addText(const QString& line);

    // add new line to the current text
    void addLine(const QString& line);

    // clear all current lines
    void clearLine();

    // prints in Qt
    void print();

    ///////////////////////////////////////////////////////////////////////////
    void setPosition( int xPos, int yPos);

    ///////////////////////////////////////////////////////////////////////////
    void resize(int xSize, int ySize);

    ///////////////////////////////////////////////////////////////////////////
    ::std::size_t getLineSize();

    ///////////////////////////////////////////////////////////////////////////
    QString getText() const;

private:

    // Helpers

    //Sets the geometry according to the value of the variables
    void updateGeometry();

    int m_xPos;
    int m_yPos;
    int m_xSize;
    int m_ySize;

    std::vector<QString> m_lines;

};

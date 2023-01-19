#include <POS/UI/Box/ATextBox.hpp>

// Constructors

///////////////////////////////////////////////////////////////////////////
ATextBox::ATextBox(QWidget& window) noexcept: ATextBox{ window, 0, 0, 0, 0 } {}

///////////////////////////////////////////////////////////////////////////
ATextBox::ATextBox(QWidget& window,
                   int xPos, int yPos,
                   int xSize, int ySize,
                   bool readOnly) noexcept
    : QTextEdit{ &window }, m_xPos{ xPos }, m_yPos{ yPos }, m_xSize{ xSize }, m_ySize{ ySize }
{
    this->updateGeometry();
    this->setAlignment(::Qt::AlignLeft);
    this->setReadOnly(readOnly);
    this->show();
}

///////////////////////////////////////////////////////////////////////////
ATextBox::~ATextBox() noexcept = default;

///////////////////////////////////////////////////////////////////////////
void ATextBox::addText(const QString& text)
{
    m_lines.back() += text;
}

///////////////////////////////////////////////////////////////////////////
void ATextBox::addLine(const QString& line)
{
    m_lines.push_back(line);
}

///////////////////////////////////////////////////////////////////////////
void ATextBox::clearLine()
{
    m_lines.clear();
}

///////////////////////////////////////////////////////////////////////////
void ATextBox::print()
{
    QString str;
    for (const auto& line : m_lines) {
        str += line;
        str += '\n';
    }
//    if (!str.isEmpty()) {
//        str.erase(str.size() - 1);
//    }
    this->setText(str);
}

///////////////////////////////////////////////////////////////////////////
void ATextBox::setPosition(int xPos, int yPos)
{
    m_xPos = xPos;
    m_yPos = yPos;
    this->updateGeometry();
}

///////////////////////////////////////////////////////////////////////////
void ATextBox::resize(int xSize,int ySize)
{
    m_xSize = xSize;
    m_ySize = ySize;
    this->updateGeometry();
}

///////////////////////////////////////////////////////////////////////////
::std::size_t ATextBox::getLineSize()
{
    return m_lines.back().size();
}

///////////////////////////////////////////////////////////////////////////
auto ATextBox::getText() const -> QString
{
    ::std::string str;
    for (const auto& line : m_lines) {
        str += line.toStdString();
        str += '\n';
    }
    if (!str.empty()) {
        str.erase(str.size() - 1);
    }
    return str.c_str();
}

///////////////////////////////////////////////////////////////////////////
void ATextBox::updateGeometry()
{
    this->setGeometry(
        (m_xPos),
        (m_yPos),
        (m_xSize),
        (m_ySize)
    );
}

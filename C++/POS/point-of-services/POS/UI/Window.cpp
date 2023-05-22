#include <POS/UI/Window.hpp>

TransactionContainer::TransactionContainer(int xSize, int ySize, const QString& name) noexcept
{
    m_window.setWindowTitle(QApplication::translate("toplevel", name.toStdString().c_str()));
    this->resize(xSize, ySize);
    m_window.showFullScreen();
    //  this->hide();
}

void TransactionContainer::resize( int xSize, int ySize )
{
    m_xSize = xSize;
    m_ySize = ySize;
    m_window.resize((m_xSize), (m_ySize));
}

///////////////////////////////////////////////////////////////////////////
QWidget& TransactionContainer::get()
{
    return m_window;
}

///////////////////////////////////////////////////////////////////////////
QSize TransactionContainer::getSize() const
{
    return m_window.size();
}

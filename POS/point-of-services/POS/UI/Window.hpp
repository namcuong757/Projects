#pragma once

#include <QtWidgets>
#include <stdlib.h>
#include <functional>
#include <POS/UI/VirtualKeyPad.hpp>

// Simplifies and automates the usage of a qt window
// Contains a QApplication and a QMainWindow window
#include <functional>

class TransactionContainer
{

public:

    // Constructors

    // Creates, Resizes, renames, and show a Qt window
    explicit TransactionContainer( int xSize,int ySize, const QString& name) noexcept;


    // Helpers

    void resize(int xSize, int ySize);

    QWidget& get();

    QSize getSize() const;

    void linkVirtualKeyPad(VirtualKeyPad& virtualKeyPad)
    {
        m_window.m_keyboardInputCallback =
            std::bind(&VirtualKeyPad::write, &virtualKeyPad, std::placeholders::_1);
        m_window.m_validateCallback =
            std::bind(&VirtualKeyPad::validate, &virtualKeyPad);
    }

public:

    class InternalWindow : public QWidget
    {
    protected:
        void keyPressEvent(QKeyEvent *event) override
        {
            if (m_keyboardInputCallback) {
                switch (event->key()) {
                case Qt::Key_0: m_keyboardInputCallback.value()("0"); break;
                case Qt::Key_1: m_keyboardInputCallback.value()("1"); break;
                case Qt::Key_2: m_keyboardInputCallback.value()("2"); break;
                case Qt::Key_3: m_keyboardInputCallback.value()("3"); break;
                case Qt::Key_4: m_keyboardInputCallback.value()("4"); break;
                case Qt::Key_5: m_keyboardInputCallback.value()("5"); break;
                case Qt::Key_6: m_keyboardInputCallback.value()("6"); break;
                case Qt::Key_7: m_keyboardInputCallback.value()("7"); break;
                case Qt::Key_8: m_keyboardInputCallback.value()("8"); break;
                case Qt::Key_9: m_keyboardInputCallback.value()("9"); break;
                case Qt::Key_Period: m_keyboardInputCallback.value()("."); break;
                case Qt::Key_Return: m_validateCallback.value()(); break;
                case Qt::Key_Enter: m_validateCallback.value()(); break;
                default: break;
                }
            }
        }

    public:
        std::optional<std::function<void(const QString&)>> m_keyboardInputCallback;
        std::optional<std::function<void()>> m_validateCallback;
    }; // END InternalWindow

    TransactionContainer::InternalWindow m_window;
    int m_xSize;
    int m_ySize;

};

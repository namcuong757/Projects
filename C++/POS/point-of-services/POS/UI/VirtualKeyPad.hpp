#pragma once

#include <optional>
#include <POS/UI/Box/ATextBox.hpp>
#include <POS/UI/Button/CustomText.hpp>
#include <POS/UI/ProductContainer.hpp>
#include <POS/UI/ErrorNotification.hpp>

//Enable number typing with virtual key pad
// 9 buttons and a text boxclass VirtualKeyPad
class VirtualKeyPad : public QWidget {

public:

    // Constructors

    explicit VirtualKeyPad( QWidget& window, ProductContainer& products,
                            int visibleXPos, int visibleYPos,
                            int unvisibleXPos, int unvisibleYPos,
                            int xSize, int ySize) noexcept;

    // Animation

    void revealAll(std::function<void(const std::vector<QString>&)> validateCallback, QString base = "", bool isForMoney = false, int numValues = 1);
    void revealAnimation(QPropertyAnimation& anim, int unvisW, int unvisH, int visW, int visH, int idx=-1);

    void concealAll();
    void concealAnimation(QPropertyAnimation& anim, int visW, int visH, int unvisW, int unvisH);

    void write(const QString& str);

    void validate();



private:

    void addText(const QString& str);



private:

    QWidget& m_window;

    bool m_isForMoney{ false };
    bool m_isVisible{ false };
    int m_visibleXPos;
    int m_visibleYPos;
    int m_unvisibleXPos;
    int m_unvisibleYPos;

    bool mouseHeld = false;
    QTimer* mouseChecker;
    void checkMouse();

    QSize m_buttonSize;

    std::optional<std::function<void(const std::vector<QString>&)>> m_validateCallback;

    ATextBox m_textBox;
    std::array<CustomText, 16> m_buttons;

    ProductContainer& m_products;

    QPropertyAnimation m_textBoxAnimation;
    std::array<QPropertyAnimation*, 16> m_buttonAnimations;

    static inline constexpr const int animationDuration{ 200 };

    int m_remainingValues{ 0 };
    std::vector<QString> m_values;

};

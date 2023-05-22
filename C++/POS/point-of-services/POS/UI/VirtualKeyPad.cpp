#include <POS/UI/VirtualKeyPad.hpp>

VirtualKeyPad::VirtualKeyPad(QWidget& window,ProductContainer& products,
                             int visibleXPos, int visibleYPos, int unvisibleXPos, int unvisibleYPos, int xSize, int ySize
                             ) noexcept
    : m_window { window }
    , m_visibleXPos { visibleXPos }
    , m_visibleYPos { visibleYPos }
    , m_unvisibleXPos { unvisibleXPos }
    , m_unvisibleYPos { unvisibleYPos }
    , m_buttonSize { ( xSize / 4), (ySize) / 5 }
    , m_validateCallback { std::nullopt }
    , m_textBox { window, unvisibleXPos, unvisibleYPos, xSize, (m_buttonSize.height()) }

    // All the buttons in the keypad along with a lambda for their functionality
    , m_buttons {

          // Clear-Text Button
          CustomText {
          window,
          "clear",
          unvisibleXPos + m_buttonSize.width() * 0,
          unvisibleYPos + m_buttonSize.height() * 4,
          (m_buttonSize.width()),
          (m_buttonSize.height()),
          [this](){
    if(mouseHeld) return;
    mouseHeld = true;
    m_textBox.clearLine();
    if (m_isForMoney) {
        m_textBox.addLine("$0.00");
    } else {
        m_textBox.addLine("");
    }
    m_textBox.print(); }},

          // 0 Button
          CustomText {
          window,
          "0",
          unvisibleXPos + m_buttonSize.width() * 1,
          unvisibleYPos + m_buttonSize.height() * 4,
          (m_buttonSize.width()),
          (m_buttonSize.height()),
          [this](){
    // 0 button lambda
    if(mouseHeld) return;
    mouseHeld = true;
    this->write("0");}},

          // Validate Button
          CustomText {
          window,
          "validate",
          unvisibleXPos + m_buttonSize.width() * 2,
          unvisibleYPos + m_buttonSize.height() * 4,
          (m_buttonSize.width()),
          (m_buttonSize.height()),
          [this](){
    // Validate button lambda
    if(mouseHeld) return;
    mouseHeld = true;
    this->validate();} },

          // Close Button
          CustomText {
          window,
          "close",
          unvisibleXPos + m_buttonSize.width() * 3,
          unvisibleYPos + m_buttonSize.height() * 4,
          (m_buttonSize.width()),
          (m_buttonSize.height()),
          // Close Button Lambda
          [this](){ this->concealAll(); } },

          // 1 Button
          CustomText {
          window,
          "1",
          unvisibleXPos + m_buttonSize.width() * 0,
          unvisibleYPos + m_buttonSize.height() * 3,
          (m_buttonSize.width()),
          (m_buttonSize.height()),
          [this](){
    // 1 Button Lambda
    if(mouseHeld) return;
    mouseHeld = true;
    this->write("1"); } },

          // 2 Button
          CustomText {
          window,
          "2",
          unvisibleXPos + m_buttonSize.width() * 1,
          unvisibleYPos + m_buttonSize.height() * 3,
          (m_buttonSize.width()),
          (m_buttonSize.height()),
          [this](){
    // 2 Button Lambda
    if(mouseHeld) return;
    mouseHeld = true;
    this->write("2"); } },

          // 3 Button
          CustomText {
          window,
          "3",
          unvisibleXPos + m_buttonSize.width() * 2,
          unvisibleYPos + m_buttonSize.height() * 3,
          (m_buttonSize.width()),
          (m_buttonSize.height()),
          [this](){
    // 3 Button Lambda
    if(mouseHeld) return;
    mouseHeld = true;
    this->write("3"); } },

          // Double 0 cents Button
          CustomText {
          window,
          ".00",
          unvisibleXPos + m_buttonSize.width() * 3,
          unvisibleYPos + m_buttonSize.height() * 3,
          (m_buttonSize.width()),
          (m_buttonSize.height()),
          [this](){
    // .00 Button Lambda
    if(mouseHeld) return;
    mouseHeld = true;
    this->write(".00"); } },

          // 4 Button
          CustomText {
          window,
          "4",
          unvisibleXPos + m_buttonSize.width() * 0,
          unvisibleYPos + m_buttonSize.height() * 2,
          (m_buttonSize.width()),
          (m_buttonSize.height()),
          [this](){
    // 4 Button Lambda
    if(mouseHeld) return;
    mouseHeld = true;
    this->write("4"); } },

          // 5 Button
          CustomText {
          window,
          "5",
          unvisibleXPos + m_buttonSize.width() * 1,
          unvisibleYPos + m_buttonSize.height() * 2,
          (m_buttonSize.width()),
          (m_buttonSize.height()),
          [this](){
    // 5 Button Lambda
    if(mouseHeld) return;
    mouseHeld = true;
    this->write("5"); } },

          // 6 Button
          CustomText {
          window,
          "6",
          unvisibleXPos + m_buttonSize.width() * 2,
          unvisibleYPos + m_buttonSize.height() * 2,
          (m_buttonSize.width()),
          (m_buttonSize.height()),
          [this](){
    // 6 Button Lambda
    if(mouseHeld) return;
    mouseHeld = true;
    this->write("6"); } },

          // Single 0 cents Button
          CustomText {
          window,
          ".0",
          unvisibleXPos + m_buttonSize.width() * 3,
          unvisibleYPos + m_buttonSize.height() * 2,
          (m_buttonSize.width()),
          (m_buttonSize.height()),
          [this](){
    // .0 Button Lambda
    if(mouseHeld) return;
    mouseHeld = true;
    this->write(".0"); } },

          // 7 Button
          CustomText {
          window,
          "7",
          unvisibleXPos + m_buttonSize.width() * 0,
          unvisibleYPos + m_buttonSize.height() * 1,
          (m_buttonSize.width()),
          (m_buttonSize.height()),
          [this](){
    // 7 Button Lambda
    if(mouseHeld) return;
    mouseHeld = true;
    this->write("7"); } },

          // 8 Button
          CustomText {
          window,
          "8",
          unvisibleXPos + m_buttonSize.width() * 1,
          unvisibleYPos + m_buttonSize.height() * 1,
          (m_buttonSize.width()),
          (m_buttonSize.height()),
          [this](){
    // 8 Button Lambda
    if(mouseHeld) return;
    mouseHeld = true;
    this->write("8"); } },

          // 9 Button
          CustomText {
          window,
          "9",
          unvisibleXPos + m_buttonSize.width() * 2,
          unvisibleYPos + m_buttonSize.height() * 1,
          (m_buttonSize.width()),
          (m_buttonSize.height()),
          [this](){
    // 9 Button Lambda
    if(mouseHeld) return;
    mouseHeld = true;
    this->write("9"); } },

          // Decimal Button
          CustomText {
          window,
          ".",
          unvisibleXPos + m_buttonSize.width() * 3,
          unvisibleYPos + m_buttonSize.height() * 1,
          (m_buttonSize.width()),
          (m_buttonSize.height()),
          [this](){
    // . Button Lambda
    if(mouseHeld) return;
    mouseHeld = true;
    this->write("."); }

}} // END BUTTONS

    , m_products{ products }

    , m_textBoxAnimation {
          QPropertyAnimation{ &m_textBox, "pos" },
          }

    , m_buttonAnimations {}//{QPropertyAnimation{ &m_buttons[0], "pos" },QPropertyAnimation{ &m_buttons[1], "pos" },QPropertyAnimation{ &m_buttons[2], "pos" },QPropertyAnimation{ &m_buttons[3], "pos" },QPropertyAnimation{ &m_buttons[4], "pos" },QPropertyAnimation{ &m_buttons[5], "pos" },QPropertyAnimation{ &m_buttons[6], "pos" },QPropertyAnimation{ &m_buttons[7], "pos" },QPropertyAnimation{ &m_buttons[8], "pos" },QPropertyAnimation{ &m_buttons[9], "pos" },QPropertyAnimation{ &m_buttons[10], "pos" },QPropertyAnimation{ &m_buttons[11], "pos" },QPropertyAnimation{ &m_buttons[12], "pos" },QPropertyAnimation{ &m_buttons[13], "pos" },QPropertyAnimation{ &m_buttons[14], "pos" },QPropertyAnimation{ &m_buttons[15], "pos" }}

    // Constructor Body
{

    for (int i=0; i < 16; ++i)
    {
        m_buttonAnimations[i] = new QPropertyAnimation(&m_buttons[i], "pos");
        m_buttons[i].raise();
    }
    m_textBox.setFontPointSize(25);
    m_textBox.addLine("");

    mouseChecker = new QTimer();
    mouseChecker->setInterval(50);
    connect(mouseChecker, &QTimer::timeout, this, &VirtualKeyPad::checkMouse);
    mouseChecker->start();
}

///////////////////////////////////////////////////////////////////////////
void VirtualKeyPad::checkMouse()
{
    if (QGuiApplication::mouseButtons() != Qt::LeftButton)
        mouseHeld = false;
}

///////////////////////////////////////////////////////////////////////////
// Animation
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void VirtualKeyPad::revealAnimation(QPropertyAnimation& anim, int unvisW, int unvisH, int visW, int visH, int idx /* default -1 */)
{
    const auto startPosX{ m_unvisibleXPos + m_buttonSize.width() *  unvisW};
    const auto startPosY{ m_unvisibleYPos + m_buttonSize.height() * unvisH };
    const auto endPosX{ m_visibleXPos + m_buttonSize.width() * visW };
    const auto endPosY{ m_visibleYPos + m_buttonSize.height() * visH };
    anim.setDuration(VirtualKeyPad::animationDuration);
    anim.setStartValue(QPoint{(startPosX),(startPosY)});
    anim.setEndValue(QPoint{(endPosX),(endPosY)});
    anim.start();

    if (idx != -1)
        m_buttons[idx].raise();
}

///////////////////////////////////////////////////////////////////////////
void VirtualKeyPad::revealAll(std::function<void(const std::vector<QString>&)> validateCallback, QString baseStr, bool isForMoney, int numValues)
{
    m_products.setReadOnly(true);
    m_isForMoney = isForMoney;
    m_isVisible = true;
    m_validateCallback = validateCallback;
    m_remainingValues = numValues;

    // short and fucky
    int idx = 0;
    for (int dec = 4; dec >= 1; --dec)
        for (int inc = 0; inc <=3; ++inc)
        { revealAnimation(*m_buttonAnimations[idx], inc, dec, inc, dec, idx); ++idx; }

    revealAnimation(m_textBoxAnimation, 0,0,0,0);
    m_textBox.raise();

    if (baseStr.size()) {
        m_textBox.addText(baseStr);
        m_textBox.print();
    }
}

///////////////////////////////////////////////////////////////////////////
void VirtualKeyPad::concealAnimation(QPropertyAnimation& anim, int visW, int visH, int unvisW, int unvisH)
{
    const auto startPosX{ m_visibleXPos + m_buttonSize.width() * visW };
    const auto startPosY{ m_visibleYPos + m_buttonSize.height() * visH };
    const auto endPosX{ m_unvisibleXPos + m_buttonSize.width() * unvisW };
    const auto endPosY{ m_unvisibleYPos + m_buttonSize.height() * unvisH };
    anim.setDuration(VirtualKeyPad::animationDuration);
    anim.setStartValue(QPoint{(startPosX),(startPosY)});
    anim.setEndValue(QPoint{(endPosX),(endPosY)});
    anim.start();
}

///////////////////////////////////////////////////////////////////////////
void VirtualKeyPad::concealAll()
{
    m_products.setReadOnly(false);
    m_isVisible = false;
    m_textBox.clearLine();
    m_textBox.addLine("");
    m_textBox.print();
    m_values.clear();

    // short and fucky
    int idx=0;
    for (int dec = 4; dec >= 1; --dec)
        for (int inc = 0; inc <=3; ++inc)
            concealAnimation(*m_buttonAnimations[idx++], inc, dec, inc, dec);

    concealAnimation(m_textBoxAnimation, 0,0,0,0);
}

///////////////////////////////////////////////////////////////////////////
void VirtualKeyPad::write(const QString& str)
{
    if (m_isVisible) {
        if (m_isForMoney) {
            auto currentStr{ m_textBox.getText().toStdString() + str.toStdString() };

            if (currentStr[1] == '0') {
                currentStr.replace(1, 1, "");
            }
            auto it{ currentStr.find(".") };
            currentStr.replace(it, 1, "");
            currentStr.insert(it + 1, ".");
            // currentStr.replace(currentStr.size() - 1, 1, str.toStdString().c_str());
            qDebug() << currentStr.c_str();

            m_textBox.clearLine();
            m_textBox.addLine(currentStr.c_str());
            m_textBox.print();
        } else {
            m_textBox.addText(str);
            m_textBox.print();
            if (m_textBox.getLineSize() >= 8) {
                this->validate();
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////
void VirtualKeyPad::validate()
{
    try {
        m_values.emplace_back(m_textBox.getText());
        m_textBox.clearLine();
        m_textBox.addLine("");
        m_textBox.print();

        if (!--m_remainingValues && m_validateCallback) {
            m_validateCallback.value()(m_values);
        }
    } catch (const std::exception& e) {
        new ErrorNotification{ m_window, e.what() };
    }

    if (!m_remainingValues) {
        this->concealAll();
    }
}

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++23

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    customermanagerview.cpp \
    dbmanager.cpp \
    itemmanagerview.cpp \
    main.cpp \
    mainwindow.cpp \
    stylehelper.cpp \
    transactioneditview.cpp \
    transactionsviewer.cpp \
    all_transactions_view.cpp \
    POS/UI/ErrorNotification.cpp \
    POS/UI/ProductContainer.cpp \
    POS/UI/VirtualKeyPad.cpp \
    POS/UI/Window.cpp \
    POS/UI/Box/ATextBox.cpp \
    POS/UI/Button/AImageButton.cpp \
    POS/UI/Button/ATextButton.cpp \
    POS/UI/Button/CustomImage.cpp \
    POS/UI/Button/CustomText.cpp \
    POS/UI/Screen/Home.cpp \

HEADERS += \
    POS/UI/Button/ATextButton.hpp \
    customermanagerview.h \
    dbmanager.h \
    displaymessage.h \
    itemmanagerview.h \
    mainwindow.h \
    stylehelper.h \
    template_customer.h \
    template_item.h \
    template_register.h \
    template_transaction.h \
    transactioneditview.h \
    transactionsviewer.h \
    all_transactions_view.h\
    POS/UI/ErrorNotification.hpp \
    POS/UI/ProductContainer.hpp \
    POS/UI/VirtualKeyPad.hpp \
    POS/UI/Window.hpp \
    POS/UI/Box/ATextBox.hpp \
    POS/UI/Button/AImageButton.hpp \
    POS/UI/Button/CustomImage.hpp \
    POS/UI/Button/CustomText.hpp \
    POS/UI/Screen/Home.hpp \

FORMS += \
    mainwindow.ui

OTHER_FILES += recreate_tables.txt

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter

RESOURCES += \
    resources.qrc


DISTFILES += \
    Dark.qss \
    POS/UI/assets/add.png \
    POS/UI/assets/addFunds.png \
    POS/UI/assets/amexlogo.png \
    POS/UI/assets/checkmark.png \
    POS/UI/assets/clear.png \
    POS/UI/assets/create.png \
    POS/UI/assets/dinersclublogo.png \
    POS/UI/assets/discoverlogo.png \
    POS/UI/assets/exit.png \
    POS/UI/assets/jcblogo.png \
    POS/UI/assets/load.png \
    POS/UI/assets/maestrologo.png \
    POS/UI/assets/mastercardlogo.png \
    POS/UI/assets/pay.png \
    POS/UI/assets/remove.png \
    POS/UI/assets/removeFromDB.png \
    POS/UI/assets/save.png \
    POS/UI/assets/search.png \
    POS/UI/assets/visalogo.png \
    add.png \
    addFunds.png \
    amexlogo.png \
    checkmark.png \
    clear.png \
    create.png \
    dinersclublogo.png \
    discoverlogo.png \
    exit.png \
    ideas.txt \
    jcblogo.png \
    load.png \
    maestrologo.png \
    mastercardlogo.png \
    modules.config \
    pay.png \
    remove.png \
    removeFromDB.png \
    save.png \
    search.png \
    visalogo.png

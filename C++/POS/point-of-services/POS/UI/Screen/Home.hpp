#pragma once

// Headers
#include <QtWidgets>
#include <POS/UI/Window.hpp>
#include <POS/UI/ProductContainer.hpp>
#include <POS/UI/VirtualKeyPad.hpp>
#include <POS/UI/Box/ATextBox.hpp>
#include <POS/UI/Button/CustomImage.hpp>

// Describes the home page
// Contains a list of items, a virtual key pad and buttons to delete and checkout
class Home {

public:

    // Constructors

    explicit Home(TransactionContainer& window /*, std::shared_ptr<::db::Products> dbProducts*/) noexcept;


    // Accessors

    VirtualKeyPad& getVirtualKeyPad();

private:

    TransactionContainer& m_window;

    ProductContainer m_products;
    VirtualKeyPad m_virtualKeyPad;

    CustomImage m_addProductButton;
    CustomImage m_removeProductButton;
    CustomImage m_clearCartButton;
    CustomImage m_addFundsButton;
    CustomImage m_payButton;
    CustomImage m_saveCartButton;
    CustomImage m_loadCartButton;
    CustomImage m_exitButton;
//    CustomImage m_createOnDataBaseButton;
//    CustomImage m_removeOnDataBaseButton;
//    CustomImage m_searchInformationOnDataBaseButton;

};

#include "new_order_view.h"

NewOrderView::NewOrderView(QWidget* parent)
{
    mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);
    this->setObjectName("main_widget");

    // Title over table
    QLabel* tableTitle = new QLabel("Order");
    mainLayout->addWidget(tableTitle);
}

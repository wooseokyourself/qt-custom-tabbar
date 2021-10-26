#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "SplitTabWidget.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create Tab Widget.
    SplitTabWidget* TabWidget = new SplitTabWidget(this);
    TabWidget->SetMaximumSplit(4);

    // Set Tab Widget's configurations.
    // TabWidget->setGeometry(10, 10, 500, 500);

    // Create tabs.
    QWidget* FirstTab = new QWidget;
    FirstTab->setLayout(new QHBoxLayout);
    QPushButton* FirstButton = new QPushButton("First", FirstTab);
    FirstTab->layout()->addWidget(FirstButton);

    QWidget* SecondTab = new QWidget;
    SecondTab->setLayout(new QHBoxLayout);
    QPushButton* SecondButton = new QPushButton("Second", SecondTab);
    SecondTab->layout()->addWidget(SecondButton);

    QWidget* ThirdTab = new QWidget;
    ThirdTab->setLayout(new QHBoxLayout);
    QPushButton* ThirdButton = new QPushButton("Third", ThirdTab);
    ThirdTab->layout()->addWidget(ThirdButton);

    // Add tabs to tab widget.
    TabWidget->AppendPage(FirstTab, "First");
    TabWidget->AppendPage(SecondTab, "Second");
    TabWidget->AppendPage(ThirdTab, "Third");
}

MainWindow::~MainWindow()
{
    delete ui;
}


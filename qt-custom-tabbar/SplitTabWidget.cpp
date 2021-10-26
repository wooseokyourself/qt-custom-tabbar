#include "SplitTabWidget.hpp"

SplitTabWidget::SplitTabWidget(QWidget* parent) : QFrame(parent), mMaxSplit(10)
{
    setFrameStyle(QFrame::Panel | QFrame::Raised);
    setWindowFlags(Qt::SubWindow);

    QGridLayout* TopLayout = new QGridLayout(this);
    setLayout(TopLayout);
    TopLayout->setSpacing(0);

    uMenuWidget = new QFrame();
    uMenuWidget->setFrameStyle(QFrame::Panel | QFrame::Raised);

    uSplitter = new QSplitter(this);
    uSplitter->setHandleWidth(1);

    TopLayout->addWidget(uMenuWidget, 0, 0, Qt::AlignTop | Qt::AlignRight);
    TopLayout->addWidget(uSplitter, 1, 0);
    TopLayout->setRowStretch(1, 1);

    uMenuWidget->setLayout(new QHBoxLayout);
    uMenuWidget->layout()->setSpacing(0);

        uSplitButton = new QPushButton("Split", uMenuWidget);
        uSplitButton->resize(30, 30);
        connect(uSplitButton, &QPushButton::released, this, &SplitTabWidget::Split);
        uMenuWidget->layout()->addWidget(uSplitButton);

        uCloseButton = new QPushButton("Close", uMenuWidget);
        uCloseButton->resize(30, 30);
        connect(uCloseButton, &QPushButton::released, this, &SplitTabWidget::CloseLast);
        uMenuWidget->layout()->addWidget(uCloseButton);

        mTabList.push_back(new CustomTabWidget(uSplitter, this));
        uSplitter->addWidget(mTabList.front());

    TopLayout->addWidget(new QSizeGrip(this), 2, 0, Qt::AlignBottom | Qt::AlignRight);
    setMinimumSize(MIN_WIDTH, MIN_HEIGHT);
    uCloseButton->setEnabled(false);
}

void SplitTabWidget::AppendPage(QWidget* Page, const QString& Name)
{
    mTabList.front()->addTab(Page, Name);
}

void SplitTabWidget::SetDraggedPage(QWidget* Page, const QString& Name)
{
    mDraggedPage = Page;
    mDraggedPageName = Name;
}

QWidget* SplitTabWidget::GetDraggedPage(QString& PageName)
{
    PageName = mDraggedPageName;
    return mDraggedPage;
}

void SplitTabWidget::SetMaximumSplit(const int n)
{
    mMaxSplit = n;
}

void SplitTabWidget::Split()
{
    if (mTabList.size() >= mMaxSplit)
        return;
    CustomTabWidget* NewTabWidget = new CustomTabWidget(uSplitter, this);
    mTabList.push_back(NewTabWidget);
    uSplitter->addWidget(NewTabWidget);
    if (mTabList.size() >= mMaxSplit)
        uSplitButton->setEnabled(false);
    if (mTabList.size() > 1)
        uCloseButton->setEnabled(true);
}

void SplitTabWidget::CloseLast()
{
    if (mTabList.size() <= 1)
        return;
    CustomTabWidget* LastWidget = mTabList.back();
    mTabList.pop_back();
    LastWidget->MoveAllTabsTo(mTabList.back());
    delete LastWidget;
    if (mTabList.size() < mMaxSplit)
        uSplitButton->setEnabled(true);
    if (mTabList.size() <= 1)
        uCloseButton->setEnabled(false);
}

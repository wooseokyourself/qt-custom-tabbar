#include "CustomTabWidget.hpp"

#include <QApplication>
#include <QDrag>
#include <QMouseEvent>
#include <QMimeData>
#include "SplitTabWidget.hpp"

CustomTabWidget::CustomTabWidget(QWidget* qParent, class SplitTabWidget* ParentTab) : QTabWidget(qParent), mTabBar(nullptr)
{
    mTabBar = new CustomTabBar;
    mSplitTabWidget = ParentTab;
    setTabBar(mTabBar);
    mTabBar->setTabWidget(this);
    this->setAcceptDrops(true);
    this->setMouseTracking(true);
    this->setMovable(true);
    this->tabBar()->setMouseTracking(true);
}

void CustomTabWidget::dragEnterEvent(QDragEnterEvent* event)
{
    event->accept();
}

void CustomTabWidget::dragLeaveEvent(QDragLeaveEvent* event)
{
    event->accept();
}

void CustomTabWidget::dropEvent(QDropEvent* event)
{
    if (mSplitTabWidget == nullptr)
        return;
    event->setDropAction(Qt::MoveAction);
    event->accept();
    if (event->source()->parent() == this)
    {
        /// 여기서 return 대신 탭의 인덱스를 바꾸는 코드 추가해야함
        return;
    }
    QString PageName;
    QWidget* Page = mSplitTabWidget->GetDraggedPage(PageName);
    addTab(Page, PageName);
}

void CustomTabWidget::SetCurrentToDragged(const QString& PageName)
{
    if (mSplitTabWidget == nullptr)
        return;
    mSplitTabWidget->SetDraggedPage(currentWidget(), PageName);
}

void CustomTabWidget::MoveAllTabsTo(CustomTabWidget *Target)
{
    setCurrentIndex(0);
    while (count() != 0)
    {
        Target->addTab(currentWidget(), tabText(0));
    }
}

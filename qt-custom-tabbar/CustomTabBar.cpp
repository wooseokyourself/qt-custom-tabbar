#include "CustomTabBar.hpp"

#include <QApplication>
#include <QDrag>
#include <QMouseEvent>
#include <QMimeData>
#include <QDebug>
#include "CustomTabWidget.hpp"

CustomTabBar::CustomTabBar(CustomTabWidget* parent) : QTabBar((QWidget*)parent), mTabWidget(nullptr)
{
    setMouseTracking(true);
}

void CustomTabBar::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        mDragStartPosition = event->pos();
        setCurrentIndex(tabAt(event->pos()));
    }
}

void CustomTabBar::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() != Qt::LeftButton)
        return;
    if ((event->pos() - mDragStartPosition).manhattanLength() < QApplication::startDragDistance())
        return;

    QPoint GlobalPos = mapToGlobal(event->pos());
    QPoint PosInTab = mapFromGlobal(GlobalPos);
    mTabWidget->SetCurrentToDragged(tabText(currentIndex()));
    QRect TabRect = tabRect(currentIndex());

    QPixmap Pixmap = QPixmap(TabRect.size());
    render(&Pixmap, QPoint(), QRegion(TabRect));
    QMimeData* MimeData = new QMimeData();
    QDrag* Drag = new QDrag(this);
    Drag->setMimeData(MimeData);
    Drag->setPixmap(Pixmap);
    QCursor Cursor = QCursor(Qt::OpenHandCursor);
    Drag->setHotSpot(event->pos() - PosInTab);
    Drag->setDragCursor(Cursor.pixmap(), Qt::MoveAction);
    Drag->exec(Qt::MoveAction);
}

void CustomTabBar::mouseReleaseEvent(QMouseEvent* event)
{
}

void CustomTabBar::setTabWidget(CustomTabWidget* TabWidget)
{
    mTabWidget = TabWidget;
}

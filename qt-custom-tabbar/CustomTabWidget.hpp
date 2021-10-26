#ifndef CUSTOMTABWIDGET_HPP
#define CUSTOMTABWIDGET_HPP

#include "CustomTabBar.hpp"
#include <QTabWidget>
#include <QPushButton>

class SplitTabWidget;

class CustomTabWidget : public QTabWidget
{
public:
    explicit CustomTabWidget(QWidget* qParent = nullptr, SplitTabWidget* ParentTab = nullptr);
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragLeaveEvent(QDragLeaveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void SetCurrentToDragged(const QString& PageName);
    void MoveAllTabsTo(CustomTabWidget* Target);

private:
    CustomTabBar* mTabBar;
    SplitTabWidget* mSplitTabWidget; // parent
};

#endif // CUSTOMTABWIDGET_HPP

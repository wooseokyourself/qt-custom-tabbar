#ifndef CUSTOMTABBAR_HPP
#define CUSTOMTABBAR_HPP

#include <QTabBar>

class CustomTabWidget;

class CustomTabBar : public QTabBar
{
public:
    explicit CustomTabBar(CustomTabWidget* parent = nullptr);
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void setTabWidget(CustomTabWidget* TabWidget);

private:
    QPoint mDragStartPosition;
    CustomTabWidget* mTabWidget;
};

#endif // CUSTOMTABBAR_HPP

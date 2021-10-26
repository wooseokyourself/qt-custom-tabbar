#ifndef SPLITTABWIDGET_HPP
#define SPLITTABWIDGET_HPP

#include "CustomTabWidget.hpp"
#include <QList>
#include <QHBoxLayout>
#include <QWidget>
#include <QFrame>
#include <QSizeGrip>
#include <QSplitter>
#include <QDebug>

#define MIN_WIDTH 400
#define MIN_HEIGHT 400

class SplitTabWidget : public QFrame
{
public:
    explicit SplitTabWidget(QWidget* parent = nullptr);
    void AppendPage(QWidget* Page, const QString& Name);
    void SetDraggedPage(QWidget* Page, const QString& Name);
    QWidget* GetDraggedPage(QString& PageName);
    void SetMaximumSplit(const int n);

public slots:
    void Split();
    void CloseLast();

private:
    QFrame* uMenuWidget;
    QSplitter* uSplitter;
    QList<CustomTabWidget*> mTabList;
    QWidget* mDraggedPage;
    QString mDraggedPageName;
    QPushButton* uSplitButton;
    QPushButton* uCloseButton;
    int mMaxSplit;
};

#endif // SPLITTABWIDGET_HPP

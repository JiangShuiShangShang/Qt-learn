#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtWidgetsApplication1.h"
#include <qstandarditemmodel.h>
#include <qtreeview.h>
#include <qtreewidget.h>

class QtWidgetsApplication1 : public QWidget
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = nullptr);
    ~QtWidgetsApplication1();
    QTreeWidgetItem* addchildNode(QTreeWidgetItem* parent, QStringList childName, int index);
    void updateParentItem(QTreeWidgetItem* item);

    void setParentPartiallyChecked(QTreeWidgetItem* itm);
    QTreeWidget* treeWidget = nullptr;
    QStandardItemModel* m_StandardMode = nullptr;

private:
    Ui::QtWidgetsApplication1Class ui;

public slots:
    void treeItemChanged(QTreeWidgetItem* item, int column);
};

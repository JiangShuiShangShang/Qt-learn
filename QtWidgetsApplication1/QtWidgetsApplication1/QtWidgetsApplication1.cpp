#include "QtWidgetsApplication1.h"
#include <qstandarditemmodel.h>
#include <QVBoxLayout>
#include <QHeaderView>
#pragma execution_character_set("utf-8")
QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    treeWidget = new QTreeWidget(this);
    treeWidget->setColumnCount(2);
    //treeWidget->setHeaderLabels({ "名称"});
    treeWidget->setHeaderHidden(true);
    QHeaderView* head = treeWidget->header();
    head->setSectionResizeMode(0, QHeaderView::Stretch);
    head->setSectionResizeMode(1, QHeaderView::Fixed);
    treeWidget->setColumnWidth(1, 20);

    QTreeWidgetItem* rootItem = new QTreeWidgetItem(treeWidget, { "根节点"});
    rootItem->setCheckState(1, Qt::Unchecked);

    for (int i = 0; i < 5; i++) {
        QTreeWidgetItem* child = addchildNode(rootItem, { "子节点1" }, 0);
        for (int j = 0; j < 3; j++) {
            QTreeWidgetItem* grandchild = addchildNode(child, { "孙子节点1" }, 0);
        }
    }

    treeWidget->addTopLevelItem(rootItem);
    connect(treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(treeItemChanged(QTreeWidgetItem*, int)));
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(treeWidget);
    setLayout(layout);
}

QtWidgetsApplication1::~QtWidgetsApplication1()
{}

QTreeWidgetItem* QtWidgetsApplication1::addchildNode(QTreeWidgetItem * parent, QStringList childName,int index)
{
    QTreeWidgetItem* child = new QTreeWidgetItem(parent, { childName[index] });
    child->setCheckState(1, Qt::Unchecked);

    return child;

}

void QtWidgetsApplication1::updateParentItem(QTreeWidgetItem* item)
{
    QTreeWidgetItem* parent = item->parent();
    if (parent == NULL)
    {
        return;
    }
    int selectedCount = 0;
    int childCount = parent->childCount();
    //判断有多少个子项被选中
    for (int i = 0; i < childCount; i++) {
        QTreeWidgetItem* childItem = parent->child(i);
        if (childItem->checkState(1) == Qt::Checked) {
            selectedCount++;
        }
    }
    if (selectedCount <= 0)  //如果没有子项被选中，父项设置为未选中状态
    {
        parent->setCheckState(1, Qt::Unchecked);
    }
    else if (selectedCount > 0 && selectedCount < childCount)    //如果有部分子项被选中，父项设置为部分选中状态，即用灰色显示
    {
        parent->setCheckState(1, Qt::PartiallyChecked);
        // 重点：针对半选中状态的设置需要单独调用setParentPartiallyChecked后返回，否则上级节点的状态及当前节点的下级第一个节点的状态会不正确
        setParentPartiallyChecked(parent);
        return;
    }
    else if (selectedCount == childCount)    //如果子项全部被选中，父项则设置为选中状态
    {
        parent->setCheckState(1, Qt::Checked);
    }
    updateParentItem(parent);
}

void QtWidgetsApplication1::setParentPartiallyChecked(QTreeWidgetItem* itm)
{
    QTreeWidgetItem* parent = itm->parent();
    if (parent) {
        parent->setCheckState(1, Qt::PartiallyChecked);
        setParentPartiallyChecked(parent);
    }
}

void QtWidgetsApplication1::treeItemChanged(QTreeWidgetItem* item, int column)
{
    if (Qt::Checked == item->checkState(1)) {
        int count = item->childCount(); //返回子项的个数
        if (count > 0) {
            for (int i = 0; i < count; i++) {
                item->child(i)->setCheckState(1, Qt::Checked);
            }
        }
        else {
            updateParentItem(item);
        }
    }
    else if (Qt::Unchecked == item->checkState(1)) {
        int count = item->childCount();
        if (count > 0) {
            for (int i = 0; i < count; i++) {
                item->child(i)->setCheckState(1, Qt::Unchecked);
            }
        }
        else {
            updateParentItem(item);
        }
    }
}
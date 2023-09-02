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
    //treeWidget->setHeaderLabels({ "����"});
    treeWidget->setHeaderHidden(true);
    QHeaderView* head = treeWidget->header();
    head->setSectionResizeMode(0, QHeaderView::Stretch);
    head->setSectionResizeMode(1, QHeaderView::Fixed);
    treeWidget->setColumnWidth(1, 20);

    QTreeWidgetItem* rootItem = new QTreeWidgetItem(treeWidget, { "���ڵ�"});
    rootItem->setCheckState(1, Qt::Unchecked);

    for (int i = 0; i < 5; i++) {
        QTreeWidgetItem* child = addchildNode(rootItem, { "�ӽڵ�1" }, 0);
        for (int j = 0; j < 3; j++) {
            QTreeWidgetItem* grandchild = addchildNode(child, { "���ӽڵ�1" }, 0);
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
    //�ж��ж��ٸ����ѡ��
    for (int i = 0; i < childCount; i++) {
        QTreeWidgetItem* childItem = parent->child(i);
        if (childItem->checkState(1) == Qt::Checked) {
            selectedCount++;
        }
    }
    if (selectedCount <= 0)  //���û�����ѡ�У���������Ϊδѡ��״̬
    {
        parent->setCheckState(1, Qt::Unchecked);
    }
    else if (selectedCount > 0 && selectedCount < childCount)    //����в������ѡ�У���������Ϊ����ѡ��״̬�����û�ɫ��ʾ
    {
        parent->setCheckState(1, Qt::PartiallyChecked);
        // �ص㣺��԰�ѡ��״̬��������Ҫ��������setParentPartiallyChecked�󷵻أ������ϼ��ڵ��״̬����ǰ�ڵ���¼���һ���ڵ��״̬�᲻��ȷ
        setParentPartiallyChecked(parent);
        return;
    }
    else if (selectedCount == childCount)    //�������ȫ����ѡ�У�����������Ϊѡ��״̬
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
        int count = item->childCount(); //��������ĸ���
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
/********************************************************************************
** Form generated from reading UI file 'ATDynamicPrototype.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATDYNAMICPROTOTYPE_H
#define UI_ATDYNAMICPROTOTYPE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "AMapView.h"

QT_BEGIN_NAMESPACE

class Ui_ATDynamicPrototypeClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    AMapView *gvMain;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *btn;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ATDynamicPrototypeClass)
    {
        if (ATDynamicPrototypeClass->objectName().isEmpty())
            ATDynamicPrototypeClass->setObjectName(QStringLiteral("ATDynamicPrototypeClass"));
        ATDynamicPrototypeClass->resize(848, 663);
        centralWidget = new QWidget(ATDynamicPrototypeClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gvMain = new AMapView(centralWidget);
        gvMain->setObjectName(QStringLiteral("gvMain"));

        horizontalLayout->addWidget(gvMain);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        btn = new QPushButton(groupBox);
        btn->setObjectName(QStringLiteral("btn"));

        verticalLayout->addWidget(btn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(groupBox);

        ATDynamicPrototypeClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ATDynamicPrototypeClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 848, 21));
        ATDynamicPrototypeClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ATDynamicPrototypeClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ATDynamicPrototypeClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ATDynamicPrototypeClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ATDynamicPrototypeClass->setStatusBar(statusBar);

        retranslateUi(ATDynamicPrototypeClass);

        QMetaObject::connectSlotsByName(ATDynamicPrototypeClass);
    } // setupUi

    void retranslateUi(QMainWindow *ATDynamicPrototypeClass)
    {
        ATDynamicPrototypeClass->setWindowTitle(QApplication::translate("ATDynamicPrototypeClass", "ATDynamicPrototype", 0));
        groupBox->setTitle(QApplication::translate("ATDynamicPrototypeClass", "Actions", 0));
        pushButton->setText(QApplication::translate("ATDynamicPrototypeClass", "Generate accidents", 0));
        pushButton_2->setText(QApplication::translate("ATDynamicPrototypeClass", "Plan and Solve", 0));
        btn->setText(QApplication::translate("ATDynamicPrototypeClass", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class ATDynamicPrototypeClass: public Ui_ATDynamicPrototypeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATDYNAMICPROTOTYPE_H

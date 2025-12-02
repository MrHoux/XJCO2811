#include "detailwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QFrame>

extern QString translate(const QString& text);

DetailWindow::DetailWindow(QWidget *parent)
    : QWidget(parent)
{
    setupSimpleContent();
}

void DetailWindow::setupSimpleContent()
{
    if (layout()) {
        delete layout();
    }
}

void DetailWindow::setupContent(const QString& title)
{
    if (layout()) {
        QLayoutItem* child;
        while ((child = layout()->takeAt(0)) != nullptr) {
            if (child->widget()) {
                child->widget()->deleteLater();
            }
            delete child;
        }
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // nav
    QWidget *header = new QWidget();
    header->setStyleSheet("background-color: #f8f8f8;");
    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(15, 15, 15, 15);

    QPushButton *backBtn = new QPushButton("←");
    backBtn->setStyleSheet("QPushButton { border: none; font-size: 20px; color: #333; background: transparent; }");
    backBtn->setFixedSize(40, 40);

    QLabel *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #333;");

    headerLayout->addWidget(backBtn);
    headerLayout->addWidget(titleLabel);
    headerLayout->addStretch();

    mainLayout->addWidget(header);

    // back
    connect(backBtn, &QPushButton::clicked, this, &DetailWindow::backClicked);

    // content
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("QScrollArea { border: none; background: white; }");

    QWidget *content = new QWidget();
    QVBoxLayout *contentLayout = new QVBoxLayout(content);
    contentLayout->setContentsMargins(20, 20, 20, 20);

    QLabel *contentLabel = new QLabel(translate("This is the detailed view for: ") + title);
    contentLabel->setWordWrap(true);
    contentLabel->setStyleSheet("font-size: 16px; color: #666; line-height: 1.5;");
    contentLayout->addWidget(contentLabel);

    contentLayout->addStretch();

    scrollArea->setWidget(content);
    mainLayout->addWidget(scrollArea);
}

#ifndef DETAILWINDOW_H
#define DETAILWINDOW_H

#include <QWidget>

class DetailWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DetailWindow(QWidget *parent = nullptr);
    void setupContent(const QString& title);

signals:
    void backClicked();

private:
    void setupSimpleContent();
};

#endif

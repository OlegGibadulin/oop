#ifndef WIDGET_H
#define WIDGET_H

#include "../ui_widget.h"
#include "../actions/action.h"
#include "../facade/mediator.h"
#include "../exceptions/baseException.h"
#include "drawer.h"

#include <QWidget>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMessageBox>
#include <QFileDialog>

#include <iostream>
#include <memory>

namespace Ui
{
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    virtual void keyPressEvent(QKeyEvent*) override;
    void setUpCanvas();
    void updateCanvas();

private slots:
    void on_AddButton_clicked();
    void on_DeleteButton_clicked();
    void on_LoadButton_clicked();
    void on_CameraBox_currentIndexChanged(int index);

private:
    Ui::Widget *ui;

    static constexpr double offset = 10;
    static constexpr double scaleCoeff = 2;
    static constexpr double angle = 2 * M_PI / 180;

    QGraphicsScene* canvas;
    Mediator actionController;
};

#endif // WIDGET_H

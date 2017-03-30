#include "canvas.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QPushButton>

class MyWidget : public QWidget
{
public:
    MyWidget(QWidget *parent = 0);
};

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    this->resize(1000, 800);

    QPushButton *triangulate = new QPushButton(tr("Triangulate"));

    Canvas *canvas = new Canvas;

    connect(triangulate, SIGNAL(clicked()), canvas, SLOT(make_triangulate()));

    QFrame *ImageAreaBox = new QFrame;
    ImageAreaBox->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);

    QHBoxLayout *b_layout = new QHBoxLayout;
    b_layout->addWidget(triangulate);
    b_layout->addStretch(1);

    QVBoxLayout *canvas_layout = new QVBoxLayout;
    canvas_layout->addLayout(b_layout);
    canvas_layout->addWidget(canvas);
    ImageAreaBox->setLayout(canvas_layout);

    setLayout(canvas_layout);
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget mw;
    mw.show();

    return a.exec();
}

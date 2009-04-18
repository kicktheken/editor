#include "mainwindow.h"
//#include <QApplication>
//#include <QPushButton>



int main(int argc, char** argv)
{
    QApplication app(argc,argv);

    /*QGraphicsScene scene;
    for (int y=0; y<5; y++)
    {
        for (int x=0; x<5; x++)
        {
            QGraphicsProxyWidget *proxy = 
                new QGraphicsProxyWidget(0, Qt::Window);
            proxy->setWidget(new Editor);

            QRectF rect = proxy->boundingRect();
            proxy->setPos(x * rect.width() * 1.05, y * rect.height() * 1.05);
            proxy->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
            scene.addItem(proxy);
        }
    }*/
    MainWindow window;
    //window.resize(700,800);
    window.show();

    /*scene.setSceneRect(scene.itemsBoundingRect());

    QGraphicsView view(&scene);
    view.scale(0.5, 0.5);
    view.setRenderHints(view.renderHints() | QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    //view.setBackgroundBrush(QPixmap(":/No-Ones-Laughing-3.jpg"));
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.show();
    view.setWindowTitle("Embedded Dialogs Demo");
    //QPushButton pb("awoejif\n");
    //pb.show();
    */

    return app.exec();
}

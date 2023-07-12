#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QtDataVisualization>
#include <QRadioButton>
#include <QCheckBox>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QAction>
#include <QStyle>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include "plot.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Plot *plot;
    QtDataVisualization::Q3DSurface *myGraph;

    void toggleGrid(bool pressed);
    void handleGrid();

    void toggleLabel(bool pressed);
    void toggleBorderLabel(bool pressed);

    void setVirdisGradient();
    void setPlasmaGradient();

public slots:
    void doSave();
    void doRevert();

    void enableEnglish();
    void enableRussian();
    void enableArmenian();

private:
    QRadioButton *sincDistanceFromZeroRB, *sincSincMapModelRB, *modeNoneRB, *modeItemRB;
    QCheckBox *gridMode, *labelEnabled, *labelBorderEnabled;
    QSpinBox *xSteps, *zSteps;
    QPushButton *gradientBtoYPB, *gradientGtoRPB;
    QLinearGradient grBtoY, grGtoR;
    QSlider *axisMinSliderX, *axisMaxSliderX, *axisMinSliderZ, *axisMaxSliderZ;
    QVBoxLayout *vLayout;
    QGroupBox *modelGroupBox, *selectionGroupBox, *gridSelection, *labelSelection, *stepsSelection, *colorGroupBox;
    QLabel *col_range, *row_range;
    QMenu *menu, *langs;
    QSettings settings;
    QAction *actSave, *actRevert, *actRussian, *actEnglish,*actArmenian;
    QTranslator *translator;

    void swapTranslator(QString postfix);

    void widgetNamings();
};
#endif // MAINWINDOW_H

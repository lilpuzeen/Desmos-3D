#include "mainwindow.h"

using namespace QtDataVisualization;

MainWindow::MainWindow(QWidget *widget)
    : QMainWindow(widget)
{
    myGraph = new QtDataVisualization::Q3DSurface();
    myGraph->setAxisX(new QtDataVisualization::QValue3DAxis);
    myGraph->setAxisY(new QtDataVisualization::QValue3DAxis);
    myGraph->setAxisZ(new QtDataVisualization::QValue3DAxis);

    QWidget *container = QWidget::createWindowContainer(myGraph);
    QSize screenSize = myGraph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    this->statusBar()->show();

    // SAVING REGION
    actSave = new QAction(style()->standardIcon(QStyle::SP_DialogSaveButton), "", this);
    actSave->setShortcuts(QKeySequence::Save);
    actSave->setStatusTip("Save state");
    connect(actSave, &QAction::triggered, this, &MainWindow::doSave);


    actRevert = new QAction(style()->standardIcon(QStyle::SP_DialogResetButton), "", this);
    actRevert->setShortcuts(QKeySequence::Refresh);
    actRevert->setStatusTip("Revert state");
    connect(actRevert, &QAction::triggered, this, &MainWindow::doRevert);

    settings.setIniCodec("UTF-8");


    menu = menuBar()->addMenu("");
    langs = menuBar()->addMenu("");
    menu->addAction(actSave);
    menu->addAction(actRevert);

    QToolBar *t = addToolBar("Toolbar");
    t->addAction(actSave);
    t->addAction(actRevert);
    // END REGION

    // LANG REGION
    actRussian = new QAction("Русский", this);
    actEnglish = new QAction("English", this);
    actArmenian = new QAction("հայերեն", this);

    langs->addAction(actRussian);
    langs->addAction(actEnglish);
    langs->addAction(actArmenian);
    // END REGION


    // WIDGETS REGION
    QWidget *boxHLayout = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(boxHLayout);
    vLayout = new QVBoxLayout();
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);
    setCentralWidget(boxHLayout);
    vLayout->setAlignment(Qt::AlignTop);

    modelGroupBox = new QGroupBox("");

    sincDistanceFromZeroRB = new QRadioButton(widget);
    sincDistanceFromZeroRB->setText("Sinc(distance_from_zero)");

    sincSincMapModelRB = new QRadioButton(widget);
    sincSincMapModelRB->setText("Sinc(x) * Sinc(z)");
    sincSincMapModelRB->setChecked(false);

    QVBoxLayout *modelVBox = new QVBoxLayout;
    modelVBox->addWidget(sincDistanceFromZeroRB);
    modelVBox->addWidget(sincSincMapModelRB);
    modelGroupBox->setLayout(modelVBox);

    selectionGroupBox = new QGroupBox("");

    modeNoneRB = new QRadioButton(widget);
    modeNoneRB->setText("");
    modeNoneRB->setChecked(false);

    modeItemRB = new QRadioButton(widget);
    modeItemRB->setText("");
    modeItemRB->setChecked(true);

    QVBoxLayout *selectionVBox = new QVBoxLayout;
    selectionVBox->addWidget(modeNoneRB);
    selectionVBox->addWidget(modeItemRB);
    selectionGroupBox->setLayout(selectionVBox);

    gridSelection = new QGroupBox("");
    gridMode = new QCheckBox(widget);
    QVBoxLayout *gridSelectionVBox = new QVBoxLayout;
    gridSelectionVBox->addWidget(gridMode);
    gridSelection->setLayout(gridSelectionVBox);
    gridMode->setText("");

    labelSelection = new QGroupBox("");

    labelEnabled = new QCheckBox(widget);
    labelBorderEnabled = new QCheckBox(widget);

    labelEnabled->setText("");
    labelBorderEnabled->setText("");


    QVBoxLayout *labelSelectionVBox = new QVBoxLayout;
    labelSelectionVBox->addWidget(labelEnabled);
    labelSelectionVBox->addWidget(labelBorderEnabled);

    labelSelection->setLayout(labelSelectionVBox);

    stepsSelection = new QGroupBox("");
    QVBoxLayout *stepsVBox = new QVBoxLayout;

    xSteps = new QSpinBox(widget);
    zSteps = new QSpinBox(widget);

    xSteps->setRange(1, 100);
    xSteps->setSingleStep(1);
    xSteps->setValue(50);

    zSteps->setRange(1, 100);
    zSteps->setSingleStep(1);
    zSteps->setValue(50);

    stepsVBox->addWidget(xSteps);
    stepsVBox->addWidget(zSteps);

    stepsSelection->setLayout(stepsVBox);

    axisMinSliderX = new QSlider(Qt::Horizontal, widget);
    axisMinSliderX->setMinimum(0);
    axisMinSliderX->setTickInterval(1);
    axisMinSliderX->setEnabled(true);
    axisMaxSliderX = new QSlider(Qt::Horizontal, widget);
    axisMaxSliderX->setMinimum(1);
    axisMaxSliderX->setTickInterval(1);
    axisMaxSliderX->setEnabled(true);
    axisMinSliderZ = new QSlider(Qt::Horizontal, widget);
    axisMinSliderZ->setMinimum(0);
    axisMinSliderZ->setTickInterval(1);
    axisMinSliderZ->setEnabled(true);
    axisMaxSliderZ = new QSlider(Qt::Horizontal, widget);
    axisMaxSliderZ->setMinimum(1);
    axisMaxSliderZ->setTickInterval(1);
    axisMaxSliderZ->setEnabled(true);

    colorGroupBox = new QGroupBox(QStringLiteral("Gradients"));

    QLinearGradient grBtoY(0, 0, 1, 100);
    grBtoY.setColorAt(1.0, Qt::black);
    grBtoY.setColorAt(0.67, Qt::blue);
    grBtoY.setColorAt(0.33, Qt::red);
    grBtoY.setColorAt(0.0, Qt::yellow);
    QPixmap pm(24, 100);
    QPainter pmp(&pm);
    pmp.setBrush(QBrush(grBtoY));
    pmp.setPen(Qt::NoPen);
    pmp.drawRect(0, 0, 24, 100);
    gradientBtoYPB = new QPushButton(widget);
    gradientBtoYPB->setIcon(QIcon(pm));
    gradientBtoYPB->setIconSize(QSize(24, 100));

    QLinearGradient grGtoR(0, 0, 1, 100);
    grGtoR.setColorAt(1.0, Qt::darkGreen);
    grGtoR.setColorAt(0.5, Qt::yellow);
    grGtoR.setColorAt(0.2, Qt::red);
    grGtoR.setColorAt(0.0, Qt::darkRed);
    pmp.setBrush(QBrush(grGtoR));
    pmp.drawRect(0, 0, 24, 100);
    gradientGtoRPB = new QPushButton(widget);
    gradientGtoRPB->setIcon(QIcon(pm));
    gradientGtoRPB->setIconSize(QSize(24, 100));

    QHBoxLayout *colorHBox = new QHBoxLayout;
    colorHBox->addWidget(gradientBtoYPB);
    colorHBox->addWidget(gradientGtoRPB);
    colorGroupBox->setLayout(colorHBox);

    col_range = new QLabel();
    row_range = new QLabel();

    vLayout->addWidget(modelGroupBox);
    vLayout->addWidget(selectionGroupBox);
    vLayout->addWidget(gridSelection);
    vLayout->addWidget(labelSelection);
    vLayout->addWidget(stepsSelection);
    vLayout->addWidget(col_range);
    vLayout->addWidget(axisMinSliderX);
    vLayout->addWidget(axisMaxSliderX);
    vLayout->addWidget(row_range);
    vLayout->addWidget(axisMinSliderZ);
    vLayout->addWidget(axisMaxSliderZ);
    vLayout->addWidget(colorGroupBox);
    setLayout(vLayout);
    // END REGION

    plot = new Plot(myGraph);

    plot->setAxisMinSliderX(axisMinSliderX);
    plot->setAxisMaxSliderX(axisMaxSliderX);
    plot->setAxisMinSliderZ(axisMinSliderZ);
    plot->setAxisMaxSliderZ(axisMaxSliderZ);

    // CONNECT REGION
    QObject::connect(sincSincMapModelRB, &QRadioButton::toggled,
                     plot, &Plot::enableSincSincMapModel);
    QObject::connect(sincDistanceFromZeroRB, &QRadioButton::toggled,
                     plot, &Plot::enableSincDistanceFromZeroModel);

    QObject::connect(modeNoneRB, &QRadioButton::toggled,
                     plot, &Plot::toggleModeNone);
    QObject::connect(modeItemRB, &QRadioButton::toggled,
                     plot, &Plot::toggleModeItem);

    QObject::connect(gridMode, &QCheckBox::toggled,
                     this, &MainWindow::toggleGrid);

    QObject::connect(labelEnabled, &QCheckBox::toggled,
                     this, &MainWindow::toggleLabel);
    QObject::connect(labelBorderEnabled, &QCheckBox::toggled,
                     this, &MainWindow::toggleBorderLabel);

    QObject::connect(xSteps, QOverload< int >::of(&QSpinBox::valueChanged),
                     plot, &Plot::changeSampleCountX);
    QObject::connect(zSteps, QOverload< int >::of(&QSpinBox::valueChanged),
                     plot, &Plot::changeSampleCountZ);

    QObject::connect(axisMinSliderX, &QSlider::valueChanged,
                     plot, &Plot::adjustXMin);
    QObject::connect(axisMaxSliderX, &QSlider::valueChanged,
                     plot, &Plot::adjustXMax);
    QObject::connect(axisMinSliderZ, &QSlider::valueChanged,
                     plot, &Plot::adjustZMin);
    QObject::connect(axisMaxSliderZ, &QSlider::valueChanged,
                     plot, &Plot::adjustZMax);

    QObject::connect(gradientBtoYPB, &QPushButton::pressed,
                     this, &MainWindow::setVirdisGradient);
    QObject::connect(gradientGtoRPB, &QPushButton::pressed,
                     this, &MainWindow::setPlasmaGradient);

    QObject::connect(actRussian, &QAction::triggered,
                     this, &MainWindow::enableRussian);

    QObject::connect(actEnglish, &QAction::triggered,
                     this, &MainWindow::enableEnglish);

    QObject::connect(actArmenian, &QAction::triggered,
                     this, &MainWindow::enableArmenian);
    // END REGION

    doRevert();
    widgetNamings();
    sincDistanceFromZeroRB->setChecked(true);
}

MainWindow::~MainWindow() {}

void MainWindow::toggleGrid(bool pressed) {
    pressed ? myGraph->activeTheme()->setGridEnabled(false) : myGraph->activeTheme()->setGridEnabled(true);
}

void MainWindow::toggleLabel(bool pressed) {
    if (pressed)
    {
        myGraph->activeTheme()->setLabelTextColor(Qt::white);
        labelBorderEnabled->setChecked(true);
        labelBorderEnabled->setEnabled(false);
    }
    else
    {
        myGraph->activeTheme()->setLabelTextColor(Qt::black);
        labelBorderEnabled->setChecked(false);
        labelBorderEnabled->setEnabled(true);
    }
}

void MainWindow::toggleBorderLabel(bool pressed) {
    if (pressed)
    {
        myGraph->activeTheme()->setLabelBorderEnabled(false);
    }
    else
    {
        myGraph->activeTheme()->setLabelBorderEnabled(true);
    }
}

void MainWindow::setVirdisGradient()
{
    QLinearGradient gr;
    gr.setColorAt(0.0, QColor(68, 1, 84));
    gr.setColorAt(0.25, QColor(59, 82, 139));
    gr.setColorAt(0.5, QColor(33, 145, 140));
    gr.setColorAt(0.75, QColor(94, 201, 98));
    gr.setColorAt(1, QColor(253, 231, 37));

    myGraph->seriesList().at(0)->setBaseGradient(gr);
    myGraph->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
}

void MainWindow::setPlasmaGradient()
{
    QLinearGradient gr;
    gr.setColorAt(0.0, QColor(13, 8, 135));
    gr.setColorAt(0.25, QColor(126, 3, 168));
    gr.setColorAt(0.5, QColor(204, 71, 120));
    gr.setColorAt(0.75, QColor(248, 149, 64));
    gr.setColorAt(1, QColor(240, 249, 33));

    myGraph->seriesList().at(0)->setBaseGradient(gr);
    myGraph->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
}

void MainWindow::doSave()
{
    settings.setValue("gridMode", gridMode->isChecked());
    settings.setValue("labelEnabled", labelEnabled->isChecked());
    settings.setValue("labelBorderEnabled", labelBorderEnabled->isChecked());
    settings.setValue("sincDistanceFromZeroRB", sincDistanceFromZeroRB->isChecked());
    settings.setValue("sincSincMapModelRB", sincSincMapModelRB->isChecked());
    settings.setValue("modeNoneRB", modeNoneRB->isChecked());
    settings.setValue("modeItemRB", modeItemRB->isChecked());
    settings.setValue("xSteps", xSteps->value());
    settings.setValue("zSteps", zSteps->value());
    settings.setValue("axisMinSliderX", axisMinSliderX->value());
    settings.setValue("axisMaxSliderX", axisMaxSliderX->value());
    settings.setValue("axisMinSliderZ", axisMinSliderZ->value());
    settings.setValue("axisMaxSliderZ", axisMaxSliderZ->value());
//	settings.setValue("firstGr", gradientBtoYPB);
//	settings.setValue("secondGr", gradientGtoRPB);
}

void MainWindow::doRevert()
{
    if (settings.contains("gridMode"))
    {
        gridMode->setChecked(settings.value("gridMode").toBool());
    }
    if (settings.contains("labelEnabled"))
    {
        labelEnabled->setChecked(settings.value("labelEnabled").toBool());
    }
    if (settings.contains("labelBorderEnabled"))
    {
        labelBorderEnabled->setChecked(settings.value("labelBorderEnabled").toBool());
    }
    if (settings.contains("sincDistanceFromZeroRB"))
    {
        sincDistanceFromZeroRB->setChecked(settings.value("sincDistanceFromZeroRB").toBool());
    }
    if (settings.contains("sincSincMapModelRB"))
    {
        sincSincMapModelRB->setChecked(settings.value("sincSincMapModelRB").toBool());
    }
    if (settings.contains("modeNoneRB"))
    {
        modeNoneRB->setChecked(settings.value("modeNoneRB").toBool());
    }
    if (settings.contains("modeItemRB"))
    {
        modeItemRB->setChecked(settings.value("modeItemRB").toBool());
    }
    if (settings.contains("xSteps") && settings.value("xSteps").canConvert< int >())
    {
        xSteps->setValue(settings.value("xSteps").toInt());
    }
    if (settings.contains("zSteps") && settings.value("zSteps").canConvert< int >())
    {
        zSteps->setValue(settings.value("zSteps").toInt());
    }
    if (settings.contains("axisMinSliderX") && settings.value("axisMinSliderX").canConvert< int >())
    {
        axisMinSliderX->setValue(settings.value("axisMinSliderX").toInt());
    }
    if (settings.contains("axisMaxSliderX") && settings.value("axisMaxSliderX").canConvert< int >())
    {
        axisMaxSliderX->setValue(settings.value("axisMaxSliderX").toInt());
    }
    if (settings.contains("axisMinSliderZ") && settings.value("axisMinSliderZ").canConvert< int >())
    {
        axisMinSliderZ->setValue(settings.value("axisMinSliderZ").toInt());
    }
    if (settings.contains("axisMaxSliderZ") && settings.value("axisMaxSliderZ").canConvert< int >())
    {
        axisMaxSliderZ->setValue(settings.value("axisMaxSliderZ").toInt());
    }
}

void MainWindow::swapTranslator(QString suffix)
{
    QApplication::removeTranslator(translator);
    translator = new QTranslator(this);
    translator->load(":/i18n/lilpuzeen_geogebra_" + suffix);
    QApplication::installTranslator(translator);
    widgetNamings();
}

void MainWindow::widgetNamings()
{
    menu->setTitle(tr("Настройки"));
    langs->setTitle(tr("Языки"));

    actSave->setStatusTip(tr("Сохранить всё"));
    actRevert->setStatusTip(tr("Загрузить всё"));

    actRussian->setStatusTip(tr("Русский"));
    actEnglish->setStatusTip(tr("Английский"));
    actArmenian->setStatusTip(tr("Армянский"));

    gridSelection->setTitle(tr("Сетка"));
    gridMode->setText(tr("Скрыть сетку"));

    labelSelection->setTitle(tr("Координаты"));
    labelEnabled->setText(tr("Скрыть координаты"));
    labelBorderEnabled->setText(tr("Скрыть окантовку координат"));

    modelGroupBox->setTitle(tr("Графики функций"));

    selectionGroupBox->setTitle(tr("Отображение координат точки"));
    modeNoneRB->setText(tr("Выключить"));
    modeItemRB->setText(tr("Включить"));

    stepsSelection->setTitle(tr("Шаги"));

    col_range->setText(tr("Z диапазон"));
    row_range->setText(tr("X диапазон"));

    colorGroupBox->setTitle(tr("Градиенты"));
}

void MainWindow::enableEnglish()
{
    MainWindow::swapTranslator("en_GB");
}

void MainWindow::enableRussian()
{
    MainWindow::swapTranslator("ru_RU");
}

void MainWindow::enableArmenian()
{
    MainWindow::swapTranslator("hy_AM");
}

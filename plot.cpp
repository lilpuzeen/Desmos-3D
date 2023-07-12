#include "plot.h"

using namespace QtDataVisualization;

const float Plot::sampleMax = 10.0f;
const float Plot::sampleMin = -10.0f;
int Plot::sampleCountX = 50;
int Plot::sampleCountZ = 50;

Plot::Plot(Q3DSurface *surface) : m_graph(surface)
{
    sincDistanceFromZeroProxy = new QtDataVisualization::QSurfaceDataProxy();
    sincDistanceFromZeroSeries = new QtDataVisualization::QSurface3DSeries(sincDistanceFromZeroProxy);
    sincSincProxy = new QtDataVisualization::QSurfaceDataProxy();
    sincSincSeries = new QtDataVisualization::QSurface3DSeries(sincSincProxy);
    m_graph->axisX()->setTitle("X");
    m_graph->axisY()->setTitle("Y");
    m_graph->axisZ()->setTitle("Z");
    m_graph->axisX()->setTitleVisible(true);
    m_graph->axisY()->setTitleVisible(true);
    m_graph->axisZ()->setTitleVisible(true);
    fillSincDistanceFromZeroProxy();
    fillSincSincProxy();
}

Plot::~Plot()
{
    delete sincDistanceFromZeroProxy;
    delete sincDistanceFromZeroSeries;
    delete sincSincProxy;
    delete sincSincSeries;
}

void Plot::fillSincDistanceFromZeroProxy()
{
    float stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
    float stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);

    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(sampleCountZ);
    for (int i = 0 ; i < sampleCountZ ; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(sampleCountX);
        float z = qMin(sampleMax, (i * stepZ + sampleMin));
        int index = 0;
        for (int j = 0; j < sampleCountX; j++) {
            float x = qMin(sampleMax, (j * stepX + sampleMin));
            float R = qSqrt(z * z + x * x) + 0.01f;
            float y = (qSin(R) / R + 0.24f) * 1.61f;
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
        }
        *dataArray << newRow;
    }

    sincDistanceFromZeroProxy->resetArray(dataArray);
}

void Plot::fillSincSincProxy()
{
    float stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
    float stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);

    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(sampleCountZ);
    for (int i = 0; i < sampleCountZ; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(sampleCountX);
        float z = qMin(sampleMax, (i * stepZ + sampleMin));
        int index = 0;
        for (int j = 0; j < sampleCountX; j++) {
            float x = qMin(sampleMax, (j * stepX + sampleMin));
            float sincX = (x != 0.0f) ? (qSin(x) / x) : 1.0f;
            float sincZ = (z != 0.0f) ? (qSin(z) / z) : 1.0f;
            float y = sincX * sincZ;
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
        }
        *dataArray << newRow;
    }

    sincSincProxy->resetArray(dataArray);
}

void Plot::enableSincSincMapModel(bool enable)
{
    if (enable) {
        sincSincSeries->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
        sincSincSeries->setFlatShadingEnabled(true);

        m_graph->axisX()->setLabelFormat("%.2f");
        m_graph->axisZ()->setLabelFormat("%.2f");
        m_graph->axisX()->setRange(sampleMin, sampleMax);
        m_graph->axisY()->setRange(-0.5f, 2.0f);
        m_graph->axisZ()->setRange(sampleMin, sampleMax);
        m_graph->axisX()->setLabelAutoRotation(30);
        m_graph->axisY()->setLabelAutoRotation(90);
        m_graph->axisZ()->setLabelAutoRotation(30);

        m_graph->removeSeries(sincDistanceFromZeroSeries);
        m_graph->addSeries(sincSincSeries);

        m_rangeMinX = sampleMin;
        m_rangeMinZ = sampleMin;
        m_stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
        m_stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);
        axisMinSliderX->setMaximum(sampleCountX - 2);
        axisMinSliderX->setValue(0);
        axisMaxSliderX->setMaximum(sampleCountX - 1);
        axisMaxSliderX->setValue(sampleCountX - 1);
        axisMinSliderZ->setMaximum(sampleCountZ - 2);
        axisMinSliderZ->setValue(0);
        axisMaxSliderZ->setMaximum(sampleCountZ - 1);
        axisMaxSliderZ->setValue(sampleCountZ - 1);
    }
}

void Plot::enableSincDistanceFromZeroModel(bool enable)
{
    if (enable) {
        sincDistanceFromZeroSeries->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
        sincDistanceFromZeroSeries->setFlatShadingEnabled(true);

        m_graph->axisX()->setLabelFormat("%.2f");
        m_graph->axisZ()->setLabelFormat("%.2f");
        m_graph->axisX()->setRange(sampleMin, sampleMax);
        m_graph->axisY()->setRange(-0.5f, 2.0f);
        m_graph->axisZ()->setRange(sampleMin, sampleMax);
        m_graph->axisX()->setLabelAutoRotation(30);
        m_graph->axisY()->setLabelAutoRotation(90);
        m_graph->axisZ()->setLabelAutoRotation(30);

        m_graph->removeSeries(sincSincSeries);
        m_graph->addSeries(sincDistanceFromZeroSeries);

        m_rangeMinX = sampleMin;
        m_rangeMinZ = sampleMin;
        m_stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
        m_stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);
        axisMinSliderX->setMaximum(sampleCountX - 2);
        axisMinSliderX->setValue(0);
        axisMaxSliderX->setMaximum(sampleCountX - 1);
        axisMaxSliderX->setValue(sampleCountX - 1);
        axisMinSliderZ->setMaximum(sampleCountZ - 2);
        axisMinSliderZ->setValue(0);
        axisMaxSliderZ->setMaximum(sampleCountZ - 1);
        axisMaxSliderZ->setValue(sampleCountZ - 1);
        //! [8]
    }
}

void Plot::changeSampleCountX(int newStep)
{
    sampleCountX = newStep + 1;
    fillSincDistanceFromZeroProxy();
    fillSincSincProxy();
}
void Plot::changeSampleCountZ(int newStep)
{
    sampleCountZ = newStep + 1;
    fillSincDistanceFromZeroProxy();
    fillSincSincProxy();
}

void Plot::adjustXMin(int min)
{
    float minX = m_stepX * float(min) + m_rangeMinX;

    int max = axisMaxSliderX->value();
    if (min >= max) {
        max = min + 1;
        axisMaxSliderX->setValue(max);
    }
    float maxX = m_stepX * max + m_rangeMinX;

    setAxisXRange(minX, maxX);
}

void Plot::adjustXMax(int max)
{
    float maxX = m_stepX * float(max) + m_rangeMinX;

    int min = axisMinSliderX->value();
    if (max <= min) {
        min = max - 1;
        axisMinSliderX->setValue(min);
    }
    float minX = m_stepX * min + m_rangeMinX;

    setAxisXRange(minX, maxX);
}

void Plot::adjustZMin(int min)
{
    float minZ = m_stepZ * float(min) + m_rangeMinZ;

    int max = axisMaxSliderZ->value();
    if (min >= max) {
        max = min + 1;
        axisMaxSliderZ->setValue(max);
    }
    float maxZ = m_stepZ * max + m_rangeMinZ;

    setAxisZRange(minZ, maxZ);
}

void Plot::adjustZMax(int max)
{
    float maxX = m_stepZ * float(max) + m_rangeMinZ;

    int min = axisMinSliderZ->value();
    if (max <= min) {
        min = max - 1;
        axisMinSliderZ->setValue(min);
    }
    float minX = m_stepZ * min + m_rangeMinZ;

    setAxisZRange(minX, maxX);
}


void Plot::setAxisXRange(float min, float max)
{
    m_graph->axisX()->setRange(min, max);
}

void Plot::setAxisZRange(float min, float max)
{
    m_graph->axisZ()->setRange(min, max);
}

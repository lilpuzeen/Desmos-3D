#ifndef PLOT_H
#define PLOT_H

#include <QWidget>
#include <QtDataVisualization>
#include <QSlider>
#include <Q3DSurface>


class Plot : public QWidget
{
public:
  static int sampleCountX;
  static int sampleCountZ;
  static const float sampleMin;
  static const float sampleMax;

  Plot(QtDataVisualization::Q3DSurface *surface);
  ~Plot();

  QtDataVisualization::QSurfaceDataProxy *sincDistanceFromZeroProxy;
  QtDataVisualization::QSurfaceDataProxy *sincSincProxy;
  QtDataVisualization::QSurface3DSeries *sincDistanceFromZeroSeries;
  QtDataVisualization::QSurface3DSeries *sincSincSeries;
  void fillSincDistanceFromZeroProxy();
  void fillSincSincProxy();
  void enableSincSincMapModel(bool enable);
  void enableSincDistanceFromZeroModel(bool enable);

  void setAxisMinSliderX(QSlider *slider) { axisMinSliderX = slider; }
  void setAxisMaxSliderX(QSlider *slider) { axisMaxSliderX = slider; }
  void setAxisMinSliderZ(QSlider *slider) { axisMinSliderZ = slider; }
  void setAxisMaxSliderZ(QSlider *slider) { axisMaxSliderZ = slider; }

  void toggleModeNone() { m_graph->setSelectionMode(QtDataVisualization::QAbstract3DGraph::SelectionNone); }
  void toggleModeItem() { m_graph->setSelectionMode(QtDataVisualization::QAbstract3DGraph::SelectionItem); }

  void adjustXMin(int min);
  void adjustXMax(int max);
  void adjustZMin(int min);
  void adjustZMax(int max);

public slots:
  void changeSampleCountX(int newStep);
  void changeSampleCountZ(int newStep);

private:
  QtDataVisualization::Q3DSurface *m_graph;

  QSlider *axisMinSliderX, *axisMaxSliderX, *axisMinSliderZ, *axisMaxSliderZ;

  void setAxisXRange(float min, float max);
  void setAxisZRange(float min, float max);

  float m_rangeMinX;
  float m_rangeMinZ;
  float m_stepX;
  float m_stepZ;
};

#endif // PLOT_H

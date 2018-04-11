#pragma once

#include <memory>
#include <QtWidgets/QWidget>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QTabBar>
#include <QtCore/QPointer>
#include <QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QLabel>
#include <QMouseEvent>

#include "ui/docks/tabwidget.h"

namespace veles {
namespace ui {

enum DropArea
{
  Invalid = 0,
  Top = 1,
  Right = 2,
  Bottom = 4,
  Left = 8,
  Center = 16,

  AllAreas = Top | Right | Bottom | Left | Center,
  Sides = Right | Left,
  Sth = Top | Bottom,
  NotCenter = Sides | Sth
};

Q_DECLARE_FLAGS(DropAreas, DropArea)


class Dock : public QWidget {

  Q_OBJECT

 public:

  explicit Dock(QWidget *parent = nullptr);

  enum DockState {Empty = 0, Consistent = 1, Divided = 2};

  void addWidget(QWidget * widget, const QString& label, DropArea area);
  void addWidget(QWidget * widget, const QIcon& Icon, const QString& label, DropArea area);
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void showTabs();
  void showSplitter();
  void becomeParent(Dock * dock1, Dock * dock2, Qt::Orientation orientation);
  void replaceDock(Dock * replaced, Dock * replacee);
  Dock * parentDock();


 public slots:

  void childDockStateChange(DockState new_state, QPointer<Dock> child);
  void setState(DockState state);

 signals:
  void stateChanged(DockState new_state);

 private:
  DockState state;
  Qt::Orientation orientation;

  QStackedLayout * stacked_layout;
  QSplitter * splitter;
  TabWidget * tabWidget;
  QPointer<Dock> dock1, dock2;

  //dragginh
  QPoint drag_start;
  const QPoint detach_boundary = QPoint(50, 50);
  int dragged_tab_index = -1;

  void printSituation();
  void printSingle(int indent);
};

}
} //veles


/*
 *
 * Problem:
 *  - nie ma type safety na Dockach -> Docki czy mają 0,1,2 elementy są dalej tym samym typem. Ciężko się tym zarządza
 *
 *  Rozwiązanie: zrobić różne klasy do docków które mają jeden lub 0 elementów i dla już podzielonych docków.
 *
 *
 *
 */
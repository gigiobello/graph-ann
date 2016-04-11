#ifndef DOJO_H
#define DOJO_H

#include "net_builder_widget.h"
#include "net_trainer_widget.h"
#include "net_runner_widget.h"
#include "nets_list.h"
#include <QMainWindow>
#include <QMenuBar>
#include <QStackedWidget>
//#include "train_operations.h"

class dojo : public QMainWindow
{
	Q_OBJECT

private:
	QMenu * net_menu;
	QMenuBar * menu_bar;

	QStackedWidget * ctrl;
	netBuilderWidget * builder;
	netTrainerWidget * trainer;
	netRunnerWidget * runner;

	nets_list * nets_dock;

public slots:
	void netBuilder();
	void netTrainer();
	void netRunner(QString t);

	void addNet();

public:
	dojo();
	QSize minimumSizeHint() const Q_DECL_OVERRIDE;
	QSize sizeHint() const Q_DECL_OVERRIDE;
};

#endif

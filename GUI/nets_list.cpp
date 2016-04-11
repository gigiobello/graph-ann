#include "nets_list.h"
#include <QListWidgetItem>

nets_list::nets_list(QWidget * parent) : QDockWidget(parent)
{
	header = new QLabel(this);
	header->setText("Open...");
	setTitleBarWidget(header);

	fs = new QFileSystemModel(this);
	fs->setRootPath(QDir::currentPath());

	files = new QListView(this);
	files->setModel(fs);
	files->setRootIndex(fs->index("/Users/giorgiogiuffre/Documents/C++/oop-ann/nets/"));
	files->setGridSize({90, 30});
	connect(files, SIGNAL(clicked(QModelIndex)), this, SLOT(selectNet(QModelIndex)));
	connect(this, SIGNAL(netSelected(QString)), parent, SLOT(netRunner(QString)));

	setFeatures(QDockWidget::DockWidgetClosable);
	files->setMinimumWidth(90);
	files->setMaximumWidth(180);
	setWidget(files);
}

void nets_list::selectNet(const QModelIndex i)
{
	emit netSelected(fs->fileName(i));
}

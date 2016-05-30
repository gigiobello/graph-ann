#include "net_trainer_widget.h"
#include <QLabel>

netTrainerWidget::netTrainerWidget(const QString t, layeredBiasedNet * n, QWidget * parent) : QWidget(parent), title(t), net(n), n_epochs(new QSpinBox), layout(new QFormLayout)
{
	n_epochs->setMinimum(1);
	n_epochs->setMaximum(100000);

	layout->addRow(title, new QLabel);
	layout->addRow("File di allenamento:", new QLineEdit);
	layout->addRow("Numero di epoche:", n_epochs);

	setLayout(layout);
}

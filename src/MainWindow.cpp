#include "MainWindow.h"

#include <QFileDialog>

#include <QPainter>


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), m_Volume(0), m_VectorField(0)
{
	m_Ui = new Ui_MainWindow();
	m_Ui->setupUi(this);

	connect(m_Ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFileAction()));
	connect(m_Ui->actionClose, SIGNAL(triggered()), this, SLOT(closeAction()));

	
	connect(m_Ui->buttonLic, SIGNAL(clicked()), this, SLOT(licButtonClicked()));
	connect(m_Ui->buttonRedraw, SIGNAL(clicked()), this, SLOT(buttonRedrawClicked()));

	connect(m_Ui->radioEuler, SIGNAL(clicked()), this, SLOT(eulerRadioClicked()));
	connect(m_Ui->radioRunge, SIGNAL(clicked()), this, SLOT(eulerRungeClicked()));

	setCheckable(false);
}

MainWindow::~MainWindow()
{
	delete m_Volume;
	delete m_VectorField;
	delete m_MultiSet;
}


//-------------------------------------------------------------------------------------------------
// Slots
//-------------------------------------------------------------------------------------------------

void MainWindow::openFileAction()
{
	QString filename = QFileDialog::getOpenFileName(this, "Data File", 0, tr("Data Files (*.dat *.gri *.csv)"));

	redraw = true;

	if (!filename.isEmpty())
	{
		// store filename
		m_FileType.filename = filename;
		std::string fn = filename.toStdString();
		bool success = false;

		// progress bar and top label
		m_Ui->progressBar->setEnabled(true);
		m_Ui->labelTop->setText("Loading data ...");

		// load data according to file extension
		if (fn.substr(fn.find_last_of(".") + 1) == "dat")		// LOAD VOLUME
		{
			// create VOLUME
			m_FileType.type = VOLUME;
			m_Volume = new Volume();

			// load file
			success = m_Volume->loadFromFile(filename, m_Ui->progressBar);
		}
		else if (fn.substr(fn.find_last_of(".") + 1) == "gri")		// LOAD VECTORFIELD
		{
			// create VECTORFIELD
			m_FileType.type = VECTORFIELD;
			m_VectorField = new VectorField();

			// load file
			success = m_VectorField->loadFromFile(filename, m_Ui->progressBar);
		}
		else if (fn.substr(fn.find_last_of(".") + 1) == "csv")		// LOAD MULTIVARIATE DATA
		{
			// create MULTIVARIATE
			m_FileType.type = MULTIVARIATE;
			m_MultiSet = new MultiSet();

			// load file
			success = m_MultiSet->loadFromFile(filename, m_Ui->progressBar);
		}

		m_Ui->progressBar->setEnabled(false);

		// status message
		if (success)
		{
			QString type;
			if (m_FileType.type == VOLUME) type = "VOLUME";
			else if (m_FileType.type == VECTORFIELD) type = "VECTORFIELD";
			else if (m_FileType.type == MULTIVARIATE) type = "MULTIVARIATE";
			m_Ui->labelTop->setText("File LOADED [" + filename + "] - Type [" + type + "]");

			if (m_FileType.type == VECTORFIELD) {

				vectorField = m_VectorField;

				integrator = new EulerIntegrator(vectorField, new RandomSeedGenerator(vectorField->width(), vectorField->height(), 25), 1.0f / 1.0f, 1600);
				integrator->simulate();	

				m_Ui->drawLabel->setPixmap(integrator->paint());

				setCheckable(true);
			}
		}
		else
		{
			m_Ui->labelTop->setText("ERROR loading file " + filename + "!");
			m_Ui->progressBar->setValue(0);
		}
	}
}

void MainWindow::setCheckable(bool checkable) {

	m_Ui->groupIntegration->setEnabled(checkable);

	m_Ui->buttonLic->setEnabled(checkable);
	m_Ui->buttonRedraw->setEnabled(checkable);

	m_Ui->widget_2->repaint();
}


void MainWindow::eulerRadioClicked() {
	
	m_Ui->radioEuler->setChecked(true);
	m_Ui->radioRunge->setChecked(false);
}

void MainWindow::eulerRungeClicked() {
	m_Ui->radioEuler->setChecked(false);
	m_Ui->radioRunge->setChecked(true);
}

void MainWindow::buttonRedrawClicked() {
	std::cout << "Button Redraw Clicked" << std::endl;

	setCheckable(false);	

	if (m_Ui->radioEuler->isChecked()) {
		if (!m_Ui->checkEven->isChecked()){
			integrator = new EulerIntegrator(vectorField, new RandomSeedGenerator(vectorField->width(), vectorField->height(), 25), 1.0f / m_Ui->textDelta->toPlainText().toFloat(), m_Ui->textSteps->toPlainText().toInt());
		}
	}
	else {
		if (!m_Ui->checkEven->isChecked()){
			integrator = new RungeKuttaIntegrator(vectorField, new RandomSeedGenerator(vectorField->width(), vectorField->height(), 25), 1.0f / m_Ui->textDelta->toPlainText().toFloat(), m_Ui->textSteps->toPlainText().toInt());
		}
	}

	integrator->simulate();

	m_Ui->drawLabel->setPixmap(integrator->paint());

	setCheckable(true);
}


void MainWindow::licButtonClicked() {
	std::cout << "Button Clicked" << std::endl;
}


void MainWindow::closeAction()
{
	close();
}

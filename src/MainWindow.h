
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include "ui_MainWindow.h"
#include "Volume.h"
#include "VectorField.h"
#include "MultiSet.h"
#include "Window.h"
#include "RandomSeedGenerator.h"
#include "EulerIntegrator.h"
#include "EvenSpacedSeedGenerator.h"
#include "VectorField.h"
#include "Integrator.h"
#include "Widget.h"


#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QStatusBar>
#include <QVariant>


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:

	MainWindow(QWidget *parent = 0);
	~MainWindow();
	
	protected slots :

	void								openFileAction();
	void								closeAction();
	void								licButtonClicked();
	void								eulerRadioClicked();
	void								eulerRungeClicked();
	void								buttonRedrawClicked();
	void								radioRandomClicked();
	void								radioEvenClicked();
	void								radioColourOneClicked();
	void								radioColourTwoClicked();


private:

	Integrator* integrator;
	VectorField* vectorField;
	QPixmap currentPix;
	bool redraw;

	void setCheckable(bool checkable);

	// USER INTERFACE ELEMENTS

	Ui_MainWindow						*m_Ui;


	// DATA 

	enum DataType
	{
		VOLUME = 0,
		VECTORFIELD = 1,
		MULTIVARIATE = 2
	};

	struct FileType
	{
		QString			filename;
		DataType		type;
	}									 m_FileType;

	Volume								*m_Volume;						// for Volume-Rendering
	VectorField							*m_VectorField;					// for Flow-Visualisation
	MultiSet							*m_MultiSet;					// for Multivariate Data

	Window* currentWindow;
};

#endif

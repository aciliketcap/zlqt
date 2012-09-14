/*
 * options.cpp
 * Copyright 2012 Sinan Akpolat
 *
 * This file is a part of zlqt, which is distributed under GNU GPLv3, see LICENSE file.
 * If you haven't received a file named LICENSE with zlqt, see <http://www.gnu.org/licenses/>.
 *
 * zlqt is distributed WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * zlqt is a work using Qt Library distributed under GNU LGPLv2.1. You can download it from <http://qt.nokia.com/downloads>
 */

#include <QWidget>
#include <QString>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include "options.h"

//radio button group used for fullscreen / windowed option
toggleOptWidget::toggleOptWidget(QWidget *parent, const QString opt1Label, const QString opt2Label) : QWidget(parent) {
	this->optG = new QButtonGroup;
	this->opt1 = new QRadioButton(opt1Label);
	this->opt2 = new QRadioButton(opt2Label);
	opt2->setChecked(true);	//choose "off" option button by default but don't set off any signals
	opt1->setCheckable(true);
	optG->addButton(opt1);	//option on
	optG->addButton(opt2);	//option off
	optG->setId(opt1, 2);	//so that signal results will be same as checkbox signals
	optG->setId(opt2, 0);	//so that signal results will be same as checkbox signals

	this->widgetLayout = new QHBoxLayout;
	widgetLayout->addWidget(opt1);
	widgetLayout->addWidget(opt2);
	setLayout(widgetLayout);

}

//lineedit with a checkbox in front of it. Used in all options that contain text
nameOptWidget::nameOptWidget (QWidget *parent, const QString label, const QString defaultText) : QWidget(parent) {
	this->nameOptCB = new QCheckBox(label, this);
	this->nameOptT = new QLineEdit(defaultText, this);
	this->value = new QString(defaultText);
	this->state = this->nameOptCB->checkState();

	connect(this->nameOptCB, SIGNAL(stateChanged(int)), this, SLOT(setState(int)));
	connect(this->nameOptT, SIGNAL(textChanged(QString)), this, SLOT(setValue(QString)));

	this->widgetLayout = new QHBoxLayout;
	widgetLayout->addWidget(nameOptCB);
	widgetLayout->addWidget(nameOptT);
	setLayout(widgetLayout);

}
void nameOptWidget::setState(int state) {
	if(state != this->state) {
		this->state = state;
		emit stateChanged(this->state, this->value);
	}
}
void nameOptWidget::setValue(const QString &value) {
	this->value->clear();
	this->value->append(value);
	emit stateChanged(this->state,this->value);
}

//two lineedits taking 4 digit integers. Used in resolution option
resOptWidget::resOptWidget(QWidget *parent, const QString label, const int width, const int height) : QWidget(parent){
	this->resOptCB = new QCheckBox(label, this);
	QString widthStr;
	QString heightStr;
	this->resOptWidthT = new QLineEdit(widthStr.setNum(width), this);
	this->resOptHeightT = new QLineEdit(heightStr.setNum(height), this);
	this->resOptWidthT->setInputMask("9999"); //only accept 4 digit numbers
	this->resOptWidthT->setMaximumSize(resOptWidthT->size().width()/2, resOptWidthT->size().height()); //can't be larger than half the normal size
	this->resOptHeightT->setInputMask("9999"); //only accept 4 digit numbers
	this->resOptHeightT->setMaximumSize(resOptHeightT->size().width()/2, resOptHeightT->size().height()); //can't be larger than half the normal size
	this->width = width;
	this->height = height;
	this->resOptSeperator = new QLabel("x", this);

	connect(this->resOptCB, SIGNAL(stateChanged(int)), this, SLOT(setState(int)));
	connect(this->resOptWidthT, SIGNAL(textChanged(QString)), this, SLOT(setWidth(QString)));
	connect(this->resOptHeightT, SIGNAL(textChanged(QString)), this, SLOT(setHeight(QString)));

	this->widgetLayout = new QHBoxLayout;
	widgetLayout->addWidget(resOptCB);
	widgetLayout->addWidget(resOptWidthT);
	widgetLayout->addWidget(resOptSeperator);
	widgetLayout->addWidget(resOptHeightT);
	setLayout(widgetLayout);

}

void resOptWidget::setState(int state) {
	if(state != this->state) {
		this->state = state;
		emit stateChanged(this->state, this->width, this->height);
	}
}

void resOptWidget::setWidth(const QString &width) {
	int iWidth = width.toInt();
	if(iWidth != this->width) {
		this->width = iWidth;
		emit stateChanged(this->state, this->width, this->height);
	}
}

void resOptWidget::setHeight(const QString &height) {
	int iHeight = height.toInt();
	if(iHeight != this->height) {
		this->height = iHeight;
		emit stateChanged(this->state, this->width, this->height);
	}
}

//Combobox with a checkbox in front of it. Used only for team selection options
teamOptWidget::teamOptWidget (QWidget *parent, const QString label) : QWidget(parent) {
	this->teamOptCB = new QCheckBox(label, this);
	this->teamOptC = new QComboBox(this);
	this->teamOptC->addItem("Red");
	this->teamOptC->addItem("Blue");
	this->teamOptC->addItem("Green");
	this->teamOptC->addItem("Yellow");
	this->teamOptC->addItem("Purple");
	this->teamOptC->addItem("Teal");
	this->teamOptC->addItem("White");
	this->teamOptC->addItem("Black");

	this->state = teamOptCB->checkState();
	this->value = new QString;
	this->value->clear();
	this->value->append(teamOptC->currentText().toLower());

	connect(this->teamOptCB, SIGNAL(stateChanged(int)), this, SLOT(setState(int)));
	connect(this->teamOptC, SIGNAL(currentIndexChanged(int)), this, SLOT(setValue(int)));


	this->widgetLayout = new QHBoxLayout;
	widgetLayout->addWidget(teamOptCB);
	widgetLayout->addWidget(teamOptC);
	setLayout(widgetLayout);

}

void teamOptWidget::setState(int state) {
	if(state != this->state) {
	this->state = state;
	emit stateChanged(this->state, this->value);
	}
}
void teamOptWidget::setValue(int value) {
	if(value >= 0 || value <= 4) {
		this->value->clear();
		this->value->append(teamOptC->currentText().toLower());
		emit stateChanged(this->state,this->value);
	}
}

//filename widget inherited from nameOpt class. Adds a button which opens a QFileDialog to get filenames/paths into line edit.
fileNameWidget::fileNameWidget(QWidget *parent, const QString label, const QString defaultText, const QString fileSuffix, const QString selectedFile) : nameOptWidget(parent, label, defaultText) {
	this->fileSuffix = QString(fileSuffix);
	this->selectedFile = QString(selectedFile);
	this->fileNameWidgetBrowseB = new QPushButton(QString(tr("Browse")), this);

	connect(this->fileNameWidgetBrowseB, SIGNAL(clicked()), this, SLOT(chooseFile()));

	widgetLayout->addWidget(this->fileNameWidgetBrowseB);
}

void fileNameWidget::chooseFile() {
	QFileDialog *filename = new QFileDialog(this);
	filename->setAcceptMode(QFileDialog::AcceptOpen);
	filename->setFileMode(QFileDialog::ExistingFile);
	if(!this->fileSuffix.isEmpty()) {
		const QString tempString1=this->fileSuffix; //like casting const
		filename->setDefaultSuffix(tempString1); //needs const
	}
	if(!this->selectedFile.isEmpty()) {
		const QString tempString2=this->selectedFile;
		filename->selectFile(tempString2); //needs const
	}
	this->value->clear();
	this->value->append(filename->getOpenFileName()); //we can put filters to the returning string...
	const QString tempString3 = *(this->value);
	this->nameOptT->setText(tempString3);	//needs const
	emit stateChanged(this->state,this->value);
}

serverOptionsGroup::serverOptionsGroup(QWidget *parent) : QGroupBox(parent) {
	const QString dedicatedLabel = QString(tr("Dedicated Server"));
	this->dedicatedCB = new QCheckBox(dedicatedLabel, this);
	const QString trayLabel = QString(tr("Tray Icon"));
	this->trayCB = new QCheckBox(trayLabel, this);

	this->serverOptionsL = new QHBoxLayout;
	serverOptionsL->addWidget(dedicatedCB);
	serverOptionsL->addWidget(trayCB);
	setLayout(this->serverOptionsL);
}

fileOptionsGroup::fileOptionsGroup(QWidget *parent) : QGroupBox(parent) {
	this->mapNameW = new fileNameWidget(this, QString(tr("Map Name:")), "\0", "map");
	this->mapListW = new fileNameWidget(this, QString(tr("Map List File:")), "map_list.txt", "txt", "map_list.txt");
	this->settingFileW = new fileNameWidget(this, QString(tr("Settings File:")), "default_settings.txt", "txt", "default_settings.txt");
	this->settingFileW2 = new fileNameWidget(this, QString(tr("Main Server Settings:")), "default_settings.txt", "txt", "default_settings.txt");

	this->fileOptionsGroupL = new QVBoxLayout;
	fileOptionsGroupL->addWidget(mapNameW);
	fileOptionsGroupL->addWidget(mapListW);
	fileOptionsGroupL->addWidget(settingFileW);
	fileOptionsGroupL->addWidget(settingFileW2);
	setLayout(this->fileOptionsGroupL);
}

loginOptionsGroup::loginOptionsGroup(QWidget *parent) : QGroupBox(parent) {
	this->serverNameW = new nameOptWidget(this, QString(tr("Server Address:")), QString("localhost"));
	this->loginNameW = new nameOptWidget(this, QString(tr("Login Name:")), "");
	this->loginPassW = new nameOptWidget(this, QString(tr("Login Password:")), "");
	this->loginOptionsGroupL = new QVBoxLayout;
	loginOptionsGroupL->addWidget(serverNameW);
	loginOptionsGroupL->addWidget(loginNameW);
	loginOptionsGroupL->addWidget(loginPassW);
	setLayout(this->loginOptionsGroupL);
}

playerOptionsGroup::playerOptionsGroup(QWidget *parent) : QGroupBox(parent) {
	this->windowedW = new toggleOptWidget(this, "Windowed", "Fullscreen");	//fullscreen radio box
	this->resolutionW = new resOptWidget(this, "Window Resolution:");	//resolution lineedits
	this->playerTeamW = new teamOptWidget(this, QString(tr("Player Team:")));
	this->botTeamW = new teamOptWidget(this, QString(tr("Bot Team:")));
	this->playerNameW = new nameOptWidget(this, QString(tr("Player Name:")), "");
	this->noSoundCB = new QCheckBox("No Sound", this);
	this->noMusicCB = new QCheckBox("No Music", this);
	this->noOpenGLCB = new QCheckBox("No OpenGL", this);
	this->betterCursorCB = new QCheckBox("Better Cursor", this);

	this->playerOptionsGroupL = new QGridLayout;
	playerOptionsGroupL->addWidget(windowedW, 1, 1, 1, 2);
	playerOptionsGroupL->addWidget(resolutionW, 2, 1, 1, 2);
	playerOptionsGroupL->addWidget(playerTeamW, 3, 1, 1, 2);
	playerOptionsGroupL->addWidget(botTeamW, 4, 1, 1, 2);
	playerOptionsGroupL->addWidget(playerNameW, 5, 1, 1, 2);
	playerOptionsGroupL->addWidget(noSoundCB, 6, 1);
	playerOptionsGroupL->addWidget(noMusicCB, 6, 2);
	playerOptionsGroupL->addWidget(noOpenGLCB, 7, 1);
	playerOptionsGroupL->addWidget(betterCursorCB, 7, 2);
	setLayout(playerOptionsGroupL);
}

optionsWidget::optionsWidget (QWidget *parent) : QWidget(parent) {
	this->serverOptionsG = new serverOptionsGroup;
	this->fileOptionsG = new fileOptionsGroup;
	this->loginOptionsG = new loginOptionsGroup;
	this->playerOptionsG = new playerOptionsGroup;

	this->optionsL = new QGridLayout;
	optionsL->addWidget(serverOptionsG, 1, 1);
	optionsL->addWidget(fileOptionsG, 2, 1);
	optionsL->addWidget(loginOptionsG, 3, 1);
	optionsL->addWidget(playerOptionsG, 1, 2, 3, 1, 0); //start from row-1, column-2 and take 3 consequent rows and 1 column, 0 is default alignment
	setLayout(this->optionsL);
}

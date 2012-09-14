/*
 * maingui.cpp
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

#include "maingui.h"
#include "cmdline.h"
#include "options.h"
#include <QWidget>
#include <QApplication> //for qApp pointer
#include <QVBoxLayout>
#include <QPushButton>
#include <QProcess>
#include <QMainWindow> //for help menu
#include <QMenuBar> //for help menu
#include <QMenu> //for help menu
#include <QAction> //for help menu
#include <QMessageBox> //for about window text
#include <QString> //for about window text

extern QProcess *zod;

mainwin::mainwin() {
	this->mainguiW = new maingui(this);
	setCentralWidget(mainguiW); //qt docs say QMainWindow takes this pointer as centralWidget and deletes mainguiW

	QMenuBar *menubar = this->menuBar(); //create a new menu bar for this window
	QAction *aboutA = new QAction(tr("About"), this);
	menubar->addAction(aboutA); //a help menu can be added using menubar->addMenu()
	connect(aboutA, SIGNAL(triggered()), this, SLOT(showAbout()));
}

void mainwin::showAbout() {
	const QString aboutText = "\
zlqt is distributed under GNU GPLv3, see LICENSE file. \
If you haven't received a file named LICENSE with zlqt, see <http://www.gnu.org/licenses/>.\n\n\
zlqt is distributed WITHOUT ANY WARRANTY; \
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n\n\
zlqt is a work using Qt Library distributed under GNU LGPLv2.1. You can download it from <http://qt.nokia.com/downloads>.\
";
	QMessageBox *aboutMsg = new QMessageBox(this);
	aboutMsg->setText(aboutText);
	aboutMsg->setWindowTitle("About");
	aboutMsg->exec();
	return;
}

maingui::maingui(QWidget *parent) : QWidget(parent)
{
	this->cmdlineW = new cmdlineWidget(this);
	this->optionsW = new optionsWidget(this);
	this->quitB = new QPushButton("Quit!", this);
	this->runB = new QPushButton("Run", this);
	this->scriptB = new QPushButton("Save as Script", this);

	connect(quitB, SIGNAL(clicked()), qApp, SLOT(quit()));
	connect(runB, SIGNAL(clicked()), this, SLOT(runCmdline()));
	connect(scriptB, SIGNAL(clicked()), cmdlineW, SLOT(saveScript()));

	//All the signals in the menu, from top to down (and left to right I guess)
	//Server Options Group
	connect(this->optionsW->serverOptionsG->dedicatedCB, SIGNAL(stateChanged(int)), this->cmdlineW, SLOT(dedicatedCBChanged(int)));
	connect(this->optionsW->serverOptionsG->trayCB, SIGNAL(stateChanged(int)), this->cmdlineW, SLOT(trayCBChanged(int)));
	//File Options Group
	connect(this->optionsW->fileOptionsG->mapNameW, SIGNAL(stateChanged(int, QString*)), this->cmdlineW, SLOT(mapNameWChanged(int, QString*)));
	connect(this->optionsW->fileOptionsG->mapListW, SIGNAL(stateChanged(int, QString*)), this->cmdlineW, SLOT(mapListWChanged(int, QString*)));
	connect(this->optionsW->fileOptionsG->settingFileW, SIGNAL(stateChanged(int, QString*)), this->cmdlineW, SLOT(settingFileWChanged(int, QString*)));
	connect(this->optionsW->fileOptionsG->settingFileW2, SIGNAL(stateChanged(int, QString*)), this->cmdlineW, SLOT(settingFileW2Changed(int, QString*)));
	//Login Options Group
	connect(this->optionsW->loginOptionsG->serverNameW, SIGNAL(stateChanged(int, QString*)), this->cmdlineW, SLOT(serverNameWChanged(int, QString*)));
	connect(this->optionsW->loginOptionsG->loginNameW, SIGNAL(stateChanged(int, QString*)), this->cmdlineW, SLOT(loginNameWChanged(int, QString*)));
	connect(this->optionsW->loginOptionsG->loginPassW, SIGNAL(stateChanged(int, QString*)), this->cmdlineW, SLOT(loginPassWChanged(int, QString*)));
	//Player Options Group
	connect(this->optionsW->playerOptionsG->windowedW->optG, SIGNAL(buttonClicked(int)), this->cmdlineW, SLOT(windowedWChanged(int)));
	connect(this->optionsW->playerOptionsG->resolutionW, SIGNAL(stateChanged(int, int, int)), this->cmdlineW, SLOT(resolutionWChanged(int, int, int)));
	connect(this->optionsW->playerOptionsG->playerTeamW, SIGNAL(stateChanged(int, QString*)), this->cmdlineW, SLOT(playerTeamWChanged(int, QString*)));
	connect(this->optionsW->playerOptionsG->botTeamW, SIGNAL(stateChanged(int, QString*)), this->cmdlineW, SLOT(botTeamWChanged(int, QString*)));
	connect(this->optionsW->playerOptionsG->playerNameW, SIGNAL(stateChanged(int, QString*)), this->cmdlineW, SLOT(playerNameWChanged(int, QString*)));
	connect(this->optionsW->playerOptionsG->noSoundCB, SIGNAL(stateChanged(int)), this->cmdlineW, SLOT(noSoundCBChanged(int)));
	connect(this->optionsW->playerOptionsG->noMusicCB, SIGNAL(stateChanged(int)), this->cmdlineW, SLOT(noMusicCBChanged(int)));
	connect(this->optionsW->playerOptionsG->noOpenGLCB, SIGNAL(stateChanged(int)), this->cmdlineW, SLOT(noOpenGLCBChanged(int)));
	connect(this->optionsW->playerOptionsG->betterCursorCB, SIGNAL(stateChanged(int)), this->cmdlineW, SLOT(betterCursorCBChanged(int)));

	QGridLayout *lowerPartL = new QGridLayout;
	lowerPartL->addWidget(cmdlineW,1,1,3,1,0); //make it 3 rows long
	lowerPartL->addWidget(scriptB,1,2);
	lowerPartL->addWidget(runB,2,2);
	lowerPartL->addWidget(quitB,3,2);

	QVBoxLayout *mainguiL = new QVBoxLayout;
	mainguiL->addWidget(optionsW);
	mainguiL->addLayout(lowerPartL);
	setLayout(mainguiL);

}

void maingui::runCmdline() {
	this->runB->setEnabled(false); //disable run button to avoid trying to run two processes, we have only one QProcess object.
	emit needConsole();	//just show the console (use this->show(); in consoleoutW object)
	QStringList cmdline = this->cmdlineW->toPlainText().split(" "); //arguments for the process
	QString cmd = cmdline.first();
	//emit writeConsole(&cmd);	//print the command to start game, for debug purpose only
	cmdline.removeFirst();
	/*//print the arguments one by one, for debug purpose only
	QStringList::const_iterator i;
	for(i=cmdline.constBegin();i!=cmdline.constEnd();++i) {
		QString p = *i;
		emit writeConsole(&p);	//I couldn't find another way to convert from iterator to pointer :/
	}*/
	zod->start(cmd, cmdline);	//start the game using command in "cmd" and arguments in "cmdline"
	return;
}

void maingui::processFinished(int meh) {
	//I couldn't get rid of the int arg of function eventhough I don't need it
	this->runB->setEnabled(true);
}



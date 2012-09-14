/*
 * main.cpp
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

#include <QApplication>
#include <QObject> //for QObject::connect function
#include <QProcess> //for game process pointer
#include "maingui.h"
#include "consoleout.h"

QProcess *zod = 0; //initialization of extern game process pointer
//You can only launch one game process from a launcher process.

int main (int argc, char* argv[]) {
	QApplication zlaunchApp(argc, argv);
	mainwin *mainwindow = new mainwin;
	consoleout *consoleoutW = new consoleout;
	//In fact writing a SLOT for zlaunchApp class which creates consoleoutW dynamically can be good
	//We can create as many console output windows as we wish. currently there is only one window used everytime process is run.
	zod = new QProcess; //we already initialized pointer to game process globally, so we don't need to set a type
	zod->setProcessChannelMode(QProcess::SeparateChannels); //whether to use seperate channels for stdout and stderr
	QObject::connect(mainwindow->centralWidget(), SIGNAL(needConsole()), consoleoutW, SLOT(showConsole()));
	QObject::connect(mainwindow->centralWidget(), SIGNAL(writeConsole(QString *)), consoleoutW, SLOT(printout(QString *)));

	QObject::connect(zod, SIGNAL(readyReadStandardOutput()), consoleoutW, SLOT(printoutProc()));
	QObject::connect(zod, SIGNAL(readyReadStandardError()), consoleoutW, SLOT(printerrorProc()));
	QObject::connect(zod, SIGNAL(started()), consoleoutW, SLOT(printstartProc()));
	QObject::connect(zod, SIGNAL(finished(int)), mainwindow->centralWidget(), SLOT(processFinished(int))); //Re-enable run button on process exit signal.
	QObject::connect(zod, SIGNAL(finished(int)), consoleoutW, SLOT(printexitProc(int)));

	mainwindow->show();
	return zlaunchApp.exec();
}

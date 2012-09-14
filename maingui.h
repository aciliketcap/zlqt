/*
 * maingui.h
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


#ifndef MAINGUI_H_
#define MAINGUI_H_

#include <QWidget>
#include <QMainWindow>
#include "options.h"
#include "cmdline.h"

class QPushButton;
class QMenuBar;
class QMenu;

class maingui : public QWidget {
	Q_OBJECT
public:
	maingui(QWidget *parent = 0);
	cmdlineWidget *cmdlineW;
	optionsWidget *optionsW;
	QPushButton *quitB;
	QPushButton *runB;
	QPushButton *scriptB; //save as script

public slots:
	void runCmdline();
	void processFinished(int meh);
signals:
	void needConsole();
	void writeConsole(QString *line);
};

class mainwin : public QMainWindow {
	Q_OBJECT
public:
	mainwin();
	QMenuBar *menubar;
	QAction *aboutA;
	maingui *mainguiW;
public slots:
	void showAbout();
};

#endif /* MAINGUI_H_ */

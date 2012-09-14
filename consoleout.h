/*
 * consoleout.h
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

#ifndef CONSOLEOUT_H_
#define CONSOLEOUT_H_

#include <QWidget>

class QTextEdit;
class QPushButton;
class QGridLayout;

class consoleout : public QWidget {
	Q_OBJECT
public:
	consoleout(QWidget *parent = 0);
	QTextEdit *consoleT;
	QPushButton *copyB;	//copy to clipboard
	QPushButton *saveB; //save output
	QPushButton *closeB; //close window
	QGridLayout *consoleL;
public slots:
	void showConsole();
	void printout(QString *out); 	//print out one line
	void printoutProc();
	void printerrorProc();
	void printstartProc();
	void printexitProc(int exitcode);
	void copyToClipboard();	//take the whole output into clipboard when copy button is pressed
	void saveToFile();
};

#endif /* CONSOLEOUT_H_ */

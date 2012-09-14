/*
 * consoleout.cpp
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

#include "consoleout.h"
#include <QTextEdit>
#include <QProcess>		//to be able to get I/O from game process
#include <QApplication> //for qApp pointer for clipboard access
#include <QClipboard>
#include <QPushButton>
#include <QGridLayout>
#include <QDateTime>	//for saving output
#include <QFile>		//for saving output
#include <QTextStream>	//for saving output
#include <stdio.h> //for itoa and outputting a few messages

extern QProcess *zod;

consoleout::consoleout(QWidget *parent) : QWidget(parent) {
	this->consoleT = new QTextEdit(this);

	this->copyB = new QPushButton("Copy");
	this->saveB = new QPushButton("Save");
	this->closeB = new QPushButton("Close");

	this->connect(copyB, SIGNAL(clicked()), this, SLOT(copyToClipboard()));
	this->connect(saveB, SIGNAL(clicked()), this, SLOT(saveToFile()));
	this->connect(closeB, SIGNAL(clicked()), this, SLOT(hide()));

	this->consoleL = new QGridLayout;
	this->consoleL->addWidget(this->consoleT,0,0,4,12);
	this->consoleL->addWidget(this->copyB,5,0);
	this->consoleL->addWidget(this->saveB,5,1);
	this->consoleL->addWidget(this->closeB,5,2);

	setLayout(consoleL);
}

void consoleout::showConsole() {
	this->show();
}

void consoleout::printout(QString *out) {
	QString tempstr = this->consoleT->toPlainText();
	tempstr.append(out);
	tempstr.append("\n");
	this->consoleT->setPlainText(tempstr);
}

//old printoutProc SLOT
/*void consoleout::printoutProc() {
	char newoutput[1024];
	int i=0;
	for(i=0;i<1024;i++) newoutput[i]='\0';
	zod->setReadChannel(QProcess::StandardOutput);
	zod->read(newoutput, 1023);
	QString text = this->consoleT->toPlainText();
	printf("reading output\n");
	printf("%s\n",newoutput);
	text.append(newoutput);
	this->consoleT->setPlainText(text);
}*/

void consoleout::printoutProc() {
	char newoutput[1024];
	int i=0;
	zod->setReadChannel(QProcess::StandardOutput);
	QString *text = new QString(this->consoleT->toPlainText());
	printf("reading output\n");
	while(zod->bytesAvailable()>0) {
		for(i=0;i<1024;i++) newoutput[i]='\0';
		zod->readLine(newoutput, 1023);
		text->append(newoutput);
		printf("%s",newoutput);
	}
	this->consoleT->setPlainText(*text);
}
//problem: doesn't print incoming output right away, waits for proc to exit :(
//It would be better if we read char by char instead of line by line, what if we encounter lines longer than 1023 bytes?

void consoleout::printerrorProc() {
	char newoutput[50];
	int i=0;
	for(i=0;i<50;i++) newoutput[i]='\0';
	zod->setReadChannel(QProcess::StandardError);
	zod->read(newoutput, 50);
	QString text = this->consoleT->toPlainText();
	printf("reading error\n");
	printf("%s\n",newoutput);
	text.append(newoutput);
	this->consoleT->setPlainText(text);
	// 1) use insert text
	// 2) try to print errors in red color using QTextEdit::setColor line by line
	// BTW I don't think error channel is used in zod engine, everything is printf there...
}

void consoleout::printstartProc() {
	QString *newoutput = new QString("process started!\n");
	QString text = this->consoleT->toPlainText();
	printf("process started!\n");
	text.append(newoutput);
	this->consoleT->setPlainText(text);
}

void consoleout::printexitProc(int exitcode) {
	printf("Process exited with code: %d\n",exitcode);
}

void consoleout::copyToClipboard() {
	qApp->clipboard()->setText(this->consoleT->toPlainText());
	//if X11, change text in middle mouse click too
	if(qApp->clipboard()->supportsSelection()) {
		qApp->clipboard()->setText(this->consoleT->toPlainText(), QClipboard::Selection);
	}
}

void consoleout::saveToFile() {
	//create new file, save the output and close the file
	QFile *outputFile = new QFile(QDateTime::currentDateTime().toString("hhmmss-ddMMyy"));
	if(outputFile->open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
		QTextStream output(outputFile);
		output << this->consoleT->toPlainText();
	}
	//TODO:	disable the save button until file is saved
}



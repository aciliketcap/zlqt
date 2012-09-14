/*
 * cmdline.cpp
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

#include <QTextEdit>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include "cmdline.h"
#include <iostream> //for save test, can be removed

cmdlineWidget::cmdlineWidget(QWidget *parent) : QTextEdit(parent) {
	/*
	 *  this class knows the relation between the options in GUI and arguments in commandline.
	 *  if new options are added they will be added to cmdopts hash.
	 */
	//server options group
	cmdopts["dedicatedCB"] = "-d";
	cmdopts["trayCB"] = "-a";
	//file options groups
	cmdopts["mapNameW"] = "-m";
	cmdopts["mapListW"] = "-l";
	cmdopts["settingFileW"] = "-z";
	cmdopts["settingFileW2"] = "-e";
	//login options group
	cmdopts["serverNameW"] = "-c";
	cmdopts["loginNameW"] = "-g";
	cmdopts["loginPassW"] = "-i";
	//player options group
	cmdopts["windowedW"] = "-w";
	cmdopts["resolutionW"] = "-r";
	cmdopts["playerTeamW"] = "-t";
	cmdopts["botTeamW"] = "-b";
	cmdopts["playerNameW"] = "-n";
	cmdopts["noSoundCB"] = "-s";
	cmdopts["noMusicCB"] = "-u";
	cmdopts["noOpenGLCB"] = "-o";
	cmdopts["betterCursorCB"] = "-k";
	//misc
	this->setPlainText("./zod");	//we can have the executable chosen from filesystem. Like selecting map files.
	return;
}

void cmdlineWidget::addOpt(QString cmdopt, QString *value = 0) {
	//first check if the option is already added...
	QString *full = new QString;
	full->append(" ");
	full->append(cmdopt);
	if(value != 0) {
		full->append(" ");
		full->append(value);
	}
	QString *newcmdline = new QString(this->toPlainText());
	if(this->toPlainText().contains(cmdopt)) {
		int startindex = newcmdline->indexOf(cmdopt);
		int endindex = newcmdline->indexOf(" -", startindex+1); //if there are no arguments following, endindex == -1
		if(endindex==-1) endindex = newcmdline->length();
		newcmdline->replace(startindex-1, endindex-startindex+1, *full);
		this->setPlainText(*newcmdline);
	}
	else {
		newcmdline->append(full);
		this->setPlainText(*newcmdline);
	}
}

void cmdlineWidget::remOpt(QString cmdopt) {
	QString *newcmdline = new QString(this->toPlainText());
	if(newcmdline->contains(cmdopt)) {
		int startindex = newcmdline->indexOf(cmdopt);
		int endindex = newcmdline->indexOf(" -", startindex+1); //if there are no arguments following, endindex == -1
		if(endindex==-1) endindex = newcmdline->length();
		newcmdline->remove(startindex-1, endindex-startindex+1);
		this->setPlainText(*newcmdline);
	}
}

//slots for all possible parameters in cmdline, from top to bottom (and left to right)

//Server Options Group

void cmdlineWidget::dedicatedCBChanged(int state) {
	/*
	 * WE NEED THIS SLOT TO SEND A SIGNAL UPWARDS AND DISABLE LOGIN OPTS AND PLAY OPTS GROUPS
	 * OR WE CAN ALSO USE THE SIGNAL FROM CHECKBOX DIRECTLY
	 */
	//if state==0 than remove arg, if state==2 add argument
	if(state==0) this->remOpt(this->cmdopts["dedicatedCB"]);
	else if(state==2) this->addOpt(this->cmdopts["dedicatedCB"]);
}

void cmdlineWidget::trayCBChanged(int state) {
	//if state==0 than remove arg, if state==2 add argument
	if(state==0) this->remOpt(this->cmdopts["trayCB"]);
	else if(state==2) this->addOpt(this->cmdopts["trayCB"]);
}

//File Options Group

void cmdlineWidget::mapNameWChanged(int state, QString *value) {
	//if state==0 than remove arg, if state==2 add argument
	if(state==0) this->remOpt(this->cmdopts["mapNameW"]);
	else if(state==2) this->addOpt(this->cmdopts["mapNameW"], value);
}

void cmdlineWidget::mapListWChanged(int state, QString *value) {
	//if state==0 than remove arg, if state==2 add argument
	if(state==0) this->remOpt(this->cmdopts["mapListW"]);
	else if(state==2) this->addOpt(this->cmdopts["mapListW"], value);
}

void cmdlineWidget::settingFileWChanged(int state, QString *value) {
	//if state==0 than remove arg, if state==2 add argument
	if(state==0) this->remOpt(this->cmdopts["settingFileW"]);
	else if(state==2) this->addOpt(this->cmdopts["settingFileW"], value);
}

void cmdlineWidget::settingFileW2Changed(int state, QString *value) {
	//if state==0 than remove arg, if state==2 add argument
	if(state==0) this->remOpt(this->cmdopts["settingFileW2"]);
	else if(state==2) this->addOpt(this->cmdopts["settingFileW2"], value);
}

//Login Options Group

void cmdlineWidget::serverNameWChanged(int state, QString *value) {
	//if state==0 than remove arg, if state==2 add argument
	if(state==0) this->remOpt(this->cmdopts["serverNameW"]);
	else if(state==2) this->addOpt(this->cmdopts["serverNameW"], value);
}

void cmdlineWidget::loginNameWChanged(int state, QString *value) {
	//if state==0 than remove arg, if state==2 add argument
	if(state==0) this->remOpt(this->cmdopts["loginNameW"]);
	else if(state==2) this->addOpt(this->cmdopts["loginNameW"], value);
}

void cmdlineWidget::loginPassWChanged(int state, QString *value) {
	//if state==0 than remove arg, if state==2 add argument
	if(state==0) this->remOpt(this->cmdopts["loginPassW"]);
	else if(state==2) this->addOpt(this->cmdopts["loginPassW"], value);
}

//Player Options Group

void cmdlineWidget::windowedWChanged(int state) {
	//if state==0 than remove arg, if state==2 add argument
	if(state==0) this->remOpt(this->cmdopts["windowedW"]);
	else if(state==2) this->addOpt(this->cmdopts["windowedW"]);
}

void cmdlineWidget::resolutionWChanged(int state, int width, int height) {
	//if state==0 than remove arg, if state==2 add argument
	if(state==0) this->remOpt(this->cmdopts["resolutionW"]);
	else if(state==2) {
		QString *value = new QString;
		QString tempstr;
		value->append(tempstr.setNum(width));
		value->append("x");
		value->append(tempstr.setNum(height));
		this->addOpt(this->cmdopts["resolutionW"], value);
	}
}

void cmdlineWidget::playerTeamWChanged(int state, QString *value) {
	//if state==0 than remove arg, if state==2 add argument
	if(state==0) this->remOpt(this->cmdopts["playerTeamW"]);
	else if(state==2) this->addOpt(this->cmdopts["playerTeamW"], value);
}

void cmdlineWidget::botTeamWChanged(int state, QString *value) {
	//if state==0 than remove arg, if state==2 add argument
	if(state==0) this->remOpt(this->cmdopts["botTeamW"]);
	else if(state==2) this->addOpt(this->cmdopts["botTeamW"], value);
}

void cmdlineWidget::playerNameWChanged(int state, QString *value) {
	//if state==0 than remove arg, if state==2 add argument
	if(state==0) this->remOpt(this->cmdopts["playerNameW"]);
	else if(state==2) this->addOpt(this->cmdopts["playerNameW"], value);
}

void cmdlineWidget::noSoundCBChanged(int state) {
	//if state==0 than remove arg, if state==2 add argument
	if(state==0) this->remOpt(this->cmdopts["noSoundCB"]);
	else if(state==2) this->addOpt(this->cmdopts["noSoundCB"]);
}

void cmdlineWidget::noMusicCBChanged(int state) {
	//if state==0 than remove arg, if state==2 add argument
	if(state==0) this->remOpt(this->cmdopts["noMusicCB"]);
	else if(state==2) this->addOpt(this->cmdopts["noMusicCB"]);
}

void cmdlineWidget::noOpenGLCBChanged(int state) {
	//if state==0 than remove arg, if state==2 add argument
	if(state==0) this->remOpt(this->cmdopts["noOpenGLCB"]);
	else if(state==2) this->addOpt(this->cmdopts["noOpenGLCB"]);
}
void cmdlineWidget::betterCursorCBChanged(int state) {
	//if state==0 than remove arg, if state==2 add argument
	if(state==0) this->remOpt(this->cmdopts["betterCursorCB"]);
	else if(state==2) this->addOpt(this->cmdopts["betterCursorCB"]);
}

void cmdlineWidget::saveScript() {
	QFileDialog *filename = new QFileDialog(this);
	filename->setAcceptMode(QFileDialog::AcceptSave);
	filename->setFileMode(QFileDialog::AnyFile);
	filename->setConfirmOverwrite(true);
	filename->selectFile("launch_zod");
	QFile *outputFile = new QFile(filename->getSaveFileName());
	if(outputFile->open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
			QTextStream output(outputFile);
			//we need to use QTextStream because it converts 16-bit unicode QStrings to 8-bit ASCII strings.
			output << this->toPlainText();
	}
}


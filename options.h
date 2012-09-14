/*
 * options.h
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

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QButtonGroup>
//Apparently we need to include whole class definitions if we are inheriting other classes from them

class QLabel;
class QLineEdit;
class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
class QFileDialog;
class QPushButton;
class QRadioButton;
//we don't include these classes so that we can compile faster.
//just write their names and they will seem to be defined.

class toggleOptWidget : public QWidget {
	//radio button group used for fullscreen / windowed option
	Q_OBJECT
public:
	toggleOptWidget(QWidget *parent = 0, const QString opt1Label = "Option1", const QString opt2Label = "Option2");
	QButtonGroup *optG;
	QRadioButton *opt1;
	QRadioButton *opt2;

protected:
	QHBoxLayout *widgetLayout;
};

class nameOptWidget : public QWidget {
	//lineedit with a checkbox in front of it. Used in all options that contain text
	Q_OBJECT
public:
	nameOptWidget(QWidget *parent = 0, const QString label = "Insert name:", const QString defaultText = "some name :/");
	QCheckBox *nameOptCB;
	QLineEdit *nameOptT;
	int state; //state of checkbox
	QString *value;
public slots:
	void setState(int state = 3);
	void setValue(const QString &value);
signals:
	void stateChanged(int state, QString *value); //option state or value is changed

protected:
	QHBoxLayout *widgetLayout;
};

class resOptWidget : public QWidget {
	//two lineedits taking 4 digit integers. Used in resolution option
	Q_OBJECT
public:
	resOptWidget(QWidget *parent = 0, const QString label = "Choose Resolution:", const int width = 1024, const int height = 768);
	QCheckBox *resOptCB;
	QLineEdit *resOptWidthT;
	QLineEdit *resOptHeightT;
	QLabel *resOptSeperator;
	int state;
	int width;
	int height;
protected:
	QHBoxLayout *widgetLayout;
public slots:
	void setState(int state = 3);
	void setWidth(const QString &width);
	void setHeight(const QString &height);
signals:
	void stateChanged(int state, int width, int height);
};

class teamOptWidget : public QWidget {
	//Combobox with a checkbox in front of it. Used only for team selection options
	//Can be extended for other combobox options
	Q_OBJECT
public:
	teamOptWidget(QWidget *parent = 0, const QString label = "Choose team:");
	QCheckBox *teamOptCB;
	QComboBox *teamOptC;
	int state;	//I guess this could have been defined as protected as well
	QString *value; // this too
public slots:
	void setState(int state = 3);
	void setValue(int value = 0);
signals:
	void stateChanged(int state, QString *value); //option state or value is changed
protected:
	QHBoxLayout *widgetLayout;
};

class fileNameWidget : public nameOptWidget {
	//filename widget inherited from nameOpt class. Adds a browse button which opens a QFileDialog to get filenames/paths into line edit.
	Q_OBJECT
public:
	fileNameWidget(QWidget *parent = 0, const QString label = "Choose file:", const QString defaultText = "some_file.txt", const QString fileSuffix = "", const QString selectedFile = "");
	QPushButton *fileNameWidgetBrowseB;
	QFileDialog *fileNameWidgetBrowseDial;
	QString fileSuffix;		//this is not working :(
	QString selectedFile;	//this is not working since we give local paths I guess :/
protected:

public slots:
	void chooseFile();
};

class mapListWidget : public fileNameWidget {
	Q_OBJECT
public:
	//Edit maplist button will be added
	//Edit maplist window will be added
protected:

};

class serverOptionsGroup : public QGroupBox {
	Q_OBJECT
public:
	serverOptionsGroup(QWidget *parent = 0);
	QCheckBox *dedicatedCB;
	QCheckBox *trayCB;
protected:
	QHBoxLayout *serverOptionsL;
};

class fileOptionsGroup : public QGroupBox {
	Q_OBJECT
public:
	fileOptionsGroup(QWidget *parent = 0);
	fileNameWidget *mapNameW;
	fileNameWidget *mapListW;	//we'll use mapListWidget later
	//mapListWidget *mapListW;
	fileNameWidget *settingFileW;
	fileNameWidget *settingFileW2; //I don't know what "main server setting file" is...
protected:
	QVBoxLayout *fileOptionsGroupL;
};

class loginOptionsGroup : public QGroupBox {
	Q_OBJECT
public:
	loginOptionsGroup(QWidget *parent = 0);
	nameOptWidget *serverNameW;
	nameOptWidget *loginNameW;
	nameOptWidget *loginPassW;
protected:
	QVBoxLayout *loginOptionsGroupL;
};

class playerOptionsGroup : public QGroupBox {
	Q_OBJECT
public:
	playerOptionsGroup(QWidget *parent = 0);
	toggleOptWidget *windowedW;	//fullscreen radio box
	resOptWidget *resolutionW;	//resolution lineedits
	teamOptWidget *playerTeamW;
	teamOptWidget *botTeamW;
	nameOptWidget *playerNameW;
	QCheckBox *noSoundCB;
	QCheckBox *noOpenGLCB;
	QCheckBox *noMusicCB;
	QCheckBox *betterCursorCB;
protected:
	QGridLayout *playerOptionsGroupL;
};

class optionsWidget : public QWidget {
	Q_OBJECT
public:
	optionsWidget(QWidget *parent = 0);
	serverOptionsGroup *serverOptionsG;
	fileOptionsGroup *fileOptionsG;
	loginOptionsGroup *loginOptionsG;
	playerOptionsGroup *playerOptionsG;
	//teamOptWidget *teamOptW;


protected:
	QGridLayout *optionsL;

};

#endif /* OPTIONS_H_ */

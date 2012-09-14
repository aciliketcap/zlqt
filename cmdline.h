/*
 * cmdline.h
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

#ifndef ZL_CMDLINE_H_
#define ZL_CMDLINE_H_

#include <QWidget>
#include <QTextEdit>

class cmdlineWidget : public QTextEdit {
	/*
	 *  this class knows the relation between the options in GUI and arguments in commandline.
	 *  if new options are added they will be added to cmdopts hash.
	 */
	Q_OBJECT
public:
	cmdlineWidget(QWidget *parent = 0);
	QHash<QString, QString> cmdopts;		//key: option ismi, value: cmdline parametresi
	void addOpt(QString cmdopt, QString *value);	//add/change option to cmdline
	void remOpt(QString cmdopt); 	//rem option from cmdline*/
public slots:
	//slots for all possible parameters in cmdline
	//server options group
	void dedicatedCBChanged(int state);
	void trayCBChanged(int state);
	//file options group
	void mapNameWChanged(int state, QString *value);
	void mapListWChanged(int state, QString *value);
	void settingFileWChanged(int state, QString *value);
	void settingFileW2Changed(int state, QString *value);
	//login options group
	void serverNameWChanged(int state, QString *value);
	void loginNameWChanged(int state, QString *value);
	void loginPassWChanged(int state, QString *value);
	//player options group
	void windowedWChanged(int state);
	void resolutionWChanged(int state, int width, int height);
	void playerTeamWChanged(int state, QString *value);
	void botTeamWChanged(int state, QString *value);
	void playerNameWChanged(int state, QString *value);
	void noSoundCBChanged(int state);
	void noMusicCBChanged(int state);
	void noOpenGLCBChanged(int state);
	void betterCursorCBChanged(int state);

	//misc
	void saveScript();
};


#endif /* ZL_CMDLINE_H_ */

Hi, here is a new launcher for [Zod Engine] (http://zod.sourceforge.net/).

There are some things I won't change, hopefully someone else will implement these changes:

1. It only works under Linux. Porting should not be a big problem since I used QT for anything system dependent. Changing the way cmdlineWidget class works should be enough. Unfortunately I don't have a Windows machine with an IDE around me right now. 

2. The inputs in text boxes are not validated! Only resolution textboxes are set to accept 4 digit numbers and that's all. You can check out what problems it can cause by entering " -" in text boxes. No quotation marks or escape chars are defined. I know how messy cleaning bad or harmful input can get, I messed a lot with SQL injection strings etc. when I was doing web development. I know validation is a must for GUI programming but I don't think about adding any kind of form validation to this project.

And there are other things I'm looking forward to implement when I have the time. Still don't count on me and change these, I can allow you access to add your code.

1. Some options don't work together. I will apply the rules in Zod Engine's input_options::checkoptions() function defined in main.cpp. When an option that won't work with others are selected those options will be disabled and their commandline strings will be removed. A help button on window menu can be used to describe this behaviour.

2. File selection dialogs don't have default selected files and they don't filter files by extension. I added the functionality but for some reason it doesn't work. I will fix it sometime, hopefully.

3. I can't render the standard output correctly for some reason. Even if it shows reliable output it still waits until the execution of the process is over. Also it's currently using 1024 char long lines to read output, should change that sometime. 

4. I'm planning to add a create/modify button next to map list option. It will open a map list creation window and let you add and remove maps from map list files without any text editing.

5. When launcher is run for the first time having some default options selected can be good. Saving last edited options can be better. Maybe even saving old server settings, so that you can choose any server you connected before from a dropdown combobox.

6. I don't know what tray (-a) and main server settings file (-e) options are. I just added them. I am also not sure if -k option gives a "better cursor". I guess I should have named it faster cursor. Can change if necessary.

The included binary dynamically links with Qt 4.8.2 and it is compiled using gcc 4.5.4 under 64-bit Gentoo Linux. Best is to recompile by typing "make" I think. I don't know how I can provide binaries for other operating systems since I don't have a working compiling environment other than Gentoo around me.

Finally this distribution of code is licensed under GNU General Public License version 3 and it should be backwards compatible with at least Qt library version 4.3 (maybe even older than that) which is distributed under GNU Lesser General Public License version 2.1. You can download Qt libraries from website http://qt.nokia.com/downloads .  

zlqt is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details. You should have received a copy of it in a file named LICENSE, if not see http://www.gnu.org/licenses/ .

By the way you should be okay as long as you don't save over an important file :) 

Have fun,
Sinan 

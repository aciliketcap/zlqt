#############################################################################
# Makefile for building: zlqt
# Generated by qmake (2.01a) (Qt 4.8.2) on: Fri Sep 14 18:31:25 2012
# Project:  zlqt.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile zlqt.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib64/qt4 -lQtGui -L/usr/lib64 -L/usr/lib64/qt4 -L/usr/X11R6/lib -lQtCore -lgthread-2.0 -lrt -lglib-2.0 -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = cmdline.cpp \
		consoleout.cpp \
		main.cpp \
		maingui.cpp \
		options.cpp moc_cmdline.cpp \
		moc_consoleout.cpp \
		moc_maingui.cpp \
		moc_options.cpp
OBJECTS       = cmdline.o \
		consoleout.o \
		main.o \
		maingui.o \
		options.o \
		moc_cmdline.o \
		moc_consoleout.o \
		moc_maingui.o \
		moc_options.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		zlqt.pro
QMAKE_TARGET  = zlqt
DESTDIR       = 
TARGET        = zlqt

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: zlqt.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib64/qt4/libQtGui.prl \
		/usr/lib64/qt4/libQtCore.prl
	$(QMAKE) -o Makefile zlqt.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib64/qt4/libQtGui.prl:
/usr/lib64/qt4/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile zlqt.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/zlqt1.0.0 || $(MKDIR) .tmp/zlqt1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/zlqt1.0.0/ && $(COPY_FILE) --parents cmdline.h consoleout.h maingui.h options.h .tmp/zlqt1.0.0/ && $(COPY_FILE) --parents cmdline.cpp consoleout.cpp main.cpp maingui.cpp options.cpp .tmp/zlqt1.0.0/ && (cd `dirname .tmp/zlqt1.0.0` && $(TAR) zlqt1.0.0.tar zlqt1.0.0 && $(COMPRESS) zlqt1.0.0.tar) && $(MOVE) `dirname .tmp/zlqt1.0.0`/zlqt1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/zlqt1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_cmdline.cpp moc_consoleout.cpp moc_maingui.cpp moc_options.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_cmdline.cpp moc_consoleout.cpp moc_maingui.cpp moc_options.cpp
moc_cmdline.cpp: cmdline.h
	/usr/bin/moc $(DEFINES) $(INCPATH) cmdline.h -o moc_cmdline.cpp

moc_consoleout.cpp: consoleout.h
	/usr/bin/moc $(DEFINES) $(INCPATH) consoleout.h -o moc_consoleout.cpp

moc_maingui.cpp: options.h \
		cmdline.h \
		maingui.h
	/usr/bin/moc $(DEFINES) $(INCPATH) maingui.h -o moc_maingui.cpp

moc_options.cpp: options.h
	/usr/bin/moc $(DEFINES) $(INCPATH) options.h -o moc_options.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

cmdline.o: cmdline.cpp cmdline.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o cmdline.o cmdline.cpp

consoleout.o: consoleout.cpp consoleout.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o consoleout.o consoleout.cpp

main.o: main.cpp maingui.h \
		options.h \
		cmdline.h \
		consoleout.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

maingui.o: maingui.cpp maingui.h \
		options.h \
		cmdline.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o maingui.o maingui.cpp

options.o: options.cpp options.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o options.o options.cpp

moc_cmdline.o: moc_cmdline.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_cmdline.o moc_cmdline.cpp

moc_consoleout.o: moc_consoleout.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_consoleout.o moc_consoleout.cpp

moc_maingui.o: moc_maingui.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_maingui.o moc_maingui.cpp

moc_options.o: moc_options.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_options.o moc_options.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:


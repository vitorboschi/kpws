/*
KDE Personal Web Server - Allow you to easily share files over http
Copyright (C) 2010 by Vitor Boschi da Silva (vitorboschi@gmail.com)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>
#include <KTextEdit>
#include <KVBox>
#include <KListWidget>
#include <KComboBox>
#include <QTreeView>

#include "webserver.h"
#include "webcontent_dummy.h"
#include "webcontent_list.h"
#include "webcontent_file.h"

class MainWindow : public KXmlGuiWindow
{
	public:
		MainWindow(QWidget *parent=0);

	private:
		KVBox* layout;
		KComboBox* bindAddress;
		QTreeView* resourcesView;
		KListWidget* logList;
		WebServer daemon;

		//test content
		WebContent_VirtualFolder* root;
		
		WebContent_Dummy* c1;
		WebContent_Dummy* c2;

		WebContent_VirtualFolder* f1;
		WebContent_Dummy* c3;

		WebContent_File* fileOk;
		WebContent_File* fileError;
	};

#endif

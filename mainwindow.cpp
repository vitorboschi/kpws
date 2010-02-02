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

#include "mainwindow.h"

#include <KLocalizedString>
MainWindow::MainWindow(QWidget *parent) : KXmlGuiWindow(parent)
{

	layout = new KVBox(this);
	setCentralWidget(layout);
	bindAddress = new KComboBox(true, layout);
	resourcesView = new QTreeView(layout);
	logList = new KListWidget(layout);
	setupGUI();
	logList->addItem(i18n("Application started"));
	
	//add some test content
	root = new WebContent_VirtualFolder();
	c1 = new WebContent_Dummy("arq1");
	c2 = new WebContent_Dummy("arq2");
	c3 = new WebContent_Dummy("arq3");
	f1 = new WebContent_VirtualFolder("folder1");

	fileOk = new WebContent_File("fileOK", "/home/vitor/sancalivre.iso");
	fileError = new WebContent_File("fileError", "/home/vitor/nonExistent");

	daemon.setRootContent(root);
	root->addContent(c1);
	root->addContent(c2);
	root->addContent(f1);
	root->addContent(fileOk);
	root->addContent(fileError);
	f1->addContent(c3);
	root->updateCache();
	f1->updateCache();

	if (daemon.listen(QHostAddress::Any, 8080)) {
		logList->addItem(i18n("Daemon started"));
	}
}

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
	root = new WebContent_List();
	c1 = new WebContent_Dummy("arq1");
	c2 = new WebContent_Dummy("arq2");
	c3 = new WebContent_Dummy("arq3");
	f1 = new WebContent_List("folder1");

	fileOk = new WebContent_File("fileOK", "/home/vitor/Desktop/trance.pls");
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

	if (daemon.startServer(/*QHostAddress::Any, 8080*/)) {
		logList->addItem(i18n("Daemon started"));
	}
}

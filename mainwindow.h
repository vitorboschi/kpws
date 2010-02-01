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
		WebContent_List* root;
		
		WebContent_Dummy* c1;
		WebContent_Dummy* c2;

		WebContent_List* f1;
		WebContent_Dummy* c3;

		WebContent_File* fileOk;
		WebContent_File* fileError;
	};

#endif

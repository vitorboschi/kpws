#ifndef WEBCONTENT_FILE_H
#define WEBCONTENT_FILE_H

#include <QString>
#include <QByteArray>
#include "webcontent.h"


class WebContent_File : public WebContent
{
	public:
	WebContent_File(QString identifier, QString file);
	int getChunk(QString url, char* buffer, quint64 start=0, int len=-1);
	QString getMime(QString url);
	qint64 getSize(QString url);
	bool validUrl(QString url);
	~WebContent_File();
	//QString getUrl();
	//void setUrl(QString url);

	private:
	QByteArray content;
	QString file;
	QString tmpFile;
	bool initOk;
};

#endif

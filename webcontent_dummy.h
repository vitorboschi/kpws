#ifndef WEBCONTENT_DUMMY_H
#define WEBCONTENT_DUMMY_H

#include <QString>
#include <QByteArray>
#include "webcontent.h"


class WebContent_Dummy : public WebContent
{
	public:
	WebContent_Dummy(QString identifier);
	int getChunk(QString url, char* buffer, quint64 start=0, int len=-1);
	QString getMime(QString url);
	qint64 getSize(QString url);
	bool validUrl(QString url);

	private:
	QByteArray content;
};

#endif

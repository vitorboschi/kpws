#ifndef WEBCONTENT_LIST_H
#define WEBCONTENT_LIST_H

#include <QString>
#include <QByteArray>
#include <QMap>
#include "webcontent.h"


class WebContent_List : public WebContent
{
	public:
	WebContent_List(QString identifier = "");
	int getChunk(QString url, QByteArray* buffer, qint64 start=0, int len=-1);
	QString getMime(QString url);
	qint64 getSize(QString url);
	bool validUrl(QString url);

	bool addContent(WebContent* content);
	WebContent* getContent(QString identifier);
	WebContent* removeContent(QString identifier);
	void updateCache();

	private:
	QByteArray content;
	QMap<QString, WebContent*> resources;
};

#endif

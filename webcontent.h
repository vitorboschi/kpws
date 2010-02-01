#ifndef WEBCONTENT_H
#define WEBCONTENT_H

#include <QString>
#include <QByteArray>

class WebContent
{
	public:
	WebContent(QString identifier= "");
	virtual int getChunk(QString url, char* buffer, quint64 start=0, int len=-1) = 0;
	virtual QString getMime(QString url) {return "";};
	virtual qint64 getSize(QString url) {return -1;};
	virtual bool validUrl(QString url) {return false;};
	QString getUrl();
	int getChildCount() {return 0;};
	WebContent* getChild(int row) {return NULL;};
	//virtual void setUrl(QString url) {};
	QString getIdentifier() {return identifier;};
	void setParent(WebContent* parent) {this->parent = parent;};
	WebContent* getParent() {return parent;};
	virtual ~WebContent() {}

	protected:
	QString identifier;
	WebContent* parent;
};

#endif

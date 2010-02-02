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

#ifndef WEBCONTENT_H
#define WEBCONTENT_H

#include <QString>
#include <QByteArray>

class WebContent
{
	public:
	WebContent(QString identifier= "");
	//Return the number of bytes written to the buffer
	virtual int getChunk(QString url, QByteArray* buffer, qint64 start=0, int len=-1) = 0;
	virtual QString getMime(QString url) {return "";};
	//Content size, in bytes, or -1 when unknown
	virtual qint64 getSize(QString url) {return 0;};
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

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

#ifndef WEBCONTENT_DUMMY_H
#define WEBCONTENT_DUMMY_H

#include <QString>
#include <QByteArray>
#include "webcontent.h"


class WebContent_Dummy : public WebContent
{
	public:
	WebContent_Dummy(QString identifier);
	int getChunk(QString url, QByteArray* buffer, qint64 start=0, int len=-1);
	QString getMime(QString url);
	qint64 getSize(QString url);
	bool validUrl(QString url);

	private:
	QByteArray content;
};

#endif

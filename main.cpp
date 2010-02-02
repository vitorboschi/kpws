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

#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KMessageBox>

#include "mainwindow.h"

int main (int argc, char *argv[])
{
    KAboutData aboutData(
        // The program name used internally.
        "KPWS",
        // The message catalog name
        // If null, program name is used instead.
        0,
        // A displayable program name string.
        ki18n("KDE Personal Web Server"),
        // The program version string.
        "0.1",
        // Short description of what the app does.
        ki18n("Allow you to easily share files"),
        // The license this code is released under
        KAboutData::License_GPL,
        // Copyright Statement
        ki18n("(c) 2009"),
        // Optional text shown in the About box.
        // Can contain any information desired.
        ki18n("Some text..."),
        // The program homepage string.
        "",
        // The bug report email address
        "vitorboschi@gmail.com");

    KCmdLineArgs::init( argc, argv, &aboutData );
    KApplication app;
    MainWindow* window = new MainWindow();
    window->show();

    return app.exec();
}


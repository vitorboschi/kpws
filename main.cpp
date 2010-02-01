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


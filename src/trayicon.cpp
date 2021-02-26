#include "trayicon.h"

TrayIcon::TrayIcon(QWidget *parent) : QWidget(parent)
{
    initializeTuned();
    setTrayIcon();
}

TrayIcon::~TrayIcon()
{
    delete tunedManager;
}

void TrayIcon::initializeTuned()
{
    tunedManager = new TunedManager();
    availableProfiles = tunedManager -> GetAvailableProfiles();
}

void TrayIcon::Show()
{
    // Showing icon...
    trayIcon -> show();
}

void TrayIcon::setTrayIcon()
{
    // Setting tray icon...
    trayIcon = new QSystemTrayIcon(this);
    QIcon trayImage(":/images/icon-48.png");
    trayIcon -> setIcon(trayImage);
    trayIcon -> setContextMenu(createTrayIconMenu());
}

QMenu* TrayIcon::createProfilesSubmenu()
{
    QMenu *trayIconProfiles = new QMenu(this);
    QActionGroup *trayIcontGroup = new QActionGroup(trayIconProfiles);
    QString currentProfile = tunedManager -> GetActiveProfile();

    trayIconProfiles -> setTitle(tr("Profiles"));
    trayIcontGroup -> setExclusive(true);

    for(int i=0; i < availableProfiles.size(); i++)
    {
        QAction* profileAction = new QAction(availableProfiles[i], this);
        profileAction -> setData(i);
        profileAction -> setCheckable(true);
        if (availableProfiles[i] == currentProfile) profileAction -> setChecked(true);
        trayIcontGroup -> addAction(profileAction);
    }

    connect(trayIcontGroup, SIGNAL(triggered(QAction*)), this, SLOT(profileSelectedEvent(QAction*)));
    trayIconProfiles -> addActions(trayIcontGroup -> actions());
    return trayIconProfiles;
}

QMenu* TrayIcon::createTrayIconMenu()
{
    // Creating QMenu object...
    QMenu *trayIconMenu = new QMenu(this);

    // Setting actions and slots...
    QAction *quitAction = new QAction(tr("Quit"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(exitEvent()));

    // Setting system tray's icon menu...
    trayIconMenu -> addMenu(createProfilesSubmenu());
    trayIconMenu -> addSeparator();
    trayIconMenu -> addAction(quitAction);
    return trayIconMenu;
}

void TrayIcon::profileSelectedEvent(QAction* action)
{
    QString profile = availableProfiles[action -> data().toInt()];
    if (tunedManager -> SetActiveProfile(profile))
        trayIcon -> showMessage(tr("Profile change"), QString(tr("The active profile was successfully changed to %1.")).arg(profile), QSystemTrayIcon::Information);
    else
        trayIcon -> showMessage(tr("Profile change"), QString(tr("Failed to change the active profile to %1!")).arg(profile), QSystemTrayIcon::Critical);
}

void TrayIcon::exitEvent()
{
    QApplication::exit(0);
}

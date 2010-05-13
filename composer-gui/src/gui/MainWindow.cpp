#include "../../include/gui/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    initGUI();
    cManager = new CoreManager(this);
    connect(cManager,SIGNAL(projectCreated(QString,QString)),
            this,SLOT(createProjectInTree(QString,QString)));
    connect(cManager,SIGNAL(onError(QString)),
            this,SLOT(errorDialog(QString)));
}

MainWindow::~MainWindow() {

}

void MainWindow::initGUI() {
    setWindowTitle(tr("Composer 2.0 Revolutionary - by Bruno Modafucker"));
    mdiArea = new QMdiArea(this);
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);
    setUnifiedTitleAndToolBarOnMac(true);
    createStatusBar();
    createTreeProject();
    createActions();
    createMenus();
    showMaximized();

}

void MainWindow::launchProjectWizard() {
    ProjectWizard *wizard = new ProjectWizard(this);
    connect(wizard,SIGNAL(infoReceived(QString,QString)),
            cManager,SLOT(createProject(QString,QString)));
    wizard->init();
}


void MainWindow::createProjectInTree(QString name,QString location) {
    QTreeWidgetItem *item = new QTreeWidgetItem(projectTree);
    item->setIcon(0,QIcon(":/mainwindow/folderEmpty"));
    item->setText(1,name);
    item->setToolTip(1,location+name);
}


void MainWindow::createTreeProject() {
    dockTree = new QDockWidget(tr("Projects"), this);
    dockTree->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    projectTree = new QTreeWidget(this);
    projectTree->setColumnCount(2);
    projectTree->setSortingEnabled(false);
    //projectTree->setHeaderLabel(tr("Name"));
    projectTree->headerItem()->setHidden(true);
    projectTree->setIconSize(QSize(35,35));
    dockTree->setWidget(projectTree);
    addDockWidget(Qt::LeftDockWidgetArea,dockTree,Qt::Horizontal);
}

void MainWindow::createMenus() {
     fileMenu = menuBar()->addMenu(tr("&File"));
     newMenu  = new QMenu(tr("New"),fileMenu);
     newMenu->addAction(newProjectAct);
     newMenu->addAction(newDocumentAct);
     fileMenu->addMenu(newMenu);

     windowMenu = menuBar()->addMenu(tr("&Window"));

     menuBar()->addSeparator();
     connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));


     helpMenu = menuBar()->addMenu(tr("&Help"));
     helpMenu->addAction(aboutComposerAct);

 }

void MainWindow::about() {
    QMessageBox::about(this, tr("About Composer"),
             tr("The <b>Composer</b> is an IDE for the NCL language."));
 }

void MainWindow::errorDialog(QString message) {
    QMessageBox::warning(this,tr("Error creating project."),
                         tr(message.toStdString().c_str()));

 }

void MainWindow::createActions() {

     newProjectAct = new QAction(tr("New &Project"), this);
     //newProjectAct->setShortcuts(QKeySequence("CTRL+P"));
     newProjectAct->setStatusTip(tr("Create a new Project"));
     connect(newProjectAct, SIGNAL(triggered()), this,
             SLOT(launchProjectWizard()));

     newDocumentAct = new QAction(tr("New &Document"), this);
     newDocumentAct->setShortcuts(QKeySequence::New);
     newDocumentAct->setStatusTip(tr("Create a new NCL Document"));
     //connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

     aboutComposerAct = new QAction(tr("&About"), this);
     aboutComposerAct->setStatusTip(tr("Show the application's About box"));
     connect(aboutComposerAct, SIGNAL(triggered()), this, SLOT(about()));

     separatorWindowAct = new QAction(this);
     separatorWindowAct->setSeparator(true);

     projectWindowAct = new QAction(tr("Projects"),this);
     projectWindowAct->setCheckable(true);
     projectWindowAct->setChecked(dockTree->isVisible());

    connect(dockTree,SIGNAL(visibilityChanged(bool)),this,
             SLOT(updateWindowMenu()));
     connect(projectWindowAct,SIGNAL(triggered(bool)),dockTree,
             SLOT(setVisible(bool)));
 }

void MainWindow::createStatusBar() {
     statusBar()->showMessage(tr("Ready"));
}

void MainWindow::updateWindowMenu()
 {
     windowMenu->clear();
     windowMenu->addAction(projectWindowAct);
     windowMenu->addAction(separatorWindowAct);
     projectWindowAct->setChecked(dockTree->isVisible());

     QList<QMdiSubWindow *> windows = mdiArea->subWindowList();
     separatorWindowAct->setVisible(!windows.isEmpty());

 }

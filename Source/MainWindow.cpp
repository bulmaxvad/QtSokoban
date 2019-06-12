#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QHash>
#include <QPainter>

#include "MapItems/MapItemBase.h"
#include "Map/Map.h"
#include "Map/MapWidget.h"
#include "Game.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actFile_LoadLevels, &QAction::triggered,
            this, &MainWindow::mnuFile_LoadLevels__clicked);
    connect(ui->actFile_NextLevel, &QAction::triggered,
            this, &MainWindow::mnuFile_NextLevel__clicked);

    game().setGameDir("P:/old_projects/Sokoban/cxx/QtApp/Sokoban/Examples/GameDir/");
    this->setCentralWidget(game().mapWidget());
    game().mapWidget()->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

Sokoban::Game& MainWindow::game() const
{
    return m_game.get();
}

void MainWindow::mnuFile_LoadLevels__clicked(bool checked)
{
    Q_UNUSED(checked);

    QFileDialog dlg;

    dlg.setNameFilter("Text files (*.sbmap)");
    dlg.setFileMode(QFileDialog::ExistingFile);
    dlg.setDirectory(game().gameDir());
    if (!dlg.exec())
        return;

    using namespace Sokoban;

    Error errorCode = game().loadMaps(dlg.selectedFiles().first());
    if (errorCode != Error::NoError)
    {
        QMessageBox::critical(this, "Error!", QString("Error code = %1").arg(errorToChars(errorCode)));
        return;
    }

    game().updateMapWidget();

    //QMessageBox::information(this, "Levels info", QString("Level's count: %1").arg(game()->mapCount()));
}

void MainWindow::mnuFile_NextLevel__clicked(bool checked)
{
    game().playNexLevel();
}

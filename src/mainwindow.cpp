#include "mainwindow.h"
#include "renderwindow.h"

#include "./ui_mainwindow.h"

#include <BlackEngine/Engine.h>

#include <QTimer>

using namespace black;
using namespace blackeditor;

MainWindow::MainWindow(std::shared_ptr<RenderWindow> window)
    : QMainWindow(nullptr)
    , AbstractApplication("BlackEngine", this->width(), this->height(), false)
    , renderWindow(std::move(window))
    , updateTimer(std::make_unique<QTimer>(this))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Substitute OpenGL widget with render window
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(renderWindow->sizePolicy().hasHeightForWidth());
    renderWindow->setSizePolicy(sizePolicy);

    ui->gridLayout->removeItem(ui->verticalSpacer);
    ui->gridLayout->addWidget(renderWindow.get(), 0, 0);

    // Setup update timer
    auto timerPtr = updateTimer.get();
    connect(timerPtr, SIGNAL(timeout()), this, SLOT(onUpdateTime()));
    timerPtr->start();

    Logger::SetLogLevel(LogLevel::TRACE);

    connect(ui->sbLightIntensity, SIGNAL(valueChanged(double)),
        &renderWindow->getScene(), SLOT(onLightIntensityChanged(double)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::onLightIntensityChanged(double newIntensity) {
//  Logger::Get("Editor")->trace("New intensity: {}", newIntensity);
//}

bool MainWindow::isKeyPressed(black::Key key)
{
    return false;
}

bool MainWindow::isKeyPressed(int key)
{
    return false;
}

bool MainWindow::isKeyReleased(black::Key key)
{
    return false;
}

bool MainWindow::isKeyReleased(int key)
{
    return false;
}

void MainWindow::setCursorMode(black::CursorMode mode)
{
}

void MainWindow::setMouseAccelerated(bool accelerated)
{
}

void MainWindow::addCursor(std::string name, const black::Image &image)
{
}

void MainWindow::setCursor(std::string name)
{
}

void MainWindow::update(float dt)
{
}

void MainWindow::init()
{
    auto renderSystem = Engine::GetCurrentRenderSystem();
    timer = std::make_shared<PerformanceCounter>();
}

void MainWindow::initializeResources()
{
}

void MainWindow::run()
{
}

void MainWindow::onUpdateTime()
{
//    Logger::Get("MainWindow")->info("Update");
    renderWindow->updateRenderTarget();
}

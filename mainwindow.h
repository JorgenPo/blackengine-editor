#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <BlackEngine/application/GameApplication.h>
#include <BlackEngine/input/InputSystemInterface.h>
#include <BlackEngine/SystemInterface.h>
#include <BlackEngine/input/Keyboard.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class RenderWindow;

class MainWindow : public QMainWindow, public black::AbstractApplication, public black::InputSystemInterface
{
    Q_OBJECT

    std::shared_ptr<RenderWindow> renderWindow;
    std::shared_ptr<black::PerformanceCounter> timer;

    std::unique_ptr<QTimer> updateTimer;
    Ui::MainWindow *ui;

public:
    MainWindow(std::shared_ptr<RenderWindow> renderWindow);
    ~MainWindow();

    // InputSystemInterface interface
public:
    bool isKeyPressed(black::Key key);
    bool isKeyPressed(int key);
    bool isKeyReleased(black::Key key);
    bool isKeyReleased(int key);
    void setCursorMode(black::CursorMode mode);
    void setMouseAccelerated(bool accelerated);
    void addCursor(std::string name, const black::Image &image);
    void setCursor(std::string name);


    // AbstractApplication interface
protected:
    void update(float dt);
    void init();

private:
    void initializeResources();
    void run();

public slots:
    void onUpdateTime();
};

#endif // MAINWINDOW_H

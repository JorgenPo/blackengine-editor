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
    explicit MainWindow(std::shared_ptr<RenderWindow> renderWindow);
    ~MainWindow() override;

    // InputSystemInterface interface
public:
    bool isKeyPressed(black::Key key) override;
    bool isKeyPressed(int key) override;
    bool isKeyReleased(black::Key key) override;
    bool isKeyReleased(int key) override;
    void setCursorMode(black::CursorMode mode) override;
    void setMouseAccelerated(bool accelerated) override;
    void addCursor(std::string name, const black::Image &image) override;
    void setCursor(std::string name) override;


    // AbstractApplication interface
protected:
    void update(float dt) override;
    void init() override;

private:
    void initializeResources() override;
    void run() override;

public slots:
    void onUpdateTime();
};

#endif // MAINWINDOW_H

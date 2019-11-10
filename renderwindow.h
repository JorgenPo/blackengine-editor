#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_4_Core>

#include <BlackEngine/render/AbstractRenderWindow.h>
#include <BlackEngine/render/RendererInterface.h>
#include <BlackEngine/scene/SimpleScene.h>

#include <memory>

class RenderWindow :
        public QOpenGLWidget,
        public black::AbstractRenderWindow,
        public std::enable_shared_from_this<RenderWindow>
{
    std::shared_ptr<black::RendererInterface> renderer;
    std::shared_ptr<black::SimpleScene> scene;
    std::shared_ptr<black::Camera> camera;
public:
    explicit RenderWindow(QWidget *parent);

    // QOpenGLWidget interface
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    // RenderTargetInterface interface
public:
    void updateRenderTarget();
    void setRenderTargetCurrent();
    float getRenderTargetWidth();
    float getRenderTargetHeight();
    float getRenderTargetAspectRatio();

    // AbstractRenderWindow interface
public:
    void show();
    void hide();
    void close();
    bool isShown();
    void pollEvents();
    bool shouldClose();

private:
    void initScene();
};

#endif // RENDERWINDOW_H

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
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    // RenderTargetInterface interface
public:
    void updateRenderTarget() override;
    void setRenderTargetCurrent() override;
    float getRenderTargetWidth() override;
    float getRenderTargetHeight() override;
    float getRenderTargetAspectRatio() override;

    // AbstractRenderWindow interface
public:
    void show() override;
    void hide() override;
    void close() override;
    bool isShown() override;
    void pollEvents() override;
    bool shouldClose() override;

private:
    void initScene();
};

#endif // RENDERWINDOW_H

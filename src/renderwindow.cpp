#include <glad/glad.h>
#include "renderwindow.h"

#include <BlackEngine/Engine.h>
#include <BlackEngine/log/Logger.h>
#include <BlackEngine/render/RenderSystemInterface.h>
#include <BlackEngine/util/ModelManager.h>
#include <BlackEngine/GameObject.h>
#include <BlackEngine/components/BoundingComponent.h>
#include <BlackEngine/components/TransformComponent.h>
#include <BlackEngine/components/ModelComponent.h>
#include <BlackEngine/Camera.h>

using namespace black;
using namespace blackeditor;

RenderWindow::RenderWindow(QWidget *parent) :
    QOpenGLWidget(parent)
    , AbstractRenderWindow(black::WindowData{
      "BlackEngine",this->width(), this->height(),
      false, {4, 4}})
    , scene(nullptr)
{
    QSurfaceFormat contextInfo;
    contextInfo.setVersion(4, 0);
    contextInfo.setProfile(QSurfaceFormat::CoreProfile);
    this->setFormat(contextInfo);
}

void RenderWindow::initializeGL()
{
    // Init GLAD
    if (gladLoadGL()) {
        renderer = Engine::GetCurrentRenderSystem()->createRenderer(shared_from_this());
    } else {
        Logger::Get("RenderWindow")->critical("Failed to init opengl functions");
    }

    scene = std::make_shared<Scene>(shared_from_this());
    scene->initialize();
}

void RenderWindow::resizeGL(int w, int h)
{
  renderer->setViewPort(0, 0, w, h);
  scene->updateCameraViewport(w, h);
}

void RenderWindow::paintGL()
{
    renderer->render(scene->get());
}


void RenderWindow::updateRenderTarget()
{
    this->repaint();
}

void RenderWindow::setRenderTargetCurrent()
{
    this->makeCurrent();
}

float RenderWindow::getRenderTargetWidth()
{
    return this->width();
}

float RenderWindow::getRenderTargetHeight()
{
    return this->height();
}

float RenderWindow::getRenderTargetAspectRatio()
{
    return (float)this->width() / (float)this->height();
}

void RenderWindow::show()
{
    QOpenGLWidget::show();
}

void RenderWindow::hide()
{
    QOpenGLWidget::hide();
}

void RenderWindow::close()
{
    QOpenGLWidget::close();
}

bool RenderWindow::isShown()
{
    return QOpenGLWidget::isVisible();
}

void RenderWindow::pollEvents()
{
}

bool RenderWindow::shouldClose()
{
    return false;
}

std::shared_ptr<Scene> RenderWindow::getScene() const noexcept {
  return scene;
}

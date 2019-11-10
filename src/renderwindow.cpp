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
#include <BlackEngine/util/Screen.h>

using namespace black;

RenderWindow::RenderWindow(QWidget *parent)
    : QOpenGLWidget(parent)
    , AbstractRenderWindow(
          black::WindowData{"BlackEngine", this->width(), this->height(), false, {4, 4}})
    , scene(std::make_shared<SimpleScene>("Scene"))
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
        Screen::Initialize(renderer);
    } else {
        Logger::Get("RenderWindow")->critical("Failed to init opengl functions");
    }

    initScene();
}

void RenderWindow::resizeGL(int w, int h)
{

}

void RenderWindow::paintGL()
{
    renderer->render(scene);
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
    return this->width() / this->height();
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

void RenderWindow::initScene()
{
    auto cottageModel = ModelManager::CreateFromFile("resources/cottage_obj.obj");
    auto cottage = std::make_shared<GameObject>("Cottage");

    cottage->add(cottageModel);
    cottage->add(std::make_shared<BoundingComponent>(
                     std::make_shared<Sphere>(cottage->transform, 12.0f)));
    cottage->transform->scale(0.1f);

    scene->addObject(std::move(cottage));

    this->camera = std::make_shared<Camera>(ProjectionType::PERSPECTIVE);
    this->camera->setPosition({0.0f, 10.0f, 1.0f});
    this->camera->setLookAt({0.0f, -1.0f, 0.0f});

    scene->setCurrentCamera(this->camera);
}

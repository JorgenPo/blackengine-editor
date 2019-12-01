//
// Created by popov on 13.11.2019.
//

#include "Scene.h"

#include <BlackEngine/Engine.h>
#include <BlackEngine/log/Logger.h>
#include <BlackEngine/Camera.h>
#include <BlackEngine/GameObject.h>
#include <BlackEngine/util/ModelManager.h>
#include <BlackEngine/components/BoundingComponent.h>
#include <BlackEngine/components/ModelComponent.h>
#include <BlackEngine/components/TransformComponent.h>
#include <BlackEngine/components/LightComponent.h>
#include <BlackEngine/terrain/TerrainBuilder.h>

#include <memory>

using namespace blackeditor;
using namespace black;

Scene::Scene(std::shared_ptr<black::RenderTargetInterface> renderTarget)
  : renderTarget(std::move(renderTarget)), scene(std::make_shared<SimpleScene>("MainScene"))
{
}

Scene::BlackScene Scene::get() const noexcept {
  return scene;
}

void Scene::initialize() {
  auto builder = Engine::GetTerrainBuilder("Flat");
  TerrainBuilder::Data data;
  data.width = 1000;
  data.height = 1000;
  data.lod = 5.0f;

  terrain = builder->build(data);
  this->scene->addObject(terrain);

  Camera::Data cameraData{
    renderTarget,
    ProjectionType::PERSPECTIVE,
    {0.0f, 10.0f, 1.0f}};
  camera = std::make_shared<Camera>(std::move(cameraData));

  this->camera->setLookAt({0.0f, -1.0f, 0.0f});

  auto cottageModel = ModelManager::CreateFromFile("resources/cottage_obj.obj");
  auto cottage = std::make_shared<GameObject>("Cottage");

  cottage->add(cottageModel);
  cottage->add(std::make_shared<BoundingComponent>(
      std::make_shared<Sphere>(cottage->transform, 12.0f)));

  cottage->transform->scale(0.1f);

  auto directedLight = std::make_shared<DirectedLight>(
      Color::WHITE, 2.0f, 0.1f, glm::vec3{-1.0f, -1.0f, 0.2f});

  mainLight = std::make_shared<GameObject>("Sun");
  mainLight->transform->setPosition({10.0f, 200.0f, 0.0f});
  mainLight->add(directedLight);
  mainLight->get<LightComponent>()->setColor(Color{1.0f, 0.8f, 0.8f});

  scene->addObjects({mainLight, std::move(cottage)});

  auto ambientLight = scene->getAmbientLight();
  ambientLight.intensity = 1.4f;
  scene->setAmbientLight(ambientLight);

  scene->setCurrentCamera(this->camera);
}

void Scene::onLightIntensityChanged(double intensity) {
  mainLight->get<LightComponent>()->setIntensity(static_cast<float>(intensity));
}

void Scene::setLightEnabled(int enable) {
  if (enable == Qt::Unchecked) {
    this->scene->removeObject(mainLight->getName());
  } else {
    this->scene->addObject(mainLight);
  }
}

void Scene::onAmbientIntensityChanged(double newIntensity) {
  this->scene->setAmbientLight({Color::WHITE, static_cast<float>(newIntensity)});
}

void Scene::updateCameraViewport(int w, int h) {
  Logger::Get("Scene")->trace("Camera updated to {}x{}", w, h);
  this->camera->updateProjectionMatrix();
}

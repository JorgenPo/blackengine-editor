//
// Created by popov on 13.11.2019.
//

#include "Scene.h"

#include <BlackEngine/Engine.h>
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

Scene::Scene()
  : scene(std::make_shared<SimpleScene>("MainScene"))
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

  camera = std::make_shared<Camera>(ProjectionType::PERSPECTIVE);

  this->camera->setPosition({0.0f, 10.0f, 1.0f});
  this->camera->setLookAt({0.0f, -1.0f, 0.0f});

  auto cottageModel = ModelManager::CreateFromFile("resources/cottage_obj.obj");
  auto cottage = std::make_shared<GameObject>("Cottage");

  cottage->add(cottageModel);
  cottage->add(std::make_shared<BoundingComponent>(
      std::make_shared<Sphere>(cottage->transform, 12.0f)));

  cottage->transform->scale(0.1f);

  mainLight = std::make_shared<GameObject>("Sun");
  mainLight->transform->setPosition({10.0f, 200.0f, 0.0f});
  mainLight->add(std::make_shared<LightComponent>(LightType::DIRECTIONAL));
  mainLight->get<LightComponent>()->setColor(Color{1.0f, 0.8f, 0.8f});

  scene->addObjects({mainLight, std::move(cottage)});

  this->camera = std::make_shared<Camera>(ProjectionType::PERSPECTIVE);
  this->camera->setPosition({0.0f, 10.0f, 1.0f});
  this->camera->setLookAt({0.0f, -1.0f, 0.0f});

  scene->setCurrentCamera(this->camera);
}

void Scene::onLightIntensityChanged(double intensity) {
  mainLight->get<LightComponent>()->setIntensity(intensity);
}

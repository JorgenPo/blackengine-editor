//
// Created by popov on 13.11.2019.
//

#include "Scene.h"

#include <BlackEngine/Camera.h>
#include <BlackEngine/GameObject.h>
#include <BlackEngine/util/ModelManager.h>
#include <BlackEngine/components/BoundingComponent.h>
#include <BlackEngine/components/ModelComponent.h>
#include <BlackEngine/components/TransformComponent.h>

#include <memory>

using namespace blackeditor;

Scene::Scene()
  : scene(std::make_shared<black::SimpleScene>("MainScene"))
{
}

Scene::BlackScene Scene::get() const noexcept {
  return scene;
}

void Scene::initialize() {
  camera = std::make_shared<black::Camera>(black::ProjectionType::PERSPECTIVE);

  this->camera->setPosition({0.0f, 10.0f, 1.0f});
  this->camera->setLookAt({0.0f, -1.0f, 0.0f});

  auto cottageModel = black::ModelManager::CreateFromFile("resources/cottage_obj.obj");
  auto cottage = std::make_shared<black::GameObject>("Cottage");

  cottage->add(cottageModel);
  cottage->add(std::make_shared<black::BoundingComponent>(
      std::make_shared<black::Sphere>(cottage->transform, 12.0f)));
  cottage->transform->scale(0.1f);

  scene->addObject(std::move(cottage));
  scene->setCurrentCamera(this->camera);
}

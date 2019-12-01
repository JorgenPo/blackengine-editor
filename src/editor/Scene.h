//
// Created by popov on 13.11.2019.
//

#ifndef BLACKENGINE_EDITOR_SRC_EDITOR_SCENE_H
#define BLACKENGINE_EDITOR_SRC_EDITOR_SCENE_H

#include <BlackEngine/scene/SimpleScene.h>
#include <BlackEngine/terrain/Terrain.h>
#include <BlackEngine/render/RenderTargetInterface.h>

#include <QObject>

namespace blackeditor {

/**
 * The edtior main scene
 */
class Scene : public QObject {
  Q_OBJECT;

  std::shared_ptr<black::SimpleScene> scene;
  std::shared_ptr<black::Camera> camera;
  std::shared_ptr<black::Terrain> terrain;
  std::shared_ptr<black::GameObject> mainLight;
  std::shared_ptr<black::RenderTargetInterface> renderTarget;

  using BlackScene = std::shared_ptr<black::SimpleScene>;

public:
  Scene(std::shared_ptr<black::RenderTargetInterface> renderTarget);

  void initialize();
  [[nodiscard]] BlackScene get() const noexcept;

public slots:
  void onLightIntensityChanged(double newIntensity);
  void onAmbientIntensityChanged(double newIntensity);
  void setLightEnabled(int state);
  void updateCameraViewport(int w, int h);
};

}

#endif //BLACKENGINE_EDITOR_SRC_EDITOR_SCENE_H

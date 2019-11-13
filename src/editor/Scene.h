//
// Created by popov on 13.11.2019.
//

#ifndef BLACKENGINE_EDITOR_SRC_EDITOR_SCENE_H
#define BLACKENGINE_EDITOR_SRC_EDITOR_SCENE_H

#include <BlackEngine/scene/SimpleScene.h>

namespace blackeditor {

/**
 * The edtior main scene
 */
class Scene {
  std::shared_ptr<black::SimpleScene> scene;
  std::shared_ptr<black::Camera> camera;

  using BlackScene = std::shared_ptr<black::SimpleScene>;

public:
  Scene();

  void initialize();
  [[nodiscard]] BlackScene get() const noexcept;
};

}

#endif //BLACKENGINE_EDITOR_SRC_EDITOR_SCENE_H

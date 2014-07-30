//
//  render_delegate.h
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLTest__render_delegate__
#define __OpenGLTest__render_delegate__

#include <iostream>

#include "gameloop.hpp"

#include "../graphics/base.hpp"
#include "../graphics/shader.hpp"

#include "../scene/group.hpp"
#include "../scene/model.hpp"
#include "../scene/visitor/model_renderer.hpp"
#include "../scene/visitor/matrix_refresher.hpp"
#include "../scene/visitor/updater.hpp"

#include "../camera/camera.hpp"
#include "../camera/first_person.hpp"


#include "../input/keyboard.hpp"
#include "../input/keyboard_adapter.hpp"

#include "../input/mouse.hpp"
#include "../input/mouse_adapter.hpp"

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"


class SceneDelegate : public GameLoopDelegate {
    struct Screen {
        int width = 800;
        int height = 600;
    } screen;
    
    Keyboard keyboard;
    const KeyboardAdapter keyboardAdapter;
    
    Mouse mouse;
    const MouseAdapter mouseAdapter;
    
    struct {
        std::shared_ptr<Group> root;
        std::shared_ptr<Model> cube;
        Camera camera;
        FirstPersonMovement movement;
        ModelRenderer renderer;
        std::shared_ptr<Shader> shader;
    } scene;
    
    struct {
        glm::vec3 position;
        glm::vec3 velocity;
        glm::vec3 acceleration{0,-9,0};
    } physic;
    
    float moveDelay;
    
    MatrixRefresher refresher;
    Updater updater;
public:
    SceneDelegate();
    ~SceneDelegate();
    
    void handleEvent(SDL_Event &e);
    
    void setViewport(int w, int h);
    
    bool setup(GameLoop &l);
    
    void teardown(GameLoop &l);
    
    void beforeUpdate(GameLoop &l);

    void update(GameLoop &l);

    void render();
    
    void afterRender() const;
    
private:
    void adjustViewport() const;
};

#endif /* defined(__OpenGLTest__render_delegate__) */

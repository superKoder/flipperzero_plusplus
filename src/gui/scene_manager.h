#pragma once

#include <gui/scene_manager.h>

#if !__cplusplus
#error Only include this header in a C++17 file (does it have the right file extension?)
#endif // !__cplusplus

#include "scene.h"

namespace gui {

class SceneManager {
private:
    using RawCPtr = ::SceneManager*;
    RawCPtr raw_ptr_;

public:
    struct Handlers {
        const Scene::OnEnterCallback* on_enter_handlers;
        const Scene::OnEventCallback* on_event_handlers;
        const Scene::OnExitCallback* on_exit_handlers;
        const size_t scene_num;
    };

    inline void SetSceneState(Scene::Id scene_id, Scene::State state) {
        ::scene_manager_set_scene_state(raw_ptr_, scene_id, state);
    }

    inline Scene::State GetSceneState(Scene::Id scene_id) {
        return ::scene_manager_get_scene_state(raw_ptr_, scene_id);
    }

    inline SceneManager(const ::SceneManagerHandlers* app_scene_handlers, void* context)
        : raw_ptr_(::scene_manager_alloc(app_scene_handlers, context)) {
    }

    inline SceneManager(const SceneManager::Handlers* app_scene_handlers, void* context)
        : raw_ptr_(::scene_manager_alloc(
              reinterpret_cast<const ::SceneManagerHandlers*>(app_scene_handlers),
              context)) {
    }

    inline ~SceneManager() {
        ::scene_manager_free(raw_ptr_);
    }

    inline bool HandleCustomEvent(Scene::Event::Number custom_event_number) {
        return ::scene_manager_handle_custom_event(raw_ptr_, custom_event_number);
    }

    inline bool HandleBackEvent() {
        return ::scene_manager_handle_back_event(raw_ptr_);
    }

    inline void HandleTickEvent() {
        return ::scene_manager_handle_tick_event(raw_ptr_);
    }

    inline void NextScene(Scene::Id next_scene_id) {
        ::scene_manager_next_scene(raw_ptr_, next_scene_id);
    }

    inline bool PreviousScene() {
        return ::scene_manager_previous_scene(raw_ptr_);
    }

    inline bool HasPreviousScrene(Scene::Id scene_id) {
        return ::scene_manager_has_previous_scene(raw_ptr_, scene_id);
    }

    inline bool SearchAndSwitchToPreviousScene(Scene::Id scene_id) {
        return ::scene_manager_search_and_switch_to_previous_scene(raw_ptr_, scene_id);
    }

    inline bool
        SearchAndSwitchToPreviousSceneOneOf(const Scene::Id* scene_ids, size_t scene_ids_size) {
        return ::scene_manager_search_and_switch_to_previous_scene_one_of(
            raw_ptr_, scene_ids, scene_ids_size);
    }

    inline bool SearchAndSwitchToAnotherScene(Scene::Id scene_id) {
        return ::scene_manager_search_and_switch_to_another_scene(raw_ptr_, scene_id);
    }

    inline void Stop() {
        ::scene_manager_stop(raw_ptr_);
    }
};

} // namespace gui
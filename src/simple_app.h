#pragma once

#if !__cplusplus
#error Only include this header in a C++17 file (does it have the right file extension?)
#endif // !__cplusplus

#include <map>
#include <memory>
#include <variant>

#include "defines.h"

#ifndef TAG
#define TAG "SimpleApp"
#endif

#include "gui/scene_manager.h"
#include "gui/view_dispatcher.h"

#include "gui/button_menu.h"
#include "gui/menu.h"
#include "gui/popup.h"

namespace fz {

class SimpleApp {
public:
    gui::SceneManager scene_manager;
    gui::ViewDispatcher view_dispatcher;

    static bool OnCustomEvent(void* context, gui::ViewDispatcher::Event custom_event) {
        FURI_LOG_FUNC;
        SimpleApp* app = static_cast<SimpleApp*>(context);
        return app->scene_manager.HandleCustomEvent(custom_event);
    }

    static bool OnNavigationEvent(void* context) {
        FURI_LOG_FUNC;
        SimpleApp* app = static_cast<SimpleApp*>(context);
        return app->scene_manager.HandleBackEvent();
    }

    SimpleApp(gui::SceneManager::Handlers const& handlers)
        : scene_manager(&handlers, this) {
        FURI_LOG_FUNC;

        view_dispatcher.EnableQueue();
        view_dispatcher.SetEventCallbackContext(this);
        view_dispatcher.SetCustomEventCallback(&SimpleApp::OnCustomEvent);
        view_dispatcher.SetNavigationEventCallback(&SimpleApp::OnNavigationEvent);
    }

    ~SimpleApp() {
        FURI_LOG_FUNC;
        for(auto const& component : components_) {
            view_dispatcher.RemoveView(component.first);
        }
    }

    SimpleApp(SimpleApp const&) = delete;
    SimpleApp(SimpleApp&&) = delete;
    SimpleApp& operator=(SimpleApp const&) = delete;
    SimpleApp& operator=(SimpleApp&&) = delete;

    enum {
        DEFAULT_MENU = 0xDEFDEF01,
        DEFAULT_POPUP = 0xDEFDEF02,
    };

    inline void CreateMenu(gui::ViewDispatcher::ViewId view_id = DEFAULT_MENU) {
        Create<gui::Menu>(view_id);
    }

    inline void CreateButtonMenu(gui::ViewDispatcher::ViewId view_id = DEFAULT_MENU) {
        Create<gui::ButtonMenu>(view_id);
    }

    inline void CreatePopup(gui::ViewDispatcher::ViewId view_id = DEFAULT_MENU) {
        Create<gui::Popup>(view_id);
    }

    inline gui::Menu& GetMenu(gui::ViewDispatcher::ViewId view_id = DEFAULT_MENU) {
        return Get<gui::Menu>(view_id);
    }

    // inline gui::ButtonMenu& GetButtonMenu(gui::ViewDispatcher::ViewId view_id = DEFAULT_MENU) {
    //     return Get<gui::ButtonMenu>(view_id);
    // }

    inline gui::Popup& GetPopup(gui::ViewDispatcher::ViewId view_id = DEFAULT_MENU) {
        return Get<gui::Popup>(view_id);
    }

    int Run(gui::Scene::Id scene_id, gui::ViewDispatcher::ViewId view_id) {
        // TODO: A way to avoid the `view_id`.

        FURI_LOG_FUNC;
        furi_record_close(RECORD_GUI);

        Gui* gui = static_cast<Gui*>(furi_record_open(RECORD_GUI));
        view_dispatcher.AttachToGui(gui, gui::ViewDispatcher::Type::Fullscreen);

        view_dispatcher.SwitchToView(view_id);
        scene_manager.NextScene(scene_id);

        view_dispatcher.Run();

        furi_record_close(RECORD_GUI);

        return 0;
    }

private:
    std::map<
        gui::ViewDispatcher::ViewId,
        std::variant<std::unique_ptr<gui::Menu>, std::unique_ptr<gui::ButtonMenu>, std::unique_ptr<gui::Popup> > >
        components_;

    template <typename T>
    void Create(gui::ViewDispatcher::ViewId view_id) {
        FURI_LOG_FUNC;
        auto component = std::make_unique<T>();
        view_dispatcher.AddView(view_id, component->GetView());
        components_[view_id] = std::move(component);
    }

    template <typename T>
    T& Get(gui::ViewDispatcher::ViewId view_id) {
        FURI_LOG_FUNC;
        return *(std::get<std::unique_ptr<T> >(components_.at(view_id)));
    }
};

} // namespace fz
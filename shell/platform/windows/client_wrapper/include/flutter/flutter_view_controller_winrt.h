// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_SHELL_PLATFORM_WINDOWS_CLIENT_WRAPPER_INCLUDE_FLUTTER_FLUTTER_VIEW_CONTROLLER_WINRT_H_
#define FLUTTER_SHELL_PLATFORM_WINDOWS_CLIENT_WRAPPER_INCLUDE_FLUTTER_FLUTTER_VIEW_CONTROLLER_WINRT_H_

#include <Windows.h>
#include <flutter_windows.h>

#include <windows.ui.core.h>

#include <memory>
#include <optional>

#include "dart_project_winrt.h"
#include "flutter_engine_winrt.h"
#include "flutter_view.h"
#include "plugin_registrar.h"
#include "plugin_registry.h"

namespace flutter {

// A controller for a view displaying Flutter content.
//
// This is the primary wrapper class for the desktop C API.
// If you use this class, you should not call any of the setup or teardown
// methods in the C API directly, as this class will do that internally.
class FlutterViewControllerWinRT : public PluginRegistry {
 public:
  // Creates a FlutterView that can be parented into a Windows View hierarchy
  // either using CoreWindow, or using compositor.
  //
  // |dart_project| will be used to configure the engine backing this view.
  explicit FlutterViewControllerWinRT(
      ABI::Windows::UI::Core::CoreWindow* window,
                                 const DartProjectWinRT& project);

  virtual ~FlutterViewControllerWinRT();

  // Prevent copying.
  FlutterViewControllerWinRT(FlutterViewControllerWinRT const&) = delete;
  FlutterViewControllerWinRT& operator=(FlutterViewControllerWinRT const&) =
      delete;

  // Returns the engine running Flutter content in this view.
  FlutterEngineWinRT* engine() { return engine_.get(); }

  // Returns the view managed by this controller.
  FlutterView* view() { return view_.get(); }

  // DEPRECATED. Call engine()->ProcessMessages() instead.
  std::chrono::nanoseconds ProcessMessages();

  // DEPRECATED. Call engine()->GetRegistrarForPlugin() instead.
  FlutterDesktopPluginRegistrarRef GetRegistrarForPlugin(
      const std::string& plugin_name) override;

 private:
  // Handle for interacting with the C API's view controller, if any.
  FlutterDesktopViewControllerRef controller_ = nullptr;

  // The backing engine
  std::unique_ptr<FlutterEngineWinRT> engine_;

  // The owned FlutterView.
  std::unique_ptr<FlutterView> view_;
};

}  // namespace flutter

#endif  // FLUTTER_SHELL_PLATFORM_WINDOWS_CLIENT_WRAPPER_INCLUDE_FLUTTER_FLUTTER_VIEW_CONTROLLER_WINRT_H_
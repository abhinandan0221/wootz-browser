// Copyright 2021 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_DESKTOP_WINDOW_TREE_HOST_LACROS_H_
#define CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_DESKTOP_WINDOW_TREE_HOST_LACROS_H_

#include "base/memory/raw_ptr.h"
#include "chrome/browser/ui/views/frame/browser_desktop_window_tree_host.h"
#include "ui/views/widget/desktop_aura/desktop_window_tree_host_lacros.h"

class BrowserView;
class BrowserFrame;
class DesktopBrowserFrameLacros;
enum class TabDragKind;

namespace views {
class DesktopNativeWidgetAura;
}

class BrowserDesktopWindowTreeHostLacros
    : public BrowserDesktopWindowTreeHost,
      public views::DesktopWindowTreeHostLacros {
 public:
  BrowserDesktopWindowTreeHostLacros(
      views::internal::NativeWidgetDelegate* native_widget_delegate,
      views::DesktopNativeWidgetAura* desktop_native_widget_aura,
      BrowserView* browser_view,
      BrowserFrame* browser_frame);
  BrowserDesktopWindowTreeHostLacros(
      const BrowserDesktopWindowTreeHostLacros&) = delete;
  BrowserDesktopWindowTreeHostLacros& operator=(
      const BrowserDesktopWindowTreeHostLacros&) = delete;
  ~BrowserDesktopWindowTreeHostLacros() override;

  // Called when the tab drag status changes for this window.
  void TabDraggingKindChanged(TabDragKind tab_drag_kind);

 private:
  // BrowserDesktopWindowTreeHost:
  DesktopWindowTreeHost* AsDesktopWindowTreeHost() override;
  int GetMinimizeButtonOffset() const override;
  bool UsesNativeSystemMenu() const override;

  // views::DesktopWindowTreeHostPlatform:
  SkPath GetWindowMaskForClipping() const override;
  void OnSurfaceFrameLockingChanged(bool lock) override;
  bool SupportsMouseLock() override;
  void LockMouse(aura::Window* window) override;
  void UnlockMouse(aura::Window* window) override;

  // ui::PlatformWindowDelegate
  void OnWindowStateChanged(ui::PlatformWindowState old_state,
                            ui::PlatformWindowState new_state) override;
  void OnFullscreenTypeChanged(ui::PlatformFullscreenType old_type,
                               ui::PlatformFullscreenType new_type) override;

  const raw_ptr<BrowserView> browser_view_;
  raw_ptr<DesktopBrowserFrameLacros> native_frame_ = nullptr;
  raw_ptr<views::DesktopNativeWidgetAura> desktop_native_widget_aura_ = nullptr;
};

#endif  // CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_DESKTOP_WINDOW_TREE_HOST_LACROS_H_

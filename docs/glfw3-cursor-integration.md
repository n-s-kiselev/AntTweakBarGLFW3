# AntTweakBar custom cursors with GLFW3

## Confirmed problem

AntTweakBar predates GLFW3 and changes the system cursor directly through
Win32, AppKit, or Xlib. GLFW3 owns cursor state through `glfwCreateCursor()`
and `glfwSetCursor()`. Bypassing that ownership model produces the same user
symptom on macOS and Linux: AntTweakBar's custom resize, hand, point, and
rotation cursors are not rendered reliably.

The immediate platform mechanisms differ:

- On macOS, AntTweakBar successfully calls `[NSCursor set]`, but GLFW3's Cocoa
  view installs an `NSTrackingArea` with `NSTrackingCursorUpdate`.
  `cursorUpdate:` calls GLFW3's `updateCursorImage()`. When the application
  has not called `glfwSetCursor()`, GLFW3 records a null cursor and explicitly
  restores the arrow, overwriting AntTweakBar's choice.
- On Linux/X11, AntTweakBar historically discovers a target using
  `glXGetCurrentDrawable()`. GLFW3 may make a separate `GLXWindow` current;
  that resource is not the X11 `Window` required by `XDefineCursor()`. Native
  window discovery is therefore toolkit-dependent and unreliable.

GLFW2 works because its older backends do not create either conflict: Cocoa
does not reassert cursor ownership, and X11 binds the context directly to the
real window.

## Recommended future design

Correct AntTweakBar itself without adding a hard GLFW dependency. Add an
optional public cursor callback that reports the semantic cursor requested by
AntTweakBar plus client data. When installed, AntTweakBar invokes the callback
instead of its native `SetCursor` path. When absent, existing native behavior
remains unchanged for GLUT, GLFW2, and legacy applications.

The GLFW3 binding should:

1. Create and cache standard and custom `GLFWcursor` objects, converting the
   existing AntTweakBar cursor masks/images to RGBA where necessary.
2. Translate each semantic AntTweakBar cursor request to the cached object.
3. Apply it with `glfwSetCursor(window, cursor)`.
4. Destroy cached cursors during binding shutdown.

Prototype this with `TwAdvanced1` first on macOS and Linux. After both
platforms confirm correct rendering, apply the binding to the remaining GLFW3
examples. This preserves AntTweakBar's toolkit independence while giving
GLFW3 authoritative cursor ownership.

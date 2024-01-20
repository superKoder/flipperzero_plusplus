# FlipperZero++ (flipperzero_plusplus)
**Object-Oriented C++ wrapper around FlipperZero's C library.**

Write FlipperZero apps in modern object-oriented code, without any overhead!

## Advantages
* **Objects with methods**: Write `popup.SetIcon({x, y}, icon)` istead of `popup_set_icon(&popup, x, y, icon)` (but you can do both).
* **Easy memory management**: Constructors and destructors do the allocation and deallocation for you.
* **Forget raw pointers**: Pass by reference, rather than pointer.
* **Zero overhead**: Compiles down to the exact same machine code. There is no price to pay.
* **Just works**: Continue to use `ufbt` and its VSCode integrations, no need for another toolchain. 
* **C still works too**: The original C header is #included by the C++ version. So you have access to both.
* **Bug-for-bug**: No added logic, so no new bugs. And all upstream updates are still updates.
* **Permissinve license**: Go ahead! Use it, change it, improve it! (Please contribute your improvements?)

## What is it not?

* Complete. It is very early progress. I am going in the order of the popular, existing tutorials of the C version.
* Well-documented. The original C library is very poorly documented, and this C++ wrapper does not (try) to fix that in any way.


## How to use?

These files are in addition to the original `f7_sdk` that you would get when you use `ufbt`.

1. Start you project with (like you normally would)
```
ufbt create APPID=your_unique_app_id
```

2. Make a directory to house these C++ wrappers: 
```
mkdir fz++
```

3. Copy all the files from my `src/` over to your the newly created `fz++/` dir, including all subdirectories.

4. Include them as:
```
#include "fz++/gui/popup.h"
#include "fz++/gui/menu.h"
...
```
They will include their C counterparts themselves. So you will have access to both C and C++ versions of everything (and yes, those can interoperate!).

For the C++ versions, don't forget to use their namespaces! (e.g. `gui::Menu` is the C++ version, the original `Menu` is the C version)

Enjoy!
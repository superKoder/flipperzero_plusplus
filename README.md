# FlipperZero++ (flipperzero_plusplus)
**A zero-cost C++ wrapper for FlipperZero's C library!**

## What is this?
A modern, object-oriented way to code apps for your FlipperZero device! Without having to deal with raw C pointers and their allocation/deallocation. 

It is built as a hand-written, 1-to-1 object wrapper to FlipperZero's official `f7_sdk` C library. Hiding the C details on the inside. All without paying any additional cost. These are inlined header-only wrappers that don't add any additional code (unless where it gives additional value). So there really is no reason why you should not use them instead of the C solution.

It has a permissive license. Feel free to use. Feel free to change. But if you make real improvements, please contribute back to this project.

## What is it not?

- Complete. It is very early progress. I am going in the order of the popular, existing tutorials of the C version.
- Well-documented. The original C library is very poorly documented, and this C++ wrapper does not (try) to fix that in any way.


## How to use?

These files go in addition to the original `f7_sdk` that you would get when you use `ufbt`.

1. Start you project with 
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
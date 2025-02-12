# MoL  ̶g̶a̶m̶e̶(physics) engine

This is(more and less) my first attempt creating a real game engine. All other stupid attempts were inside other game engines, so I don't consider them too much. And that's not even the first version of the "real" MoL; it's probably the fourth version of this engine, going through versions in C++ and even using Vulkan.

Thus, the code will obviously suck -- and, actually, it already does. I won't pretend -- especially for myself -- that I can write good code when I simply can't. So, do expect unsafe code, grotesque errors regarding to optimization and building and many more.

Furthermore, I'm going to try not to suddenly rewrite this engine again, but I don't promise anything.

## How to build

No silly build tools or anything. Just compiling and running. That should be something to think about.

Dependencies:
- glfw;
- glad;

Command to build (compile and run):
> ./build.sh --b

Command only to compile:
> ./build.sh --c

Command only to run:
> ./build.sh --r


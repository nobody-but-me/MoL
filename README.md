# MoL ̶p̶h̶y̶s̶i̶c̶s̶(game) engine

This is(more and less) my first attempt creating a real game engine. All other attempts were inside other game engines, so I do not consider them too much. And that is not even the first version of the "real" MoL; it is probably the fourth version of this engine, going through versions in C++ and even Vulkan.

Thus, the code will obviously suck -- and, actually, it already does. I will not pretend -- especially for myself -- that I can write good code when I simply can't. So, do expect unsafe code, grotesque errors regarding to optimization and building and many more.

Furthermore, I am going to try not to suddenly rewrite this engine again, but I do not promise it.

## How to build

No silly build tools or anything. Just compiling and running through a very, very simple bash script. This should be something to think about...

Dependencies(I feel like I am forgetting something):
- glfw;
- glad;

First of all, you are going to need to create a build folder:
> mkdir build

Command to build (compile and run):
> ./build.sh --b

Command only to compile:
> ./build.sh --c

Command only to run:
> ./build.sh --r


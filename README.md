[![](https://jitpack.io/v/jaquobia/frankinglfw.svg)](https://jitpack.io/#jaquobia/frankinglfw)

# frankinglfw
A rudimentary fork? of JGLFW to modern glfw
Named as frankin from frankenstein (yes its mispelled), since its a cursed port of an older java library to a newer c++ glfw version

# Why was this made?
I wanted to try rewriting minecraft b1.7.3 to use glfw instead of java applets, but came across the issue that b1.7.3 was written in lwjgl2, which had no glfw.  
When looking for a java glfw library, all I could find was lwjgl3 (which can't load beside lwjgl2) and jglfw (which is mightily outdated)

# Using this with JOGL
```java   
Glfw.glfwMakeContextCurrent(window);
GLContext glContext = GLDrawableFactory.getFactory(GLProfile.get(GLProfile.GL3)).createExternalGLContext();
if (!glContext.isCurrent())
    glContext.makeCurrent();
Glfw.glfwShowWindow(window);
GL3 gl = glContext.getGL().getGL3();
```

# Side Notes
- This is my first repo I tried using releases because I wanted to try using jitpack, which doesn't work
- I show jogl example code because I needed something to test the gl context, as lwjgl2 requires a lot more hack-work to function without a display
- **There is only a .so as I've only built for linux, possible dll for windows in the future, but im lazy af**

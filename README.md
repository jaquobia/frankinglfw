[![](https://jitpack.io/v/jaquobia/frankinglfw.svg)](https://jitpack.io/#jaquobia/frankinglfw)
![GitHub Workflow Status](https://img.shields.io/github/workflow/status/jaquobia/frankinglfw/Java%20CI%20with%20Gradle)

# frankinglfw
A cursed port of [JGLFW](https://github.com/badlogic/jglfw) to modern [glfw](https://github.com/glfw/glfw) 3.4  
Named as frankin from frankenstein (yes its mispelled), since its a cursed port of an older java library to a newer c++ glfw version

# Why was this made?
I wanted to try rewriting minecraft b1.7.3 to use glfw instead of java applets, but came across the issue that b1.7.3 was written in lwjgl2, which had no glfw.  
When looking for a java glfw library, all I could find was lwjgl3 (which can't load beside lwjgl2) and jglfw (which is mightily outdated)
# Including in project
```gradle
repositories {
    maven { url "https://jitpack.io" }
}
dependencies {
    implementation 'com.github.jaquobia:frankinglfw:v1.3.3'
}
```
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
- First time using jitpack and releases/tags
- I show jogl example code because I needed something to test the gl context, as lwjgl2 requires a lot more hack-work to function without a display

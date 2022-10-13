import com.jogamp.opengl.*;
import io.github.jaquobia.Glfw;
import io.github.jaquobia.GlfwCallback;

import java.util.logging.Logger;

public class Main {
    public static Logger logger = Logger.getLogger("Test");

    public static void main(String[] args) {
        Glfw.glfwInit();
        Glfw.glfwDefaultWindowHints();
        GlfwCallback callback = getCallback();
        Glfw.glfwSetCallback(callback);
        Glfw.glfwWindowHint(Glfw.GLFW_OPENGL_FORWARD_COMPAT, 1);
        Glfw.glfwWindowHint(Glfw.GLFW_OPENGL_PROFILE, Glfw.GLFW_OPENGL_COMPAT_PROFILE);
        Glfw.glfwWindowHint(Glfw.GLFW_CONTEXT_VERSION_MAJOR, 3);
        Glfw.glfwWindowHint(Glfw.GLFW_CONTEXT_VERSION_MINOR, 3);

        long window = Glfw.glfwCreateWindow(800, 600, "Demo", 0, 0);
        Glfw.glfwMakeContextCurrent(window);
        GLContext glContext = GLDrawableFactory.getFactory(GLProfile.get(GLProfile.GL3)).createExternalGLContext();
        if (!glContext.isCurrent())
            glContext.makeCurrent();
        Glfw.glfwShowWindow(window);

        GL3 gl = glContext.getGL().getGL3();
        gl.glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
        gl.glViewport(0, 0, 100, 100);
        while (!Glfw.glfwWindowShouldClose(window)) {
            gl.glClear(GL.GL_COLOR_BUFFER_BIT);
            Glfw.glfwPollEvents();
            Glfw.glfwSwapBuffers(window);
        }
        glContext.destroy();
    }

    public static GlfwCallback getCallback() {
        return new GlfwCallback() {
            @Override
            public void error(int error, String description) {

            }

            @Override
            public void monitor(long monitor, boolean connected) {

            }

            @Override
            public void windowPos(long window, int x, int y) {

            }

            @Override
            public void windowSize(long window, int width, int height) {
                logger.fine("Window Size: " + width + " " + height);
            }

            @Override
            public void windowClose(long window) {
                logger.fine("Window Close");
            }

            @Override
            public void windowRefresh(long window) {

            }

            @Override
            public void windowFocus(long window, boolean focused) {

            }

            @Override
            public void windowIconify(long window, boolean iconified) {

            }

            @Override
            public void key(long window, int key, int scancode, int action, int mods) {

            }

            @Override
            public void character(long window, char character) {

            }

            @Override
            public void mouseButton(long window, int button, boolean pressed, int mods) {

            }

            @Override
            public void cursorPos(long window, double x, double y) {

            }

            @Override
            public void cursorEnter(long window, boolean entered) {

            }

            @Override
            public void scroll(long window, double scrollX, double scrollY) {

            }
        };
    }


}

package io.github.jaquobia;

/**
 * Registered with Glfw3#glfwSetCallback(), reacts to all
 * callback events of Glfw
 * @author mzechner
 *
 */
public interface GlfwCallback {
	/**
	 * Called in case of an error, on the thread
	 * the error was generated on.
	 * @param error the error code
	 * @param description the description of the error
	 */
	void error(int error, String description);

	/**
	 * Called when the position of a window changed
	 * @param window the window handle
	 * @param x the new x coordinate, in pixels, of the top left corner of the client area of the window
	 * @param y the new y coordinate, in pixels, of the top left corner of the client area of the window
	 */
	void windowPos(long window, int x, int y);
	
	/**
	 * Called when the size of the window changed
	 * @param window the window handle
	 * @param width the new width in pixels
	 * @param height the new height in pixels
	 */
	void windowSize(long window, int width, int height);
	
	/**
	 * Called when the window should be closed.
	 * @param window the window handle
	 */
	void windowClose(long window);
	
	/**
	 * Called when the window content needs to be refreshed
	 * @param window the window handle
	 */
	void windowRefresh(long window);
	
	/**
	 * Called when the focus of the window changed
	 * @param window the window handle
	 * @param focused whether the window is focused
	 */
	void windowFocus(long window, boolean focused);
	
	/**
	 * Called when the window is (de-)iconified
	 * @param window the window handle
	 * @param iconified whether the window is iconified
	 */
	void windowIconify(long window, boolean iconified);

	/**
	 * Called when the window is (de-)maximized
	 * @param window the window handle
	 * @param maximized whether the window is maximized
	 */
	void windowMaximize(long window, boolean maximized);

	/**
	 * Called when the window framebuffer is resized
	 * @param window the window handle
	 * @param width width of the new framebuffer
	 * @param height height of the new framebuffer
	 */
	void windowFramebufferSize(long window, int width, int height);

	/**
	 * Called when the window content scale is changed
	 * @param window the window handle
	 * @param xScale new x-axis scale content scale of the window
	 * @param yScale new y-axis scale content scale of the window
	 */
	void windowContentScale(long window, float xScale, float yScale);

	/**
	 * Called when a mouse button was pressed or released
	 * @param window the window handle
	 * @param button the button id
	 * @param pressed whether the button was pressed (true) or released (false)
	 */
	void mouseButton(long window, int button, boolean pressed, int mods);

	/**
	 * Called when the mouse cursor moved
	 * @param window the window
	 * @param x the x-coordinate in client area coordinates
	 * @param y the y-coordinate in client area coordinates
	 */
	void cursorPos(long window, double x, double y);

	/**
	 * Called when the mouse entered the client area
	 * @param window the window handle
	 * @param entered whether the mouse cursor entered or left the window
	 */
	void cursorEnter(long window, boolean entered);

	/**
	 * Called when the mouse wheel was scrolled
	 * @param window the window handle
	 * @param scrollX The scroll offset along the x-axis.
	 * @param scrollY The scroll offset along the y-axis.
	 */
	void scroll(long window, double scrollX, double scrollY);
	
	/**
	 * Called when a key was pressed or released
	 * @param window the window handle
	 * @param key the key code
	 * @param scancode the scan code as reported by the OS
	 * @param action whether the key was pressed (GLFW_PRESSED), released (GLFW_RELEASE) or repeated (GLFW_REPEAT)
	 * @param mods the modifier flags
	 */
	void key(long window, int key, int scancode, int action, int mods);
	
	/**
	 * Called when a Unicode character was generated by the keyboard
	 * @param window the window handle
	 * @param codepoint the Unicode character
	 */
	void character(long window, int codepoint);

	/**
	 * Called when a Unicode character was generated by the keyboard with mods
	 * @param window the window handle
	 * @param codepoint the Unicode character
	 * @param mods key mods
	 */
	void characterMods(long window, int codepoint, int mods);

	/**
	 *
	 * @param window the window handle
	 * @param paths the paths array
	 */
	void drop(long window, String[] paths);

	/**
	 * Called when a monitor was connected/disconnected
	 * @param monitor the monitor handle
	 * @param connected whether the monitor was connected or disconnected
	 */
	void monitor(long monitor, boolean connected);

	/**
	 *
	 * @param jid id of the joystick
	 * @param event event of the joystick
	 */
	void joystick(int jid, int event);
}

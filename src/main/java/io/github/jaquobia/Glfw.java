package io.github.jaquobia;

import java.util.ArrayList;
import java.util.List;

public class Glfw {

	static {
		try {
			// https://github.com/adamheinrich/native-utils
			NativeUtils.loadLibraryFromJar("/libFrankinGlfw.so");
		} catch (Exception e) {e.printStackTrace();}
	}


	public static final int GLFW_VERSION_MAJOR = 3;
	public static final int GLFW_VERSION_MINOR = 4;
	public static final int GLFW_VERSION_REVISION = 0;

	public static final int GLFW_TRUE = 1;
	public static final int GLFW_FALSE = 0;

	public static final int GLFW_RELEASE = 0;
	public static final int GLFW_PRESS = 1;
	public static final int GLFW_REPEAT = 2;

	public static final int GLFW_HAT_CENTERED = 0;
	public static final int GLFW_HAT_UP = 1;
	public static final int GLFW_HAT_RIGHT = 2;
	public static final int GLFW_HAT_DOWN = 4;
	public static final int GLFW_HAT_LEFT = 8;
	public static final int GLFW_HAT_RIGHT_UP = (GLFW_HAT_RIGHT | GLFW_HAT_UP);
	public static final int GLFW_HAT_RIGHT_DOWN = (GLFW_HAT_RIGHT | GLFW_HAT_DOWN);
	public static final int GLFW_HAT_LEFT_UP = (GLFW_HAT_LEFT  | GLFW_HAT_UP);
	public static final int GLFW_HAT_LEFT_DOWN = (GLFW_HAT_LEFT  | GLFW_HAT_DOWN);

	public static final int GLFW_KEY_UNKNOWN = -1;

	public static final int GLFW_KEY_SPACE = 32;
	public static final int GLFW_KEY_APOSTROPHE = 39 /* ' */;
	public static final int GLFW_KEY_COMMA = 44 /* , */;
	public static final int GLFW_KEY_MINUS = 45 /* - */;
	public static final int GLFW_KEY_PERIOD = 46 /* . */;
	public static final int GLFW_KEY_SLASH = 47 /* / */;
	public static final int GLFW_KEY_0 = 48;
	public static final int GLFW_KEY_1 = 49;
	public static final int GLFW_KEY_2 = 50;
	public static final int GLFW_KEY_3 = 51;
	public static final int GLFW_KEY_4 = 52;
	public static final int GLFW_KEY_5 = 53;
	public static final int GLFW_KEY_6 = 54;
	public static final int GLFW_KEY_7 = 55;
	public static final int GLFW_KEY_8 = 56;
	public static final int GLFW_KEY_9 = 57;
	public static final int GLFW_KEY_SEMICOLON = 59 /* ; */;
	public static final int GLFW_KEY_EQUAL = 61 /* = */;
	public static final int GLFW_KEY_A = 65;
	public static final int GLFW_KEY_B = 66;
	public static final int GLFW_KEY_C = 67;
	public static final int GLFW_KEY_D = 68;
	public static final int GLFW_KEY_E = 69;
	public static final int GLFW_KEY_F = 70;
	public static final int GLFW_KEY_G = 71;
	public static final int GLFW_KEY_H = 72;
	public static final int GLFW_KEY_I = 73;
	public static final int GLFW_KEY_J = 74;
	public static final int GLFW_KEY_K = 75;
	public static final int GLFW_KEY_L = 76;
	public static final int GLFW_KEY_M = 77;
	public static final int GLFW_KEY_N = 78;
	public static final int GLFW_KEY_O = 79;
	public static final int GLFW_KEY_P = 80;
	public static final int GLFW_KEY_Q = 81;
	public static final int GLFW_KEY_R = 82;
	public static final int GLFW_KEY_S = 83;
	public static final int GLFW_KEY_T = 84;
	public static final int GLFW_KEY_U = 85;
	public static final int GLFW_KEY_V = 86;
	public static final int GLFW_KEY_W = 87;
	public static final int GLFW_KEY_X = 88;
	public static final int GLFW_KEY_Y = 89;
	public static final int GLFW_KEY_Z = 90;
	public static final int GLFW_KEY_LEFT_BRACKET = 91 /* [ */;
	public static final int GLFW_KEY_BACKSLASH = 92 /* \ */;
	public static final int GLFW_KEY_RIGHT_BRACKET = 93 /* ] */;
	public static final int GLFW_KEY_GRAVE_ACCENT = 96 /* ` */;
	public static final int GLFW_KEY_WORLD_1 = 161 /* non-US #1 */;
	public static final int GLFW_KEY_WORLD_2 = 162 /* non-US #2 */;

	/* Function keys */
	public static final int GLFW_KEY_ESCAPE = 256;
	public static final int GLFW_KEY_ENTER = 257;
	public static final int GLFW_KEY_TAB = 258;
	public static final int GLFW_KEY_BACKSPACE = 259;
	public static final int GLFW_KEY_INSERT = 260;
	public static final int GLFW_KEY_DELETE = 261;
	public static final int GLFW_KEY_RIGHT = 262;
	public static final int GLFW_KEY_LEFT = 263;
	public static final int GLFW_KEY_DOWN = 264;
	public static final int GLFW_KEY_UP = 265;
	public static final int GLFW_KEY_PAGE_UP = 266;
	public static final int GLFW_KEY_PAGE_DOWN = 267;
	public static final int GLFW_KEY_HOME = 268;
	public static final int GLFW_KEY_END = 269;
	public static final int GLFW_KEY_CAPS_LOCK = 280;
	public static final int GLFW_KEY_SCROLL_LOCK = 281;
	public static final int GLFW_KEY_NUM_LOCK = 282;
	public static final int GLFW_KEY_PRINT_SCREEN = 283;
	public static final int GLFW_KEY_PAUSE = 284;
	public static final int GLFW_KEY_F1 = 290;
	public static final int GLFW_KEY_F2 = 291;
	public static final int GLFW_KEY_F3 = 292;
	public static final int GLFW_KEY_F4 = 293;
	public static final int GLFW_KEY_F5 = 294;
	public static final int GLFW_KEY_F6 = 295;
	public static final int GLFW_KEY_F7 = 296;
	public static final int GLFW_KEY_F8 = 297;
	public static final int GLFW_KEY_F9 = 298;
	public static final int GLFW_KEY_F10 = 299;
	public static final int GLFW_KEY_F11 = 300;
	public static final int GLFW_KEY_F12 = 301;
	public static final int GLFW_KEY_F13 = 302;
	public static final int GLFW_KEY_F14 = 303;
	public static final int GLFW_KEY_F15 = 304;
	public static final int GLFW_KEY_F16 = 305;
	public static final int GLFW_KEY_F17 = 306;
	public static final int GLFW_KEY_F18 = 307;
	public static final int GLFW_KEY_F19 = 308;
	public static final int GLFW_KEY_F20 = 309;
	public static final int GLFW_KEY_F21 = 310;
	public static final int GLFW_KEY_F22 = 311;
	public static final int GLFW_KEY_F23 = 312;
	public static final int GLFW_KEY_F24 = 313;
	public static final int GLFW_KEY_F25 = 314;
	public static final int GLFW_KEY_KP_0 = 320;
	public static final int GLFW_KEY_KP_1 = 321;
	public static final int GLFW_KEY_KP_2 = 322;
	public static final int GLFW_KEY_KP_3 = 323;
	public static final int GLFW_KEY_KP_4 = 324;
	public static final int GLFW_KEY_KP_5 = 325;
	public static final int GLFW_KEY_KP_6 = 326;
	public static final int GLFW_KEY_KP_7 = 327;
	public static final int GLFW_KEY_KP_8 = 328;
	public static final int GLFW_KEY_KP_9 = 329;
	public static final int GLFW_KEY_KP_DECIMAL = 330;
	public static final int GLFW_KEY_KP_DIVIDE = 331;
	public static final int GLFW_KEY_KP_MULTIPLY = 332;
	public static final int GLFW_KEY_KP_SUBTRACT = 333;
	public static final int GLFW_KEY_KP_ADD = 334;
	public static final int GLFW_KEY_KP_ENTER = 335;
	public static final int GLFW_KEY_KP_EQUAL = 336;
	public static final int GLFW_KEY_LEFT_SHIFT = 340;
	public static final int GLFW_KEY_LEFT_CONTROL = 341;
	public static final int GLFW_KEY_LEFT_ALT = 342;
	public static final int GLFW_KEY_LEFT_SUPER = 343;
	public static final int GLFW_KEY_RIGHT_SHIFT = 344;
	public static final int GLFW_KEY_RIGHT_CONTROL = 345;
	public static final int GLFW_KEY_RIGHT_ALT = 346;
	public static final int GLFW_KEY_RIGHT_SUPER = 347;
	public static final int GLFW_KEY_MENU = 348;
	public static final int GLFW_KEY_LAST = GLFW_KEY_MENU;

	public static final int GLFW_KEY_ESC = GLFW_KEY_ESCAPE;
	public static final int GLFW_KEY_DEL = GLFW_KEY_DELETE;
	public static final int GLFW_KEY_PAGEUP = GLFW_KEY_PAGE_UP;
	public static final int GLFW_KEY_PAGEDOWN = GLFW_KEY_PAGE_DOWN;
	public static final int GLFW_KEY_KP_NUM_LOCK = GLFW_KEY_NUM_LOCK;
	public static final int GLFW_KEY_LCTRL = GLFW_KEY_LEFT_CONTROL;
	public static final int GLFW_KEY_LSHIFT = GLFW_KEY_LEFT_SHIFT;
	public static final int GLFW_KEY_LALT = GLFW_KEY_LEFT_ALT;
	public static final int GLFW_KEY_LSUPER = GLFW_KEY_LEFT_SUPER;
	public static final int GLFW_KEY_RCTRL = GLFW_KEY_RIGHT_CONTROL;
	public static final int GLFW_KEY_RSHIFT = GLFW_KEY_RIGHT_SHIFT;
	public static final int GLFW_KEY_RALT = GLFW_KEY_RIGHT_ALT;
	public static final int GLFW_KEY_RSUPER = GLFW_KEY_RIGHT_SUPER;

	public static final int GLFW_MOD_SHIFT 		= 0x0001;
	public static final int GLFW_MOD_CONTROL 	= 0x0002;
	public static final int GLFW_MOD_ALT 		= 0x0004;
	public static final int GLFW_MOD_SUPER 		= 0x0008;
	public static final int GLFW_MOD_CAPS_LOCK	= 0x0010;
	public static final int GLFW_MOD_NUM_LOCK	= 0x0020;


	public static final int GLFW_MOUSE_BUTTON_1 = 0;
	public static final int GLFW_MOUSE_BUTTON_2 = 1;
	public static final int GLFW_MOUSE_BUTTON_3 = 2;
	public static final int GLFW_MOUSE_BUTTON_4 = 3;
	public static final int GLFW_MOUSE_BUTTON_5 = 4;
	public static final int GLFW_MOUSE_BUTTON_6 = 5;
	public static final int GLFW_MOUSE_BUTTON_7 = 6;
	public static final int GLFW_MOUSE_BUTTON_8 = 7;
	public static final int GLFW_MOUSE_BUTTON_LAST = GLFW_MOUSE_BUTTON_8;
	public static final int GLFW_MOUSE_BUTTON_LEFT = GLFW_MOUSE_BUTTON_1;
	public static final int GLFW_MOUSE_BUTTON_RIGHT = GLFW_MOUSE_BUTTON_2;
	public static final int GLFW_MOUSE_BUTTON_MIDDLE = GLFW_MOUSE_BUTTON_3;

	public static final int GLFW_JOYSTICK_1 = 0;
	public static final int GLFW_JOYSTICK_2 = 1;
	public static final int GLFW_JOYSTICK_3 = 2;
	public static final int GLFW_JOYSTICK_4 = 3;
	public static final int GLFW_JOYSTICK_5 = 4;
	public static final int GLFW_JOYSTICK_6 = 5;
	public static final int GLFW_JOYSTICK_7 = 6;
	public static final int GLFW_JOYSTICK_8 = 7;
	public static final int GLFW_JOYSTICK_9 = 8;
	public static final int GLFW_JOYSTICK_10 = 9;
	public static final int GLFW_JOYSTICK_11 = 10;
	public static final int GLFW_JOYSTICK_12 = 11;
	public static final int GLFW_JOYSTICK_13 = 12;
	public static final int GLFW_JOYSTICK_14 = 13;
	public static final int GLFW_JOYSTICK_15 = 14;
	public static final int GLFW_JOYSTICK_16 = 15;
	public static final int GLFW_JOYSTICK_LAST = GLFW_JOYSTICK_16;

	public static final int GLFW_GAMEPAD_BUTTON_A = 0;
	public static final int GLFW_GAMEPAD_BUTTON_B = 1;
	public static final int GLFW_GAMEPAD_BUTTON_X = 2;
	public static final int GLFW_GAMEPAD_BUTTON_Y = 3;
	public static final int GLFW_GAMEPAD_BUTTON_LEFT_BUMPER = 4;
	public static final int GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER = 5;
	public static final int GLFW_GAMEPAD_BUTTON_BACK = 6;
	public static final int GLFW_GAMEPAD_BUTTON_START = 7;
	public static final int GLFW_GAMEPAD_BUTTON_GUIDE = 8;
	public static final int GLFW_GAMEPAD_BUTTON_LEFT_THUMB = 9;
	public static final int GLFW_GAMEPAD_BUTTON_RIGHT_THUMB = 10;
	public static final int GLFW_GAMEPAD_BUTTON_DPAD_UP = 11;
	public static final int GLFW_GAMEPAD_BUTTON_DPAD_RIGHT = 12;
	public static final int GLFW_GAMEPAD_BUTTON_DPAD_DOWN = 13;
	public static final int GLFW_GAMEPAD_BUTTON_DPAD_LEFT = 14;
	public static final int GLFW_GAMEPAD_BUTTON_LAST = GLFW_GAMEPAD_BUTTON_DPAD_LEFT;

	public static final int GLFW_GAMEPAD_BUTTON_CROSS = GLFW_GAMEPAD_BUTTON_A;
	public static final int GLFW_GAMEPAD_BUTTON_CIRCLE = GLFW_GAMEPAD_BUTTON_B;
	public static final int GLFW_GAMEPAD_BUTTON_SQUARE = GLFW_GAMEPAD_BUTTON_X;
	public static final int GLFW_GAMEPAD_BUTTON_TRIANGLE = GLFW_GAMEPAD_BUTTON_Y;

	public static final int GLFW_GAMEPAD_AXIS_LEFT_X = 0;
	public static final int GLFW_GAMEPAD_AXIS_LEFT_Y = 1;
	public static final int GLFW_GAMEPAD_AXIS_RIGHT_X = 2;
	public static final int GLFW_GAMEPAD_AXIS_RIGHT_Y = 3;
	public static final int GLFW_GAMEPAD_AXIS_LEFT_TRIGGER = 4;
	public static final int GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER = 5;
	public static final int GLFW_GAMEPAD_AXIS_LAST = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER;

	public static final int GLFW_NO_ERROR = 0;

	public static final int GLFW_NOT_INITIALIZED = 0x00010001;

	public static final int GLFW_NO_CURRENT_CONTEXT = 0x00010002;

	public static final int GLFW_INVALID_ENUM = 0x00010003;

	public static final int GLFW_INVALID_VALUE = 0x00010004;

	public static final int GLFW_OUT_OF_MEMORY = 0x00010005;

	public static final int GLFW_API_UNAVAILABLE = 0x00010006;

	public static final int GLFW_VERSION_UNAVAILABLE = 0x00010007;

	public static final int GLFW_PLATFORM_ERROR = 0x00010008;

	public static final int GLFW_FORMAT_UNAVAILABLE = 0x00010009;
	public static final int GLFW_NO_WINDOW_CONTEXT = 0x0001000A;
	public static final int GLFW_CURSOR_UNAVAILABLE = 0x0001000B;
	public static final int GLFW_FEATURE_UNAVAILABLE = 0x0001000C;
	public static final int GLFW_FEATURE_UNIMPLEMENTED = 0x0001000D;
	public static final int GLFW_PLATFORM_UNAVAILABLE = 0x0001000E;

	public static final int GLFW_FOCUSED = 0x00020001;
	public static final int GLFW_ICONIFIED = 0x00020002;
	public static final int GLFW_RESIZABLE = 0x00020003;
	public static final int GLFW_VISIBLE = 0x00020004;
	public static final int GLFW_DECORATED = 0x00020005;
	public static final int GLFW_AUTO_ICONIFY = 0x00020006;
	public static final int GLFW_FLOATING = 0x00020007;
	public static final int GLFW_MAXIMIZED = 0x00020008;
	public static final int GLFW_CENTER_CURSOR = 0x00020009;
	public static final int GLFW_TRANSPARENT_FRAMEBUFFER = 0x0002000A;
	public static final int GLFW_HOVERED = 0x0002000B;
	public static final int GLFW_FOCUS_ON_SHOW = 0x0002000C;
	public static final int GLFW_MOUSE_PASSTHROUGH = 0x0002000D;
	public static final int GLFW_POSITION_X = 0x0002000E;
	public static final int GLFW_POSITION_Y = 0x0002000F;
	public static final int GLFW_RED_BITS = 0x00021001;
	public static final int GLFW_GREEN_BITS = 0x00021002;
	public static final int GLFW_BLUE_BITS = 0x00021003;
	public static final int GLFW_ALPHA_BITS = 0x00021004;
	public static final int GLFW_DEPTH_BITS = 0x00021005;
	public static final int GLFW_STENCIL_BITS = 0x00021006;
	public static final int GLFW_ACCUM_RED_BITS = 0x00021007;
	public static final int GLFW_ACCUM_GREEN_BITS = 0x00022008;
	public static final int GLFW_ACCUM_BLUE_BITS = 0x00021009;
	public static final int GLFW_ACCUM_ALPHA_BITS = 0x0002100A;
	public static final int GLFW_AUX_BUFFERS = 0x0002100B;
	public static final int GLFW_STEREO = 0x0002100C;
	public static final int GLFW_SAMPLES = 0x0002100D;
	public static final int GLFW_SRGB_CAPABLE = 0x0002100E;
	public static final int GLFW_REFRESH_RATE = 0x0002100F;
	public static final int GLFW_DOUBLEBUFFER = 0x00021010;

	public static final int GLFW_CLIENT_API = 0x00022001;
	public static final int GLFW_CONTEXT_VERSION_MAJOR = 0x00022002;
	public static final int GLFW_CONTEXT_VERSION_MINOR = 0x00022003;
	public static final int GLFW_CONTEXT_REVISION = 0x00022004;
	public static final int GLFW_CONTEXT_ROBUSTNESS = 0x00022005;
	public static final int GLFW_OPENGL_FORWARD_COMPAT = 0x00022006;
	public static final int GLFW_CONTEXR_DEBUG = 0x00022007;
	public static final int GLFW_OPENGL_DEBUG_CONTEXT = GLFW_CONTEXR_DEBUG;
	public static final int GLFW_OPENGL_PROFILE = 0x00022008;
	public static final int GLFW_CONTEXT_RELEASE_BEHAVIOR = 0x00022009;
	public static final int GLFW_CONTEXT_NO_ERROR       = 0x0002200A;
	public static final int GLFW_CONTEXT_CREATION_API   = 0x0002200B;
	public static final int GLFW_SCALE_TO_MONITOR       = 0x0002200C;
	public static final int GLFW_COCOA_RETINA_FRAMEBUFFER = 0x00023001;
	public static final int GLFW_COCOA_FRAME_NAME         = 0x00023002;
	public static final int GLFW_COCOA_GRAPHICS_SWITCHING = 0x00023003;
	public static final int GLFW_X11_CLASS_NAME         = 0x00024001;
	public static final int GLFW_X11_INSTANCE_NAME      = 0x00024002;
	public static final int GLFW_WIN32_KEYBOARD_MENU    = 0x00025001;
	public static final int GLFW_WAYLAND_APP_ID         = 0x00026001;
	public static final int GLFW_NO_API                          = 0;

	public static final int GLFW_OPENGL_API = 0x00030001;
	public static final int GLFW_OPENGL_ES_API = 0x00030002;

	public static final int GLFW_NO_ROBUSTNESS = 0x00000000;
	public static final int GLFW_NO_RESET_NOTIFICATION = 0x00031001;
	public static final int GLFW_LOSE_CONTEXT_ON_RESET = 0x00031002;

	public static final int GLFW_OPENGL_ANY_PROFILE = 0x00000000;
	public static final int GLFW_OPENGL_CORE_PROFILE = 0x00032001;
	public static final int GLFW_OPENGL_COMPAT_PROFILE = 0x00032002;

	public static final int GLFW_CURSOR = 0x00033001;
	public static final int GLFW_STICKY_KEYS = 0x00033002;
	public static final int GLFW_STICKY_MOUSE_BUTTONS = 0x00033003;
	public static final int GLFW_LOCK_KEY_MODS         = 0x00033004;
	public static final int GLFW_RAW_MOUSE_MOTION      = 0x00033005;

	public static final int GLFW_CURSOR_NORMAL = 0x00034001;
	public static final int GLFW_CURSOR_HIDDEN = 0x00034002;
	public static final int GLFW_CURSOR_DISABLED        = 0x00034003;
	public static final int GLFW_CURSOR_CAPTURED = 0x00034004;

	public static final int GLFW_NATIVE_CONTEXT_API     = 0x00036001;
	public static final int GLFW_EGL_CONTEXT_API        = 0x00036002;
	public static final int GLFW_OSMESA_CONTEXT_API     = 0x00036003;

	public static final int GLFW_ANGLE_PLATFORM_TYPE_NONE    = 0x00037001;
	public static final int GLFW_ANGLE_PLATFORM_TYPE_OPENGL  = 0x00037002;
	public static final int GLFW_ANGLE_PLATFORM_TYPE_OPENGLES = 0x00037003;
	public static final int GLFW_ANGLE_PLATFORM_TYPE_D3D9    = 0x00037004;
	public static final int GLFW_ANGLE_PLATFORM_TYPE_D3D11   = 0x00037005;
	public static final int GLFW_ANGLE_PLATFORM_TYPE_VULKAN  = 0x00037007;
	public static final int GLFW_ANGLE_PLATFORM_TYPE_METAL   = 0x00037008;

	public static final int GLFW_ANY_POSITION           = 0x80000000;

	public static final int GLFW_ARROW_CURSOR           = 0x00036001;
	public static final int GLFW_IBEAM_CURSOR           = 0x00036002;
	public static final int GLFW_CROSSHAIR_CURSOR       = 0x00036003;
	public static final int GLFW_POINTING_HAND_CURSOR   = 0x00036004;
	public static final int GLFW_RESIZE_EW_CURSOR       = 0x00036005;
	public static final int GLFW_RESIZE_NS_CURSOR       = 0x00036006;
	public static final int GLFW_RESIZE_NWSE_CURSOR     = 0x00036007;
	public static final int GLFW_RESIZE_NESW_CURSOR     = 0x00036008;
	public static final int GLFW_RESIZE_ALL_CURSOR      = 0x00036009;
	public static final int GLFW_NOT_ALLOWED_CURSOR     = 0x0003600A;
	public static final int GLFW_HRESIZE_CURSOR         = GLFW_RESIZE_EW_CURSOR;
	public static final int GLFW_VRESIZE_CURSOR         = GLFW_RESIZE_NS_CURSOR;
	public static final int GLFW_HAND_CURSOR            = GLFW_POINTING_HAND_CURSOR;

	public static final int GLFW_CONNECTED = 0x00040001;
	public static final int GLFW_DISCONNECTED = 0x00040002;

	public static final int GLFW_JOYSTICK_HAT_BUTTONS   = 0x00050001;
	public static final int GLFW_ANGLE_PLATFORM_TYPE    = 0x00050002;
	public static final int GLFW_PLATFORM               = 0x00050003;
	public static final int GLFW_COCOA_CHDIR_RESOURCES  = 0x00051001;
	public static final int GLFW_COCOA_MENUBAR          = 0x00051002;
	public static final int GLFW_X11_XCB_VULKAN_SURFACE = 0x00052001;
	public static final int GLFW_ANY_PLATFORM           = 0x00060000;
	public static final int GLFW_PLATFORM_WIN32         = 0x00060001;
	public static final int GLFW_PLATFORM_COCOA         = 0x00060002;
	public static final int GLFW_PLATFORM_WAYLAND       = 0x00060003;
	public static final int GLFW_PLATFORM_X11           = 0x00060004;
	public static final int GLFW_PLATFORM_NULL          = 0x00060005;
	public static final int GLFW_DONT_CARE              = -1;

	private static GlfwCallback callback = null;

	// @off
	/*JNI
	#include <GL/glfw3.h>

	static jmethodID errorId = 0;
	static jmethodID monitorId = 0;
	static jmethodID windowPosId = 0;
	static jmethodID windowSizeId = 0;
	static jmethodID windowCloseId = 0;
	static jmethodID windowRefreshId = 0;
	static jmethodID windowFocusId = 0;
	static jmethodID windowIconifyId = 0;
	static jmethodID keyId = 0;
	static jmethodID characterId = 0;
	static jmethodID mouseButtonId = 0;
	static jmethodID cursorPosId = 0;
	static jmethodID cursorEnterId = 0;
	static jmethodID scrollId = 0;
	static jobject callback = 0;
	static int useOldKey = 0;
	static JavaVM* staticVM = 0;

#ifndef _WIN32
	#include <pthread.h>
	static pthread_key_t envTLS = 0;

	void createTLS() {
		pthread_key_create(&envTLS, NULL);
	}

	JNIEnv* getEnv () {
		JNIEnv* env = (JNIEnv*)pthread_getspecific(envTLS);
		if (!env) {
			if (staticVM->AttachCurrentThread((void**)&env, NULL) != JNI_OK) {
				printf("Unable to get Env."); fflush(stdout);
				return 0;
			}
			pthread_setspecific(envTLS, env);
		}
		return env;
	}

	void destroyEnv() {
		if (envTLS) {
			pthread_key_delete(envTLS);
			envTLS = 0;
		}
	}
#else
	static __thread JNIEnv* envTLS = 0;

	void createTLS() {
	}

	JNIEnv* getEnv () {
		if (!envTLS) {
			if (staticVM->AttachCurrentThread((void**)&env, NULL) != JNI_OK) {
				printf("Unable to get Env."); fflush(stdout);
				return 0;
			}
		}
		return envTLS;
	}

	void destroyEnv() {
		envTLS = 0;
	}
#endif

	void error(int errorCode, const char* description) {
		if(callback) {
			JNIEnv* env = getEnv();
			env->CallVoidMethod(callback, errorId, (jint)errorCode, env->NewStringUTF(description));
		}
	}

	void windowPos(GLFWwindow* window, int x, int y) {
		if(callback) {
			getEnv()->CallVoidMethod(callback, windowPosId, (jlong)window, (jint)x, (jint)y);
		}
	}

	void windowSize(GLFWwindow* window, int width, int height) {
		if(callback) {
			getEnv()->CallVoidMethod(callback, windowSizeId, (jlong)window, (jint)width, (jint)height);
		}
	}

	int windowClose(GLFWwindow* window) {
		if(callback) {
			return (getEnv()->CallBooleanMethod(callback, windowCloseId, (jlong)window)?GL_TRUE:GL_FALSE);
		}
		return GL_TRUE;
	}

	void windowRefresh(GLFWwindow* window) {
		if(callback) {
			getEnv()->CallVoidMethod(callback, windowRefreshId, (jlong)window);
		}
	}

	void windowFocus(GLFWwindow* window, int focused) {
		if(callback) {
			getEnv()->CallVoidMethod(callback, windowFocusId, (jlong)window, (jboolean)(GL_TRUE==focused));
		}
	}

	void windowIconify(GLFWwindow* window, int iconified) {
		if(callback) {
			getEnv()->CallVoidMethod(callback, windowIconifyId, (jlong)window, (jboolean)(GL_TRUE==iconified));
		}
	}

	void mouseButton(GLFWwindow* window, int button, int action) {
		if(callback) {
			getEnv()->CallVoidMethod(callback, mouseButtonId, (jlong)window, (jint)button, (jint)action);
		}
	}

	void cursorPos(GLFWwindow* window, int x, int y) {
		if(callback) {
			getEnv()->CallVoidMethod(callback, cursorPosId, (jlong)window, (jint)x, (jint)y);
		}
	}

	void cursorEnter(GLFWwindow* window, int entered) {
		if(callback) {
			getEnv()->CallVoidMethod(callback, cursorEnterId, (jlong)window, (jboolean)(GL_TRUE==entered));
		}
	}

	void scroll(GLFWwindow* window, double xpos, double ypos) {
		if(callback) {
			getEnv()->CallVoidMethod(callback, scrollId, (jlong)window, (jdouble)xpos, (jdouble)ypos);
		}
	}

	void key(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if(callback) {
			if (!useOldKey)
				getEnv()->CallVoidMethod(callback, keyId, (jlong)window, (jint)key, (jint)scancode, (jint)action, (jint)mods);
			else
				getEnv()->CallVoidMethod(callback, keyId, (jlong)window, (jint)key, (jint)action);
		}
	}

	void character(GLFWwindow* window, unsigned int character) {
		if(callback) {
			getEnv()->CallVoidMethod(callback, characterId, (jlong)window, (jchar)character);
		}
	}

	void monitor(GLFWmonitor* monitor, int event) {
		if(callback) {
			getEnv()->CallVoidMethod(callback, monitorId, (jlong)monitor, (jboolean)(GLFW_CONNECTED==event));
		}
	}

	*/

	public static native boolean glfwInit(); /*
		env->GetJavaVM(&staticVM);
		createTLS();

		jclass exception = env->FindClass("java/lang/Exception");

		jclass callbackClass = env->FindClass("com/badlogic/jglfw/GlfwCallback");
		if(!callbackClass) {
			env->ThrowNew(exception, "Couldn't find class GlfwCallback");
			return false;
		}

		errorId = env->GetMethodID(callbackClass, "error", "(ILjava/lang/String;)V");
		if(!errorId) {
			env->ThrowNew(exception, "Couldn't find error() method");
			return false;
		}

		monitorId = env->GetMethodID(callbackClass, "monitor", "(JZ)V");
		if(!monitorId) {
			env->ThrowNew(exception, "Couldn't find monitor() method");
			return false;
		}

		windowPosId = env->GetMethodID(callbackClass, "windowPos", "(JII)V");
		if(!windowPosId) {
			env->ThrowNew(exception, "Couldn't find windowPosId() method");
			return false;
		}

		windowSizeId = env->GetMethodID(callbackClass, "windowSize", "(JII)V");
		if(!windowSizeId) {
			env->ThrowNew(exception, "Couldn't find windowSizeId() method");
			return false;
		}

		windowCloseId = env->GetMethodID(callbackClass, "windowClose", "(J)Z");
		if(!windowCloseId) {
			env->ThrowNew(exception, "Couldn't find windowCloseId() method");
			return false;
		}

		windowRefreshId = env->GetMethodID(callbackClass, "windowRefresh", "(J)V");
		if(!windowRefreshId) {
			env->ThrowNew(exception, "Couldn't find windowRefresh() method");
			return false;
		}

		windowFocusId = env->GetMethodID(callbackClass, "windowFocus", "(JZ)V");
		if(!windowFocusId) {
			env->ThrowNew(exception, "Couldn't find windowFocus() method");
			return false;
		}

		windowIconifyId = env->GetMethodID(callbackClass, "windowIconify", "(JZ)V");
		if(!windowIconifyId) {
			env->ThrowNew(exception, "Couldn't find windowIconify() method");
			return false;
		}

		keyId = env->GetMethodID(callbackClass, "key", "(JIIII)V");
		if(!keyId) {
			env->ExceptionClear();
			keyId = env->GetMethodID(callbackClass, "key", "(JII)V");
			if (!keyId) {
				useOldKey = -1;
				env->ThrowNew(exception, "Couldn't find key(JIIII)V method");
				return false;
			}
		}

		characterId = env->GetMethodID(callbackClass, "character", "(JC)V");
		if(!characterId) {
			env->ThrowNew(exception, "Couldn't find character() method");
			return false;
		}

		mouseButtonId = env->GetMethodID(callbackClass, "mouseButton", "(JIZ)V");
		if(!mouseButtonId) {
			env->ThrowNew(exception, "Couldn't find mouseButton() method");
			return false;
		}

		cursorPosId = env->GetMethodID(callbackClass, "cursorPos", "(JII)V");
		if(!cursorPosId) {
			env->ThrowNew(exception, "Couldn't find cursorPos() method");
			return false;
		}

		cursorEnterId = env->GetMethodID(callbackClass, "cursorEnter", "(JZ)V");
		if(!cursorEnterId) {
			env->ThrowNew(exception, "Couldn't find cursorEnter() method");
			return false;
		}

		scrollId = env->GetMethodID(callbackClass, "scroll", "(JDD)V");
		if(!scrollId) {
			env->ThrowNew(exception, "Couldn't find scroll() method");
			return false;
		}

		jboolean result = glfwInit() == GL_TRUE;
		if(result) {
			glfwSetErrorCallback(error);
			glfwSetMonitorCallback(monitor);

		}
		return result;
	*/

	public static native void glfwTerminate(); /*
		if (callback) {
			env->DeleteGlobalRef(callback);
			callback = 0;
		}
		destroyEnv();
		glfwTerminate();
	*/

	public static String glfwGetVersion() {
		return "3.3.0";
	}

	public static native String glfwGetVersionString(); /*
		return env->NewStringUTF(glfwGetVersionString());
	*/

	public static long[] glfwGetMonitors() {
		long[] monitors = new long[256]; // 256 monitors are enough for everyone...
		int count = glfwGetMonitorsJni(monitors);
		long[] n = new long[count];
		System.arraycopy(monitors, 0, n, 0, count);
		return n;
	}

	private static native int glfwGetMonitorsJni(long[] monitors); /*
		int count = 0;
		GLFWmonitor** mons = glfwGetMonitors(&count);
		if(!mons) return 0;

		for(int i = 0; i < count; i++) {
			monitors[i] = (jlong)mons[i];
		}
		return count;
	*/

	public static native long glfwGetPrimaryMonitor(); /*
		return (jlong)glfwGetPrimaryMonitor();
	*/

	public static native int glfwGetMonitorX(long monitor); /*
		int x = 0;
		int y = 0;
		glfwGetMonitorPos((GLFWmonitor*)monitor, &x, &y);
		return x;
	*/

	public static native int glfwGetMonitorY(long monitor); /*
		int x = 0;
		int y = 0;
		glfwGetMonitorPos((GLFWmonitor*)monitor, &x, &y);
		return y;
	*/

	public static native int glfwGetMonitorPhysicalWidth(long monitor); /*
		int width = 0;
		int height = 0;
		glfwGetMonitorPhysicalSize((GLFWmonitor*)monitor, &width, &height);
		return width;
	*/

	public static native int glfwGetMonitorPhysicalHeight(long monitor); /*
		int width = 0;
		int height = 0;
		glfwGetMonitorPhysicalSize((GLFWmonitor*)monitor, &width, &height);
		return height;
	*/

	public static native String glfwGetMonitorName(long monitor); /*
		return env->NewStringUTF(glfwGetMonitorName((GLFWmonitor*)monitor));
	*/

	public static List<GlfwVideoMode> glfwGetVideoModes(long monitor) {
		int[] buffer = new int[5 * 256]; // 256 video modes are enough for everyone...
		int numModes = glfwGetVideoModesJni(monitor, buffer);
		List<GlfwVideoMode> modes = new ArrayList<GlfwVideoMode>();
		for(int i = 0, j=0; i < numModes; i++) {
			GlfwVideoMode mode = new GlfwVideoMode();
			mode.width = buffer[j++];
			mode.height = buffer[j++];
			mode.redBits = buffer[j++];
			mode.greenBits = buffer[j++];
			mode.blueBits = buffer[j++];
			modes.add(mode);
		}
		return modes;
	}

	private static native int glfwGetVideoModesJni(long monitor, int[] modes); /*
		int numModes = 0;
		const GLFWvidmode* vidModes = glfwGetVideoModes((GLFWmonitor*)monitor, &numModes);
		for(int i = 0, j = 0; i < numModes; i++) {
			modes[j++] = vidModes[i].width;
			modes[j++] = vidModes[i].height;
			modes[j++] = vidModes[i].redBits;
			modes[j++] = vidModes[i].greenBits;
			modes[j++] = vidModes[i].blueBits;
		}
		return numModes;
	*/

	public static GlfwVideoMode glfwGetVideoMode(long monitor) {
		int[] buffer = new int[5];
		glfwGetVideoModeJni(monitor, buffer);
		GlfwVideoMode mode = new GlfwVideoMode();
		mode.width = buffer[0];
		mode.height = buffer[1];
		mode.redBits = buffer[2];
		mode.greenBits = buffer[3];
		mode.blueBits = buffer[4];
		return mode;
	}

	private static native void glfwGetVideoModeJni(long monitor, int[] buffer); /*
		GLFWvidmode mode = glfwGetVideoMode((GLFWmonitor*)monitor);
		buffer[0] = mode.width;
		buffer[1] = mode.height;
		buffer[2] = mode.redBits;
		buffer[3] = mode.greenBits;
		buffer[4] = mode.blueBits;
	*/

	public static native void glfwSetGamma(long monitor, float gamma); /*
		glfwSetGamma((GLFWmonitor*)monitor, gamma);
	*/

	public static native void glfwDefaultWindowHints(); /*
		glfwDefaultWindowHints();
	*/

	public static native void glfwWindowHint(int target, int hint); /*
		glfwWindowHint(target, hint);
	*/

	public static long glfwCreateWindow(int width, int height, String title, long monitor, long share) {
		return glfwCreateWindowJni(width, height, title == null ? "GLFW" : title, monitor, share);
	}

	private static native long glfwCreateWindowJni(int width, int height, String title, long monitor, long share); /*
		GLFWwindow* window = glfwCreateWindow(width, height, title, (GLFWmonitor*)monitor, (GLFWwindow*)share);
		if (window) {
			glfwSetWindowPosCallback(window, windowPos);
			glfwSetWindowSizeCallback(window, windowSize);
			glfwSetWindowCloseCallback(window, windowClose);
			glfwSetWindowRefreshCallback(window, windowRefresh);
			glfwSetWindowFocusCallback(window, windowFocus);
			glfwSetWindowIconifyCallback(window, windowIconify);
			glfwSetKeyCallback(window, key);
			glfwSetCharCallback(window, character);
			glfwSetMouseButtonCallback(window, mouseButton);
			glfwSetCursorPosCallback(window, cursorPos);
			glfwSetCursorEnterCallback(window, cursorEnter);
			glfwSetScrollCallback(window, scroll);
		}
		return (jlong)window;
	*/

	public static native void glfwDestroyWindow(long window); /*
		glfwDestroyWindow((GLFWwindow*)window);
	*/

	public static native boolean glfwWindowShouldClose(long window); /*
		return GL_TRUE == glfwWindowShouldClose((GLFWwindow*)window);
	*/

	public static native void glfwSetWindowShouldClose(long window, int value); /*
		glfwSetWindowShouldClose((GLFWwindow*)window, value);
	*/

	public static native void glfwSetWindowTitle(long window, String title); /*
		glfwSetWindowTitle((GLFWwindow*)window, title);
	*/

	public static native void glfwSetWindowPos(long window,  int x, int y); /*
		glfwSetWindowPos((GLFWwindow*)window, x, y);
	*/

	public static native int glfwGetWindowX(long window); /*
		int x = 0;
		int y = 0;
		glfwGetWindowPos((GLFWwindow*)window, &x, &y);
		return x;
	*/

	public static native int glfwGetWindowY(long window); /*
		int x = 0;
		int y = 0;
		glfwGetWindowPos((GLFWwindow*)window, &x, &y);
		return y;
	*/

	public static native int glfwGetWindowWidth(long window); /*
		int width = 0;
		int height = 0;
		glfwGetWindowSize((GLFWwindow*)window, &width, &height);
		return width;
	*/

	public static native int glfwGetWindowHeight(long window); /*
		int width = 0;
		int height = 0;
		glfwGetWindowSize((GLFWwindow*)window, &width, &height);
		return height;
	*/

	public static native void glfwSetWindowSize(long window, int width, int height); /*
		glfwSetWindowSize((GLFWwindow*)window, width, height);
	*/

	public static native void glfwIconifyWindow(long window); /*
		glfwIconifyWindow((GLFWwindow*)window);
	*/

	public static native void glfwRestoreWindow(long window); /*
		glfwRestoreWindow((GLFWwindow*)window);
	*/

	public static native void glfwHideWindow(long window); /*
		glfwHideWindow((GLFWwindow*)window);
	*/

	public static native void glfwShowWindow(long window); /*
		glfwShowWindow((GLFWwindow*)window);
	*/

	public static native long glfwGetWindowMonitor(long window); /*
		return (jlong)glfwGetWindowMonitor((GLFWwindow*)window);
	*/

	public static native int glfwGetWindowAttrib(long window, int param); /*
		return glfwGetWindowAttrib((GLFWwindow*)window, param);
	*/

	/**
	 * Sets the {@link GlfwCallback} that will get invoked by
	 * various events. Replaces the single callback functions of GLFW
	 * @param callback the callback or null
	 */
	public static void glfwSetCallback(GlfwCallback callback) {
		glfwSetCallbackJni(callback);
	}

	public static native void glfwSetCallbackJni(GlfwCallback javaCallback); /*
		if (callback) {
			env->DeleteGlobalRef(callback);
			callback = 0;
		}
		if (javaCallback) callback = env->NewGlobalRef(javaCallback);
	*/

	public static void glfwPollEvents() {
		glfwPollEventsJni(callback);
	}

	private static native void glfwPollEventsJni(GlfwCallback javaCallback); /*
		glfwPollEvents();
	*/

	public static void glfwWaitEvents() {
		glfwWaitEventsJni(callback);
	}

	private static native void glfwWaitEventsJni(GlfwCallback javaCallback); /*
		glfwWaitEvents();
	*/

	public static native int glfwGetInputMode(long window, int mode); /*
		return glfwGetInputMode((GLFWwindow*)window, mode);
	*/

	public static native void glfwSetInputMode(long window, int mode, int value); /*
		glfwSetInputMode((GLFWwindow*)window, mode, value);
	*/

	public static native boolean glfwGetKey(long window, int key); /*
		return glfwGetKey((GLFWwindow*)window, key) == GLFW_PRESS;
	*/

	public static native boolean glfwGetMouseButton(long window, int button); /*
		return glfwGetMouseButton((GLFWwindow*)window, button) == GLFW_PRESS;
	*/

	public static native int glfwGetCursorPosX(long window); /*
		int x = 0;
		int y = 0;
		glfwGetCursorPos((GLFWwindow*)window, &x, &y);
		return x;
	*/

	public static native int glfwGetCursorPosY(long window); /*
		int x = 0;
		int y = 0;
		glfwGetCursorPos((GLFWwindow*)window, &x, &y);
		return y;
	*/

	public static native void glfwSetCursorPos(long window, int x, int y); /*
		glfwSetCursorPos((GLFWwindow*)window, x, y);
	*/

	public static native int glfwGetJoystickParam(int joy, int param); /*
		return glfwGetJoystickParam(joy, param);
	*/

	public static native int glfwGetJoystickAxes(int joy, float[] axes); /*
		return glfwGetJoystickAxes(joy, axes, env->GetArrayLength(obj_axes));
	*/

	public static native int glfwGetJoystickButtons(int joy, byte[] buttons); /*
		return glfwGetJoystickButtons(joy, (unsigned char*)buttons, env->GetArrayLength(obj_buttons));
	*/

	public static native String glfwGetJoystickName(int joy); /*
		return env->NewStringUTF(glfwGetJoystickName(joy));
	*/

	public static native void glfwSetClipboardString(long window, String string); /*
		glfwSetClipboardString((GLFWwindow*)window, string);
	*/

	public static native String glfwGetClipboardString(long window); /*
		return env->NewStringUTF(glfwGetClipboardString((GLFWwindow*)window));
	*/

	public static native double glfwGetTime(); /*
		return glfwGetTime();
	*/

	public static native void glfwSetTime(double time); /*
		glfwSetTime(time);
	*/

	public static void glfwMakeContextCurrent(long window) {
		glfwMakeContextCurrentJni(window);
		//GL.init();
	}

	private static native void glfwMakeContextCurrentJni(long window); /*
		glfwMakeContextCurrent((GLFWwindow*)window);
	*/

	public static native long glfwGetCurrentContext(); /*
		return (jlong)glfwGetCurrentContext();
	*/

	public static native void glfwSwapBuffers(long window); /*
		glfwSwapBuffers((GLFWwindow*)window);
	*/

	public static native void glfwSwapInterval(int interval); /*
		glfwSwapInterval(interval);
	*/

	public static native boolean glfwExtensionSupported(String extension); /*
		return glfwExtensionSupported(extension) == GL_TRUE;
	*/

	// Not used in JAva
//	private static native void glfwSetWindowUserPointer(); /*
//	*/
//
//	private static native void glfwGetWindowUserPointer(); /*
//	*/
//

	// These are all callback functions that are replaced by
	// glfwSetCallback();
//	public static native void glfwSetErrorCallback(); /*
//	 */
//
//	public static native void glfwSetMonitorCallback(); /*
//	*/
//
//	private static native void glfwSetWindowPosCallback(); /*
//	*/
//
//	private static native void glfwSetWindowSizeCallback(); /*
//	*/
//
//	private static native void glfwSetWindowCloseCallback(); /*
//	*/
//
//	private static native void glfwSetWindowRefreshCallback(); /*
//	*/
//
//	private static native void glfwSetWindowFocusCallback(); /*
//	*/
//
//	private static native void glfwSetWindowIconifyCallback(); /*
//	*/
//
//	private static native void glfwSetKeyCallback(); /*
//	*/
//
//	private static native void glfwSetCharCallback(); /*
//	*/
//
//	private static native void glfwSetMouseButtonCallback(); /*
//	*/
//
//	private static native void glfwSetCursorPosCallback(); /*
//	*/
//
//	private static native void glfwSetCursorEnterCallback(); /*
//	*/
//
//	private static native void glfwSetScrollCallback(); /*
//	*/
}
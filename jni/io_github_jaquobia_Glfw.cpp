#include "io_github_jaquobia_Glfw.h"
#include <GLFW/glfw3.h>
#include <iostream>

 // JGLFW Callback Methods

	static int useOldKey = 0;
	static JavaVM* staticVM = 0;
  static jobject callback = 0;
  static jmethodID errorId = 0;
	static jmethodID monitorId = 0;
	static jmethodID windowPosId = 0;
	static jmethodID windowSizeId = 0;
	static jmethodID windowCloseId = 0;
	static jmethodID windowRefreshId = 0;
	static jmethodID windowFocusId = 0;
	static jmethodID windowIconifyId = 0;
  static jmethodID windowMaximizeId = 0;
  static jmethodID windowFrameBufferId = 0;
  static jmethodID windowContentScaleId = 0;
	static jmethodID keyId = 0;
	static jmethodID characterId = 0;
  static jmethodID characterModsId = 0;
	static jmethodID mouseButtonId = 0;
	static jmethodID cursorPosId = 0;
	static jmethodID cursorEnterId = 0;
	static jmethodID dropId = 0;
	static jmethodID scrollId = 0;
  static jmethodID joyId = 0;

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
	static thread_local JNIEnv* envTLS = 0;

	void createTLS() {
	}

	JNIEnv* getEnv () {
		if (!envTLS) {
			if (staticVM->AttachCurrentThread((void**)&envTLS, NULL) != JNI_OK) {
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

	void windowClose(GLFWwindow* window) {
		if(callback) {
			getEnv()->CallBooleanMethod(callback, windowCloseId, (jlong)window);
		}
	}

	void windowRefresh(GLFWwindow* window) {
		if(callback) {
			getEnv()->CallVoidMethod(callback, windowRefreshId, (jlong)window);
		}
	}

	void windowFocus(GLFWwindow* window, int focused) {
		if(callback) {
			getEnv()->CallVoidMethod(callback, windowFocusId, (jlong)window, (jboolean)(GLFW_TRUE==focused));
		}
	}

	void windowIconify(GLFWwindow* window, int iconified) {
		if(callback) {
			getEnv()->CallVoidMethod(callback, windowIconifyId, (jlong)window, (jboolean)(GLFW_TRUE==iconified));
		}
	}

  void windowMaximize(GLFWwindow* window, int maximized) {
    if (callback) {
      getEnv()->CallVoidMethod(callback, windowMaximizeId, (jlong)window, (jboolean)(GLFW_TRUE==maximized));
    }
  }

  void windowFramebufferSize(GLFWwindow* window, int width, int height) {
    if (callback) {
      getEnv()->CallVoidMethod(callback, windowFrameBufferId, (jlong)window, (jint)width, (jint)height);
    }
  }

  void windowContentScale(GLFWwindow* window, float xScale, float yScale) {
    if (callback) {
      getEnv()->CallVoidMethod(callback, windowContentScaleId, (jlong)window, (jfloat)xScale, (jfloat)yScale);
    }
  }

	void mouseButton(GLFWwindow* window, int button, int action, int mods) {
		if(callback) {
			getEnv()->CallVoidMethod(callback, mouseButtonId, (jlong)window, (jint)button, (jint)action);
		}
	}

	void cursorPos(GLFWwindow* window, double x, double y) {
		if(callback) {
			getEnv()->CallVoidMethod(callback, cursorPosId, (jlong)window, (jdouble)x, (jdouble)y);
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

	void character(GLFWwindow* window, unsigned int codepoint) {
		if(callback) {
			getEnv()->CallVoidMethod(callback, characterId, (jlong)window, (jint)codepoint);
		}
	}

  void characterMods(GLFWwindow* window, unsigned int charpoint, int mods) {
    if(callback) {
			getEnv()->CallVoidMethod(callback, characterModsId, (jlong)window, (jint)charpoint, (jint)mods);
		}
  }

  void drop(GLFWwindow* window, int path_count, const char* paths[]) {
    if(callback) {
      JNIEnv* env = getEnv();
      jobjectArray paths_arr = env->NewObjectArray(path_count, env->FindClass("java/lang/String"), 0);
      for (int i = 0; i < path_count; i++) {
        env->SetObjectArrayElement(paths_arr, i, env->NewStringUTF(paths[i]));
      }
			env->CallVoidMethod(callback, dropId, (jlong)window, paths_arr);
		}
  }

	void monitor(GLFWmonitor* monitor, int event) {
		if(callback) {
			getEnv()->CallVoidMethod(callback, monitorId, (jlong)monitor, (jboolean)(GLFW_CONNECTED==event));
		}
	}
  void joystick(int jid, int event) {
		if(callback) {
			getEnv()->CallVoidMethod(callback, joyId, (jint) jid, (jint)event);
		}
	}

/*
 * Class:     Glfw
 * Method:    glfwInitJni
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_jaquobia_Glfw_glfwInit
  (JNIEnv *env, jclass clazz)
  {
    env->GetJavaVM(&staticVM);
		createTLS();

		jclass exception = env->FindClass("java/lang/Exception");

		jclass callbackClass = env->FindClass("io/github/jaquobia/GlfwCallback");
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

		windowCloseId = env->GetMethodID(callbackClass, "windowClose", "(J)V");
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

		characterId = env->GetMethodID(callbackClass, "character", "(JI)V");
		if(!characterId) {
			env->ThrowNew(exception, "Couldn't find character() method");
			return false;
		}

		mouseButtonId = env->GetMethodID(callbackClass, "mouseButton", "(JIZI)V");
		if(!mouseButtonId) {
			env->ThrowNew(exception, "Couldn't find mouseButton() method");
			return false;
		}

		cursorPosId = env->GetMethodID(callbackClass, "cursorPos", "(JDD)V");
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

    windowMaximizeId = env->GetMethodID(callbackClass, "windowMaximize", "(JZ)V");
		if(!windowMaximizeId) {
			env->ThrowNew(exception, "Couldn't find windowMaximize() method");
			return false;
		}
    windowFrameBufferId = env->GetMethodID(callbackClass, "windowFramebufferSize", "(JII)V");
		if(!windowFrameBufferId) {
			env->ThrowNew(exception, "Couldn't find windowFramebufferSize() method");
			return false;
		}
    windowContentScaleId = env->GetMethodID(callbackClass, "windowContentScale", "(JFF)V");
		if(!windowContentScaleId) {
			env->ThrowNew(exception, "Couldn't find windowContentScale() method");
			return false;
		}
    characterModsId = env->GetMethodID(callbackClass, "characterMods", "(JII)V");
		if(!characterModsId) {
			env->ThrowNew(exception, "Couldn't find characterMods() method");
			return false;
		}
    dropId = env->GetMethodID(callbackClass, "drop", "(J[Ljava/lang/String;)V");
		if(!dropId) {
			env->ThrowNew(exception, "Couldn't find drop() method");
			return false;
		}
    joyId = env->GetMethodID(callbackClass, "joystick", "(II)V");
		if(!joyId) {
			env->ThrowNew(exception, "Couldn't find joystick() method");
			return false;
		}
		jboolean result = glfwInit() == GL_TRUE;
		if(result) {
			glfwSetErrorCallback(error);
			glfwSetMonitorCallback(monitor);

		}
		return result;

  }

/*
 * Class:     Glfw
 * Method:    glfwTerminate
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwTerminate
  (JNIEnv *env, jclass clazz)
  {
    if (callback) {
			env->DeleteGlobalRef(callback);
			callback = 0;
		}
		destroyEnv();
    glfwTerminate();
  }

/*
 * Class:     Glfw
 * Method:    glfwGetVersionString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_jaquobia_Glfw_glfwGetVersionString
  (JNIEnv *env, jclass clazz)
  {
    return env->NewStringUTF(glfwGetVersionString());
  }

JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetPlatform
  (JNIEnv *env, jclass clazz)
  {
    return (jint)glfwGetPlatform();
  }
JNIEXPORT jboolean JNICALL Java_io_github_jaquobia_Glfw_glfwPlatformSupported
  (JNIEnv *env, jclass clazz, jint platform)
  {
    return (jboolean)(glfwPlatformSupported((int)platform) == GLFW_TRUE);
  }

/*
 * Class:     Glfw
 * Method:    glfwGetMonitorsJni
 * Signature: ([J)I
 */
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetMonitorsJni
  (JNIEnv *env, jclass clazz, jlongArray monitors)
  {
    auto monArray = env->GetLongArrayElements(monitors, 0);
    int count = 0;
    auto glfwmonitors = glfwGetMonitors(&count);

    for (int i = 0; i < count; i++)
      monArray[i] = (jlong)glfwmonitors[i];
    env->ReleaseLongArrayElements(monitors, monArray, 0);
    return count;
  }

/*
 * Class:     Glfw
 * Method:    glfwGetPrimaryMonitor
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_io_github_jaquobia_Glfw_glfwGetPrimaryMonitor
  (JNIEnv *env, jclass clazz)
  {
    return (jlong)glfwGetPrimaryMonitor();
  }

/*
 * Class:     Glfw
 * Method:    glfwGetMonitorX
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetMonitorX
  (JNIEnv *env, jclass clazz, jlong monitor)
  {
    int x, y = 0;
    glfwGetMonitorPos((GLFWmonitor*)monitor, &x, &y);
    return x;
  }

/*
 * Class:     Glfw
 * Method:    glfwGetMonitorY
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetMonitorY
  (JNIEnv *env, jclass clazz, jlong monitor)
  {
    int x, y = 0;
    glfwGetMonitorPos((GLFWmonitor*)monitor, &x, &y);
    return y;
  }

JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetMonitorWorkX
  (JNIEnv *, jclass, jlong)
  {
    int x = 0, y = 0, width = 0, height = 0;
    glfwGetMonitorWorkarea((GLFWmonitor*)monitor, &x, &y, &width, &height);
    return x;
  }
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetMonitorWorkY
  (JNIEnv *, jclass, jlong)
  {
    int x = 0, y = 0, width = 0, height = 0;
    glfwGetMonitorWorkarea((GLFWmonitor*)monitor, &x, &y, &width, &height);
    return y;
  }
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetMonitorWorkWidth
  (JNIEnv *, jclass, jlong)
  {
    int x = 0, y = 0, width = 0, height = 0;
    glfwGetMonitorWorkarea((GLFWmonitor*)monitor, &x, &y, &width, &height);
    return width;
  }
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetMonitorWorkHeight
  (JNIEnv *, jclass, jlong)
  {
    int x = 0, y = 0, width = 0, height = 0;
    glfwGetMonitorWorkarea((GLFWmonitor*)monitor, &x, &y, &width, &height);
    return height;
  }

/*
 * Class:     Glfw
 * Method:    glfwGetMonitorPhysicalWidth
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetMonitorPhysicalWidth
  (JNIEnv *env, jclass clazz, jlong monitor)
  {
    int width, height = 0;
    glfwGetMonitorPhysicalSize((GLFWmonitor*)monitor, &width, &height);
    return width;
  }

/*
 * Class:     Glfw
 * Method:    glfwGetMonitorPhysicalHeight
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetMonitorPhysicalHeight
  (JNIEnv *env, jclass clazz, jlong monitor)
  {
    int width, height = 0;
    glfwGetMonitorPhysicalSize((GLFWmonitor*)monitor, &width, &height);
    return height;
  }


JNIEXPORT jfloat JNICALL Java_io_github_jaquobia_Glfw_glfwGetMonitorScaleX
  (JNIEnv *, jclass, jlong)
  {
    float width = 0, height = 0;
    glfwGetMonitorContentScale((GLFWmonitor*)monitor, &width, &height);
    return width;
  }
JNIEXPORT jfloat JNICALL Java_io_github_jaquobia_Glfw_glfwGetMonitorScaleY
  (JNIEnv *, jclass, jlong)
  {
    float width = 0, height = 0;
    glfwGetMonitorContentScale((GLFWmonitor*)monitor, &width, &height);
    return height;
  }

/*
 * Class:     Glfw
 * Method:    glfwGetMonitorName
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_jaquobia_Glfw_glfwGetMonitorName
  (JNIEnv *env, jclass clazz, jlong monitor)
  {
      return env->NewStringUTF(glfwGetMonitorName((GLFWmonitor*) monitor));
  }

/*
 * Class:     Glfw
 * Method:    glfwGetVideoModesJni
 * Signature: (J[I)I
 */
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetVideoModesJni
  (JNIEnv *env, jclass clazz, jlong monitor, jintArray videoModesOut)
  {
    int* videoModes = (int*)env->GetPrimitiveArrayCritical(videoModesOut, 0);
    int count = 0;
    auto vidModes = glfwGetVideoModes((GLFWmonitor*)monitor, &count);
    for (int i = 0, j = 0; i < count; i++) {
			videoModes[j++] = vidModes[i].width;
			videoModes[j++] = vidModes[i].height;
			videoModes[j++] = vidModes[i].redBits;
			videoModes[j++] = vidModes[i].greenBits;
			videoModes[j++] = vidModes[i].blueBits;
    }
    env->ReleasePrimitiveArrayCritical(videoModesOut, videoModes, 0);
    return count;
  }

/*
 * Class:     Glfw
 * Method:    glfwGetVideoModeJni
 * Signature: (J[I)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwGetVideoModeJni
  (JNIEnv *env, jclass clazz, jlong monitor, jintArray videoModeOut)
  {
    int* videoModes = (int*)env->GetPrimitiveArrayCritical(videoModeOut, 0);
    auto vidMode = glfwGetVideoMode((GLFWmonitor*)monitor);
		videoModes[0] = vidMode->width;
		videoModes[1] = vidMode->height;
		videoModes[2] = vidMode->redBits;
		videoModes[3] = vidMode->greenBits;
		videoModes[4] = vidMode->blueBits;
    env->ReleasePrimitiveArrayCritical(videoModeOut, videoModes, 0);
  }

/*
 * Class:     Glfw
 * Method:    glfwSetGamma
 * Signature: (JF)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwSetGamma
  (JNIEnv *env, jclass clazz, jlong monitor, jfloat gamma)
  {
      glfwSetGamma((GLFWmonitor*) monitor, gamma);
  }

/*
 * Class:     Glfw
 * Method:    glfwDefaultWindowHints
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwDefaultWindowHints
  (JNIEnv *env, jclass clazz)
  {
    glfwDefaultWindowHints();
  }

/*
 * Class:     Glfw
 * Method:    glfwWindowHint
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwWindowHint
  (JNIEnv *env, jclass clazz, jint hint, jint value)
  {
    glfwWindowHint((int) hint, (int) value);
  }

  JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwWindowHintString
  (JNIEnv *env, jclass clazz, jint hint, jstring value)
  {
    auto cvalue = env->GetStringUTFChars(value, 0);
    glfwWindowHintString((int)hint, cvalue);
    env->ReleaseStringUTFChars(value, cvalue);
  }

/*
 * Class:     Glfw
 * Method:    glfwCreateWindowJni
 * Signature: (IILjava/lang/String;JJ)J
 */
JNIEXPORT jlong JNICALL Java_io_github_jaquobia_Glfw_glfwCreateWindowJni
  (JNIEnv *env, jclass clazz, jint width, jint height, jstring title, jlong monitor, jlong share)
  {
    jclass exception = env->FindClass("java/lang/Exception");
    auto ctitle = env->GetStringUTFChars(title, 0);
    auto window = glfwCreateWindow((int) width, (int) height, ctitle, (GLFWmonitor*)monitor, (GLFWwindow*)share);
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
      glfwSetWindowMaximizeCallback(window, windowMaximize);
      glfwSetFramebufferSizeCallback(window, windowFramebufferSize);
      glfwSetWindowContentScaleCallback(window, windowContentScale);
      glfwSetCharModsCallback(window, characterMods);
      glfwSetDropCallback(window, drop);
      glfwSetJoystickCallback(joystick);
    } else {
      env->ThrowNew(exception, "JNI Window could not be created!\n");
    }
    env->ReleaseStringUTFChars(title, ctitle);
    return (jlong)window;
  }

/*
 * Class:     Glfw
 * Method:    glfwDestroyWindow
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwDestroyWindow
  (JNIEnv *env, jclass clazz, jlong window)
  {
    glfwDestroyWindow((GLFWwindow*)window);
  }

/*
 * Class:     Glfw
 * Method:    glfwWindowShouldClose
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_jaquobia_Glfw_glfwWindowShouldClose
  (JNIEnv *env, jclass clazz, jlong window)
  {
    return (jboolean)glfwWindowShouldClose((GLFWwindow*)window);
  }

/*
 * Class:     Glfw
 * Method:    glfwSetWindowShouldClose
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwSetWindowShouldClose
  (JNIEnv *env, jclass clazz, jlong window, jint value)
  {
    glfwSetWindowShouldClose((GLFWwindow*)window, (int)value);
  }

/*
 * Class:     Glfw
 * Method:    glfwSetWindowTitle
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwSetWindowTitle
  (JNIEnv *env, jclass clazz, jlong window, jstring title)
  {
    auto ctitle = env->GetStringUTFChars(title, 0);
    glfwSetWindowTitle((GLFWwindow*)window, ctitle);
    env->ReleaseStringUTFChars(title, ctitle);
  }

/*
 * Class:     Glfw
 * Method:    glfwSetWindowPos
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwSetWindowPos
  (JNIEnv *env, jclass clazz, jlong window, jint x, jint y)
  {
    glfwSetWindowPos((GLFWwindow*)window, (int) x, (int) y);
  }

/*
 * Class:     Glfw
 * Method:    glfwGetWindowX
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetWindowX
  (JNIEnv *env, jclass clazz, jlong window)
  {
    int x, y;
    glfwGetWindowPos((GLFWwindow*)window, &x, &y);
    return (jint)x;
  }

/*
 * Class:     Glfw
 * Method:    glfwGetWindowY
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetWindowY
  (JNIEnv *env, jclass clazz, jlong window)
  {
    int x, y;
    glfwGetWindowPos((GLFWwindow*)window, &x, &y);
    return (jint)y;
  }

/*
 * Class:     Glfw
 * Method:    glfwGetWindowWidth
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetWindowWidth
  (JNIEnv *env, jclass clazz, jlong window)
  {
    int x, y;
    glfwGetWindowSize((GLFWwindow*)window, &x, &y);
    return (jint)x;
  }

/*
 * Class:     Glfw
 * Method:    glfwGetWindowHeight
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetWindowHeight
  (JNIEnv *env, jclass clazz, jlong window)
  {
    int x, y;
    glfwGetWindowSize((GLFWwindow*)window, &x, &y);
    return (jint)y;
  }

/*
 * Class:     Glfw
 * Method:    glfwSetWindowSize
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwSetWindowSize
  (JNIEnv *env, jclass clazz, jlong window, jint width, jint height)
  {
    glfwSetWindowSize((GLFWwindow*) window, (int) width, (int) height);
  }

JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwSetWindowSizeLimits
  (JNIEnv *env, jclass clazz, jlong window, jint x, jint y, jint width, jint height)
  {
    glfwSetWindowSizeLimits((GLFWwindow*)window, (int)x, (int)y, (int)width, (int)height);
  }

/*
 * Class:     Glfw
 * Method:    glfwIconifyWindow
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwIconifyWindow
  (JNIEnv *env, jclass clazz, jlong window)
  {
    glfwIconifyWindow((GLFWwindow*) window);
  }

JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwSetWindowAspectRatio
  (JNIEnv *env, jclass clazz, jlong window, jint num, jint denom)
  {
    glfwSetWindowAspectRatio((GLFWwindow*)window, (int)num, (int)denom);
  }

JNIEXPORT jfloat JNICALL Java_io_github_jaquobia_Glfw_glfwGetWindowOpacity
  (JNIEnv *env, jclass clazz, jlong window)
  {
    return (jfloat)glfwGetWindowOpacity((GLFWwindow*)window);
  }

JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwSetWindowOpacity
  (JNIEnv *env, jclass clazz, jlong window, jfloat opacity)
  {
    glfwSetWindowOpacity((GLFWwindow*)window, (float)opacity);
  }


/*
 * Class:     Glfw
 * Method:    glfwRestoreWindow
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwRestoreWindow
  (JNIEnv *env, jclass clazz, jlong window)
  {
    glfwRestoreWindow((GLFWwindow*) window);
  }

/*
 * Class:     Glfw
 * Method:    glfwHideWindow
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwHideWindow
  (JNIEnv *env, jclass clazz, jlong window)
  {
    glfwHideWindow((GLFWwindow*) window);
  }

JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwMaximizeWindow
  (JNIEnv *env, jclass clazz, jlong window)
  {
    glfwMaximizeWindow((GLFWwindow*) window);
  }

/*
 * Class:     Glfw
 * Method:    glfwShowWindow
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwShowWindow
  (JNIEnv *env, jclass clazz, jlong window)
  {
    glfwShowWindow((GLFWwindow*) window);
  }

JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwFocusWindow
  (JNIEnv *env, jclass clazz, jlong window)
  {
    glfwFocusWindow((GLFWwindow*) window);
  }

JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwRequestWindowAttention
  (JNIEnv *env, jclass clazz, jlong window)
  {
    glfwRequestWindowAttention((GLFWwindow*) window);
  }

/*
 * Class:     Glfw
 * Method:    glfwGetWindowMonitor
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_io_github_jaquobia_Glfw_glfwGetWindowMonitor
  (JNIEnv *env, jclass clazz, jlong window)
  {
    return (jlong) glfwGetWindowMonitor((GLFWwindow*) window);
  }

static int mini(int x, int y)
{
    return x < y ? x : y;
}

static int maxi(int x, int y)
{
    return x > y ? x : y;
}

GLFWmonitor* get_current_monitor(GLFWwindow *window)
{
    int nmonitors, i;
    int wx, wy, ww, wh;
    int mx, my, mw, mh;
    int overlap, bestoverlap;
    GLFWmonitor *bestmonitor;
    GLFWmonitor **monitors;
    const GLFWvidmode *mode;

    bestoverlap = 0;
    bestmonitor = NULL;

    glfwGetWindowPos(window, &wx, &wy);
    glfwGetWindowSize(window, &ww, &wh);
    monitors = glfwGetMonitors(&nmonitors);

    for (i = 0; i < nmonitors; i++) {
        mode = glfwGetVideoMode(monitors[i]);
        glfwGetMonitorPos(monitors[i], &mx, &my);
        mw = mode->width;
        mh = mode->height;

        overlap =
            maxi(0, mini(wx + ww, mx + mw) - maxi(wx, mx)) *
            maxi(0, mini(wy + wh, my + mh) - maxi(wy, my));

        if (bestoverlap < overlap) {
            bestoverlap = overlap;
            bestmonitor = monitors[i];
        }
    }

    return bestmonitor;
}
JNIEXPORT jlong JNICALL Java_io_github_jaquobia_Glfw_glfwGetCurrentWindowMonitor
  (JNIEnv *env, jclass clazz, jlong window)
  {
    return (jlong) get_current_monitor((GLFWwindow*) window);
  }
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwSetCurrentWindowMonitor
  (JNIEnv *env, jclass clazz, jlong window)
  {
    auto monitor = get_current_monitor((GLFWwindow*) window);
    auto mode = glfwGetVideoMode((GLFWmonitor*)monitor);
    glfwSetWindowMonitor((GLFWwindow*)window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
  }

JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwSetWindowMonitor
  (JNIEnv *env, jclass clazz, jlong window, jlong monitor, jint x, jint y, jint width, jint height, jint refresh)
  {
    glfwSetWindowMonitor((GLFWwindow*)window, (GLFWmonitor*)monitor, x, y, width, height, refresh);
  }
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwSetWindowMonitorDefault
  (JNIEnv *env, jclass clazz, jlong window, jlong monitor)
  {
    auto mode = glfwGetVideoMode((GLFWmonitor*)monitor);
    glfwSetWindowMonitor((GLFWwindow*)window, (GLFWmonitor*)monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
  }



/*
 * Class:     Glfw
 * Method:    glfwGetWindowAttrib
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetWindowAttrib
  (JNIEnv *env, jclass clazz, jlong window, jint attribute)
  {
    return (jint)glfwGetWindowAttrib((GLFWwindow*)window, (int) attribute);
  }

JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwSetWindowAttrib
  (JNIEnv *env, jclass clazz, jlong window, jint key, jint value)
  {
    glfwSetWindowAttrib((GLFWwindow*)window, key, value);
  }

/*
 * Class:     Glfw
 * Method:    glfwSetCallbackJni
 * Signature: (LGlfwCallback;)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwSetCallbackJni
  (JNIEnv *env, jclass clazz, jobject javaCallback)
  {
    if (callback) {
			env->DeleteGlobalRef(callback);
			callback = 0;
		}
		if (javaCallback) callback = env->NewGlobalRef(javaCallback);
  }

/*
 * Class:     Glfw
 * Method:    glfwPollEventsJni
 * Signature: (LGlfwCallback;)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwPollEventsJni
  (JNIEnv *env, jclass clazz, jobject obj)
  {
    glfwPollEvents();
  }

/*
 * Class:     Glfw
 * Method:    glfwWaitEventsJni
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwWaitEventsJni
  (JNIEnv *env, jclass clazz, jobject obj)
  {
    glfwWaitEvents();
  }


JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwWaitEventsTimeoutJni
  (JNIEnv *env, jclass clazz, jdouble timeout)
  {
    glfwWaitEventsTimeout(timeout);
  }

/*
 * Class:     Glfw
 * Method:    glfwGetInputMode
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetInputMode
  (JNIEnv *env, jclass clazz, jlong window, jint mode)
  {
    return (jint) glfwGetInputMode((GLFWwindow*) window, (int) mode);
  }

JNIEXPORT jstring JNICALL Java_io_github_jaquobia_Glfw_glfwGetKeyName
  (JNIEnv *env, jclass clazz, jint key, jint scancode)
  {
    auto keyName = glfwGetKeyName(key, scancode);
    return env->NewStringUTF(keyName);
  }
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetScancode
  (JNIEnv *env, jclass clazz, jint key)
  {
    return glfwGetKeyScancode(key);
  }

/*
 * Class:     Glfw
 * Method:    glfwSetInputMode
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwSetInputMode
  (JNIEnv *env, jclass clazz, jlong window, jint mode, jint value)
  {
    glfwSetInputMode((GLFWwindow*) window, (int) mode, (int) value);
  }

/*
 * Class:     Glfw
 * Method:    glfwGetKey
 * Signature: (JI)Z
 */
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetKey
  (JNIEnv *env, jclass clazz, jlong window, jint key)
  {
    return (jint)glfwGetKey((GLFWwindow*) window, (int) key);
  }

/*
 * Class:     Glfw
 * Method:    glfwGetMouseButton
 * Signature: (JI)Z
 */
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetMouseButton
  (JNIEnv *env, jclass clazz, jlong window, jint button)
  {
    return (jint)glfwGetMouseButton((GLFWwindow*) window, (int) button);
  }

/*
 * Class:     Glfw
 * Method:    glfwGetCursorPosX
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetCursorPosX
  (JNIEnv *env, jclass clazz, jlong window)
  {
    double x = 0, y = 0;
    glfwGetCursorPos((GLFWwindow*) window, &x, &y);
    return (jint)x;
  }

/*
 * Class:     Glfw
 * Method:    glfwGetCursorPosY
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetCursorPosY
  (JNIEnv *env, jclass clazz, jlong window)
  {
    double x = 0, y = 0;
    glfwGetCursorPos((GLFWwindow*) window, &x, &y);
    return (jint)y;
  }

/*
 * Class:     Glfw
 * Method:    glfwSetCursorPos
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwSetCursorPos
  (JNIEnv *env, jclass clazz, jlong window, jint x, jint y)
  {
    glfwSetCursorPos((GLFWwindow*) window, (int) x, (int) y);
  }

/*
 * Class:     Glfw
 * Method:    glfwGetJoystickParam
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetJoystickParam
  (JNIEnv *env, jclass clazz, jint id, jint)
  {
    return (jint)glfwJoystickPresent((int) id);
  }

/*
 * Class:     Glfw
 * Method:    glfwGetJoystickAxes
 * Signature: (I[F)I
 */
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetJoystickAxes
  (JNIEnv *env, jclass clazz, jint id, jfloatArray values)
  {
    auto valuesdata = (float*)env->GetFloatArrayElements(values, 0);
    int count = 0;
    auto axesdata = glfwGetJoystickAxes((int) id, &count);
    env->ReleaseFloatArrayElements(values, valuesdata, 0);
    return (jint)count;
  }

/*
 * Class:     Glfw
 * Method:    glfwGetJoystickButtons
 * Signature: (I[B)I
 */
JNIEXPORT jint JNICALL Java_io_github_jaquobia_Glfw_glfwGetJoystickButtons
  (JNIEnv *env, jclass clazz, jint id, jbyteArray buttonArray)
  {
    auto data = env->GetByteArrayElements(buttonArray, 0);
    int count = 0;
    data = (jbyte*)glfwGetJoystickButtons((int) id, &count);
    env->ReleaseByteArrayElements(buttonArray, data, 0);
    return (jint)count;
  }

/*
 * Class:     Glfw
 * Method:    glfwGetJoystickName
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_jaquobia_Glfw_glfwGetJoystickName
  (JNIEnv *env, jclass clazz, jint id)
  {
    return env->NewStringUTF(glfwGetJoystickName((int) id));
  }

/*
 * Class:     Glfw
 * Method:    glfwSetClipboardString
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwSetClipboardString
  (JNIEnv *env, jclass clazz, jlong window, jstring contents)
  {
    auto cstrContents = env->GetStringUTFChars(contents, 0);
    glfwSetClipboardString((GLFWwindow*)window, cstrContents);
    env->ReleaseStringUTFChars(contents, cstrContents);
  }

/*
 * Class:     Glfw
 * Method:    glfwGetClipboardString
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_jaquobia_Glfw_glfwGetClipboardString
  (JNIEnv *env, jclass clazz, jlong window)
  {
    return env->NewStringUTF(glfwGetClipboardString((GLFWwindow*)window));
  }

/*
 * Class:     Glfw
 * Method:    glfwGetTime
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_io_github_jaquobia_Glfw_glfwGetTime
  (JNIEnv *env, jclass clazz)
  {
    return (jdouble)glfwGetTime();
  }

/*
 * Class:     Glfw
 * Method:    glfwSetTime
 * Signature: (D)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwSetTime
  (JNIEnv *env, jclass clazz, jdouble time)
  {
    glfwSetTime(time);
  }

/*
 * Class:     Glfw
 * Method:    glfwMakeContextCurrentJni
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwMakeContextCurrentJni
  (JNIEnv *env, jclass clazz, jlong window)
  {
    glfwMakeContextCurrent((GLFWwindow*)window);
  }

/*
 * Class:     Glfw
 * Method:    glfwGetCurrentContext
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_io_github_jaquobia_Glfw_glfwGetCurrentContext
  (JNIEnv *env, jclass clazz)
  {
    return (jlong)glfwGetCurrentContext();
  }

/*
 * Class:     Glfw
 * Method:    glfwSwapBuffers
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwSwapBuffers
  (JNIEnv *env, jclass clazz, jlong window)
  {
    glfwSwapBuffers((GLFWwindow*)window);
  }

/*
 * Class:     Glfw
 * Method:    glfwSwapInterval
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwSwapInterval
  (JNIEnv *env, jclass clazz, jint interval)
  {
    glfwSwapInterval(interval);
  }

/*
 * Class:     Glfw
 * Method:    glfwExtensionSupported
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_jaquobia_Glfw_glfwExtensionSupported
  (JNIEnv *env, jclass clazz, jstring extension)
  {
    auto cstrContents = env->GetStringUTFChars(extension, 0);
    auto ret = glfwExtensionSupported(cstrContents);
    env->ReleaseStringUTFChars(extension, cstrContents);
    return (jboolean)(ret == GL_TRUE);
  }




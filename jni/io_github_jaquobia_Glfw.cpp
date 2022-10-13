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
	static jmethodID keyId = 0;
	static jmethodID characterId = 0;
	static jmethodID mouseButtonId = 0;
	static jmethodID cursorPosId = 0;
	static jmethodID cursorEnterId = 0;
	static jmethodID scrollId = 0;

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
			getEnv()->CallVoidMethod(callback, windowFocusId, (jlong)window, (jboolean)(GL_TRUE==focused));
		}
	}

	void windowIconify(GLFWwindow* window, int iconified) {
		if(callback) {
			getEnv()->CallVoidMethod(callback, windowIconifyId, (jlong)window, (jboolean)(GL_TRUE==iconified));
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

		characterId = env->GetMethodID(callbackClass, "character", "(JC)V");
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
    std::cout << "Hint: " << hint << ", Value: " << value << std::endl;
    glfwWindowHint((int) hint, (int) value);
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
    std::cout << "JNI Attempting to make glfw Window\n";
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
      // std::cout << "Successfutlly made a window!\n";
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

/*
 * Class:     Glfw
 * Method:    glfwGetWindowMonitor
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_io_github_jaquobia_Glfw_glfwGetWindowMonitor
  (JNIEnv *env, jclass clazz, jlong window)
  {
    auto monitor = glfwGetWindowMonitor((GLFWwindow*) window);
    return (jlong) monitor;
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
  (JNIEnv *env, jclass clazz, jobject)
  {
    glfwPollEvents();
  }

/*
 * Class:     Glfw
 * Method:    glfwWaitEventsJni
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_io_github_jaquobia_Glfw_glfwWaitEventsJni
  (JNIEnv *env, jclass clazz)
  {
    glfwWaitEvents();
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
JNIEXPORT jboolean JNICALL Java_io_github_jaquobia_Glfw_glfwGetKey
  (JNIEnv *env, jclass clazz, jlong window, jint key)
  {
    return (jboolean)glfwGetKey((GLFWwindow*) window, (int) key);
  }

/*
 * Class:     Glfw
 * Method:    glfwGetMouseButton
 * Signature: (JI)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_jaquobia_Glfw_glfwGetMouseButton
  (JNIEnv *env, jclass clazz, jlong window, jint button)
  {
    return (jboolean)glfwGetMouseButton((GLFWwindow*) window, (int) button);
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




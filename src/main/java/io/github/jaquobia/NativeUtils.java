package io.github.jaquobia;/*
 * Class NativeUtils is published under the The MIT License:
 *
 * Copyright (c) 2012 Adam Heinrich <adam@adamh.cz>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

import java.io.*;
import java.nio.file.FileSystemNotFoundException;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.ProviderNotFoundException;
import java.nio.file.StandardCopyOption;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;

/**
 * A simple library class which helps with loading dynamic libraries stored in the
 * JAR archive. These libraries usually contain implementation of some methods in
 * native code (using JNI - Java Native Interface).
 *
 * @see <a href="http://adamheinrich.com/blog/2012/how-to-load-native-jni-library-from-jar">http://adamheinrich.com/blog/2012/how-to-load-native-jni-library-from-jar</a>
 * @see <a href="https://github.com/adamheinrich/native-utils">https://github.com/adamheinrich/native-utils</a>
 *
 */
public class NativeUtils {

    /**
     * The minimum length a prefix for a file has to have according to {@link File#createTempFile(String, String)}}.
     */
    private static final int MIN_PREFIX_LENGTH = 3;
    public static final String NATIVE_FOLDER_PATH_PREFIX = "nativeutils";

    /**
     * Temporary directory which will contain the DLLs.
     */
    private static File temporaryDir;

    /**
     * Private constructor - this class will never be instanced
     */
    private NativeUtils() {
    }

    /**
     * Practically sto.. *cough* copied from mc b1.7.3
     * @param libName name of the library
     * @param libPrefix if lib should be prefixed to the libname for unix, 99% of the time this will be true
     * @param macLibPrefix if lib should be prefixed to the libname for mac, useful for bundles
     * @param macDylib if .dylib should be used for mac, .so otherwise
     * @return a true name for the library based on the OS
     */
    public static String getOsDynamicLibName(String libName, boolean libPrefix, boolean macLibPrefix, boolean macDylib) {
        String osName = System.getProperty("os.name").toLowerCase();
        if (osName.contains("win")) {
            return (libName + ".dll");
        } else if (osName.contains("mac")) {
            return ((macLibPrefix ? "lib" : "") + libName + (macDylib ? ".dylib" : ".so"));
        } else { // this should be some unix-like architecture
            return ((libPrefix ? "lib" : "") + libName + ".so");
        }
    }

    /**
     * Load a dynamic library, first from the system path, then try to dispatch it.
     * @param libName   The unformatted name of the library, no lib-, -.so, -.dll, or -.dylib.
     * @param nativesPath   The path to the natives folder to load/dispatch the library, only get 1 that should be visible from {@link System#getProperty(String)}, where String is "java.library.path".
     */
    public static void LoadDynLib(String libName, String nativesPath) {
        System.out.println("Loading dynamic library " + libName);
        if (LoadFromSystem(libName, nativesPath)) {
            return;
        }

        String libNameFixed = getOsDynamicLibName(libName, true, true, false);
        if (DispatchAndLoadSystem(libName, libNameFixed, nativesPath)) {
            return;
        }

        if (DispatchAndLoadTemporary(libName, libNameFixed, nativesPath)) {
            return;
        }

        throw new IllegalArgumentException("Couldnt find " + libName + " in " + nativesPath + " dispatch it to native path, or generate a temporary file for it");
    }

    private static boolean LoadFromSystem(String libName, String nativesPath) {
        try {
            // Try to load the library outright
            System.out.print("Trying loading from natives directories: ");
            System.loadLibrary(libName);
            return true;
        } catch (UnsatisfiedLinkError | SecurityException | NullPointerException e) {
            if (e instanceof UnsatisfiedLinkError) {
                System.out.println("Couldn't find library in system path");
            } else if (e instanceof NullPointerException) {
                System.out.println("Not a valid library name");
            } else {
                e.printStackTrace();
            }
            return false;
        }
    }

    private static boolean DispatchAndLoadSystem(String libName, String libNameFixed, String nativesPath) {
        // Try to dispatch the library and try again
        try {
            // https://github.com/adamheinrich/native-utils
            // Don't try to dispatch if no path is provided
            if (nativesPath != null) {
                System.out.print("Trying dispatching and loading from natives directory " + nativesPath + " : ");
                boolean ret = NativeUtils.dispatchLibraryFromJar("/" + libNameFixed, nativesPath);
                return ret;
            }
            return false;
        } catch (UnsatisfiedLinkError | IOException ex) {
            return false;
        }
    }

    private static boolean DispatchAndLoadTemporary(String libName, String libNameFixed, String nativesPath) {
        // Try to extract to a temporary location and manually load
        try {
            System.out.println("Trying dispatching and loading from a temporary(delete on exit) directory: ");
            NativeUtils.loadLibraryFromJar("/" + libNameFixed);
            return true;
        } catch (IOException exc) {
            return false;
        }
    }

    /**
     * Loads library from current JAR archive
     *
     * The file from JAR is copied into system temporary directory and then loaded. The temporary file is deleted after
     * exiting.
     * Method uses String as filename because the pathname is "abstract", not system-dependent.
     *
     * @param path The path of file inside JAR as absolute path (beginning with '/'), e.g. /package/File.ext
     * @throws IOException If temporary file creation or read/write operation fails
     * @throws IllegalArgumentException If source file (param path) does not exist
     * @throws IllegalArgumentException If the path is not absolute or if the filename is shorter than three characters
     * (restriction of {@link File#createTempFile(java.lang.String, java.lang.String)}).
     * @throws FileNotFoundException If the file could not be found inside the JAR.
     */
    public static void loadLibraryFromJar(String path) throws IOException {

        if (null == path || !path.startsWith("/")) {
            throw new IllegalArgumentException("The path has to be absolute (start with '/').");
        }

        // Obtain filename from path
        String[] parts = path.split("/");
        String filename = (parts.length > 1) ? parts[parts.length - 1] : null;

        // Check if the filename is okay
        if (filename == null || filename.length() < MIN_PREFIX_LENGTH) {
            throw new IllegalArgumentException("The filename has to be at least 3 characters long.");
        }

        // Prepare temporary file
        if (temporaryDir == null) {
            temporaryDir = createTempDirectory(NATIVE_FOLDER_PATH_PREFIX);
            temporaryDir.deleteOnExit();
        }

        File temp = new File(temporaryDir, filename);

        try (InputStream is = NativeUtils.class.getResourceAsStream(path)) {
            Files.copy(is, temp.toPath(), StandardCopyOption.REPLACE_EXISTING);
        } catch (IOException e) {
            temp.delete();
            throw e;
        } catch (NullPointerException e) {
            temp.delete();
            throw new FileNotFoundException("File " + path + " was not found inside JAR.");
        }

        try {
            System.load(temp.getAbsolutePath());
        } finally {
            if (isPosixCompliant()) {
                // Assume POSIX compliant file system, can be deleted after loading
                temp.delete();
            } else {
                // Assume non-POSIX, and don't delete until last file descriptor closed
                temp.deleteOnExit();
            }
        }
    }

    /**
     * Loads library from current JAR archive
     *
     * The file from JAR is copied into system temporary directory and then loaded. The temporary file is deleted after
     * exiting.
     * Method uses String as filename because the pathname is "abstract", not system-dependent.
     *
     * @param pathToInnerLib The path of file inside JAR as absolute path (beginning with '/'), e.g. /package/File.ext
     * @throws IOException If temporary file creation or read/write operation fails
     * @throws IllegalArgumentException If source file (param path) does not exist
     * @throws IllegalArgumentException If the path is not absolute or if the filename is shorter than three characters
     * (restriction of {@link File#createTempFile(java.lang.String, java.lang.String)}).
     * @throws FileNotFoundException If the file could not be found inside the JAR.
     */
    public static boolean dispatchLibraryFromJar(String pathToInnerLib, String pathToNativesFolder) throws IOException {

        if (null == pathToInnerLib || !pathToInnerLib.startsWith("/")) {
            throw new IllegalArgumentException("The path has to be absolute (start with '/').");
        }

        // Obtain filename from path
        String[] parts = pathToInnerLib.split("/");
        String filename = (parts.length > 1) ? parts[parts.length - 1] : null;

        // Check if the filename is okay
        if (filename == null || filename.length() < MIN_PREFIX_LENGTH) {
            throw new IllegalArgumentException("The filename has to be at least 3 characters long.");
        }

        // Prepare temporary file
        File nativesDir = new File(pathToNativesFolder);
        if (!nativesDir.isDirectory()) {
            throw new IllegalArgumentException("The natives directory was not a folder.");
        }

        Optional<File> optLibFile = loadLibraryFromNativesFolder(nativesDir, filename);
        if (optLibFile.isPresent()) {
            System.load(optLibFile.get().getAbsolutePath());
            System.out.println("Found " + filename + " in native directory early");
            return true;
        }

        System.out.println();
        optLibFile = Optional.of(new File(nativesDir, filename));
        try (InputStream is = NativeUtils.class.getResourceAsStream(pathToInnerLib)) {
            Files.copy(is, optLibFile.get().toPath(), StandardCopyOption.REPLACE_EXISTING);
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }

        loadLibraryFromNativesFolder(nativesDir, filename);
        System.load(optLibFile.get().getAbsolutePath());
        return true;
    }

    private static Optional<File> loadLibraryFromNativesFolder(File nativesDir, String filename) {
        File[] rawFiles = nativesDir.listFiles();
        List<File> natives = rawFiles.length > 0 ? Arrays.asList(rawFiles) : new ArrayList<>();
        for (File f : natives) {
            if (f.getName().contains(filename)) {
                // Library is already dispatched! Load it and use it
                return Optional.of(f);
            }
        }
        return Optional.empty();
    }

    private static boolean isPosixCompliant() {
        try {
            return FileSystems.getDefault()
                    .supportedFileAttributeViews()
                    .contains("posix");
        } catch (FileSystemNotFoundException
                 | ProviderNotFoundException
                 | SecurityException e) {
            return false;
        }
    }

    private static File createTempDirectory(String prefix) throws IOException {
        String tempDir = System.getProperty("java.io.tmpdir");
        File generatedDir = new File(tempDir, prefix + System.nanoTime());

        if (!generatedDir.mkdir())
            throw new IOException("Failed to create temp directory " + generatedDir.getName());

        return generatedDir;
    }
}


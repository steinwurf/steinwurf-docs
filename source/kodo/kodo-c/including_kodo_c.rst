.. including_kodo_c:

Including kodo-c in Your Application
====================================

This guide shows how to include the Kodo C library in your application.

First of all, you need to build kodo-c following the :ref:`getting_started`
guide. If you want to cross-compile for your target platform (e.g. Android,
iOS, Raspberry Pi), please follow the :ref:`cross_compile` section.

In principle, you can use the library with any build system. Basically,
you can choose between the shared library and the static library.

Shared Library
--------------

In many cases, it is easier to include kodo-c as a *shared* library in
your application. With the following command, you can copy the compiled
shared library to the target folder specified by the ``install_path`` option.
In this example, we will create the ``shared_test`` folder for this purpose::

    python waf install --install_shared_libs --install_path="./shared_test"

The kodo-c shared library is called ``libkodoc.so`` on Linux, ``kodoc.dll`` on
Windows and ``libkodoc.dylib`` on Mac OSX. You can link with this shared
library using your own build system. You also need to include ``kodoc.h``
in your code. This header file is installed to the ``include`` folder within
the specified ``install_path``.

Now we copy an existing kodo-c example (encode_decode_simple) to the
``shared_test`` folder and we compile it to a binary called ``myapp``::

    cp examples/encode_decode_simple/encode_decode_simple.c shared_test/myapp.c
    cd shared_test

The following command demonstrates the necessary flags for the gcc/g++ compiler
(other compilers require similar settings)::

    gcc myapp.c -o myapp -I./include -L. -Wl,-Bdynamic -lkodoc -lstdc++ \
    -Wl,-rpath .

In practice, you should set the ``-I`` and ``-L`` flags to the path where you
installed the shared library.

Now you should be able to run the new binary::

    ./myapp

If you dynamically link your application with the shared library, then you
have to copy the shared library to a folder where your system can find it
when you execute your application. On Windows, you typically place the DLL
in the same folder as your executable. On Unix systems, you can set the
``rpath`` of your executable or you can adjust ``LD_LIBRARY_PATH`` to include
the path where you installed the shared library.

Static Library
--------------

After building kodo-c, you can install the static libraries to your target
folder with the following command (the ``install_path`` option specifies
the target folder which will be ``static_test`` in this example)::

    python waf install --install_static_libs --install_path="./static_test"

The kodo-c static library is called ``libkodoc_static.a`` on Linux and Mac and
``kodoc_static.lib`` on Windows. The install command also installs the static
libraries from the kodo-c dependencies (you will need the ``fifi`` and ``cpuid``
libraries as well).

You can link with these static libraries using your own build system. Of course,
you will need to include ``kodoc.h`` in your code (which is installed to the
``include`` folder within the specified ``install_path``).

Now we copy an existing kodo-c example (encode_decode_simple) to the
``static_test`` folder and we compile it to a binary called ``myapp``::

    cp examples/encode_decode_simple/encode_decode_simple.c static_test/myapp.c
    cd static_test

The following command demonstrates the necessary flags for the gcc/g++ compiler
(other compilers require similar settings)::

    gcc myapp.c -o myapp -I./include -Wl,-Bstatic -L. -lkodoc_static -lfifi \
    -lcpuid -Wl,-Bdynamic -lm -lstdc++

In practice, you should set the ``-I`` and ``-L`` flags to the path where you
installed the static libraries.

Now you should be able to run the new binary (note that this binary will
be quite large, since it includes all the static libraries)::

    ./myapp

It is important to note that you need to link with the C++ standard library
(by using ``-lstdc++`` above), because the kodo-c library actually wraps a
C++ library (kodo) that uses the C++ standard library. However, you can omit
this flag if you link your application with g++ instead of gcc (g++
automatically includes the stdc++ library)::

    g++ myapp.c -o myapp -I./include -Wl,-Bstatic -L. -lkodoc_static -lfifi \
    -lcpuid -Wl,-Bdynamic


Android
-------

The ``examples/android_app`` folder contains an Android Studio demo project
for including the kodo-c bindings in an Android application.

First we need to configure and build kodo-c using the Android NDK. Go to the
root of the kodo-c repository and run the following commands::

  python waf configure --cxx_mkspec=cxx_android_gxx48_armv7 \
  --android_sdk_dir={android-sdk} --android_ndk_dir={android-ndk}
  python waf build

Where ``{android-sdk}`` and ``{android-ndk}`` should be replaced with your
path to the Android SDK and a standalone version of the Android NDK.

After building kodo-c with the specified mkspec, you can install the generated
static libraries to ``examples/android_app/app/src/main/jni/libs/armeabi-v7a``.
It is also recommended to copy the ``kodoc.h`` header to
``examples/android_app/app/src/main/jni/kodoc/kodoc.h``.
After this, you need to adjust the build settings in
``examples/android_app/app/src/main/jni/Android.mk``. The preconfigured
solution shows how to link with the static libraries: ``kodoc fifi cpuid``.

.. note:: If you want to use the generated static libraries with ``ndk-build``,
          then make sure that you process at least one C++ source file (.cpp)
          with ``ndk-build`` (this might be a dummy cpp file). Otherwise you
          will get a lot of linkage issues, because ``ndk-build`` does not link
          with the C++ standard library by default.

Creating a new project
......................

First, create a new project using the Android Studio wizard.

Now add the path to the Android NDK to local.properties

Right click in the Project panel, then select: New -> Folder -> JNI Folder.

This will create a folder called C in the project panel
(note: the actual name of this folder on the filesystem is ``jni``).

Go to this newly generated directory and use ``javah`` to generate the
JNI headers, using the following command::

    javah -cp {android-sdk}/platforms/android-16/android.jar:../java {class}

Replace ``{android-sdk}`` with the path to the Android SDK on your
machine, and ``{class}`` with the name of the class. In the ``dummy_android``
sample project, this would be ``com.steinwurf.dummy_android.MainActivity``.
You can generate JNI headers for any class in your project.


iOS
---

The ``examples/ios_app/kodoc-ios-demo`` folder contains an iOS demo
project that can be opened in XCode. This project uses the iOS multi-arch
libraries that can be compiled by running the following helper scripts::

    cd examples/ios_app
    sh configure_and_build_all.sh
    sh build_ios_fat_libs.sh

This project should work on all architectures (device and simulator)
after you execute the helper scripts.

If you want to include kodo-c in your own Xcode project, then please set
the library and include path options as follows:

- Specify the library path and dependencies in "Link Binary with Libraries"
  under "Build Phases" in the project navigator.
- Specify the include path in "Header Search Paths" under "Search Paths",
  in the "Build Settings".

Manual compilation
..................

The helper scripts provided above can automate the build process, but you
can also configure and compile kodo-c manually for your desired architecture by
executing the following commands from the root of the kodo-c repository::

    python waf configure --cxx_mkspec=cxx_ios70_apple_llvm_{arch}
    python waf build
    python waf install --install_path=/tmp/{arch} --install_static_libs

The ``{arch}`` placeholder defines the target architecture. Currently
``armv7``, ``armv7s``, ``arm64``, ``i386``, and ``x86_64`` are available
(the latter two are needed for the iOS simulator builds).

The ``install_path`` option determines where the static libraries will be
installed. Here, we install the static libraries to ``/tmp/{arch}``. This
means 5 target folders for the 5 supported architectures.

After completing the above steps for each architecture, the static libraries
can be combined into a "fat", multi-arch static library using the ``lipo``
command::

  lipo -create /tmp/{arch1}/libkodoc_static.a /tmp/{arch2}/libkodoc_static.a \
  -output libkodoc_static.a

Several input libraries can be included in the multi-arch lib, e.g. all the
above-mentioned architectures.

You can use the ``file`` command to check if all the desired architectures
are included in the fat library::

    file libkodoc_static.a

This should output something like this::

    libkodoc_static.a: Mach-O universal binary with 5 architectures
    libkodoc_static.a (for architecture i386):      current ar archive random library
    libkodoc_static.a (for architecture x86_64):    current ar archive random library
    libkodoc_static.a (for architecture armv7):     current ar archive random library
    libkodoc_static.a (for architecture armv7s):    current ar archive random library
    libkodoc_static.a (for architecture arm64):     current ar archive random library

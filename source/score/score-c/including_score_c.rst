.. _including_score_c:

Including score-c in Your Application
=====================================

This guide shows how to include the score-c library in your application.

First of all, you need to build score-c following the :ref:`getting_started`
guide. If you want to cross-compile for your target platform (e.g. Android,
iOS, Raspberry Pi), please follow the :ref:`cross_compile` section.

In principle, you can use the library with any build system. Basically,
you can choose between the shared library and the static library.

Shared Library
--------------

In many cases, it is easier to include the *shared* library in
your application. With the following command, you can copy the compiled
shared library to the target folder specified by the ``install_path`` option.
In this example, we will create the ``shared_test`` folder for this purpose::

    python waf install --install_shared_libs --install_path="./shared_test"

The score-c shared library is called ``libscorec.so`` on Linux, ``scorec.dll``
on Windows and ``libscorec.dylib`` on Mac OSX. You can link with this shared
library using your own build system. You also need to include ``scorec.h``
in your code. This header file is installed to the ``include`` folder within
the specified ``install_path``.

Now we copy an existing score-c example (simple_sender) to the
``shared_test`` folder and we compile it to a binary called ``myapp``::

    cp examples/simple_sender/simple_sender.c shared_test/myapp.c
    cd shared_test

The following command demonstrates the necessary flags for the gcc/g++ compiler
(other compilers require similar settings)::

    gcc myapp.c -o myapp -I./include -L. -Wl,-Bdynamic -lscorec -lstdc++ \
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

After building score-c, you can install the static libraries to your target
folder with the following command (the ``install_path`` option specifies
the target folder which will be ``static_test`` in this example)::

    python waf install --install_static_libs --install_path="./static_test"

The score-c static library is called ``libscorec_static.a`` on Linux and Mac
and ``scorec_static.lib`` on Windows. The install command also installs the
static libraries from the score-c dependencies (you will need the ``fifi``and
``cpuid`` libraries as well).

You can link with these static libraries using your own build system. Of course,
you will need to include ``scorec.h`` in your code (which is installed to the
``include`` folder within the specified ``install_path``).

Now we copy an existing score-c example (simple_sender) to the
``static_test`` folder and we compile it to a binary called ``myapp``::

    cp examples/simple_sender/simple_sender.c static_test/myapp.c
    cd static_test

The following command demonstrates the necessary flags for the gcc/g++ compiler
(other compilers require similar settings)::

    gcc myapp.c -o myapp -I./include -Wl,-Bstatic -L. -lscorec_static -lfifi \
    -lcpuid -Wl,-Bdynamic -lm -lstdc++

In practice, you should set the ``-I`` and ``-L`` flags to the path where you
installed the static libraries.

Now you should be able to run the new binary (note that this binary will
be quite large, since it includes all the static libraries)::

    ./myapp

To reduce the size of the resulting binary, you can add the ``-s`` flag to the
gcc command above to strip all debugging symbols.

It is important to note that you need to link with the C++ standard library
(by using ``-lstdc++`` above), because the score-c library actually wraps a
C++ library (score) that uses the C++ standard library. However, you can omit
this flag if you link your application with g++ instead of gcc (g++
automatically includes the stdc++ library)::

    g++ myapp.c -o myapp -I./include -Wl,-Bstatic -L. -lscorec_static -lfifi \
    -lcpuid -Wl,-Bdynamic



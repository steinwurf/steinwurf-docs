.. _including_score:

Including score in Your Application
===================================

This guide shows how to include the score library in your application.

First of all, you need to build score following the :ref:`getting_started`
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

The score shared library is called ``libscore_shared.so`` on Linux,
``score_shared.dll`` on Windows and ``libscore_shared.dylib`` on Mac OSX.
You can link with this shared library using your own build system.
The necessary header files are installed to the ``include`` folder within
the specified ``install_path``. So you can include the necessary header
files in your code, for example ``<score/api/udp_sender.hpp>``.

Now we copy an existing score example (udp_object_sender) to the
``shared_test`` folder and we compile it to a binary called ``myapp``::

    cp examples/udp_object_sender_receiver/udp_object_sender.cpp shared_test/myapp.cpp
    cd shared_test

The following command demonstrates the necessary flags for the g++ compiler
(other compilers require similar settings)::

    g++ myapp.cpp -o myapp -std=c++14 -I./include -L. -Wl,-Bdynamic \
    -lscore_shared -Wl,-rpath .

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

After building score, you can install the static libraries to your target
folder with the following command (the ``install_path`` option specifies
the target folder which will be ``static_test`` in this example)::

    python waf install --install_static_libs --install_path="./static_test"

The top-level score static library is called ``libscore_static.a`` on Linux and
Mac and ``score_static.lib`` on Windows. Actually, the install command also
installs the static libraries from several score dependencies that are needed
when you link your application against the top-level shared library (the
compilation commands below show the list of required libraries).

You can link with these static libraries using your own build system.
The necessary header files are installed to the ``include`` folder within
the specified ``install_path``. So you can include the necessary header
files in your code, for example ``<score/api/udp_sender.hpp>``.

Now we copy an existing score example (udp_object_sender) to the
``static_test`` folder and we compile it to a binary called ``myapp``::

    cp examples/udp_object_sender_receiver/udp_object_sender.cpp static_test/myapp.cpp
    cd static_test

The following command demonstrates the necessary flags for the g++ compiler
(other compilers require similar settings)::

    g++ myapp.cpp -o myapp -std=c++14 -I./include -L. -lscore_static \
    -lscore_internal -lchunkie -lfifi -lcpuid -lboost_system

In practice, you should set the ``-I`` and ``-L`` flags to the path where you
installed the static libraries.

Now you should be able to run the new binary (note that this binary will
be quite large, since it includes all the static libraries)::

    ./myapp

To reduce the size of the resulting binary, you can add the ``-s`` flag to the
g++ command above to strip all debugging symbols.


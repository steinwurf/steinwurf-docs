.. _hello_kodo:

Hello Kodo
----------

This example shows how to use our build system to create a simple C++
application which depends on kodo-rlnc. The example consists of 3 files:
``main.cpp``, ``wscript`` and ``waf``.

``main.cpp`` contains a very limited amount of code:

.. literalinclude:: /../../kodo-rlnc/examples/hello_kodo/main.cpp
    :language: c++
    :linenos:

It's basically a main function which prints ``Hello Kodo!`` and exits. In this
example, we include a particular RLNC codec defined in the following header
file:

.. literalinclude:: /../../kodo-rlnc/examples/hello_kodo/main.cpp
    :language: c++
    :start-after: //! [0]
    :end-before: //! [1]
    :linenos:

The include is not used however. Its only purpose is to detect whether or not
the include paths for the kodo-rlnc library are configured correctly.

The remaining two files are needed to build the executable.
The ``waf`` file is a `complete standalone build system <https://waf.io/>`_,
whereas the ``wscript`` is the recipe used by ``waf`` to build our example.
The ``wscript`` contains information regarding dependencies and build targets.
The simplest way to get started is to copy the files to a folder of your own
choosing, and then run the following commands in a terminal (while using the
selected folder as your working directory).

.. code-block:: none

    python waf configure
    python waf build

The build system will download all dependencies, compile some static libraries
and finally the example. You can find the compiled executable in the waf build
folder, which depends on your operating system:

   a. **Linux**: ``./build/linux``

   b. **Mac OSX**: ``./build/darwin``

   c. **Windows**: ``./build/win32``

You can directly run the executable by executing the appropriate command::

    ./build/linux/hello_kodo
    ./build/darwin/hello_kodo
    build\win32\hello_kodo.exe

You can use this as a starting point for the coming examples, or even your own
application.

For more information regarding how to use the waf build systems, go
:ref:`here<waf_build_system>`.

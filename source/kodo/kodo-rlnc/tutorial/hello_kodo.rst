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
The simplest way to get started is to copy the ``hello_kodo`` files to a folder
where you want to develop your application, and then run the standard waf
commands in that folder (the ``cp`` command is Unix-only)::

    cd kodo-rlnc
    cp -R examples/hello_kodo/ ~/my_app
    cd my_app
    python waf configure
    python waf build

The build system will download all dependencies, compile some static libraries
and finally the example. You can find the compiled executable in the waf build
folder, which depends on your operating system:

   a. **Linux**: ``./build/linux``

   b. **Mac OSX**: ``./build/darwin``

   c. **Windows**: ``./build/win32``

You can directly run the executable by executing the appropriate command::

    build/linux/hello_kodo
    build/darwin/hello_kodo
    build\win32\hello_kodo.exe

You can use this as a starting point for the coming examples, or even your own
application.

For more information regarding how to use the waf build system, go
:ref:`here<waf_build_system>`.

Note that the currently used version of kodo-rlnc is set in the ``resolve``
function of the ``wscript`` file like this:

.. code-block:: python
    :emphasize-lines: 5

    ctx.add_dependency(
        name='kodo-rlnc',
        resolver='git',
        method='semver',
        major=9,
        sources=['github.com/steinwurf/kodo-rlnc.git'])

When a new major version is released and you want to update, you can just
modify this version number and run ``python waf configure`` again to get
the chosen version.

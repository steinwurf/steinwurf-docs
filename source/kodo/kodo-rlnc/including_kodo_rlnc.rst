.. _including_kodo_rlnc:

Including kodo-rlnc in Your Application
=======================================

The following sections describe how you can include kodo-rlnc in your
application / project.

.. contents:: Table of Contents
   :local:

Using waf as a Build System
---------------------------

The easiest option is to use the waf build system and our tools to define
kodo-rlnc as a dependency for your standalone project. The
:ref:`hello_kodo` section provides a great starting point that can be extended
to meet your specific requirements. It is easy to learn the basic features
of waf from the `official documentation <https://waf.io/>`_ or from our simple
examples.

Using Another Build System
--------------------------

If you cannot use waf for some reason, then it is also possible to compile
kodo-rlnc with another build system. Of course, this requires more manual
configuration.

Note that kodo-rlnc contains a static library and some header-only components.
Moreover, it also requires some dependencies that are compiled as
static libraries. This means that both kodo-rlnc and its dependencies
should be included when you build a custom application.

The following guide explains how you can do this manually with ``g++``,
you can adapt these commands to your custom build system.

#. As a starting point, we assume that you completed the kodo-rlnc
   :ref:`quick_start_kodo_rlnc` section and you can successfully execute our
   unit tests with this command::

    python waf --run_tests

#. The following command will copy the static libraries to the ``kodo_build``
   folder (these static libraries should be added to your application)::

    python waf install --install_path=kodo_build --install_static_libs

#. Here we show the command to manually compile one of the Kodo examples
   (you can use your own application instead). Change the directory to the
   decode_encode_simple example::

    cd examples/encode_decode_simple

#. Compile the example using the following (rather long) command::

    g++ \
    -O2 \
    -ftree-vectorize \
    -std=c++14 \
    -I../../src \
    -I../../resolve_symlinks/boost \
    -I../../resolve_symlinks/fifi/src \
    -I../../resolve_symlinks/kodo-core/src \
    -I../../resolve_symlinks/storage/src \
    -I../../resolve_symlinks/endian/src \
    encode_decode_simple.cpp \
    -o encode_decode_simple \
    -Wl,-Bstatic \
    -L../../kodo_build \
    -lkodo_rlnc \
    -lfifi \
    -lcpuid \
    -Wl,-Bdynamic

   This command is only provided to facilitate the integration with your build
   system or IDE. It is not recommended to build your software manually with a
   command like this.

   .. warning:: This command only contains the basic optimization flags, and
                you might need to add more flags to get optimal performance.

   .. warning:: The relative include paths presented here are going to change
                according to the location of your application. It is
                recommended to use absolute paths or environment variables
                in your build system. Furthermore, you might need to add
                more include paths and libraries depending on the actual
                program that you want to compile.

#. Run the compiled example application::

    ./encode_decode_simple





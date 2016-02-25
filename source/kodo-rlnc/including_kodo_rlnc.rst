.. _including-kodo-rlnc:

Including kodo-rlnc in Your Application
=======================================
Following sections describe what you need to do to include Kodo in your
application / project, and how to handle the Kodo dependencies using our
build system.

.. contents:: Table of Contents
   :local:

Including Kodo and Its Dependencies
------------------------------------
Kodo is a header-only library with some dependencies that are compiled as
static libraries. This means that both Kodo and its dependencies
should be included in an application that uses Kodo.

The easiest way to achieve that is to use our build system. You can find more
information about how to do so in :ref:`this tutorial<hello_kodo>`.

If this approach is not feasible for you for some reason, the following will
guide you through one of the many other ways to include Kodo in your
application.

.. note:: If you have issues, please double check that you have all the
          requirements specified in the :ref:`getting_started` section.
          If you do, please write on our developer
          `mailing list <http://groups.google.com/group/steinwurf-dev>`_, and
          we'll be happy to help.

#. Start by cloning the Kodo repository to a folder of your choice::

    cd folder/of/your/choice
    git clone https://github.com/steinwurf/kodo.git

#. Now change directory to the kodo repository::

    cd kodo

#. Configure kodo using our build system. The Kodo build system is capable of
   automatically downloading its dependencies. This is further elaborated in
   `Kodo Dependency Management`_::

    python waf configure

#. Assuming everything went as planned, you should have a folder called
   ``bundle_dependencies`` in your kodo folder. You can now build
   Kodo and its dependencies::

    python waf build

#. You can run the unit tests to verify that Kodo works fine on your system::

    python waf --run_tests

#. The following command will copy the static libraries to the ``kodo_build``
   folder (these static libraries should be added to your application)::

    python waf install --install_path=kodo_build --install_static_libs

#. At this point, you should be ready to include Kodo in your application.
   Here we demonstrate the procedure with one of the Kodo examples (you can
   use your own application instead). Change the directory to the
   decode_encode_simple example::

    cd examples/encode_decode_simple

#. Compile the example using the following (rather long) command::

    g++ \
    -O2 \
    -ftree-vectorize \
    -std=c++0x \
    -I../../src \
    -I../../bundle_dependencies/boost-abe3de/1.7.0 \
    -I../../bundle_dependencies/cpuid-4d8071/3.1.0/src \
    -I../../bundle_dependencies/fifi-8960fd/15.0.0/src \
    -I../../bundle_dependencies/platform-bccd32/1.1.0/src \
    -I../../bundle_dependencies/recycle-b2469b/1.0.1/src \
    -I../../bundle_dependencies/sak-1bdcea/13.0.0/src \
    encode_decode_simple.cpp \
    -o encode_decode_simple \
    -Wl,-Bstatic \
    -L../../kodo_build \
    -lfifi \
    -lcpuid \
    -lsak \
    -Wl,-Bdynamic

   This command is only provided to facilitate the integration with your build
   system or IDE. It is not recommended to build your software manually with a
   command like this.

   .. warning:: This command only contains the basic optimization flags, and
                you might need to add more flags to get maximum performance.

   .. warning:: The include paths presented here are going to change when a new
                version of a dependency is released and you run
                ``python waf configure`` to reconfigure your project. You can
                update the include paths based on the output of the configure
                command. Note that the include paths will be different if you
                use the Git-over-SSH protocol to clone Kodo from Github.

#. Run the compiled example application::

    ./encode_decode_simple

Using a Makefile
----------------

If you would like to see an example to build an application with
Kodo using a makefile. We provide a small makefile
which shows how to invoke the ``g++`` compiler. The example can be found
in the ``examples/sample_makefile`` folder in the `Kodo repository`_.

.. _`Kodo repository`: https://github.com/steinwurf/kodo/blob/master/examples/sample_makefile/makefile

By default, the example makefile assumes that the required libraries are
downloaded side-by-side with Kodo itself.
To achieve this, you can clone the projects in the same directory::

    git clone https://github.com/steinwurf/cpuid.git
    git clone https://github.com/steinwurf/boost.git
    git clone https://github.com/steinwurf/fifi.git
    git clone https://github.com/steinwurf/platform.git
    git clone https://github.com/steinwurf/sak.git
    git clone https://github.com/steinwurf/kodo.git

You can now build the example with make::

    cd kodo/examples/sample_makefile
    make

And execute the ``encode_decode_simple`` binary::

    ./encode_decode_simple


.. _kodo-dependencies:

Kodo Dependency Management
--------------------------
Kodo relies on a number of external libraries, these must be available
in order to compile an application including Kodo.

The easiest way to get these is by using the Kodo build scripts. It will
automatically download and setup the dependencies and build the Kodo library.

The libraries are:

#. **Cpuid**: this library contains functionality to detect certain CPU
   features.

   https://github.com/steinwurf/cpuid

#. **Boost** C++ libraries: this library contains a wide range
   of C++ utilities. We use only a subset of this functionality, such as
   smart pointers.

   https://github.com/steinwurf/boost

#. **Fifi**: this library contains finite field arithmetics used in ECC
   (Error Correcting Code) algorithms.

   https://github.com/steinwurf/fifi

#. **Platform**: this library contains functionality to detect the compiler and
   target platform architecture.

   https://github.com/steinwurf/platform

#. **Sak**: this library contains a few utility functions used in Kodo such as
   endian conversion.

   https://github.com/steinwurf/sak

.. note:: Additional libraries, besides the ones listed above, will be
   downloaded if you use the Kodo build script. These libraries are only needed
   when/if you want to compile the Kodo unit tests or benchmarks.
   So you don't have to link with these when using Kodo in your application.

.. _selecting-the-correct-versions:

Selecting the Correct Versions
..............................
If you use the Kodo build script to build Kodo, the latest compatible versions
of its dependencies will automatically be downloaded. If you download
the dependencies manually, you will have to select a compatible version
yourself. This information is stored in the ``wscript`` file found in Kodo's
root folder.

Within that file, in the ``resolve`` function, you will find all Kodo's
dependencies specified in the following way:

.. code-block:: python
    :emphasize-lines: 4

    ctx.add_dependency(resolve.ResolveVersion(
        name='fifi',
        git_repository='github.com/steinwurf/fifi.git',
        major=21))

The above command sets up a dependency for the Fifi library. The version
required is specified in the ``major=21`` line. This means that Kodo
requires version ``21.x.y`` of the Fifi library, where ``x.y`` should be
selected to pick the newest available version. You can get a list of available
versions by visiting the download page at GitHub for the Fifi library:

* https://github.com/steinwurf/fifi/releases

At the time of writing, the appropriate version for Fifi, when using Kodo
(master branch), would be version ``21.0.0``. Note these version numbers are
available as ``git tags`` if you choose to manually checkout the git
repositories.

.. _download-kodo-dependencies:

Download Kodo Dependencies
..........................

There are several ways in which you may get the Kodo library and its
dependencies.

#. As shown in the :ref:`getting_started` section, the Kodo build scripts
   supports downloading the dependency repositories automatically. The build
   script will do a ``git clone`` and check out the latest compatible tagged
   version of the dependency.

#. You may wish to manually download Kodo's dependencies as separate git
   repositories, see `Download Using Git`_.

#. You can also download the Kodo dependencies as zip or tar.gz archives
   from the dependencies corresponding GitHub page, see
   `Download as zip/tar.gz archives`_.

.. note:: Downloading all dependencies is only necessary if you wish to build
          Kodo using our build system. If you simply want to use Kodo
          in your application you only need to download the libraries listed
          under `Kodo Dependency Management`_.

Download Using Git
^^^^^^^^^^^^^^^^^^

#. Create a suitable directory for the projects (optional)::

     mkdir dev
     cd dev

#. Clone and download the libraries by running::

      git clone https://github.com/steinwurf/cpuid.git
      git clone https://github.com/steinwurf/boost.git
      git clone https://github.com/steinwurf/fifi.git
      git clone https://github.com/steinwurf/platform.git
      git clone https://github.com/steinwurf/sak.git

      git clone https://github.com/steinwurf/gauge.git
      git clone https://github.com/steinwurf/gtest.git
      git clone https://github.com/steinwurf/tables.git
      git clone https://github.com/steinwurf/waf-tools.git

Now we have to select the correct versions for all the downloaded dependencies
e.g. for Fifi, first list the available tags::

    cd fifi
    git tag -l

Using the information from the ``wscript`` (described in
`Selecting the correct versions`_) we can checkout a tagged version::

    git checkout 21.0.0

We now do this for all the downloaded repositories.

Download as zip/tar.gz archives
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Here we have to visit the download pages of the different dependencies
and download the correct versions (described in `Selecting the correct
versions`_):

#. Cpuid: https://github.com/steinwurf/cpuid/releases
#. Boost: https://github.com/steinwurf/boost/releases
#. Fifi: https://github.com/steinwurf/fifi/releases
#. Platform: https://github.com/steinwurf/platform/releases
#. Sak: https://github.com/steinwurf/sak/releases

#. Gauge: https://github.com/steinwurf/gauge/releases
#. Gtest: https://github.com/steinwurf/gtest/releases
#. Tables: https://github.com/steinwurf/tables/releases
#. Waf-tools: https://github.com/steinwurf/waf-tools/releases


Configuring Kodo With Manually Downloaded Dependencies
......................................................

After downloading all the dependencies manually, we have to inform the
Kodo build scripts to use those instead of trying to automatically downloading
them. Assuming you have the kodo repository alongside the downloaded
dependencies, this can be done using the following command::

  python waf configure \
  --cpuid-path=../cpuid \
  --boost-path=../boost \
  --fifi-path=../fifi \
  --platform-path=../platform \
  --sak-path=../sak \
  --gauge-path=../gauge \
  --gtest-path=../gtest \
  --tables-path=../tables \
  --waf-tools-path=../waf-tools

The bundle options supports a number of different use cases. The following
will bundle all dependencies but the Fifi library, which we have to
manually specify a path for::

  python waf configure --fifi-path=../fifi

Or we may bundle some selected libraries::

  python waf configure \
  --cpuid-path=../cpuid \
  --boost-path=../boost \
  --tables-path=../tables \
  --waf-tools-path=../waf-tools

The bundle options can be seen by running::

  python waf --help

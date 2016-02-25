.. _getting_started_kodo_rlnc:

Getting Started
===============

Obtain a License for Kodo
-------------------------
Before you download or use Kodo you **MUST** obtain a valid license.

* If you will use Kodo for **research and educational** purposes, please
  fill out this form_ to obtain a research license.

* If you will **evaluate or test** Kodo in a commercial context, you can
  obtain a 30-day trial license by filling out this form_ or contact us
  at sales@steinwurf.com.

* For a general **commercial license**, contact us at sales@steinwurf.com

.. _form: http://steinwurf.com/license/

.. _tools-needed:

Tools Needed
------------

If you wish to build Kodo (using our build system), you will need to
install the following tools:

1. **C++11 compliant compiler:** Kodo is a C++11 library so you will need
   a C++ compiler that supports the new C++11 standard. You
   can see a list of compilers on our buildbot page (`Steinwurf Buildbot`_).

2. **Git:** we use the git version control system for managing our libraries.

3. **Python:** needed by our build scripts. We use the Python based `waf`_
   build system.

.. _waf: https://code.google.com/p/waf/
.. _Steinwurf Buildbot: http://buildbot.steinwurf.dk

The following sections describe how to install the tools on different platforms.

Download Tools (Ubuntu or other Debian-based distributions)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Get the dependencies using the following command::

    sudo apt-get install g++ python git-core

Download Tools (Windows)
~~~~~~~~~~~~~~~~~~~~~~~~

1. **C++11 compliant compiler:** You need a working C++11 compiler. We tested
   `Visual Studio Express 2013 for Windows Desktop`_ (which is free of
   charge).

2. **Python:** You need a working Python installation. Find the available
   download on the `Python homepage`_. If you are in doubt about which version
   to install, you may use the `Python 2.7.9 Windows Installer`_.

3. **Git:** There are several ways to get git on Windows. If you plan to use
   the waf build scripts to build the Kodo examples and unit tests, you should
   install the msysgit_ tool (version 1.8.x and above).

4. **TortoiseGit (Optional):**
   You can also install the latest version of TortoiseGit_ if you prefer to use
   a GUI instead of the command-line git tools. Version 1.8.1 and later should
   work fine.

.. _`Visual Studio Express 2013 for Windows Desktop`:
   http://www.microsoft.com/visualstudio/eng/downloads

.. _`Python homepage`:
   http://www.python.org/download/

.. _`Python 2.7.9 Windows Installer`:
   https://www.python.org/ftp/python/2.7.9/python-2.7.9.msi

.. _msysgit:
   http://msysgit.github.io/

.. _`TortoiseGit`:
   https://code.google.com/p/tortoisegit/

Download Tools (Mac OSX)
~~~~~~~~~~~~~~~~~~~~~~~~

**C++11 compliant compiler:** You need a working C++ compiler. We have
tested using `XCode`_ 6.0 and the Apple LLVM 6.0 compiler which can be
downloaded free of charge. Newer versions should also be fine.

On Mountain Lion (OSX 10.8):
   1. Download and install `XCode`_ from the Mac App Store
   2. Open XCode Preferences/Downloads and install **Command Line Tools**

On Mavericks (OSX 10.9):
   1. Installing `XCode`_ from the Mac App Store is optional
   2. Install the standalone **Command Line Tools** package::

        xcode-select --install

   This command will open a GUI window (do not run this over SSH).

.. _`XCode`:
   https://developer.apple.com/xcode/


Download the Kodo Source Code
-----------------------------

The library can be downloaded with git. This version control system allows you
to easily get new updates whenever the library is updated.

If you don't want to type your GitHub username and password when downloading
Kodo (and its dependencies), then we recommend using Git-over-SSH. It is easy
to configure SSH authentication on all platforms following this `Github guide`_.

You don't have to use a passphrase, and you can skip Step 3. If you are using
Windows, then run these commands in Git Bash (which is installed with msysgit).
We don't recommend using "GitHub for Windows", so don't follow the
Windows-specific guide (the generic guide is good for all platforms).

.. note:: If you don't want to configure SSH authentication against github.com,
          you can also clone the repository with the ``https`` protocol
          (URL: ``https://github.com/steinwurf/kodo-rlnc.git``).

          Normally, you have to type your GitHub username and password with
          ``https``. On Windows, you can configure msysgit to store your
          credentials with the following command::

              git config --global credential.helper wincred


.. _`Github guide`:
   https://help.github.com/articles/generating-ssh-keys/#platform-all

Recommended: Clone the Git Repository Using the Terminal (Linux and Mac OSX)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. (Optional) Create a suitable directory (e.g. 'dev') for the projects using
   the terminal::

    mkdir dev
    cd dev

2. Clone and download the Kodo library by running (this will create a
   new directory called 'kodo')::

    git clone git@github.com:steinwurf/kodo-rlnc.git

Recommended: Clone the Git Repository Using TortoiseGit (Windows)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Open the directory where you want to clone the project, right-click on empty
space and select **Git Clone...** from the context menu. The TortoiseGit clone
dialog will appear, copy this to the URL field::

    git@github.com:steinwurf/kodo-rlnc.git

You can also customize the name of the target directory if you wish.
By default, a new folder called 'kodo' will be created.

.. _waf_build_system:

Waf (Build System)
------------------

We use the Waf build system to build all Kodo examples and
unit tests. Waf is a Python-based build system that supports
a wide variety of use cases. You may read more about Waf at
the project homepage: http://code.google.com/p/waf/

A Waf project typically contains two types of files:

1. The ``waf`` file is the actual build system executable.
   This binary file is not meant to be edited.

2. Several ``wscript`` and ``wscript_build`` files: These files contain the
   project build information. You can think of it as a type
   of ``makefile`` written in Python.

.. note:: See the ``waf`` build options by running ``python waf -h``
          in your terminal.

In the following, we will look at how you can build Kodo's examples, benchmarks
and unit tests using the Waf build system.

Quick Start (Building Kodo Examples and Unit Tests)
---------------------------------------------------

.. _quick-start:

If you are primarily interested in quickly trying some Kodo examples
or building the unit tests, we have tried to make that as easy as possible.
Provided that you have the `Tools Needed`_ installed.

.. note:: We recommend trying to build and run the unit tests before
          using Kodo in your own project. However, if you want to skip this step
          you may jump directly to :ref:`including-kodo-in-your-application`

1. Navigate to the directory where you have downloaded the Kodo source code::

     cd dev/kodo-rlnc/

2. Invoke ``waf`` to build the Kodo unit tests and examples::

     python waf configure

   The ``waf configure`` command ensures that all tools needed by Kodo are
   available and prepares to build Kodo. This step will also download
   several auxiliary libraries (see :ref:`kodo-dependencies`) into a
   folder called ``bundle_dependencies`` within the kodo folder.

   .. note:: The ``waf configure`` step might take several minutes depending on
             the speed of your Internet connection. This would be a
             good time to grab a coffee or similar while the dependencies are
             downloaded. If you do not have an Internet connection you can see
             the :ref:`including-kodo-in-your-application` section which shows
             how to manually download and specify the Kodo dependencies.

   .. note:: You can specify the ``--bundle=ALL`` option to instruct waf
             to download all dependencies. You can also use the
             ``--bundle-path`` option to specify the download location for the
             dependencies (if you want to change the default location).

             On Linux and Mac OSX::

                 python waf configure --bundle-path=~/dev/bundle_dependencies

             On Windows, you can also specify the ``bundle-path`` as an absolute
             path with a drive letter, for example::

                 python waf configure --bundle-path=C:\dev\bundle_dependencies


   .. note:: If you have not configured SSH to automatically authenticate
             against github.com, you might see a similar error::

                 Resolve dependency sak: Command ['C:\\Program Files (x86)\\Git\\
                 bin\\git.exe', 'clone', 'git@github.com:steinwurf/sak.git',
                 'C:\\dev\\bundle_dependencies\\sak-2baed8\\master'] returned 128

             In this case, you can instruct the waf tools to use the ``https``
             protocol for downloading the dependencies by adding the
             ``--git-protocol=https://`` option to the ``configure`` command
             (you might have to type your GitHub username and password)::

                 python waf configure --git-protocol=https://


3. Invoke ``waf`` to build the unit tests and examples::

       python waf build

4. Run the Kodo unit tests::

       python waf --run_tests

   You can also run the generated executables by specifying their relative path
   (this will vary depending on the operating system):

   a. **Linux**: Run unit tests from the Kodo directory by running
      ``./build/linux/test/kodo_rlnc_tests`` in your terminal.

   b. **Mac OSX**: Run unit tests from the Kodo directory by running
      ``./build/darwin/test/kodo_rlnc_tests`` in your terminal.

   c. **Windows**: Run unit tests from the Kodo directory by running
      ``build/win32/test/kodo_rlnc_tests.exe`` in your command prompt.

Customize the Build
-------------------

You may also customize the build process. The list below describes the most
common changes you may want for your build.

* Changing the compiler

  To change compiler, set the ``CXX`` variable to your preferred compiler.
  In case you want to use clang++, add ``CXX=clang++`` in front of
  ``python waf configure``::

      CXX=clang++ python waf configure

  .. note:: ``clang++`` is currently the default compiler on Mac OSX, therefore
            this customization step is not needed on that operating system.

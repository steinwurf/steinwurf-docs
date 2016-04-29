.. _quick_start_score_cpp:

Quick Start
===========

You should complete all steps in the :ref:`getting_started` guide before you
try to download and build the source code.

Download the Source Code
------------------------

Recommended: Clone the Git Repository Using the Terminal (Linux and Mac OSX)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. (Optional) Open your Terminal and create a new directory (e.g. ``~/dev``)
   in your home folder that will contain this project and its dependencies::

    cd ~
    mkdir dev
    cd dev

2. Clone and download the score-cpp library by running (this will create a
   new directory called ``score-cpp``)::

    git clone git@gitlab.com:steinwurf/score-cpp.git

Recommended: Clone the Git Repository Using TortoiseGit (Windows)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Open the directory where you want to clone the project, right-click on empty
space and select ``Git Clone...`` from the context menu. The TortoiseGit clone
dialog will appear, copy this to the URL field::

    git@gitlab.com:steinwurf/score-cpp.git

You can also customize the name of the target directory if you wish.
By default, a new folder called ``score-cpp`` will be created.

.. note:: If you decide to clone the repository with the ``https`` protocol
          then use this URL in TortoiseGit::

            https://gitlab.com/steinwurf/score-cpp.git


Building the Score Examples and Unit Tests
------------------------------------------

In the following, we will look at how you can build the Score examples
and unit tests using the Waf build system.

1. Navigate to the directory where you have downloaded the Score source code::

     cd ~/dev/score-cpp/

2. Invoke ``waf`` to build the Score unit tests and examples::

     python waf configure

   The ``waf configure`` command ensures that all tools needed by Score are
   available and prepares to build Score. This step will also download
   several libraries into a local folder called ``bundle_dependencies``.

   .. note:: The ``waf configure`` step might take several minutes depending on
             the speed of your Internet connection. This would be a
             good time to grab a coffee or similar while the dependencies are
             downloaded.

   .. note:: You can use the ``--bundle-path`` option to specify the download
             location for the dependencies (if you want to change the default
             location).

             On Linux and Mac OSX::

                 python waf configure --bundle-path=~/dev/bundle_dependencies

             On Windows, you can also specify the ``bundle-path`` as an absolute
             path with a drive letter, for example::

                 python waf configure --bundle-path=C:\dev\bundle_dependencies

   .. note:: If you have not configured Git-over-SSH to automatically
             authenticate on gitlab.com, you might see an error when waf
             tries to resolve the dependencies.

             In this case, you can instruct the waf tools to use the ``https``
             protocol for downloading the dependencies by adding the
             ``--git-protocol=https://`` option to the ``configure`` command
             (you will have to type your GitHub username and password)::

                 python waf configure --git-protocol=https://


3. Invoke ``waf`` to build the unit tests and examples::

       python waf build

4. Run the unit tests::

       python waf --run_tests

   You can find the compiled library and executables in the waf build folder,
   which depends on your operating system:

   a. **Linux**: ``./build/linux``

   b. **Mac OSX**: ``./build/darwin``

   c. **Windows**: ``./build/win32``

   You can directly run the executables here.

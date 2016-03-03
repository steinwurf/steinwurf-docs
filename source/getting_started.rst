.. _getting_started:

Getting Started
===============

Obtain a Steinwurf License
--------------------------

Before you download or use Kodo you **MUST** obtain a valid license.

* If you will use Kodo for **research and educational** purposes, please
  fill out this form_ to obtain a Research License.

* If you will **evaluate or test** Kodo in a commercial context, you can
  obtain a Commercial Evaluation License for a license fee. You can fill out
  this form_ or contact us at sales@steinwurf.com.

* For a general **commercial license**, contact us at sales@steinwurf.com.

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

3. **Python:** needed by our build scripts. We use the Python-based `waf`_
   build system.

.. _waf: https://waf.io/
.. _Steinwurf Buildbot: http://buildbot.steinwurf.com

The following sections describe how to install the tools on different platforms.

Download Tools (Ubuntu or other Debian-based distributions)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Get the dependencies using the following command::

    sudo apt-get install g++ python git-core

Download Tools (Windows)
~~~~~~~~~~~~~~~~~~~~~~~~

1. **C++11 compliant compiler:** You need a working C++11 compiler. We tested
   `Visual Studio Express 2015 for Desktop`_ (which is free of charge).

2. **Python:** You need a working Python installation. Find the available
   download on the `Python homepage`_. If you are in doubt about which version
   to install, you may use the `Python 2.7.10 Windows Installer`_.

3. **Git:** There are several ways to get git on Windows. If you plan to use
   the waf build scripts to build the Kodo examples and unit tests, you should
   install the msysgit_ tool (version 1.8.x or above).

4. **TortoiseGit (Optional):**
   You can also install the latest version of TortoiseGit_ if you prefer to use
   a GUI instead of the command-line git tools. Version 1.8.1 and later should
   work fine.

.. _`Visual Studio Express 2015 for Desktop`:
   https://www.visualstudio.com/downloads/download-visual-studio-vs

.. _`Python homepage`:
   http://www.python.org/download/

.. _`Python 2.7.10 Windows Installer`:
   https://www.python.org/ftp/python/2.7.10/python-2.7.10.msi

.. _msysgit:
   http://msysgit.github.io/

.. _`TortoiseGit`:
   https://tortoisegit.org/

Download Tools (Mac OSX)
~~~~~~~~~~~~~~~~~~~~~~~~

**C++11 compliant compiler:** You need a working C++ compiler. We have
tested using `XCode`_ 7.0 and the Apple LLVM 7.0 compiler which can be
downloaded free of charge. Newer versions should also be fine.

On Mavericks or above (OSX 10.9+):
   1. Installing `XCode`_ from the Mac App Store is optional
   2. Install the standalone **Command Line Tools** package::

        xcode-select --install

   This command will open a GUI window (do not run this over SSH).

.. _`XCode`:
   https://developer.apple.com/xcode/

.. _waf_build_system:

Waf (Build System)
------------------

We use the Waf build system to build all Kodo examples and unit tests.
Waf is a Python-based build system that supports a wide variety of use cases.
You may read more about Waf at the project homepage: https://waf.io/

A Waf project typically contains two types of files:

1. The ``waf`` file is the actual build system executable.
   This binary file is not meant to be edited.

2. Several ``wscript`` and ``wscript_build`` files: These files contain the
   project build information. You can think of it as a type
   of ``makefile`` written in Python.

.. note:: See the ``waf`` build options by running ``python waf -h``
          in your terminal.

Git Version Control System
--------------------------

Our projects can be downloaded with git. This version control system allows you
to easily get new updates whenever a project is updated.

If you don't want to type your GitHub username and password when downloading
Kodo (and its dependencies), then we recommend using Git-over-SSH. It is easy
to configure SSH authentication on all platforms following this `Github guide`_.

You don't have to use a passphrase, and you can skip Step 3. If you are using
Windows, then run these commands in Git Bash (which is installed with msysgit).
We don't recommend using "GitHub for Windows", so don't follow the
Windows-specific guide (the generic guide is good for all platforms).

After adding your SSH key on Github, please make sure that the following
login works for you::

    ssh -T git@github.com


.. note:: If you don't want to configure SSH authentication on github.com,
          you can also clone the repository with the ``https`` protocol.

          Normally, you have to type your GitHub username and password with
          ``https``. On Windows, you can configure msysgit to store your
          credentials with the following command::

              git config --global credential.helper wincred


.. _`Github guide`:
   https://help.github.com/articles/generating-ssh-keys/#platform-all

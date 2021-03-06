.. _getting_started:

Getting Started
===============

Obtain a Steinwurf License
--------------------------

Before you download or use our libraries, you **MUST** obtain a valid
Steinwurf license.

Please read the license terms at http://steinwurf.com/license.html and
fill out the license request form with the appropriate details.

.. _tools-needed:

Tools Needed
------------

If you wish to build our libraries with our build system, you will need to
install the following tools:

1. **C++14 compliant compiler:** A C++ compiler that supports the
   C++14 standard. This can be g++, clang or msvc.

2. **Git:** The git version control system for managing our libraries.

3. **Python:** We use the Python-based `waf <https://waf.io/>`_ build system.

The following sections describe how to install the tools on different platforms.

Download Tools (Ubuntu or other Debian-based distributions)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Get the dependencies using the following command::

    sudo apt-get install g++ python git-core

Download Tools (Windows)
~~~~~~~~~~~~~~~~~~~~~~~~

1. **C++14 compliant compiler:** You need a working C++14 compiler. The latest
   supported version is Visual Studio 2017: you can get the Community,
   Professional or Enterprise versions from the main
   `Visual Studio download page <https://visualstudio.microsoft.com/downloads/>`_
   or the `Express version <https://aka.ms/vs/15/release/vs_WDExpress.exe>`_
   or you can install the standalone `Build Tools for Visual Studio 2017
   <https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2017>`_
   (which is a smaller package). If you need an earlier version, you may also use
   `Visual Studio Express 2015 for Desktop <https://visualstudio.microsoft.com/vs/older-downloads/>`_.

.. note:: If you get the following compiler error::

              Cannot open include file: 'corecrt.h'

          Then most likely, you need to install the ``Windows Universal CRT SDK``,
          please follow the instructions here: https://stackoverflow.com/a/43905001

          If the waf configure step fails, because ``mt.exe`` and ``rc.exe``
          are missing from these locations::

              C:\Program Files (x86)\Windows Kits\10\bin\x64
              C:\Program Files (x86)\Windows Kits\10\bin\x86

          Then you should install an earlier version of the Windows 10 SDK
          (10.0.14393) to fix this.

          The Visual Studio Command Prompt can be useful to verify your
          installation. If the VS Command Prompt cannot find your Windows SDK
          installation, then please check that the ``%SystemRoot%\System32``
          folder is added to your system ``PATH``.

2. **Python:** You need a working Python installation. Find the available
   download on the `Python homepage <http://www.python.org/download/>`_.
   If you are in doubt about which version to install, you may use the
   `Python 2.7.15 Windows Installer
   <https://www.python.org/ftp/python/2.7.15/python-2.7.15.msi>`_.

3. **Git:** There are several ways to get git on Windows. If you plan to use
   the waf build scripts to build our examples and unit tests, you should
   install the `Git for Windows <https://git-for-windows.github.io/>`_ tool
   (version 2.8.x or above).

4. **TortoiseGit (Optional):**
   You can also install the latest version of
   `TortoiseGit <https://tortoisegit.org/>`_ if you prefer to use a GUI
   instead of the command-line git tools. Version 2.1.0 and later should
   work fine.

Download Tools (Mac OSX)
~~~~~~~~~~~~~~~~~~~~~~~~

**C++14 compliant compiler:** You need a working C++14 compiler. We tested
tested `XCode <https://developer.apple.com/xcode/>`_ 10.0 with the Apple LLVM
10.0 compiler which can be downloaded for free. Newer versions should also be
fine.

On Mavericks or above (OSX 10.9+):
   1. Installing XCode from the Mac App Store is optional
   2. Install the standalone **Command Line Tools** package::

        xcode-select --install

   This command will open a GUI window (do not run this over SSH).

.. _waf_build_system:

Waf (Build System)
------------------

We use the Waf build system to build our libraries, examples and unit tests.
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

.. _git_version_control_system:

Git Version Control System
--------------------------

Our projects can be downloaded with git. This version control system allows you
to easily get new updates whenever a project is updated.

.. note:: We are currently migrating our private repositories from github.com to
         gitlab.com.

* The :ref:`kodo` libraries are currently still hosted on GitHub so to
  access those you just need a GitHub account.

* The :ref:`score` libraries are hosted on GitLab with some dependencies
  hosted on Github. Therefore you will need an account on both platforms.

.. _github_gitlab_accounts:

GitHub / GitLab accounts
~~~~~~~~~~~~~~~~~~~~~~~~

Accounts for GitHub and GitLab can be created at:

1. `Sign up GitHub <https://github.com/join>`_
2. `Sign up GitLab <https://gitlab.com/users/sign_in>`_

GitHub / GitLab authentication
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you don't want to type your GitHub or GitLab username and password when
downloading our main libraries (and their dependencies), then we recommend using
Git-over-SSH. It is easy to configure SSH authentication on all platforms
following this `GitHub guide`_ or `GitLab guide`_.

You don't have to use a passphrase, and you can skip anything about the
ssh-agent, because your key will be loaded automatically. If you are using
Windows, then run these commands in Git Bash.
We don't recommend using "GitHub for Windows", so don't follow the
Windows-specific guide (the generic guide is good for all platforms).

After adding your SSH key on GitHub, please make sure that the following
login works for you::

    ssh -T git@github.com

And try the same thing on GitLab::

    ssh -T git@gitlab.com

In both cases, you should get a short welcome message.


.. note:: If you don't want to configure SSH authentication on github.com or
          gitlab.com you can also clone the repository using the ``https``
          protocol.

          Normally, you have to type your GitLab/GitHub username and password with
          ``https``. On Windows, you can configure git to store your
          credentials with the following command::

              git config --global credential.helper wincred


.. _`GitHub guide`:
   https://help.github.com/articles/adding-a-new-ssh-key-to-your-github-account/

.. _`GitLab guide`:
   https://docs.gitlab.com/ee/gitlab-basics/create-your-ssh-keys.html

.. _getting_started:

Getting Started
===============

Obtain a Steinwurf License
--------------------------

Before you download or use our libraries, you **MUST** obtain a valid license.

* If you intend to use Kodo for **research and educational** purposes, please
  fill out this form_ to obtain a Research License.

* If you intend to **evaluate or test** Kodo or Score in a commercial context,
  you can obtain a Commercial Evaluation License. Please contact us at
  sales@steinwurf.com.

* For a general **Commercial License**, contact us at sales@steinwurf.com.

.. _form: http://steinwurf.com/license/



.. _tools-needed:

Tools Needed
------------

If you wish to build our libraries with our build system, you will need to
install the following tools:

1. **C++11 compliant compiler:** A C++ compiler that supports the
   C++11 standard. You can see a list of currently supported compilers on our
   Buildbot page (`Steinwurf Buildbot`_).

2. **Git:** The git version control system for managing our libraries.

3. **Python:** We use the Python-based `waf`_ build system.

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
   the waf build scripts to build our examples and unit tests, you should
   install the `Git for Windows`_ tool (version 2.8.x or above).

4. **TortoiseGit (Optional):**
   You can also install the latest version of TortoiseGit_ if you prefer to use
   a GUI instead of the command-line git tools. Version 2.1.0 and later should
   work fine.

.. _`Visual Studio Express 2015 for Desktop`:
   https://www.visualstudio.com/downloads/download-visual-studio-vs

.. _`Python homepage`:
   http://www.python.org/download/

.. _`Python 2.7.10 Windows Installer`:
   https://www.python.org/ftp/python/2.7.10/python-2.7.10.msi

.. _`Git for Windows`:
   https://git-for-windows.github.io/

.. _`TortoiseGit`:
   https://tortoisegit.org/

Download Tools (Mac OSX)
~~~~~~~~~~~~~~~~~~~~~~~~

**C++11 compliant compiler:** You need a working C++ compiler. We tested
tested `XCode`_ 7.1 with the Apple LLVM 7.0 compiler which can be
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

          The :ref:`kodo` libraries are currently still hosted on GitHub so to
          access those you just need a GitHub account.

          The :ref:`score` libraries are hosted on GitLab with some dependencies
          hosted on Github. Therefore you will need an account on both platforms.

.. _github_gitlab_accounts:

GitHub / GitLab accounts
~~~~~~~~~~~~~~~~~~~~~~~~

Accounts for GitHub and GitLab respectively can be created at:

1. `Sign-up GitHub <https://github.com/join>`_
2. `Sign-up GitLab <https://gitlab.com/users/sign_in>`_

.. note:: Users utilizing our commercial license or commercial evaluation
          license needs to register their user-name with Steinwurf before they
          can access the repositories. This can be done by sending an email to
          sales@steinwurf.com containing the GitHub/GitLab username and company
          affiliation of the specific user.

GitHub / GitLab authentication
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you don't want to type your GitHub or GitLab username and password when
downloading our main libraries (and their dependencies), then we recommend using
Git-over-SSH. It is easy to configure SSH authentication on all platforms
following this `GitHub guide`_ or `GitLab guide`_.

You don't have to use a passphrase, and you can skip Step 3. If you are using
Windows, then run these commands in Git Bash.
We don't recommend using "GitHub for Windows", so don't follow the
Windows-specific guide (the generic guide is good for all platforms).

After adding your SSH key on GitHub, please make sure that the following
login works for you::

    ssh -T git@github.com

Unfortunately a similar pre-check is not possible with GitLab.


.. note:: If you don't want to configure SSH authentication on github.com or
          gitlab.com you can also clone the repository using the ``https``
          protocol.

          Normally, you have to type your GitLab/GitHub username and password with
          ``https``. On Windows, you can configure git to store your
          credentials with the following command::

              git config --global credential.helper wincred


.. _`GitHub guide`:
   https://help.github.com/articles/generating-ssh-keys/#platform-all

.. _`GitLab guide`:
   http://docs.gitlab.com/ce/ssh/README.html

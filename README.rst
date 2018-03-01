steinwurf-docs
==============

Sphinx documentation for kodo and related projects.

.. contents:: Table of Contents:
   :local:

Installation
------------

#. Clone the project and cd into it::

    git clone git@gitlab.com:steinwurf/steinwurf-docs.git
    cd steinwurf-docs

#. Install pip (if it is not installed already)::

    sudo apt-get install python-pip

#. Install the sphinx package::

    sudo apt-get install python-sphinx

#. Install version 0.1.9 of the ReadTheDocs theme::

    sudo pip install sphinx-rtd-theme==0.1.9

   Newer versions of the RTD theme might be incompatible with Google Chrome
   due to the Lato 2.0 fonts that were added on Dec 5, 2016. Google Chrome
   cannot load these fonts so almost all text will be white on the generated
   website (verified with Google Chrome 55 on Windows). The font updates
   can be followed here:
   https://github.com/snide/sphinx_rtd_theme/commits/master/sphinx_rtd_theme/static/fonts/Lato-Regular.ttf

Building the docs
-----------------

After installing the dependencies simply run make in the `steinwurf-docs`
folder::

    cd steinwurf-docs
    make html

Launch a browser to see the result e.g.::

    google-chrome build/html/index.html


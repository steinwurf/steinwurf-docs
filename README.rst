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

#. Install the sphinx and our theme::

    pip install -r requirements.txt

Building the docs
-----------------

After installing the dependencies simply run sphinx-build::

    sphinx-build -b html source build/html

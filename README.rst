steinwurf-docs
==============


.. image:: https://travis-ci.org/steinwurf/steinwurf-docs.svg?branch=master
    :target: https://travis-ci.org/steinwurf/steinwurf-docs


Sphinx documentation for kodo and related projects.

.. contents:: Table of Contents:
   :local:

Automated build
---------------

You can generate the docs using waf which will create a temporary virtualenv
and install all dependencies::

    git clone git@gitlab.com:steinwurf/steinwurf-docs.git
    cd steinwurf-docs
    python waf configure
    python waf docs


Manual build
------------

If you don't want to use waf, you can also install the requirements
and invoke sphinx-build manually::

    pip install -r source/requirements.txt
    sphinx-build -b html source build/html

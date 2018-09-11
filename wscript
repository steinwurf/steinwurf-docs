#! /usr/bin/env python
# encoding: utf-8

import os

from waflib.Build import BuildContext

APPNAME = 'steinwurf-docs'
VERSION = '0.1.0'


class DocsContext(BuildContext):
    cmd = 'docs'
    fun = 'docs'


def docs(ctx):
    """ Build the documentation in a virtualenv """
    with ctx.create_virtualenv(cwd=ctx.bldnode.abspath()) as venv:

        # Install the requirements in the temporary virtualenv
        venv.run('python -m pip install -r source/requirements.txt',
                 cwd=ctx.path.abspath())

        # Run sphinx-build to generate the html
        venv.run('sphinx-build -b html source build/html',
                 cwd=ctx.path.abspath())



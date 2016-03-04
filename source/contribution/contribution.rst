Contributing
============

We encourage and appreciate contributions by all users e.g. in the form of
bug reports, bug fixes, adding features, providing examples, improving
documentation, etc.

In this section we will describe both the workflow of the contributor and
the maintainer. If you have suggestions which may make the workflow easier
for either side, please do not hesitate to :ref:`contact_us`.

.. contents:: :depth: 2

Contributing documentation changes
----------------------------------

If you find errors in the documentation i.e. this manual or source code
comments you help us fix it using the following procedure.

* Edit the `files <https://github.com/steinwurf/kodo>`_ directly on GitHub
  using their `online editor
  <https://help.github.com/articles/editing-files-in-another-user-s-repository/>`_.

If the issue is in the manual you can press the **Edit on GitHub** link in
the top right corner of every page. This will take you directly to the
GitHub editor with the relevant file open.

.. note:: Remember to follow our :ref:`sign_off` procedure to sign off the
          copyright to your changes.

.. note:: If you forgot to do the sign off procedure, you can can ammend the
          last commit directly in the command line with:
          ::

            git commit --amend -m "New commit message"

          And then pushing the commit.

          Remember that if you want to ammend an already pushed commit, you
          will need to force push the commit with:
          ::

            git push <remote> <branch> --force

.. warning:: To force push a commit will overwrite the remote branch with the
            state of your local one.

In both cases GitHub will automatically create a fork of the Kodo
repository and send a pull request to notify Kodo's maintainers.

Since all our documentation is written in
`reStructredText <http://en.wikipedia.org/wiki/ReStructuredText>`_
(rst). You can also edit the source files locally on your computer in which
case you can follow the steps in :ref:`contributing_source_code_changes`.

Accepting documentation changes
-------------------------------

If the pull-request is a pure documentation update, simply review the
change and merge at will.

.. _contributing_source_code_changes:

Contributing source code changes
--------------------------------

The most common contribution is code changes, where you fix exiting code or
implement new functionality. Roughly speaking we need to go though the
following steps:

* Fork the repository.
* Implement the changes.
* Submit pull request for review

In the following we will use the ``git`` command line, feel free to use any git
tool that you feel comfortable with.

Step 1: Fork the repository
...........................

Kodo is hosted as a private GitHub repository, to get access you first need to
obtain a valid license:

* Sign up for a `GitHub user account <http://github.com/join>`_.
* Obtain a valid license and access to the repository
  `here <http://steinwurf.com/license>`_. You will need to provide your
  github username for us to grant you access.

Once you have access to the code you can create a fork to your Github user
account. Using a fork you will be implementing your changes in your own
copy of the Kodo repository.

 * Go to the `Kodo GitHub repository <https://github.com/steinwurf/kodo>`_
   and press the **Fork** button. Your work should be ready in a few
   minutes.
 * After *forking* is done, clone the repository to your development
   machine. In the terminal type:

   ::

      git clone <your-forked-kodo-repo's-git-url>

The will clone your fork of the Kodo repository into the current folder.

Syncing your fork
,,,,,,,,,,,,,,,,,

Use the following command to add **upstream** (the original Kodo
repository) as a remote repository.

::

   git remote add upstream <kodo-repo's-git-url>

To fetch and merge the latest changes from the Kodo repository into your
fork, type:

::

    git pull upstream

Step 2: Implement the changes
.............................

Your fork is ready and you can start to hack the Kodo source code.

.. warning:: Now here's the part people usually don't figure out until it's
             too late - do not commit any changes to your fork's master
             branch! The master branch of your fork is always kept in sync
             with Kodo's master branch (from remote).

It is good practice to make your changes to your fork in a separate branch
(we typically call this a feature branch).

If you don't know how to make a branch there's quite a bit of good
tutorials and guides. For example this `one
<http://git-scm.com/book/en/v2/Git-Branching-Basic-Branching-and-Merging>`_.

.. warning:: Before you start changing the code look at our :ref:`sign_off`
             procedure. In short any commits to the Kodo source code needs
             to contain a sign-off statement which ensures that Steinwurf
             ApS hold the copyright of all the Kodo source code.

To decrease the amount of formatting corrections, please try to follow our
conventions:

1. Ensure you name your files and classes follow our
   :ref:`files_and_classes`.
2. Ensure that your files are placed according to our
   :ref:`namespaces_and_directories`.
3. Ensure that you follow our :ref:`coding_style`.
4. If you added new functionality remember to add the corresponding unit
   tests. See our :ref:`unit_testing` section for more information.

Step 3: Submit pull for review
..............................

We never allow commits directly on the master branch. Changes go to the
master branch after our buildbot has completed testing that the changes
work on all supported platforms.

When you create a pull-request for the first time, you can choose the
branch where the commits should be applied. However, since no feature
branch exists yet - you should choose the ``master`` branch. The Kodo
maintainers will then create a feature branch for your changes and notify
you.

Unfortunately GitHub does not allow you to change the base branch of a pull
request so once the feature branch is ready on the main Kodo repository you
need to create a new pull request using the new feature branch as the base.

The maintainer may now comment on your changes before they can be merged.

If the maintainer pushes commits to the feature branch for you to review,
you can pull them in by (assuming you already set an upstream)::

    git checkout newfeature
    git fetch upstream
    git merge upstream/newfeature


Accepting source code changes
-----------------------------

In the following we will describe the process followed by the Kodo
maintainers to accept changes to Kodo.

* Create feature branch in response to pull requst.
* Collaborate with contributor to fix potential issues with the changes::

    git checkout master
    git pull
    git checkout -b newfeature
    git push origin newfeature

Fetch changes from the contributor::

    git remote add <GitHub username> git@github.com:<GitHub username>/kodo.git

Get the changes::

    git checkout newfeature
    git fetch <GitHub username>
    git merge <GitHub username>/newfeature


.. _sign_off:

Sign-off
--------

To accept changes to the Kodo repository, we ask that you sign over the
copyright of your changes to us. This is similar to what is done for the
`SQLite project <https://www.sqlite.org/copyright.html>`_.

We require this in order to maintain clear title to the Kodo code and
prevent the introduction of code with incompatible licenses or other
entanglements that might cause legal problems for us and our users. In
order to manage this you can choose to use either of the two methods below:

1. :ref:`sign_off_per_commit` Each commit message must include a short sign
   off statement.
2. :ref:`permanent_sign_off_assignment` Sign a copyright assignment
   covering all your future contributions to Kodo.

.. _sign_off_per_commit:

Sign-off per commit
...................

This option is based on the sign off procedure described
`in this guide
<http://gerrit.googlecode.com/svn/documentation/2.0/user-signedoffby.html>`_

The copyright sign-off is used per commit, and as such is a more temporary
solution and/or better suited for developers who for whatever reason do not
wish to sign a permanent copyright assignment.

First read our sign-off `statement <https://github.com/steinwurf/kodo/blob/master/docs/source/contribution/SIGNOFF.rst>`_.

Once you are ready to commit some of your changes add the following
sign-off line as the last line of your commit message::

   Signed-off-to-Steinwurf-by: Developer Name <developername@example.org>

That it.

.. note:: If you forget to add the sign off statement you can use the
   rebase/amend option of git to add it.

.. _permanent_sign_off_assignment:

Permanent sign-off assignment
.............................

The copyright assignment is the permanent solution if you which to
contribute current and future changes to one or multiple of our projects.

#. Read the content of the `ASSIGNMENT.rst
   <https://github.com/steinwurf/kodo/blob/master/docs/source/contribution/ASSIGNMENT.rst>`_
#. Replace *DEVELOPER NAME* with your name and *PROJECT NAME* with the name of the project(s) you will work on (e.g. Kodo) in
   `ASSIGNMENT.rst
   <https://github.com/steinwurf/kodo/blob/master/docs/source/contribution/ASSIGNMENT.rst>`_.
#. Convert it into a pdf (e.g. use rst2pdf).
#. Alternatively you can send your name to copyright@steinwurf.com and we
   will send you a pdf.
#. Print
#. Sign (remember the date).
#. Scan
#. Email to copyright@steinwurf.com.
#. Store the returned signed document for your records.

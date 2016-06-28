.. _overview_score:

Overview
========

The score library implements the Simple COded REliability (SCORE) protocol
for reliable unicast and multicast communication over UDP. The protocol is
designed for distribution of data from a sender to one or more receivers.
It is primarily intended for reliable transmission, but it also supports
best-effort delivery, e.g. for cases where no feedback channel is available.
Reliability is ensured using Random Linear Network Coding.

.. _libraries_score:

Libraries
---------

The score libraries are implemented in several projects and each project has
its own git repository. It is recommended to choose a single project and work
with the API that is exposed by that project.

:ref:`score_cpp`
    The score-cpp library defines a simple, high-level C++ API to conveniently
    access the basic functionality of Score, such as sending and receiving
    data. It is very easy to integrate score-cpp into your C++ project,
    so **it is the recommended option for most users**.

:ref:`score_c`
    The score-c library provides a simple C API that allows the programmer to
    use Score in a C program. The C API also enables interoperability with
    other programming languages that are not directly supported.

score
    The score repository contains the low-level C++ implementation of the SCORE
    protocol. This is intended for experienced C++ developers who would like
    to know more about the inner workings of the library.


Platform Support
----------------

Score is portable to a wide range of platforms (both hardware platforms and
operating systems).

We ensure compatibility with the supported platforms through a suite of unit
tests, the current status can be checked at the `Steinwurf Buildbot`_ page.
At the bottom of the main page, you can find detailed information
about which platforms and compilers are currently tested by Steinwurf.

.. _Steinwurf Buildbot: http://buildbot.steinwurf.com

.. note:: The Buildbot is used for several different libraries. The
  score-c and score-cpp libraries can be found in the overview on the
  main page.

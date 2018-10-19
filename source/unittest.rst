.. _unit_testing:

Unit Testing
============

This section describes how the Steinwurf unit tests work, how to run them
and how to extend them.

Overview
--------

The purpose of our unit tests is to verify that the various
features work across a number of different platforms and
compilers. Having an extensive unit test suite makes it
easier for developers to ensure that their changes work as expected
and do not cause regressions in unexpected areas of the library.

The goal is that all features in a library should have a corresponding test
case. Often a test case is added while implementing a new
feature. This makes it possible to check that the new functionality
works as expected as early as possible.

The unit tests are implemented using the Google C++ Testing Framework
(gtest) which defines a bunch of helpers that are useful when writing
tests. You can find more information on gtest on their homepage.

Running the tests
-----------------
One of the first things you might want to try is to run the unit
tests on your own machine. There are two ways to do this:

Run the test binary manually
............................

The test binary is built using the waf build scripts shipped
with the library. You can read more about how you can get the
source code and how to build it in the :ref:`getting_started` section.

Once the code is built, the test binary will be located in a subfolder of the
``build`` folder that depends on your platform:

Linux
    ``build/linux/test/xyz_tests``

Mac OSX
    ``build/darwin/test/xyz_tests``

Windows
    ``build/win32/test/xyz_tests.exe``

If you are cross-compiling with an *mkspec* (as described in the
:ref:`cross_compile` section), then the resulting binary will
be located in:

mkspec
    ``build/[mkspec]/test/xyz_tests``

.. note:: Running the unit tests may take a long time on mobile and embedded
          platforms, since we test with an extensive set of parameters.
          For some projects, we defined the ``embedded`` profile to lower
          the complexity and speed up the tests::

            ./xyz_tests --profile=embedded


Run the test as part of the build
.................................

In some cases, it is convenient to run the test binary as part of a build.
This can be done by passing the following option to waf::

  python waf --run_tests

Adding a new test
-----------------

When adding a new feature to a library, it is a good idea to
also add a corresponding unit test. The source code for the different
unit tests are placed in the ``test/src`` folder of the project.

All files with a ``.cpp`` file extension in the ``test/src`` will
automatically be included in the test executable produced when
building the project with waf.

In general we follow these guidelines regarding the unit tests:

1. Every class should have a corresponding unit test cpp file.
2. Remember to place the test file as described in
   :ref:`namespaces_and_directories`

The purpose of this is to make it easy to find the unit test for a
specific class. In some cases it makes sense to have multiple classes
tested in the same file. In those cases we still make a placeholder
.cpp file referring to the actual .cpp file where the test can be
found. An example of this can be seen for some of the codecs, e.g. the
class ``encoder`` located in ``src/kodo/rlnc/encoder.hpp`` is tested in
``test_coders.cpp`` but the place holder file still exists.

The placeholder file in this case
(``test/src/test_encoder.cpp``) looks like the following:

.. literalinclude:: includes/test_encoder.cpp
    :language: c++
    :linenos:

Once the ``.cpp`` test file has been created, we can start to implement
the unit test code. This is done with the help of the gtest framework.

Dealing with type aliases
.........................

In some cases we have headers containing only ``type aliases`` such as
``using`` statements. We currently do not require that
these are unit tested in isolation.

Regardless of whether a unit test is implemented or not we still leave
a place holder .cpp file in the test folder.

Example unit test
-----------------

The Kodo library is build using the
``parameterized-inheritance``/ ``mixin-layers`` C++ design
technique. When unit testing a layer we try to isolate it as much as
possible. To do this we typically introduce dummy layers with the sole
purpose of satisfying the layer's dependencies. To see this in action
let's look at one of the existing unit tests.

The ``storage_bytes_used`` layer is used when we want add
functionality allowing us to keep track of how many useful bytes an
encoder or decoder contains.

.. note:: In general the amount of data which can be encoded or
          decoded will be determined by the number of symbols we are
          coding and the size of every symbol in bytes (we call this
          the block size). However, in practical applications we
          sometimes do not have enough data to fill an entire
          block. In those cases we can add the storage_bytes_used
          layer to embed in every encoder and decoder the ability to
          store the number of actual data bytes.

.. literalinclude:: includes/storage_bytes_used.hpp
    :language: c++
    :linenos:

As seen, the layer depends on two functions being provided by the
``SuperCoder``:

1. ``SuperCoder::initialize(the_factory)``
2. ``SuperCoder::block_size()``

Using our project documentation, it is possible to look up the
purpose of the two undefined functions.

In this case we want to check that the state is correctly updated when
calling ``set_bytes_used`` and that the state is correctly reset when
calling ``initialize``. The following unit test code was implemented
in ``test/src/test_storage_bytes_used.cpp`` to test this:

.. literalinclude:: includes/test_storage_bytes_used.cpp
    :language: c++
    :linenos:

In the above test code we use a test helper which allows us to
easily add testing stubs to the unit test.

http://en.wikipedia.org/wiki/Test_stub

The library is called stub and is freely available under the BSD license:

https://github.com/steinwurf/stub

Naming the test case
--------------------

When we define a test using gtest we use the ``TEST(test_case_name, test_name)``
macro to define and name a test function. We follow this naming guideline:

1. The ``test_case_name`` should match the name of the .cpp file. For example,
   ``test_my_fancy_code.cpp`` contains ``test_my_fancy_code`` test cases.
   This should make it trivial to find the .cpp if a unit test fails.
   If a project contains multiple classes with the same name (in different
   subfolders), then it is recommended to modify those class names.
   If that is not possible, then we can add the subfolder as a prefix to the
   ``test_case_name``, e.g. ``subfolder_test_my_fancy_code``.
   Remember to place the test files as described in
   :ref:`namespaces_and_directories`
2. The ``test_name`` is up to the developer, but should be as
   descriptive of the purpose of the unit test as possible.

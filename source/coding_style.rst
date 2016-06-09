.. _coding_style:

Coding Style
============

This section describes the coding style used in the Steinwurf projects
covering several programming languages.

.. contents:: Table of Contents:
   :local:

------
Python
------
For Python the `PEP8 <http://legacy.python.org/dev/peps/pep-0008/>`_ standard
is used. There are plenty of plugins and tools to automatically locate and fix
any diversions from this style.

---
C++
---

Naming
------

* Names of classes, members, functions, namespaces are all lowercase letters
  separated with ``_`` if it enhances readability.
* Template parameters should be CamelCase.
* Member variables are prefixed with ``m_``
* In general, we try to avoid abbreviations in parameter names, member
  variables, class names, function names.
* For temporary local variables, you can use abbreviations, even single
  character names as long as you use common sense (what you think makes the
  code the most readable).

File Extensions
---------------
We use the ``.cpp`` extension for source files and ``.hpp`` for header files.
This makes it easier to differentiate between C and C++ code.

.. _files_and_classes:

Files and Classes
-----------------
We have a one class per one file rule. If you make a new class ``happy``, then
put it in ``happy.hpp``. This makes the classes easier to find in the
source tree. Exceptions to this rule are nested classes.

.. note:: Remember to also add a unit test for your new class.
          Find more information about this in our :ref:`unit_testing` section.

.. note:: If your new class resides in a namespace, make sure to place
          the source file in the corresponding directory. More details in the
          :ref:`namespaces_and_directories` section.

Indentation
-----------
We always indent code using **SPACES** and **NOT TABS**. The size of an
indentation is **4 spaces**.

Warnings
--------
All code should compile without any warnings. Please make sure this is the case
on all supported platforms (Linux, Windows, etc.)

Line width
----------
We use the column 80 rule. Break any lines you have that exceed 80 characters.

Comments
--------
- Use ``//`` for simple inline C++ comments that are not meant for Doxygen,
  but for other devs.
- Use ``///`` for comments that are meant for Doxygen (do not use this in
  function bodies!).
- Start comments on new lines if possible

Include Guards
--------------

Using #pragma once is preferred instead of the lengthy include guards, as this
approach is shorter and less error-prone. Furthermore, it might speed up the
compilation on modern compilers.

Start every header file like this (after the copyright comment):

.. code-block:: cpp

    #pragma once

#include Statements
-------------------

The first include in a ``.cpp`` file should always be the associated header file
(if any). The goal of this is to enforce that all necessary includes are
specified within the header. If some necessary includes are missing from 
that header, then the compilation of the ``.cpp`` will break at this point. 

In a library, internal includes should be included with double quotes
(``#include "header.hpp"``), like so:

.. code-block:: cpp

    #include "associated_header_file.hpp"

    // C/C++ standard headers
    // Headers from dependencies

    #include "header_from_same_project.hpp"
    #include "inner_namespace/other_header_from_same_project.hpp"

In a unit test for a header in a library, the header should be included
with angle brackets (``#include <project/header.hpp>``), like so:

.. code-block:: cpp

    #include <my_project/associated_header_file.hpp>

    // C/C++ standard headers
    // Headers from dependencies

    #include <my_project/header_from_same_project.hpp>
    #include <my_project/inner_namespace/other_header_from_same_project.hpp>

The order of the includes should be as follows (a newline should be
added between these groups):

#. The header of the ``.hpp`` belonging to this ``.cpp`` file (if any).
#. C/C++ standard headers
#. Grouped Headers from dependencies
#. Headers of the current project

Complete example (from a library ``.cpp`` file):

.. code-block:: cpp

    #include "associated_header_file.hpp"

    #include <vector>
    #include <math>

    #include <boost/shared_ptr>

    #include <fifi/log_table.hpp>
    #include <fifi/is_binary.hpp>

    #include <kodo/storage.hpp>

    #include "header_from_same_project.hpp"
    #include "inner_namespace/other_header_from_same_project.hpp"

The reasoning behind having the system headers before the dependencies is that
it will enable us to handle any include issues with external dependencies,
without breaking our coding style.

Header file extension
---------------------

We have decided to start using ``.hpp`` for header files. This makes it easier
to differentiate between C and C++ code.

Class Declarations
------------------

We group private and public functions and members in different sections:

.. code-block:: cpp

  class foo
  {
  public:

      // Public functions

  private:

      // Private functions

  public:

      // Public members (avoid these!)

  private:

      // Private members
  };

With one newline between scope specifiers, members and functions:

.. code-block:: cpp

  class coffee_machine
  {
  public:

      /// Some comment
      void make_me_a_cup()
      {
          // Function body
      }

      /// Another comment
      void better_make_that_two()
      {
          // Function body
      }

  private:

      /// Important functionality
      void grind_beans()
      {
          // Function body
      }
  };

Member Initializer List
-----------------------

The colon starting a member initializer list should *not* be on a new line
and it should be padded by one space:

.. code-block:: cpp

    // CORRECT style
    class correct_style
    {
    public:

        correct_style() :
          m_value(42)
        { }

    private:

        int m_value;
    };

    // WRONG style (missing space!)
    class incorrect_style
    {
    public:

        incorrect_style():
          m_value(42)
        { }

    private:

        int m_value;
    };

    // WRONG style (colon on new line!)
    class incorrect_style
    {
    public:

        incorrect_style()
          : m_value(42)
        { }

    private:

        int m_value;
    };


Explicit Constructors
---------------------

Use the C++ keyword ``explicit`` for constructors with one argument. This is
inspired by `Google's C++ Style Guide
<http://google-styleguide.googlecode.com/svn/trunk/
cppguide.xml#Explicit_Constructors>`_.

Testing
-------
Testing is hard, but we try to have a test for all new functionality added in
our projects. For this purpose we use the GoogleTest framework (gtest). You can
find more information on it here: http://code.google.com/p/googletest/

Writing tests
.............
When writing tests remember to:

1. Remove your debug prints before merging with the master.
2. Describe what is the purpose of a test and comment your tests

Casts
-----

1. Numeric types: If you are casting from a numeric type use either
   C-style cast or C++ style casts. E.g. both of these are fine:

   .. code-block:: cpp

     uint32_t o = (uint32_t) some_value;
     uint32_t k = static_cast<uint32_t>(some_value);

   See this http://stackoverflow.com/a/12321860 for more info.

2. All other cases (pointers etc.): Cast using C++ style casts e.g.
   ``static_cast`` etc.

Braces
------

Braces are always placed on new lines (Allman/ANSI-style). Separator keywords
like ``else`` or ``catch`` should always start on a new line (they cannot
be combined with braces).

1. In very simple statements (e.g. an if with single statement) you may
   optionally omit the braces:

   .. code-block:: cpp

     // Fine
     if (coffee_pot == full)
         continue;

     // Also fine
     if (coffee_pot == empty)
     {
         continue;
     }

2. However in more complicated statements we always put braces - and always
   with a new line:

   .. code-block:: cpp

     // CORRECT (Allman/ANSI-style)
     if (ok == true)
     {
         call_mom();
         call_function();
     }

     // WRONG (in multi-line statements, put the braces)
     if (ok == false)
     {
         // do something fun
     }
     else
         continue;

     // CORRECT
     if (ok == false)
     {
         // do something fun
     }
     else
     {
         continue;
     }

     // WRONG (K&R style)
     if (ok == true) {
         call_function();
     } else {
         other_function();
     }

     // CORRECT (Allman/ANSI-style)
     try
     {
         my_function();
     }
     catch (const std::exception& e)
     {
        // handles std::exception
     }
     catch (...)
     {
        // handles int or std::string or any other unrelated type
     }

3. The brace rules also apply for initializer lists and lambdas. If the given
   expression would fit on a single line, then you can keep the one-liner
   since that improves readability (no need for newlines):

   .. code-block:: cpp

     // CORRECT (Allman/ANSI-style)
     std::vector<uint8_t> data =
     {
         0x67, 0x42, 0x00, 0x0A, 0xF8, 0x41, 0xA2
     };

     // WRONG (K&R style)
     std::vector<uint8_t> data = {
         0x67, 0x42, 0x00, 0x0A, 0xF8, 0x41, 0xA2 };

     // CORRECT (one-liner expression)
     std::vector<uint8_t> data = { 0x67, 0x42 };

     // CORRECT (Allman/ANSI-style)
     auto callback = [](const std::string& data)
     {
         std::cout << data << std::endl;
     };

     // WRONG (K&R style)
     auto callback = [](const std::string& data) {
         std::cout << data << std::endl;
     };

Operators
---------
Do not start lines with operators (e.g. ``+-\*/%&^|:=``).
Unary operators (e.g. ``~-&``) are exceptions to this rule.

Add one space around common arithmetic operators to clearly separate the
operands:

.. code-block:: cpp

  // CORRECT
  boost::shared_ptr<very_long_type> instance =
      boost::make_shared<very_long_type>(param);

  // WRONG (misplaced '=' sign)
  boost::shared_ptr<very_long_type> instance
      = boost::make_shared<very_long_type>(param);

  // CORRECT
  m_pep = m_pep * std::pow(base, losses + 1.0) +
          (1.0 - std::pow(base, losses));

  // WRONG (misplaced '+' sign)
  m_pep = m_pep * std::pow(base, losses + 1.0)
          + (1.0 - std::pow(base, losses));

  // WRONG (missing spaces)
  m_pep=m_pep*std::pow(base,losses+1.0)+
        (1.0-std::pow(base,losses));

Padding
-------
Padding can greatly improve the readability of long code lines.
Try to keep symmetry and break long lines so that the code is aligned with
similar code elements on the previous line.

For example:

.. code-block:: cpp

  // Long method signature
  void fake_loopback::send(
      const uint8_t* data, uint32_t size, const address& address, uint16_t port,
      fake_udp_socket* socket)

  // A slightly shorter parameter list fits on a single line
  void fake_loopback::send(
      const uint8_t* data, uint32_t size, const address& address, uint16_t port)

  // Member initializer list (members are aligned)
  mutable_storage() :
      m_data(0),
      m_size(0)
  {
      // Constructor body
  }

  // Stack of mixin layers
  template<class Field>
  class on_the_fly_encoder : public
      // Payload Codec API
      payload_encoder<
      // Codec Header API
      systematic_encoder<
      symbol_id_encoder<
      // Symbol ID API
      plain_symbol_id_writer<
      // Coefficient Generator API
      storage_aware_generator<
      uniform_generator<
      // Codec API
      encode_symbol_tracker<
      zero_symbol_encoder<
      linear_block_encoder<
      storage_aware_encoder<
      // Coefficient Storage API
      coefficient_info<
      // Symbol Storage API
      deep_symbol_storage<
      storage_bytes_used<
      storage_block_info<
      // Finite Field API
      finite_field_math<typename fifi::default_field<Field>::type,
      finite_field_info<Field,
      // Factory API
      final_coder_factory_pool<
      // Final type
      on_the_fly_encoder<Field>
      > > > > > > > > > > > > > > > > >
  { };


Declaring pointers and references
---------------------------------

The * and & characters should be tied to the type names, and not to the variable
names:

.. code-block:: cpp

  // CORRECT (C++-style)
  int* pValue;

  // WRONG (C-style)
  int *pValue;

  // CORRECT (C++-style)
  void add(const complex& x, const complex& y)
  {
  }

  // WRONG (C-style)
  void add(const complex &x, const complex &y)
  {
  }

The following regular expressions are helpful to check & replace any violations
of this rule::

  Find &: ([\w>])\s+&(\w)
  Replace with: $1& $2
  Find *: ([\w>])\s+\*(\w)
  Replace with: $1* $2
  Watch out for return statements like: return *io_ptr;
  Regex to find trailing whitespace: [ \t]+(?=\r?$)


Using asserts
-------------

Using ``asserts`` is a hot-potato in many development discussions. In
particiular when talking about high performance code. In our projects we will
adopt the following simple strategy:

* Before **using** a variable or parameter we use an ``assert``:

  .. code-block:: cpp

    void test(int* a, int* p)
    {
        // We just use the p variable so we only assert on that one. The
        // variable a is only forwarded so it should have an assert elsewhere.
        assert(p);

        *p = 10;
        test2(a, p);
    }

Read the following article for more information on this
http://queue.acm.org/detail.cfm?id=2220317


Handling unused parameters
--------------------------
Use the following approach to handle warnings caused by unused parameters:

.. code-block:: cpp

  void test(int a);
  {
      (void) a;
  }


Hiding internal implementation details
--------------------------------------
To prevent polluting the namespace of a project with internal helper functions,
use a nested namespace called ``detail`` to hide them:

.. code-block:: cpp

  namespace project_name
  {
      namespace detail
      {
          void help()
          {
              // Do help
          }
      }

      void api()
      {
          // Get help
          detail::help();
      }
  }

An example of this can be seen `here <https://github.com/steinwurf/sak/blob/
8a75568b80c063331ae08d5667a1d67bb92c87b8/src/sak/easy_bind.hpp#L38>`_

.. _namespaces_and_directories:

Namespaces and Directories
--------------------------

Let's say that we are working on a project called ``magic``. Then the
root namespace of the project should be ``magic`` and all classes
defined in this namespace should be placed in the ``src/magic`` folder and
their corresponding unit tests should be placed in ``test/src/``.

For example, if you create a class ``speedy``:

.. code-block:: cpp

    namespace magic
    {
        class speedy
        {
        ...
        };

    }

Then it should be placed in ``speedy.hpp`` (as described in
:ref:`files_and_classes`) and the file should be placed in
``src/magic/speedy.hpp`` and the corresponding unit test in
``test/src/test_speedy.cpp``.

If you create a class in a nested namespace called ``wonder``:

.. code-block:: cpp

    namespace magic
    {
    namespace wonder
    {
        class smart
        {
        ...
        };
    }
    }

Then the file should be called ``smart.hpp`` and it should be
placed in the ``src/magic/wonder/smart.hpp``. Similarly, the
corresponding test file ``test_smart.cpp`` should be placed in
``test/src/wonder/test_smart.cpp``.

The general rule is that namespaces are represented by a directory in
the filesystem. So if you see a class in a namespace, then you know
the directory of the corresponding source file.

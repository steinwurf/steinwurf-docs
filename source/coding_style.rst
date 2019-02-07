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

We use the following format for docstrings:

.. code-block:: python

    def add(value1, value2):
        """
        Add the given values and return the result.

        This function uses the given objects built-in + operator to add
        them together. Afterwards the result is returned.

        :param value1: the first value.
        :param value2: the second value.
        :return: the result of the addition of value1 and value2.
        """
        return value1 + value2

----------------------
C++ general guidelines
----------------------

This section presents general guidelines for C++ that are not checked by
the automatic code formatter. Therefore our developers should pay special
attention to these rules.

Naming
------

* Names of classes, members, functions, namespaces are all lowercase letters
  separated with ``_`` if it enhances readability.
* Template parameters should be CamelCase.
* Member variables are prefixed with ``m_``, but no prefix should be used for
  simple structs which only hold data members.
* In general, we try to avoid abbreviations in parameter names, member
  variables, class names, function names.
* For temporary local variables, you can use abbreviations, even single
  character names as long as you use common sense (what you think makes the
  code the most readable).

File extensions
---------------
We use the ``.cpp`` extension for source files and ``.hpp`` for header files.
This makes it easier to differentiate between C and C++ code.

.. _files_and_classes:

Files and classes
-----------------
We have a one class per one file rule. If you make a new class ``happy``, then
put it in ``happy.hpp``. This makes the classes easier to find in the
source tree. Exceptions to this rule are nested classes.

.. note:: Remember to also add a unit test for your new class.
          Find more information about this in our :ref:`unit_testing` section.

.. note:: If your new class resides in a namespace, make sure to place
          the source file in the corresponding directory. More details in the
          :ref:`namespaces_and_directories` section.

.. _namespaces_and_directories:

Namespaces and directories
--------------------------

The general rule is that namespaces are represented by a directory in
the filesystem. So if you see a class in a namespace, then you know
the directory of the corresponding source file.

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

Then it should be defined in ``speedy.hpp`` and the file should be placed in
``src/magic/speedy.hpp``. The corresponding unit test should be in
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

Warnings
--------
All code should compile without any warnings. Our build system automatically
verifies this on all supported platforms (Linux, Windows, etc.)

Include guards
--------------

Using #pragma once is preferred instead of the lengthy include guards, as this
approach is shorter and less error-prone. Furthermore, it might speed up the
compilation on modern compilers.

Start every header file like this (after the copyright comment):

.. code-block:: cpp

    #pragma once

#include statements
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

Getters and setters
-------------------

We use the following approach for handling getters and setters:

* The setter should be the name of the value which is to be set, prefixed with
  ``set_``.
* The getter should be the name of the value. So **without** a ``get_`` prefix.

Example:

.. code-block:: cpp

    class my_class
    {
    public:

        my_class() :
            m_value(0U)
        { }

        uint32_t value() const
        {
            return m_value;
        }

        void set_value(uint32_t value)
        {
            m_value = value;
        }

    private:

        uint32_t m_value;
    };

Explicit constructors
---------------------

Use the C++ keyword ``explicit`` for constructors with one argument. This is
inspired by `Google's C++ Style Guide
<http://google-styleguide.googlecode.com/svn/trunk/
cppguide.xml#Explicit_Constructors>`_.

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


-------------------
C++ code formatting
-------------------

We use a modified version of `astyle <https://github.com/steinwurf/astyle>`_
to automatically format our C++ code. The formatting tool tries to follow the
rules specified here.

Indentation
-----------
We always indent code using **SPACES** and **NOT TABS**. The size of an
indentation is **4 spaces**.

Line length
-----------
Break any lines that exceed 80 characters.
This makes it possible to display two source files side-by-side on a widescreen
monitor.

Comments
--------
- Use ``//`` for simple inline C++ comments that are not meant for Doxygen,
  but for other devs.
- Use ``///`` for comments that are meant for Doxygen (do not use this in
  function bodies!).
- Start comments on new lines if possible

Class declarations
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

There should be *no newlines* after the block opening ``{`` and before the
block closing ``}``:

.. code-block:: cpp

  class coffee_machine
  {
                            <- WRONG: EXTRA NEWLINE
  public:

      /// Some comment
      void make_me_a_cup()
      {
          // Function body
                            <- WRONG: EXTRA NEWLINE
      }

      /// Another comment
      void better_make_that_two()
      {
                            <- WRONG: EXTRA NEWLINE
          // Function body
      }
                            <- WRONG: EXTRA NEWLINE
  };


Member initializer list
-----------------------

The colon starting a member initializer list should *not* be on a new line
and it should be padded by one space. The indentation does not change if the
constructor has a parameter list, although multiple options are possible in
this case.

.. code-block:: cpp

    // CORRECT style
    class correct_style
    {
    public:

        correct_style() :
            m_value(42),
            m_second(1U)
        { }
    };

    // WRONG style (missing space!)
    class incorrect_style
    {
    public:

        incorrect_style():
            m_value(42),
            m_second(1U)
        { }
    };

    // WRONG style (colon on new line!)
    class incorrect_style
    {
    public:

        incorrect_style()
          : m_value(42),
            m_second(1U)
        { }
    };

    // CORRECT style (Option 1)
    class correct_style
    {
    public:

        correct_style(
            uint32_t parameter1,
            uint32_t parameter1) :
            m_value(42),
            m_second(1U)
        { }
    };

    // CORRECT style (Option 2)
    class correct_style
    {
    public:

        correct_style(uint32_t parameter1,
                      uint32_t parameter1) :
            m_value(42),
            m_second(1U)
        { }
    };


Braces
------

Braces are always placed on new lines (Allman/ANSI-style). Separator keywords
like ``else`` or ``catch`` should always start on a new line (they cannot
be combined with braces).

1. In very simple statements (e.g. an if with single statement) you may
   choose to omit the braces if that improves readability:

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
   expression would fit on a single line, then you can keep the one-liner,
   since that improves readability (no need for newlines):

   .. code-block:: cpp

     // CORRECT (Allman/ANSI-style)
     std::vector<uint8_t> data =
         {
             0x67, 0x42, 0x00, 0x0A, 0xF8, 0x41, 0xA2
         };

     // ALSO CORRECT
     std::vector<uint8_t> data =
         { 0x67, 0x42, 0x00, 0x0A, 0xF8, 0x41, 0xA2 };

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

Alignment
---------

Padding can greatly improve the readability of long code lines.
Try to keep symmetry and break long lines so that the code is aligned with
similar code elements on the previous line. This is called "sibling alignment"
and it is demonstrated by the following examples.

Assigment and operators
.......................

By default, the operands are aligned with each other on the right side of the
``=`` sign. The operators are not moved to the next line, so it is generally
incorrect to start lines with operators (e.g. ``+-\*/%&^|:=``). Unary operators
(e.g. ``~-&``) and shift operators (``<< >>``) can be exceptions
to this rule.

It is recommended to add one space around common arithmetic operators to
clearly separate the operands (this is optional and it will not be enforced
by astyle).

.. code-block:: cpp

  // CORRECT
  int result = operand1 +
               operand2 +
               operand3;

  // WRONG (operands must be aligned)
  int result = operand1 +
      operand2 +
      operand3;

  // CORRECT
  m_pep = m_pep * std::pow(base, losses + 1.0) +
          (1.0 - std::pow(base, losses));

  // WRONG (misplaced '+' sign)
  m_pep = m_pep * std::pow(base, losses + 1.0)
          + (1.0 - std::pow(base, losses));

  // WRONG (missing spaces)
  m_pep=m_pep*std::pow(base,losses+1.0)+
        (1.0-std::pow(base,losses));

  // CORRECT (<< operators are aligned)
  std::cout << "This is a very loooooooooong line for this Hello World! "
            << num << std::endl;

  // WRONG (<< operator should be on the next line)
  std::cout << "This is a very loooooooooong line for this Hello World! " <<
            num << std::endl;

  // CORRECT
  out << "\t\t" << "dest = " << ((uintptr_t) std::get<0>(v))
      << " src = " << ((uintptr_t) std::get<1>(v))
      << " length = " << ((uint32_t) std::get<2>(v)) << std::endl;

If the operands are long and some lines would exceed the 80-character limit,
then it is recommended to break the line after the ``=`` sign. In this case,
the operands will be only indented by 4 spaces, and they will be aligned
with each other.

.. code-block:: cpp

  // CORRECT
  int result =
    loooooooooooong_operand1 + loooooooooooong_operand2 +
    loooooooooooong_operand3;

  // CORRECT
  m_insanely_looooooooooong_variable =
    m_insanely_looooooooooong_variable * std::pow(base, losses + 1.0) +
    (1.0 - std::pow(base, losses));

  // CORRECT
  boost::shared_ptr<very_long_type> instance =
      boost::make_shared<very_long_type>(param);

  // WRONG (misplaced '=' sign)
  boost::shared_ptr<very_long_type> instance
      = boost::make_shared<very_long_type>(param);

Functions
.........

similarly to assignments, the parameters of functions are aligned with each
other (provided that they are on the same level).

.. code-block:: cpp

    // CORRECT (but can be improved!)
    void vector4_dot_product(uint8_t** dest, const uint8_t** src,
                             uint8_t** constants, uint32_t size,
                             uint32_t dest_vectors,
                             uint32_t src_vectors) const;

    // CORRECT (but can be improved!)
    m_encoders->copy_from_symbol(symbol_id,
                                 sak::storage(symbol.data()));

    // WRONG (proper alignment but the line is too long!)
    boost::asio::ip::multicast::join_group option(addr,
                                                  score::manual_sender::address_type());

    // BARELY CORRECT (layout should be improved!)
    score::generation_storage_out::coder_type::factory factory(generation_size,
                                                               symbol_size);

If the line is broken after the opening ``(``, then the next line will be
indented by 4 spaces (even if the line has multiple opening ``(`` characters):

.. code-block:: cpp

    // CORRECT
    m_redundancy_estimator.sample(
        1.0 + m_redundancy_estimator.estimate(),
        m_generation_size() / m_worst.get() - 1.0);

    // CORRECT (improved layout)
    void vector4_dot_product(
        uint8_t** dest, const uint8_t** src, uint8_t** constants,
        uint32_t size, uint32_t dest_vectors, uint32_t src_vectors) const;

    // CORRECT (improved layout)
    m_encoders->copy_from_symbol(
        symbol_id, sak::storage(symbol.data()));

    // CORRECT (improved layout)
    boost::asio::ip::multicast::join_group option(
        addr, score::manual_sender::address_type());

    // CORRECT (improved layout)
    score::generation_storage_out::coder_type::factory factory(
        generation_size, symbol_size);

If a function call has multiple levels of nesting, then it is really important
to break the lines at appropriate places:

.. code-block:: cpp

    // CORRECT
    m_socket->async_receive_from(
        // Level 1 parameter
        looooooooooooooooong_function_name1(m_receive_buffer),
        // Level 1 parameter
        looooooooooooooooong_function_name2(
            // Level 2 parameters
            &sockets::handle_async_receive_from, this,
            ph::_1, ph::_2, ep));

    // CORRECT (but can be improved!)
    EXPECT_TRUE(std::equal(data_out.begin(),
                           data_out.end(),
                           data_in.begin()));

    // CORRECT (only 4 spaces are added)
    EXPECT_TRUE(std::equal(
        data_out.begin(), data_out.end(), data_in.begin()));

    // CORRECT (cleaner layout)
    EXPECT_TRUE(
        std::equal(data_out.begin(), data_out.end(), data_in.begin()));

When a function call is placed on the right side of an assignment and
the line is broken after the opening ``(``, then the function parameters will
be indented by 4 spaces. So the assignment expression is not constrained to
fit on the right side of the ``=`` sign.

.. code-block:: cpp

    // CORRECT
    uint32_t snacks = detail::calculate_redundancy(
        1, message.m_feedback_probability - 1.0);

    // CORRECT
    m_encoded_symbols += kodo_core::write_payloads(
        *m_encoder, m_payloads.data(), m_payloads.size());

If the line is not after the opening ``(``, then the function arguments
will be properly aligned:

.. code-block:: cpp

    // CORRECT
    statistics iter = calculate_statistics(iterations.cbegin(),
                                           iterations.cend());

An indentation is added if the line ends with ``->``, this is common for
new-style function definitions using the ``auto`` keyword:

.. code-block:: cpp

    // CORRECT
    template<typename U>
    static auto test(int) ->
        decltype(std::declval<U>().some_function(), yes());


Lambda functions
................

The bodies of lambda functions are indented as separate blocks. So the
indentation is not constrained by the ``=`` sign or the opening ``(``:

.. code-block:: cpp

    // CORRECT
    auto callback = [](const std::string& data)
    {
        std::cout << data << std::endl;
    };

    // CORRECT
    s.write_data(buffer, [&]()
    {
        io.post(write_data_callback);
    });

    // CORRECT
    auto callback = [function](const std::string& zone,
                               const std::string& message)
    {
        boost::python::call<void>(function, zone, message);
    };

    // CORRECT (useful when the parameter list is long)
    auto callback = [function](
        const std::string& zone,const std::string& message)
    {
        boost::python::call<void>(function, zone, message);
    };

Single-line lambda expressions can also occur inline as the last parameter of a
function call (if a function takes multiple lambda arguments, then you must use
named lambda functions).

.. code-block:: cpp

    // CORRECT
    std::generate(data.begin(), data.end(),
                  [&]() { return randval(engine); });

    // CORRECT
    in.fetch_data_ready(
        [&](std::vector<uint8_t>& cb) { fetch_data_ready_stub(cb); });

    // CORRECT
    in.fetch_data_ready([&](std::vector<uint8_t>& cb)
    {
        fetch_data_ready_stub(cb);
    });

    // WRONG (the line break is not necessary)
    in.fetch_data_ready(
        [&](std::vector<uint8_t>& cb)
    {
        fetch_data_ready_stub(cb);
    });

Return statements
.................

The arguments of a multiline return expression are aligned on the right side
of the ``return`` statement.

.. code-block:: cpp

    // CORRECT
    return loooooooooooong_operand1 +
           loooooooooooong_operand2 +
           loooooooooooong_operand3;

If the line is broken after the opening ``(`` of a function parameter list,
then then the parameters will be indented by 4 spaces:

.. code-block:: cpp

    // CORRECT
    return detail::easy_bind(
        detail::build_indices<sizeof...(Args)>(),
        mf, std::forward<Args>(args)...));

Template expressions
....................

Template instantiations in class headers and using expressions follow a flat
layout (no nesting for each ``<``):

.. code-block:: cpp

    template
    <
        class MainStack,
        class Features
    >
    class full_vector_recoding_stack : public
        // Payload API
        kodo_core::payload_info<
        // Codec Header API
        kodo_core::default_off_systematic_encoder<
        kodo_core::symbol_id_encoder<
        // Symbol ID API
        recoder_symbol_id<
        // Coefficient Generator API
        kodo_core::uniform_generator_layers::type<Features,
        kodo_core::pivot_aware_generator<
        // Encoder API
        kodo_core::write_symbol_tracker<
        kodo_core::zero_symbol_encoder<
        kodo_core::trace_write_symbol<kodo_core::find_enable_trace<Features>,
        kodo_core::trace_symbol<kodo_core::find_enable_trace<Features>,
        kodo_core::linear_block_encoder<
        // Coefficient Storage API
        kodo_core::coefficient_value_access<
        // Proxy
        kodo_core::proxy_layer<MainStack,
        kodo_core::final_layer
        > > > > > > > > > > > > >
    { };

    template<class Features, class SuperCoder>
    using on_the_fly_generator =
        kodo_core::check_partial_generator<
        kodo_core::uniform_generator_layers::type<Features,
        kodo_core::pivot_aware_generator<
        SuperCoder> > >;

In contrast with this, we apply a new level of indentation for each ``<`` in
standalone template instantiations and template argument lists. However, if
you open multiple template instantiations on the same line (with multiple
``<`` characters), then you only get a single indent. It is recommended to
place the closing ``>`` on a new line to get a symmetrical layout.

.. code-block:: cpp

    // CORRECT
    run_test_on_the_fly<
        Encoder<fifi::binary16>,
        Decoder<fifi::binary16>
    >(symbols, symbol_size);

    // WRONG (closing > should be on a new line)
    run_test_on_the_fly<
        Encoder<fifi::binary16>,
        Decoder<fifi::binary16> >(
    symbols, symbol_size);

    // CORRECT (single indent for two < openers on the same line)
    parser<
        box::moov<parser<
            box::trak<parser<
                box::mdia<parser<
                    box::hdlr,
                    box::mdhd
                >>
            >>
        >>
    > parser;

If a template argument list does not fit on a single line, then each
argument should have its own line:

.. code-block:: cpp

    // CORRECT
    template
    <
        class Super,
        uint32_t MaxGenerationSize = 500,
        uint32_t MaxSymbolSize = 2000
    >
    class something : public Super{};

    // WRONG (missing newlines + template parameter names should be CamelCase)
    template <class Super, uint32_t max_generation_size = 500,
              uint32_t max_symbol_size = 2000>
    class something : public Super{};

    // CORRECT (the type specifier is too long to fit on a single line)
    stub::call<
        void(std::shared_ptr<score::snack_message>, std::function<void()>)
    > send;


Declaring pointers and references
---------------------------------

The * and & characters should be tied to the type names, and not to the
variable names:

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

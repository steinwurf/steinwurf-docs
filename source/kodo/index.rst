.. _kodo:

Kodo
====

Kodo is a high-performance erasure coding library with a special focus on
network coding algorithms and codecs. Kodo is written in C++ and
it was designed to ensure high performance, testability, flexibility and
extendability.

A fast implementation of finite fields is a prerequisite for fast RLNC
and other linear block codes. Kodo relies on our optimized
`Fifi <http://github.com/steinwurf/fifi>`_ library which supports multiple
finite fields with different sizes.

The Kodo libraries expose a simple Application Programming Interface (API)
which allows a programmer to take advantage of network coding in a
custom application. Kodo supports various network coding codecs e.g. standard
Random Linear Network Coding (RLNC), Systematic RLNC, Sparse RLNC.
Each algorithm offers unique advantages and drawbacks as well as a different
set of parameters that can be tuned in real time. For example, this can
be employed to adapt to varying cellular channels, to change the amount of
redundancy in a distributed storage network, or to adapt to node failures in
meshed networks.

For researchers, Kodo's layered structure greatly simplifies the
implementation of new and experimental RLNC variants, since typically
only a new layer needs to be added. For example, this can be exploited to
develop codes with special structures targeted and optimized towards
specific uses, e.g. audio and video streaming, meshed networks and
distributed storage.

.. _projects_kodo:

Projects
--------

The Kodo libraries are implemented in several projects and each project has
its own git repository. It is recommended to choose a single project and work
with the API that is exposed by that project.

:ref:`kodo_cpp`
    The kodo-cpp library defines a simple, high-level C++ API to conveniently
    access the basic functionality of Kodo, such as encoding and decoding data
    with various codecs. It is very easy to integrate kodo-cpp into your
    C++ project, so **it is the recommended option for most users**.

:ref:`kodo_c`
    The kodo-c library provides a simple C API that allows the programmer to
    use Kodo in a C program. The C API also enables interoperability with
    other programming languages that are not directly supported by the
    Kodo libraries.

:ref:`kodo_rlnc`
    The kodo-rlnc project provides low-level access to the underlying C++
    implementation of the various RLNC codecs. This enables the developer
    to customize the operation of these codecs or create new variants, but
    working with the low-level details might present some difficulties.
    This option is only recommended for experienced C++ programmers.

:ref:`kodo_python`
    This library provides high-level Python bindings for Kodo. The simple
    examples demonstrate how to use the basic functionality of Kodo through
    the Python API. This option is recommended for Python-based projects
    and for programmers who are not familiar with C++.

:ref:`kodo_ns3_examples`
    This project contains examples for using Kodo with the ns-3 network
    simulator. This can be a great starting point for researchers who
    are mainly interested in network simulations.

Features
--------

Recoding
    One of the most prominent features of Network Coding is the
    possibility to use coding at the intermediate network nodes
    (recoding) and not only at the sender (encoding) and the receiver
    (decoding).

Systematic coding
    The sender can send some or all of the original symbols within a
    given block uncoded. Coded packets can be generated later to repair
    any packet losses. Systematic coding is useful in simple topologies
    as it increases the decoding throughput and decreases the coding
    overhead.

On-the-fly coding
    The sender can encode over a growing block of data. This is useful
    for live content where the data becomes available over time,
    potentially at a variable rate.

Partial decoding
    The receiver can decode some of the original symbols before the
    entire data block is decoded. This approach is more compatible with
    error-resilient codecs (video, audio) as instead of receiving the
    whole data block or nothing, a partial data block can be retrieved.

Variable symbol length (coming soon)
    The symbols in a block of coded data can have different lengths. The
    fragmentation and aggregation is handled transparently by the library.
    This can be useful when the size of the incoming data packets is
    variable.

Real-time adjustable density
    The density at the sender can be adjusted in real time which permits
    adaptation to changing network conditions.

Symbol pruning
    The encoder can drop certain symbols which were already decoded at
    the decoder.

File encoder
    The sender can directly encode data files that are automatically split
    into generations.

Zero-copy API
    The encoder and decoder can operate directly on user provided buffers,
    eliminating the need for costly copy operations.

Object pooling
    The library can re-use existing encoder and decoder instances to
    facilitate efficient memory management.

Hardware optimized (on select hardware)
    Optimizations for various CPU architectures, using SIMD instructions
    and various coding algorithms to provide the best performance.


Random Linear Network Coding codecs
...................................

Standard RLNC
    All symbols are combined uniformly at random. In general, this type
    of coding is "dense", since the symbols in the data block are mixed
    as much as possible. Density is lower for small field sizes.

Sparse RLNC with uniform density
    Some symbols are excluded with a given probability during encoding.
    The remaining symbols are combined as in the standard RLNC case.
    This is typically useful when the block size is very high. The density
    can be reduced significantly without any negative effect and
    the decoding throughput can be increased substantially at the same time.

Sparse RLNC with fixed density
    A fixed number of symbols are combined at random. This can be used
    when feedback is available from the decoder. The encoding process
    can be tuned at the encoder according to the state of the decoder.

Seed-based RLNC
    Instead of sending the full coding vector, a small random seed can
    be sent to generate the coding vector. This reduces the overhead,
    but makes recoding difficult and in some cases impossible. This is
    typically used when recoding is not necessary or used very sparingly.

On-the-fly RLNC
    Symbols can be encoded as they are made available and data is released from
    the decoder as decoding progresses. This is different from traditional block
    codes where all data has to be available before encoding or decoding takes
    place. This codec is well suited for low-delay services such as messaging,
    voice over IP or video streaming.

Perpetual RLNC
    A sparse and structured code where the non-zero coding coefficients are
    localized to a specific part of the coding vector. The width of this non-zero
    part is analogous to the density parameter of random sparse codes. This
    approach allows for structured decoding, which can yield a substantially
    higher throughput than random sparse codes, especially for large generation
    sizes.

Fulcrum RLNC
    The Fulcrum network codes use a concatenated code structure with an "outer"
    and "inner" code. They provide an end-to-end performance that is close
    to that of a large field size network coding system for high–end receivers,
    while simultaneously catering to low–end ones that can only decode in GF(2).
    For a detailed description of the Fulcrum codec, see the following
    `paper <http://arxiv.org/abs/1404.6620>`_ by Lucani et. al.

Other codecs and approaches
...........................

Reed-Solomon code
    Traditional Reed-Solomon (RS) code which does not support recoding. The
    current implementation uses a systematic Vandermonde matrix as described in
    `RFC 5510 <http://tools.ietf.org/html/rfc5510>`_.

Carousel code
    Also called a repetition code, the data is simply transmitted in a
    round-robin fashion. This code is mostly useful for simulation
    purposes and performance evaluations. Furthermore it can be used to
    provide the Compact No-Code scheme described in
    `RFC 5445 <http://tools.ietf.org/html/rfc5445>`_.

Random Annex overlay code
    Enables mixing of several generations. By using multi-stage decoding,
    this technique can offer increased decoding throughput at the cost of
    increased decoding delay.
    The Random Annex code is useful in scenarios where large objects
    need to be transmitted in a feedback-constrained system (feedback
    is expensive or impossible) and where using a single large generation
    is not feasible.


Platform Support
----------------

Kodo is portable to a wide range of platforms. The `Kodo Specifications`_
page provides an overview of the supported platforms and compilers.

We ensure compatibility with the supported platforms through a suite of unit
tests, the current status can be checked at the `Steinwurf Buildbot`_ page.
At the bottom of the main page, you can find detailed information
about which platforms and compilers are currently tested by Steinwurf.

.. _Steinwurf Buildbot: http://buildbot.steinwurf.com
.. _Kodo Specifications: http://steinwurf.com/kodo-specifications/

.. note:: The Buildbot is used for several different libraries. The
  Kodo library can be found in the overview on the main page.

.. toctree::
   :hidden:

   kodo-cpp/index
   kodo-c/index
   kodo-rlnc/index
   kodo-python/index
   kodo_ns3_examples
   kodo_basic_simulations
   kodo_migration_guide
   using_kodo_for_research
   contribution/contribution

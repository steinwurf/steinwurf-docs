.. _kodo:

Kodo
====

Kodo is a high-performance erasure coding library with a special focus on
network coding algorithms and codecs. Kodo is written in C++ and
it was designed to ensure high performance, testability, flexibility and
extendability.

The Kodo libraries expose a simple Application Programming Interface (API)
which allows a programmer to take advantage of network coding in a
custom application. Kodo supports various network coding codecs, e.g. standard
Random Linear Network Coding (RLNC), Systematic RLNC, Sparse RLNC.
Each algorithm offers unique advantages and drawbacks as well as a different
set of parameters that can be tuned in real time. For example, this can
be employed to adapt to varying cellular channels, to change the amount of
redundancy in a distributed storage network, or to adapt to node failures in
meshed networks.

Kodo is available under a research- and education-friendly license, and
it enables researchers to implement new codes and algorithms,
perform simulations, and benchmark the coding operations on any platform
where a modern C++ compiler is available. The library provides a multitude of
building blocks and parameters that can be combined to create custom codes.

.. _projects_kodo:

Codecs and Repositories
-----------------------

The Kodo libraries implement various codecs and each codec has its own git
repository. As a first step, it is recommended to choose a single codec/project
and work with the API that is exposed by that project.

Note that these repositories are **private** on Github, so you need to complete
all steps in the :ref:`getting_started` guide before you can access them.

kodo-rlnc: http://docs.steinwurf.com/kodo-rlnc/master/index.html
    This project implements a standard RLNC codec and provides
    a simple, high-level C++ API which is the **the recommended starting
    option for most users**. The RLNC codec has a number of parameters that
    can be configured to fit the user requirements: e.g. the code density
    can be adjusted and the coding vector representation can include the
    full vector or just a random seed to reduce overhead.

kodo-fulcrum: http://docs.steinwurf.com/kodo-fulcrum/master/index.html
    The Fulcrum network codes use a concatenated code structure with an "outer"
    and "inner" code. They provide an end-to-end performance that is close
    to that of a large field size network coding system for high–end receivers,
    while simultaneously catering to low–end ones that can only decode in GF(2).
    For a detailed description of the Fulcrum codec, see the following
    `paper <http://arxiv.org/abs/1404.6620>`_ by Lucani et. al.

kodo-perpetual: http://docs.steinwurf.com/kodo-perpetual/master/index.html
    Perpetual RLNC is a sparse and structured code where the non-zero coding
    coefficients are localized to a specific part of the coding vector.
    The width of this non-zero part is analogous to the density parameter of
    random sparse codes. This approach allows for structured decoding, which
    can yield a substantially higher throughput than random sparse codes,
    especially for large generation sizes.

kodo-slide: https://kodo-slide.steinwurf.com
    The kodo-slide library implements a sliding window RLNC codec that could
    provide interesting benefits over a traditional block code.

kodo-reed-solomon: http://docs.steinwurf.com/kodo-reed-solomon/master/index.html
    Traditional Reed-Solomon (RS) code which does not support recoding. The
    current implementation uses a systematic Vandermonde matrix as described in
    `RFC 5510 <http://tools.ietf.org/html/rfc5510>`_.

kodo-core: https://github.com/steinwurf/kodo-core
    The kodo-core repository contains general erasure coding components that
    are used by the other codec implementations that are listed above.
    This project also includes a carousel code (or repetition code) where
    the data is simply transmitted in a round-robin fashion. This code can
    be useful for simulation and testing purposes.


Language Bindings and Wrappers
------------------------------

kodo-python: https://github.com/steinwurf/kodo-python
    This library provides high-level Python bindings for Kodo. The simple
    examples demonstrate how to use the basic functionality of Kodo through
    the Python API. This option is recommended for Python-based projects
    and for programmers who are not familiar with C++.

kodo-rlnc-c: http://docs.steinwurf.com/kodo-rlnc-c/master/index.html
    The kodo-rlnc-c library provides a simple C API that allows the programmer
    to use kodo-rlnc in a C program. The C API also enables interoperability
    with other programming languages that are not directly supported by the
    Kodo libraries.

kodo-c: https://github.com/steinwurf/kodo-c
    The kodo-c library is a **deprecated project** that was created to
    provide a C wrapper over some earlier implementation of our RLNC codecs.
    This project will not be updated, please use kodo-rlnc-c if a C wrapper
    is needed.

kodo-cpp: https://github.com/steinwurf/kodo-cpp
    The kodo-cpp library is a **deprecated project** that was
    designed as a high-level C++ wrapper over kodo-c and it only exposed
    a limited API to access the Kodo codecs. This project will not be updated,
    please use kodo-rlnc that provides a complete C++ API.


Simulations
-----------

kodo-basic-simulations: https://github.com/steinwurf/kodo-basic-simulations
    The kodo-basic-simulations project contains some basic Network Coding
    simulations using our simple C++ simulator where you can define simple
    network topologies.

kodo-ns3-examples: https://github.com/steinwurf/kodo-ns3-examples
    This project contains examples for using Kodo with the ns-3 network
    simulator. This can be a great starting point for researchers who
    are mainly interested in network simulations.


Features
--------

The following generic features are available in the various Kodo libraries.

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

Real-time adjustable density
    The density at the sender can be adjusted in real time which permits
    adaptation to changing network conditions.

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


Platform Support
----------------

Kodo is portable to a wide range of platforms (both hardware platforms and
operating systems).

We ensure compatibility with the supported platforms through a suite of unit
tests that are executed by our Continuous Integration system.

.. _using_kodo_for_research:

Using Kodo for Your Research
----------------------------

One of the initial reasons for building Kodo was to make a tool for doing
research on erasure correcting codes with a specific focus on network
codes. So if you have used or plan to use Kodo for your research, we would
love to hear about it!

If you are doing a publication using Kodo, all we ask is that you cite our
work. Find the pdf and bibtex of the initial `Kodo paper here`_.

.. _Kodo paper here: http://vbn.aau.dk/en/publications/kodo-an-open-and-research-oriented-network-coding-library(1fc1d13c-922a-4f19-b582-6eaf67296029).html


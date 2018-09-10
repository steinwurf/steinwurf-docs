.. _kodo_rlnc:

kodo-rlnc
=========

The kodo-rlnc library implements various Network Coding codecs based on the
kodo-core library.

The kodo-rlnc repository: https://github.com/steinwurf/kodo-rlnc

.. rubric:: Subpages

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

.. toctree::
   :maxdepth: 2

   quick_start_kodo_rlnc
   tutorial_kodo_rlnc
   including_kodo_rlnc
   hacking_kodo




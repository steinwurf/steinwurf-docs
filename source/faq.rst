Frequently Asked Questions
==========================

.. _faq:

This page tries to answer common questions about network coding and Kodo.


.. contents::

Practical Questions about Kodo
------------------------------

Our users typically ask questions like these when using Kodo.

Which Kodo codec should I choose for my application?
....................................................

The Kodo library provides multiple code variants and most of these have
dedicated examples that demonstrate the API differences. Therefore it is a
good idea to go through the ``examples`` folder of the given repository
before choosing a codec. You can also find a detailed description of each
codec and its API in the corresponding ``kodo-rlnc`` header file and the
generated Doxygen documentation.

For most applications, the standard RLNC implementation in kodo-rlnc is a
good first choice, since it provides a straightforward API that is used in
many of our examples.

Which finite field should I choose?
...................................

Our fastest finite field is GF(2) which is called ``binary`` in our Fifi
library, so this can be a good starting point. We should note that using the
``binary`` field entails higher linear_dependency_ and therefore it might not
be optimal for all applications. We also provide GF(2^4) as ``binary4`` and
GF(2^8) as ``binary8`` which are slower, but their linear_dependency_ is much
lower. The ``binary`` field can be up to 10 times faster than ``binary4`` and
``binary8``, although the difference largely depends on the available hardware
acceleration (the gap is a lot smaller on CPUs with SSSE3, AVX2 or NEON
instruction sets).

How can I choose the number of symbols in a generation?
.......................................................

The number of symbols has a very significant impact on coding performance,
therefore it is recommended to choose the smallest number of symbols
(i.e. generation size) that works for your application. A good starting
point can be 100 symbols and the maximum recommended value is about 1000,
but this largely depends on the hardware. You can start with a lower value
and increase it as necessary according to the packet loss patterns of your
network. You should also consider that a higher generation size will result
in a higher delay, and that could be problematic for your application. If
you have to work with a large number of symbols, you can also lower the
code_density_ to improve performance (using our ``sparse`` or ``sparse_seed``
codecs).

What is a good symbol size for my application?
..............................................

If there are no external constraints, you are free to set the symbol size to
large values, even megabytes are feasible. However, if you want to send some
coded symbols over a network, then it makes sense to choose a symbol size that
is a bit smaller than your network MTU (which is typically 1500 bytes).
If you choose a symbol size that is too high, then your UDP packets will get
fragmented and that will increase your packet loss.

Kodo adds a small header to the symbols and the exact header size depends
on your configuration, so it is recommended to check the maximum payload size
with the ``payload_size()`` function. Typically we choose a symbol size of 1400
bytes to make room for the header. The ``seed`` codec has a fixed header size,
so it is safe to set 1480 bytes for the symbol size to stay below the MTU of
1500 bytes.

Can I code an entire file with Kodo?
....................................

Yes, you can encode any data you like. If you have a regular file, please
take a look at the encode_decode_file_ example in kodo-rlnc.

If the file is relatively small, then all data can fit into a single block
that contains a moderate number of symbols. However, if you have a large file,
then it is not a good idea to code everything in a single block. As explained
above, the coding performance largely depends on the number of symbols in a
block. Fortunately, the file encoder in the encode_decode_file_ example
can partition the file into multiple smaller blocks to improve performance.
You can set the number of symbols and the symbol size parameters following
the recommendations above. Of course, if you have multiple blocks, then your
decoder has to complete all blocks to recover the full file.

If you want to transmit a file over the network to one or more receivers,
then the udp_file_sender_receiver_ example should be helpful.

.. _encode_decode_file: https://github.com/steinwurf/kodo-rlnc/tree/master/examples/encode_decode_file

How to choose the coding parameters based on my packet loss statistics?
.......................................................................

If you have accurate and timely feedback about the lost packets from your
receiver or receivers, then you can retransmit as many coded packets as needed
to repair the packet losses (this is called backward error correction).
So in this case, you are essentially free to choose coding parameters that
are optimal for performance.

If you cannot rely on feedback, then Forward Error Correction (FEC) is an obvious
strategy. For example, if you estimate that 10-15% of your packets will be lost
based on previous measurements, then you can send an additional 20% of coded
packets right away to compensate for the expected losses. This 20% is called
overhead, and the decoder should be able to recover the original data as long
as the overhead is higher than the actual loss rate. Obviously, we cannot
know the actual loss rate in advance, therefore we commonly use a worst-case
estimate to set the overhead. Note that it is not possible to implement fully
reliable data transfer without some minimal feedback, so FEC only provides a
partial solution if reliability is required.

In addition to the nominal packet loss rate, we should also consider the
typical burst losses on the target network. For example, if the overall loss
rate is relatively low, but it is common to lose 100 packets in a row, then
such a loss event can completely erase a block of 100 symbols. One option is
to increase the number of symbols to e.g. 200, then we can protect the block
against a burst loss of 100 packets with 50% overhead, i.e. 100 coded symbols.
Of course, this would significantly decrease our coding performance and using
such a high overhead can be wasteful. A better strategy is interleaving the
packets from multiple blocks: for example, we send 10 packets from the first
block, then 10 packets from the second block and so on. If we encounter a burst
loss of 100 packets, then the erasures will be evenly spread to 10 different
blocks (each missing about 10 symbols). Therefore we can compensate for such
a loss event with only 10% overhead and we don't have to increase the number
of symbols. Our udp_file_sender_receiver_ example implements a customizable
interleaving scheme.

.. _udp_file_sender_receiver: https://github.com/steinwurf/kodo-rlnc/tree/master/examples/udp_file_sender_receiver

Network Coding
--------------

Questions about general terms and concepts in network coding.

What is a source, sink, and relay?
..................................
.. _source:
.. _relay:
.. _sink:

One common application for erasure correcting codes (which includes
network coding) is to improve the performance of computer networks or
communication networks in general. For such applications, specific
terminology is often used to precisely define the roles of the
different entities in the network. For example:

A source is a device that transmits data to one or more other
devices(s). This is also often called the server.

A sink is a device that receives data from other devices(s). These
are also sometimes referred to as the clients.

A relay is a device that receives data from other devices(s) and
re-transmits that data to other devices(s), typically the relay itself
is not interested in receiving the data.

What do we mean by the original data?
.....................................

The original data is a file or a buffer stored in memory before it is
passed to the erasure correcting code. We sometimes also refer
to this as the uncoded data.

What is a code?
...............
.. _code:

Coding can be thought of as transforming the original data
to a form that is more appropriate for transportation. The erasure codes
that are implemented in Kodo can be used to recover packet erasures.
A packet erasure is the loss of a packet, similar to a lost letter in the
postal service.

What is a rateless code?
........................
.. _rateless:

With a rateless code an infinite number of representations of the
original data can be created, unlike for codes with a rate where a
fixed number of representations are possible. That makes it possible to
recover from any number of erasures with a rateless code.

What is a finite field?
.......................
.. _finite_field:

A finite field or Galois Field (GF) is a mathematical construct that entails
too much explanation to be included here, but some basic understanding can be
useful. In simple terms, a finite field is a field that contains a finite
number of elements where special rules are defined for the arithmetic
operations. These rules guarantee that the result of an arithmetic operation
is always an element that is in the field. This feature is very useful on
computers with fixed precision. One common field is the binary fieldm GF(2)
where addition is defined as the XOR operation. Typically we use GF(2) or
GF(2^8) where an element corresponds to a bit and a byte, respectively. The
size of a field is typically denoted as :math:`q`.

What is an element?
...................
.. _finite_field_element:

A finite field element can be thought of as an integer variable with a range
that corresponds to a specific finite field.

What is a symbol?
.................
.. _symbol:

A symbol is a vector of GF elements that represent some data. The size
of a symbol is given by the number of elements and the size of each
element.

:math:`|\boldsymbol{s}| = n \cdot \log_2(q) ~ [b]`

As an example 16 elements in GF(2) can represent two bytes.

What is a generation?
.....................
.. _generation:

Each generation constitutes :math:`g` symbols of size :math:`m`, where
:math:`g` is called the generation size. The :math:`g` original
symbols in one generation, are arranged in the matrix
:math:`\boldsymbol{M}= [ \boldsymbol{m}_1 ; \boldsymbol{m}_2 ; \dots
; \boldsymbol{m}_g ]`, where :math:`\boldsymbol{m}_i` is a column
vector. In an application the block of data can be a file or a part of
a media stream, and is divided into :math:`\lceil \frac{B}{m} \rceil`
pieces, called symbols. Generation number 0 constitutes the first `g`
symbols, or the first :math:`g \cdot m` bytes of data, there are
:math:`\lceil \frac{B}{g \cdot m} \rceil` of such generations.

What is the generation size?
............................
.. _generation_size:

The generation size is the number of symbols in the generation denoted
:math:`g`.


What is a coding vector?
........................
.. _coding_vector:

The coding vector describes how a coded symbol was coded. It contains
a coefficient (which is a element) for each symbol in the generation.

The coding vector is typically denoted; :math:`\boldsymbol{v} = \{v_0;
v_1; ... ; v_{g-1} \}`

This column vector of elements are the coefficients which have been
multiplied onto the original symbols.


What is a coded symbol?
.......................
.. _coded_symbol:

A coded symbol is a symbol which is a combination of the original
symbols in a generation. Therefore a coded symbol is a representation
of all the data in a generation, but it has the same size as an
original symbol.

A coded symbol is encoded by multiplying the original data with a
coding vector; :math:`\boldsymbol{x} = \boldsymbol{M} \cdot
\boldsymbol{v}`. See encoding_ for a more detailed description, and
recoding_ for how coded symbols are created when recoding.

What is a coded packet?
.......................
.. _coded_packet:

It is a pair of a coded symbol and a coding vector. To decode a coded
symbol the corresponding coding vector must be known and therefore
typically the two are transmitted together in a single packet;
:math:`\{ \boldsymbol{v}, \boldsymbol{x} \}`


What is linear dependency?
..........................
.. _linear_dependency:

A packet is non-innovative or linearly dependent if it only contains
information about previously known symbols. In other words, the packet
can be reduced to the zero vector using the linear combination of some
(partially) decoded symbols, therefore it is not useful in the decoding
process.

What is systematic coding?
..........................
.. _systematic_coding:

Systematic coding means first transmitting all symbols in two
stages. In the first stage, the sender transmits all original symbols
uncoded.  In the second stage, the sender generates random linear
combinations of the original symbols in order to correct any packet
losses which might have occurred during the first stage.

What is the code density?
.........................
.. _code_density:

The code density can be defined as the ratio of non-zero elements in
an coding vector. Full density can be achieved by selecting coding
coefficients according to a random uniform distribution. In contrast,
sparse codes use many zero coefficients in the coding vectors which
makes the encoding process significantly faster. The density of a
coding vector is the ratio of non-zero elements in the coding vector.

:math:`d(\boldsymbol{v}) = \frac{\sum_{i=1}^g \boldsymbol{v}_i \neq
0}{g}`, where: :math:`\boldsymbol{v}_i` is the coding vector

The density is sometimes also referred to as the degree.

How does encoding work?
.......................
.. _encoding:

To encode a new symbol :math:`\boldsymbol{x}` from a generation at the
source, :math:`\boldsymbol{M}` is multiplied with a randomly generated
coding vector :math:`\boldsymbol{v}` of length :math:`g`,
:math:`\boldsymbol{x} = \boldsymbol{M} \cdot \boldsymbol{v}`. In this
way we can construct :math:`g+r` coded symbols and coding vectors,
where :math:`r` is any number of redundant symbols as the code is
rateless. When a coded symbol is transmitted on the network it is
accompanied by its coding vector, and together they form a coded
packet. A practical interpretation is that each coded symbol, is a
combination or mix of the original symbols from one generation. The
benefit is that nearly infinite coded symbols can be created.

How does decoding work?
.......................
.. _decoding:

In order for a sink to successfully decode a generation, it must
receive :math:`g` linearly independent symbols and coding vectors from
that generation. All received symbols are placed in the matrix
:math:`\boldsymbol{\hat{X}} = [\boldsymbol{\hat{x}_1} ;
\boldsymbol{\hat{x}_2} ; \dots ; \boldsymbol{\hat{x}_g}]` and all
coding vectors are placed in the matrix
:math:`\boldsymbol{\hat{V}}=[\boldsymbol{\hat{v}_1} ;
\boldsymbol{\hat{v}_2} ; \dots ;\boldsymbol{\hat{v}_g} ]`, we denote
:math:`\boldsymbol{\hat{V}}` the coding matrix. The original data
:math:`\boldsymbol{M}` can then be decoded as
:math:`\boldsymbol{\hat{M}} = \boldsymbol{\hat{X}} \cdot
\boldsymbol{\hat{V}}^{-1}`. In practice if approximately **any**
:math:`g` symbols from a generation are received the original data in
that generation can be decoded. This is a much looser condition,
compared to when no coding is used, where exactly **all** :math:`g`
unique original symbols must be collected.

How does recoding work?
.......................
.. _recoding:

Any node that have received :math:`g'`, where :math:`g' = [2,g]` is
the number of received linearly independent symbols from a generation
and is equal to the rank of :math:`\boldsymbol{\hat{V}}`, can
recode. All received symbols are placed in the matrix
:math:`\boldsymbol{\hat{X}} = [\boldsymbol{\hat{x}_1} ;
\boldsymbol{\hat{x}_2} ; \dots ; \boldsymbol{\hat{x}_{g'}}]` and all
coding vectors in the matrix :math:`\boldsymbol{\hat{V}} =
[\boldsymbol{\hat{v}_1} ; \boldsymbol{\hat{v}_2} ; \dots ;
\boldsymbol{\hat{v}_{g'}}]`. To recode a symbol these matrices are
multiplied with a randomly generated vector :math:`\boldsymbol{w}` of
length `g'`, :math:`\boldsymbol{\tilde{v}} = \boldsymbol{\hat{G}}
\cdot \boldsymbol{w}`, :math:`\boldsymbol{\tilde{x}} =
\boldsymbol{\hat{X}} \cdot \boldsymbol{w}`. In this way we can
construct :math:`r'` randomly generated recoding vectors and
:math:`r'` recoded symbols. :math:`r'>g'` is possible, however a node
can never create more than :math:`g'` independent symbols. Note that
:math:`\boldsymbol{w}` is only used locally and that there is no need
to distinguish between coded and recoded symbols. In practice this
means that a node that have received more than one symbol can
recombine those symbols into recoded symbols, similar to the way coded
symbols are constructed at the source.


How can the role of a node change during a session?
...................................................

A sink can become a relay, and a relay can become a source. As an
example lets consider a topology with three nodes, A, B and C. B has a
link to both A and C, but A and C only have a link to B, and therefore
cannot communicate directly. A is the source and hold data that is to
be transmitted to both sinks B and C. Initially A transmits coded
packets to B. After some time B holds some coded (and uncoded) packets
but not the full data from A and starts to send recoded packets to C,
B has now become a relay. After some more time B has received enough
packets from A to decode the original data, B continues to send
packets to C, but B is now a source since it has all the original data
and can encode.

How does coding affect the overhead?
....................................

Network Coding involves some overhead as it is necessary to
communicate additional information in the coded packets (in the coding
vectors).  In practice, the size of the coding vector is generally
small compared to the packet payload. The exact size depends on the
finite field size, the generation size and the coding vector
representation.

Another source of overhead is linear dependency since a random code
might produce a small number of linearly dependent (redundant) coded
packets.  This should be considered if we choose a small field size or
low/sparse code density.

In practice, we can use a systematic code to ensure reliability with a
low overhead. This is the recommended approach in single-hop networks.


.. How does the field size affect the overhead?
.. ............................................

How does the generation size affect delay?
..........................................

The generation size :math:`g` is the number of symbols over which
encoding is performed, and defines the maximal number of symbols that
can be combined into a coded symbol. Data is decoded on a per
generation level, thus at least :math:`g` symbols must be received
before decoding is possible. Hence the size of a generation :math:`g
\cdot m` dictates the decoding delay which is the minimum amount of
data that must be received before decoding is possible.


.. How does the density impact coding?
.. ...................................

Why do we need generations?
...........................

If a whole file was considered one big block, then the computational
complexity of the encoding and decoding operations would be very
high. This is especially problematic on mobile and embedded devices
with limited computational capabilities. Therefore, large data sets
are typically split into several equal-sized generations.


When are the lost symbols/packets recovered?
............................................

Let's suppose the :math:`N` packets were lost from a generation
and the sender does not have any information about which packets were
lost. In this case, at least :math:`N` coded packets are required to
recover them. Note that the packets will not be recovered one-by-one,
but all at once after the decoder processes :math:`N` innovative coded
packets.

.. _the_basics:

The Basics
----------

In the following, we will walk through the process of creating an
encoder and a decoder for a single buffer of data.

Kodo implements a number of different erasure correcting codes. In
this example, we have chosen to use a particular version of a RLNC
(Random Linear Network Code).

The Full RLNC is one of the most common RLNC variants, and provides
several of the advantages that RLNCs have over traditional erasure
correcting codes.  However, for the time being we will just use it as
a standard erasure correcting code, namely to encode and decode some
data.

In the following, we will go through three of the key parameters to
choose when configuring an erasure correcting code:

* The number of ``symbols``
* The ``symbol_size``
* The finite field

In general if a block of data is to be encoded, it's split into a number of
:ref:`symbols <symbol>` of a specific size. If you multiply the number of
symbols with the symbol size, you get the total amount of data in bytes that
will be encoded or decoded per :ref:`generation <generation>`.

.. note:: Sizes in Kodo are always measured in bytes. So if you see a
          variable or function name that includes the word "size",
          bytes is the unit used.

.. note:: In network applications, a single symbol typically corresponds to
          a single packet (for example, a UDP datagram).

Let us briefly outline the impact of changing the three parameters.

Number of Symbols
.................

Denotes the number of symbols in a block/generation. Increasing this
number will have the following effects:

* The computational complexity will increase, and can therefore slow
  down the encoding/decoding.
* For some variants of RLNC, the per-:ref:`packet<coded_packet>`
  overhead will increase due to added coding coefficients.
* The per-symbol decoding delay will become larger: when we increase the
  number of encoded symbols, the decoder has to receive more symbols before
  decoding a full block.
* The protocol complexity can be decreased. If the number of symbols
  is increased so that all the data can fit in a single generation, then
  the protocol will only have to handle a single generation. But if multiple
  generations are needed, the receivers will have to tell from which
  generations the server should send data, and hence increasing the complexity
  of the protocol.
* The need for a high field size decreases (which is an advantage
  since, in short, a higher field size leads to higher complexity).
  The reason for this is that when the decoder is only missing a few
  symbols, the chance for it to receive a *useful* encoded symbol
  decreases. This reduction depends on the field size (higher is
  better). You pay this price at each generation, but if a generation
  contains many symbols this issue becomes smaller. Furthermore with
  many symbols, the generations will be bigger, and hence fewer
  generations are needed.

Symbol Size
...........

Denotes the size of each symbol in bytes. The choice of symbol size
typically depends on the application. For network applications we may
choose the symbol size according to the network MTU (Maximum Transfer
Unit) so that datagrams do not get fragmented as they traverse the
network. In those cases, symbol sizes are typically around 1300-1400
bytes. On the other hand, for storage applications the symbol size is
typically much larger, e.g., in the order of several megabytes.

Field Size
..........

The field size determines the core mathematics. Most erasure
correcting codes are based on :ref:`finite fields<finite_field>`.

* Increasing the field size will increase the probability of
  successful decoding.
* However it will typically also lead to increased computational
  complexity which results in slower applications.

We're now ready to look at the next example. Building on the previous
and very limited example, we extend this in a step-by-step manner to
finally end up with something that resembles the following:

.. literalinclude:: /../../kodo-rlnc/examples/tutorial/basic.cpp
    :language: c++
    :linenos:

Initially we define the three parameters that we mentioned above.
Note that the `Fifi <https://github.com/steinwurf/fifi>`_ library provides
efficient implementations for finite field computations You can choose
from a number of different finite fields, such as
``binary``, ``binary4``, ``binary8``, and ``binary16``.

.. literalinclude:: /../../kodo-rlnc/examples/tutorial/basic.cpp
    :language: c++
    :start-after: //! [0]
    :end-before: //! [1]
    :linenos:

Then we define a shorthand for our encoder and decoder types.

.. literalinclude:: /../../kodo-rlnc/examples/tutorial/basic.cpp
    :language: c++
    :start-after: //! [1]
    :end-before: //! [2]
    :linenos:

Once the key parameters are selected, we are ready to create an
encoder and a decoder to perform the actual coding.

.. literalinclude:: /../../kodo-rlnc/examples/tutorial/basic.cpp
    :language: c++
    :start-after: //! [2]
    :end-before: //! [3]
    :linenos:

The encoder and decoder types define a nested type called the
``factory``. Using the factory we can configure and build encoders and
decoders. We instantiate the factory using the chosen parameters.
Invoking the ``build()`` function will return a C++ shared pointer to a
new encoder or decoder. A shared pointer behaves like a normal pointer, but
it will delete the object when there are no more references to it.

Before the encoding and decoding of data can begin, two buffers are
needed.

.. literalinclude:: /../../kodo-rlnc/examples/tutorial/basic.cpp
    :language: c++
    :start-after: //! [3]
    :end-before: //! [4]
    :linenos:

The first buffer is the ``payload`` buffer. Once we start coding, this
buffer will contain a single encoded symbol which we can "transmit" to
the decoder. Besides the encoded symbol data, the payload buffer will
also contain internal meta-data describing how the symbol was
encoded. The format and size of this data depends on the chosen
coding vector format. Fortunately we don't have to worry about
that, as long as we provide a buffer large enough. The needed size of
the buffer is returned by the ``payload_size`` call.

The second buffer, ``block_in``, contains the data we wish to
encode. As mentioned earlier the size of this buffer is the number of
symbols multiplied by the symbol size. For convenience we can use the
``block_size`` function to get this value. In this case we are not
encoding real data, so we just fill the ``block_in`` buffer with some
randomly generated bytes. After this, we can call the ``set_const_symbols``
function on the encoder to specify which buffer it should encode.

We also define the ``block_out`` buffer for the decoder and call the
``set_mutable_symbols`` function. The decoder will decode the symbols in
this user-defined buffer.

.. note:: The ``block_in`` and ``block_out`` buffers should not be destroyed
          or moved after they are associated with the encoder and decoder.
          If these buffers are compromised, then the coding operations will
          be corrupted.

.. literalinclude:: /../../kodo-rlnc/examples/tutorial/basic.cpp
    :language: c++
    :start-after: //! [4]
    :end-before: //! [5]
    :linenos:

Finally, we have everything ready to start the coding. This is done in
a loop until the decoding has successfully completed.

.. literalinclude:: /../../kodo-rlnc/examples/tutorial/basic.cpp
    :language: c++
    :start-after: //! [5]
    :end-before: //! [6]
    :linenos:

We use a variable ``encoded_count`` to keep track of the number of
symbols we've encoded. When we finish this number should match the
``symbols``, as all data is passed safely on to the decoder, we shall
later see examples where this is not necessarily the case.  The loop
stops when the decoders ``is_complete`` function returns true. This
happens when all symbols have been decoded.  The encoder encodes into
the payload buffer and returns then number of bytes used during the
encoding, and hence the number of bytes we have to transmit over the network
in a real application.  The payload is passed to the decoder which decodes
the encoded data and thereby increases its rank. When the decoding process is
completed, the decoded data will be available in the ``block_out`` buffer.

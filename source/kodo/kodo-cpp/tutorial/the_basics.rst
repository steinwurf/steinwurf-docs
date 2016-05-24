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
* The finite field, or more specifically the field size used.

In general if a block of data is to be encoded, it's split into a number of
:ref:`symbols <symboĺ>` of a specific size. If you multiply the number of
symbols with the symbol size, you get the total amount of data in bytes that
will be either encoded or decoded per :ref:`generation <generation>`.

.. note:: Sizes in Kodo are always measured in bytes. So if you see a
          variable or function name that includes the word "size",
          bytes is the unit used.

.. note:: In network applications, a single symbol typically
          corresponds to a single packet (for example, an UDP
          datagram).

Let us briefly outline the impact of changing the three parameters.

Number of Symbols
.................

Denotes the number of symbols in a block/generation. Increasing this
number will have the following effects:

* The computational complexity will increase, and can therefore slow
  down the encoding/decoding.
* For some variants of RLNC, the per-:ref:`packet<coded_packet>`
  overhead will increase due to added coding coefficients.
* The per-symbol decoding delay will become larger. The reason for
  this is that when we increase the number of symbols that are encoded
  the decoder has to receive more symbols before decoding.
* The protocol complexity can be decreased. If the number of symbols
  is increased so that all the data which is to be encoded can fit in
  a single generation, the protocol will only have to handle a single
  generation.  If multiple generations are needed, the receivers will
  have to tell from which generations the server should send data, and
  hence increasing the complexity of the protocol.
* The need for a high field size decreases (which is an advantage
  since, in short, a higher field size leads to higher complexity).
  The reason for this is that when the decoder is only missing a few
  symbols, the chance for it to receive a *useful* encoded symbol
  decreases.  This reduction depends on the field size (higher is
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
network. In those cases symbols sizes are typically around 1300-1400
bytes. On the other hand for storage applications the symbol size is
typically much larger, e.g., in the order of several megabytes.

Field Size
..........

The field size determines the core mathematics. Most erasure
correcting codes are based on :ref:`finite fields<finite_field>`.

* Increasing the field size will increase the probability of
  successful decoding.
* However it will typically also lead to increased computational
  complexity which results in slower applications.

We are now ready to look at our first example:

.. literalinclude:: /../../kodo-cpp/examples/tutorial/basic.cpp
    :language: c++
    :linenos:

Initially we define the two parameters number of ``symbols`` and the
``symbol_size``.

.. literalinclude:: /../../kodo-cpp/examples/tutorial/basic.cpp
    :language: c++
    :start-after: //! [0]
    :end-before: //! [1]
    :linenos:

In the given example, the codec and the finite field types are specified
by first two parameters of encoder and decoder factories. Since
fast finite field computations are not only useful in erasure
correcting codes, this part of the functionality has been split into a
second library called `Fifi <https://github.com/steinwurf/fifi>`_. The
Fifi library defines a number of different finite fields such as
``binary``, ``binary4``, ``binary8``. To switch to a different field you
can simple replace ``field::binary8`` with one of the other field types,
e.g. ``field::binary``.

Once the key parameters have been selected, we are ready to create an
encoder and a decoder to perform the actual coding.

.. literalinclude:: /../../kodo-cpp/examples/tutorial/basic.cpp
    :language: c++
    :start-after: //! [1]
    :end-before: //! [2]
    :linenos:

We use the ``encoder_factory`` and ``decoder_factory`` objects to configure
and build encoders and decoders. Invoking the ``build()`` function will return
a new encoder or decoder object. These objects actually contain C++ smart
pointers under the hood, so you can pass them around to other fuctions and
the underlying objects will be deleted when there are no more references
to them.

Before the encoding and decoding of data can begin, we define two buffers.

.. literalinclude:: /../../kodo-cpp/examples/tutorial/basic.cpp
    :language: c++
    :start-after: //! [2]
    :end-before: //! [3]
    :linenos:

The first buffer is the ``payload`` buffer. Once we start coding, this
buffer will contain a single encoded symbol which we can "transmit" to
the decoder. Besides the encoded symbol data, the payload buffer will
also contain a header that describes how the symbol was
encoded. The format and size of this data depends on the chosen
erasure correcting code. Fortunately we don't have to worry about
that as long as we provide a large enough buffer. The needed size of
the buffer is returned by the ``payload_size`` function.

The second buffer, ``data_in``, contains the data we wish to
encode. As mentioned earlier the size of this buffer is the number of
symbols multiplied by the symbol size. For convenience we can use the
``block_size`` function to get this value. In this case we are not
encoding real data, so we just fill the ``data_in`` buffer with some
randomly generated data.

Once the buffers have been created we can call the ``set_const_symbols``
function on the encoder to specify which buffer it should encode.

.. literalinclude:: /../../kodo-cpp/examples/tutorial/basic.cpp
    :language: c++
    :start-after: //! [3]
    :end-before: //! [4]
    :linenos:

We also create a third buffer, ``data_out``, where the decoder will store
the decoded data. The size of this buffer is the same as the size of
``data_in``. Again, we call the ``block_size`` function to get the proper size.
We do not have to initialize this buffer, we just pass it as a parameter
of the ``set_mutable_symbols`` function, and the decoder will take control
of the buffer.

.. literalinclude:: /../../kodo-cpp/examples/tutorial/basic.cpp
    :language: c++
    :start-after: //! [4]
    :end-before: //! [5]
    :linenos:

Finally we have everything ready to start the coding. This is done in
a loop until the decoding is completed.

.. literalinclude:: /../../kodo-cpp/examples/tutorial/basic.cpp
    :language: c++
    :start-after: //! [5]
    :end-before: //! [6]
    :linenos:

We use a variable ``encoded_count`` to keep track of the number of
symbols we have encoded. When we finish, this number should match the
``symbols`` as all data is passed safely to the decoder, we shall
later see examples where this is not necessarily the case.  The loop
stops when the decoders ``is_complete`` function returns true. This
happens when all symbols have been decoded.  The encoder encodes into
the payload buffer and returns the number of bytes used during the
encoding, and hence the number of bytes we would have to transmit
over the network. The payload is passed to the decoder which decodes
the encoded data and thereby increases its rank.

When the decoding process is completed, the data will be available in
the ``data_out`` buffer, so we check that its contents match the original
data be in ``data_in``.

.. literalinclude:: /../../kodo-cpp/examples/tutorial/basic.cpp
    :language: c++
    :start-after: //! [6]
    :end-before: //! [7]
    :linenos:


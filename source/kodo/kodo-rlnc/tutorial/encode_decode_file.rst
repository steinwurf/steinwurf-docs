.. _encode_decode_file:

Encoding and decoding files
---------------------------

In this example we show how to encode/decode files with Kodo. Note that
this example is nearly identical to the :ref:`encoding_and_decoding_large_objects`
example. For this reason, we will mainly highlight the differences.

.. contents:: Table of Contents
   :local:

The complete example
~~~~~~~~~~~~~~~~~~~~

.. literalinclude:: /../../kodo-rlnc/examples/encode_decode_file/encode_decode_file.cpp
    :language: c++
    :linenos:

Adding the includes
~~~~~~~~~~~~~~~~~~~

First we have to provide the appropriate includes which defines the
codec that we want to use and the ``kodo_core::object::file_encoder``
and ``kodo_core::object::file_decoder`` classes.

.. literalinclude:: /../../kodo-rlnc/examples/encode_decode_file/encode_decode_file.cpp
    :language: c++
    :start-after: //! [0]
    :end-before: //! [1]
    :linenos:

Specifying the coding parameters
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

For the file encoder/decoder case three options are new. The first is
the file name for encoding, the second is the file name for decoding
and finally the file size.

.. note:: In a real application, we would most likely not use different
          file names for the encoder and decoder.

.. note:: The file size is only needed by the file decoder. The file
          encoder knows the file size after opening the file.

As with the :ref:`encoding_and_decoding_large_objects` example, we pass the
type of the actual encoder and decoder as a template argument.

.. literalinclude:: /../../kodo-rlnc/examples/encode_decode_file/encode_decode_file.cpp
    :language: c++
    :start-after: //! [2]
    :end-before: //! [3]
    :linenos:


Creating a test file
~~~~~~~~~~~~~~~~~~~~

Here we create a test file to use for the encoder. This is just for
the sake of the example.

.. literalinclude:: /../../kodo-rlnc/examples/encode_decode_file/encode_decode_file.cpp
    :language: c++
    :start-after: //! [4]
    :end-before: //! [5]
    :linenos:


Using the file encoder and decoder
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

As with the storage encoders, we now build the file encoder and decoder.

.. literalinclude:: /../../kodo-rlnc/examples/encode_decode_file/encode_decode_file.cpp
    :language: c++
    :start-after: //! [6]
    :end-before: //! [7]
    :linenos:

Also the encoding/decoding loop is similar to the
:ref:`encoding_and_decoding_large_objects` example, since we
potentially need more than one encoder/decoder pair to code the entire
file.

.. literalinclude:: /../../kodo-rlnc/examples/encode_decode_file/encode_decode_file.cpp
    :language: c++
    :start-after: //! [8]
    :end-before: //! [9]
    :linenos:

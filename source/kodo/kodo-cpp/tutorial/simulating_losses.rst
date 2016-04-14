Simulating Losses
-----------------

In this example we will expand the previous basic example by
simulating some loss of the encoded data. This can be done simply by
not "transmitting" some encoded symbols to the decoder. The complete
example is shown below.

.. literalinclude:: /../../kodo-cpp/examples/tutorial/add_loss.cpp
    :language: c++
    :linenos:

As the attentive reader might notice, only the coding loop is changed
from the basic example.

.. literalinclude:: /../../kodo-cpp/examples/tutorial/add_loss.cpp
    :language: c++
    :start-after: //! [0]
    :end-before: //! [1]
    :linenos:

The change is fairly simple. We introduce a 50% loss using ``rand() %
2`` and add a variable ``dropped_count`` to keep track of the dropped
symbols.

The encoder can, in theory, create an infinite number of
coded symbols, because we are using a rateless code. This means that as long
as the loss is below 100%, the decoder will be able to finish the decoding.

A graphical representation of the setup is seen in the figure below.

.. image:: /../images/tutorial_add_loss.svg
   :align: center

The output of this example will be something like this (the output
will change as we seed the random generator with the time):

.. code-block:: none

    Bytes used = 1405
    Bytes used = 1405
    Bytes used = 1405
    Bytes used = 1405
    Bytes used = 1405
    Bytes used = 1405
    Bytes used = 1405
    Bytes used = 1405
    Bytes used = 1405
    Bytes used = 1405
    Bytes used = 1405
    Bytes used = 1405
    Bytes used = 1405
    Bytes used = 1405
    Bytes used = 1405
    Bytes used = 1405
    Bytes used = 1417
    Bytes used = 1417
    Bytes used = 1417
    Bytes used = 1417
    Bytes used = 1417
    Bytes used = 1417
    Bytes used = 1417
    Bytes used = 1417
    Bytes used = 1417
    Bytes used = 1417
    Bytes used = 1417
    Encoded count = 27
    Dropped count = 11

An interesting thing to notice is the number of bytes used. It
increases slightly after the encoder has encoded 16 symbols (the same
number as the number of symbols in the generation). This is because
the encoder exits the systematic phase where it sends the symbols
uncoded. This technique will be explained in following example.

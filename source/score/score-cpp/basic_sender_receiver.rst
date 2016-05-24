Basic sender & receiver
-----------------------

This basic example shows a score-cpp sender and receiver application that are
used to multicast a single buffer of data on a local network.

The complete sender example is shown below.

.. literalinclude:: /../../score-cpp/examples/simple_sender/simple_sender.cpp
    :language: c++
    :linenos:

First we create an io_service and a sender object, then configure the
destination address for the sender. We also set the end-of-transmission
callback that will be executed when the sender completes the transmission of
all data and repair packets.

After the initialization, we allocate a small buffer that should be transmitted
to the receiver(s). We could fill this block with some actual data (e.g. from
a small file), but that is not relevant here. We write this data block to the
sender with ``write_data``, then we call ``end_of_transmission``
to notify the sender that no more data will be added after this. The receivers
will also get this information.

The actual network operations start when we run the io_service (this is the
event loop that drives the sender). The event loop will terminate when the
sender finishes all transmissions, because we explicitly stop the io_service
in our ``eot_callback`` function.

There is no need to manually clean up the allocated objects, since score-cpp
provides automatic memory management. The objects will be deleted when they
go out of scope.

The code for the corresponding receiver application is shown below.

.. literalinclude:: /../../score-cpp/examples/simple_receiver/simple_receiver.cpp
    :language: c++
    :linenos:

The initialization steps are very similar for the receiver, but we also set
a callback function that will be executed when data is received. We could
process the incoming data, but here the ``read_data`` lambda function just
prints the size of the received block. Note that we have written a single
block of data on the sender side, so the same block will be received in one go
(i.e. ``read_data`` will be called once when the full block is available).
If we send multiple blocks, then this callback function would be invoked for
each block.

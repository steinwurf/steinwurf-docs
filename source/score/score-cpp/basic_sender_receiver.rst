Basic sender & receiver
=======================

This basic example shows a score-cpp sender and receiver application that are
used to multicast a single buffer of data on a local network.

The complete sender example is shown below.

.. literalinclude:: /../../score-cpp/examples/simple_sender/simple_sender.cpp
    :language: c++
    :linenos:

First we create an io_service and a sender object, then configure the
destination address for the sender.

After the initialization, we allocate a small buffer that should be transmitted
to the receiver(s). We could fill this block with some actual data (e.g. from
a small file), but that is not relevant here. We write this data block to the
sender with ``write_data``. After this, we send a small 1-byte message using the
same ``write_data`` function. This small 1-byte message is the
end-of-transmission message. When the receiving application sees this message,
it knows no data more will arrive, and it can shut down.
The end-of-transmission message format is defined by the application, and can be
anything.  After this we set a callback to be executed when the sender'
transmission queue is empty and no more data is to be sent. Here, we stop the
IO service in this callback.

The actual network operations start when we run the io_service (this is the
event loop that drives the sender). The event loop will terminate when the
sender finishes all transmissions, because we explicitly stop the io_service
in our ``on_send_queue_threshold_callback`` callback function. This also means
that receivers that have not received everything when this callback is executed
will never finish transmission. This approach does not leave much time for
repairing packet loss. A more advanced application may want to leave time for
receivers to request and receive repair data before shutting down
the event loop.

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
prints the size of the received block and checks if the received message is the
defined end-of-transmission messsage. The receiver event loop is stopped when
this message is received.
Note that we have written a single block of data on the sender side,
so the same block will be received in one go (i.e. ``read_data`` will be called
once when the full block is available, and finally when the end-of-transmission
message is received.). If we send multiple blocks, this callback function would
be invoked for each block.
The data messages are atomic in scorecpp, so no partial message will be passed
to the read_data function.

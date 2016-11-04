Basic sender & receiver
-----------------------

This basic example shows a score-c sender and receiver application that are
used to multicast a single buffer of data on a local network.

The complete sender example is shown below.

.. literalinclude:: /../../score-c/examples/simple_sender/simple_sender.c
    :language: c
    :linenos:

First we create an io_service and a sender object, then configure the
destination address for the sender.

After the initialization, we allocate a small buffer that should be transmitted
to the receiver(s). We could fill this block with some actual data (e.g. from
a small file), but that is not relevant here. We write this data block to the
sender with ``score_write_data``. After this, we send a small
end-of-transmission message that the receiver recognizes and can act upon.
Here this message is just a single byte with value 'zero'.
Finally, we call ``score_flush`` to make sure that everything buffered inside
the sender will be queued for transmission.

We also set the callback that will be executed when the sender transmission
queue is emptied. This is a normal C function where we can also pass an
arbitrary value using the ``context`` parameter. If this callback is set before
any data is written to the sender (and thus the send queue is empty when it is
set), the callback will be called immediately.

The actual network operations start when we run the io_service (this is the
event loop that drives the sender). The event loop will terminate when the
sender finishes all transmissions, because we explicitly stop the io_service
in our ``on_queue_empty_callback`` function.

The final step is cleaning up all resources with the appropriate deleters.
This is very important in C that does not provide automatic memory management.

The code for the corresponding receiver application is shown below.

.. literalinclude:: /../../score-c/examples/simple_receiver/simple_receiver.c
    :language: c
    :linenos:

The initialization steps are very similar for the receiver, but we also set
a callback function that will be executed when data is received. We could
process the incoming data, but here the ``read_data_callback`` function just
prints the size of the received block. Note that we have written a single
block of data on the sender side, so the same block will be received in one go
(i.e. the ``read_data_callback`` function will be called once when the full
block is available). If we send multiple blocks, then this callback function
would be invoked for each block.

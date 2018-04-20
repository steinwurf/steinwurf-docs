Stream Sender & Receiver
========================

This example shows a score sender and receiver application that are
used to multicast a stream of atomic messages on a local network.

The complete sender example is shown below.

.. literalinclude:: /../../score/examples/udp_stream_sender_receiver/udp_stream_sender.cpp
    :language: c++
    :linenos:

After creating an io_service and a sender object, we configure the
destination address for the sender with ``add_remote``. We set the
end-of-transmission callback to stop the io_service when the sender completes
the transmission of all data and repair packets. This should happen after
the user closes the stream by typing Q.

We start a separate thread for running the io_service (this is the event
loop that drives the sender and all network operations), because we will
use the main thread to get input from the user. We read lines from standard
input in a while loop, and each line is written to the sender as a separate
atomic message. We call ``flush`` after each ``write_data`` to ensure that
the messages are transmitted immediately. **Calling flush() after each
message is not recommended in a real application,** but this example functions
like a multicast chat program, and we want to deliver the messages to our
receivers right away. The ``flush`` function should only be called when we want
to ensure that no data is buffered within the sender. For example, before
shutting down the sender. It may also be used before a break or pause in the
data stream will occur.

If the input message is the end-of-transmission message ('Q'), then we set a
callback to be executed when the sender transmission queue gets empty
(everything is sent). We will stop the IO service when this happens.

We also exit the while loop if the user types Q or q.  After this, we join
the ``io_thread`` to wait for the io_service to stop when all data has been
pushed to the network.

The code for the corresponding receiver application is shown below.

.. literalinclude:: /../../score/examples/udp_stream_sender_receiver/udp_stream_receiver.cpp
    :language: c++
    :linenos:

The receiver is less complex in this case, since we only run the main thread
where we print the incoming messages in the ``read_message`` lambda function.
This callback function is invoked for each atomic message that is received
from the sender. It is guaranteed that the messages are delivered in order,
but some messages might be lost under poor network conditions. The score sender
can be configured to compensate a certain level of packet loss or to
automatically adjust the data redundancy based on the feedback from the
receivers. For these adjustments, see the :ref:`score_parameters` section.

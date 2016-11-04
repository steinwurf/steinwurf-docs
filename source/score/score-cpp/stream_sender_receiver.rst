Stream sender & receiver
========================

This example shows a score-cpp sender and receiver application that are
used to multicast a stream of atomic messages on a local network.

The complete sender example is shown below.

.. literalinclude:: /../../score-cpp/examples/simple_stream_sender/simple_stream_sender.cpp
    :language: c++
    :linenos:

After creating an io_service and a sender object, we configure the
destination address for the sender with ``set_remote``. We set the
end-of-transmission callback to stop the io_service when the sender completes
the transmission of all data and repair packets. This should happen after
the user closes the stream by typing Q.

We start a separate thread for running the io_service (this is the event
loop that drives the sender and all network operations), because we will
use the main thread to get input from the user. We read lines from standard
input in a whileloop, and each line is written to the sender as a separate
atomic message. If the message is the end-of-transmission message ('Q'),
we call ``flush`` after ``write_data`` to ensure the internal buffers are
cleared and everything is queued for transmission. After this we set a callback
to be executed when the sender transmission queue is empty (everything is sent).
Here we just stop the IO service.

The ``flush`` function should only be called when it should be certain that no
data is buffered within the sender. For example before shutting down the sender.
It may also be used before a break or pause in the data stream will occur.
However for such cases the sender has a built-in auto flush mechanism that will
trigger a flush after an idle period, ensuring that no data will be buffered
in the sender for long periods of time.

We exit the while loop if the user types Q or q.
The receivers will stop after receiving the end-of-transmission message
("Q" or "q"). After this, we join ``io_thread`` to wait for the io_service to
stop. The io_service is stopped in the callback given to
``set_on_send_queue_threshold_callback``. This means that the thread stops when
all data has been pushed to the network.

The code for the corresponding receiver application is shown below.

.. literalinclude:: /../../score-cpp/examples/simple_stream_receiver/simple_stream_receiver.cpp
    :language: c++
    :linenos:

The receiver is less complex in this case, since we only run the main thread
where we print the incoming messages in the ``read_data`` lambda function.
This callback function is invoked for each atomic message that is received
from the sender. It is guaranteed that the messages are delivered in order,
but some messages might be lost under poor network conditions. The score sender
can be configured to compensate a certain level of packet loss or to
automatically adjust the data redundancy based on the feedback from the
receivers. For these adjustments, see the score parameters section.

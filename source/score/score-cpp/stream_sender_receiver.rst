Stream sender & receiver
------------------------

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
atomic message. After ``write_data`` we also call ``flush`` to ensure
the transmission of the current message to the receivers. Without this call,
the sender would buffer some data to send coded packets of optimal size, but
here we prefer low delay over optimal link utilization.

We exit the while loop if the user types Q or q,  then we call
``end_of_transmission`` to notify the sender that no more data will be added
after this. The receivers will also get this information. After this, we join
the ``io_thread`` to wait for the io_service to stop.

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
receivers.

.. _overview_score:

Overview
========

The score library implements the Simple COded REliability (SCORE) protocol
for reliable unicast and multicast communication over UDP. The protocol is
designed for distribution of data from a sender to one or more receivers.
It is primarily intended for reliable transmission, but it also supports
best-effort delivery, e.g. for cases where no feedback channel is available.
Reliability is ensured using an erasure correcting code, provided by Kodo.

.. _libraries_score:

Libraries
---------

The score repository is located here: https://gitlab.com/steinwurf/score

The score API also contains the generic ``source`` and ``sink`` objects that
can process data without relying on a specific network stack. It is possible to
use this generic API with a custom socket implementation, so this could be
the preferred option if you want to integrate score into an application that
already has a custom socket framework. If you want to make to experiment with 
other custom modification or learn more about the inner workings of the library 
this would also be the place to look.


A high level C++ Wrapper is available here https://gitlab.com/steinwurf/score-udp

These wrappers provide access to the full functionality of score without
exposing any implementation details to the user. 
The high-level API includes the ``udp_sender`` and ``udp_receiver`` classes
that implement the score protocol features on top of a boost::asio UDP socket.
This can be a convenient option when a customized socket implementation is
not necessary.

.. _score_parameters:

Features
--------

Proactive Redundancy
    Redundancy generated using an erasure correcting code can be scheduled
    proactively e.g. to overcome some know link erasure probability and/or to
    reduce delay due to reduced feedback and scheduling additional redundancy.

Reactive Redundancy
    When too little data is received to ensure reliability, additional redundancy
    can be generated using and erasure correcting code and transmitted from the
    sender.

Data Flush
    When a file transfer is completed or a pause in a stream occurs, the
    outgoing data at the sender can be flushed to ensure reliability and avoid
    adding delay.

Sender Profiles
    Different profiles catering to different scnearios and use cases are provided.
    The stream profile sender should be chosen for scenarios where timely delivery
    is more important than reliability, e.g. audio or video streaming. The object
    profile should be used in scenarios where data integrity (reliable transmission)
    is important, e.g. file delivery.

Receiver Feedback (Optional)
    The receivers can provide feedback to the sender over the link where data is
    transmitted or over some independent link, e.g. if a one-way link is used for
    transmitting the data. The feedback is can be used by the sender to report user
    statistics and adapt to changing network conditions.

Serializing and Deseserializing (Optional)
    Application data can be send as atomic units (messages) or as a stream.


Parameters
----------

The score protocol provides a set of parameters that can be adpated to
accommodate the needs of different applications. Should the default stream and
object senders not provide the needed performance, a set of parameters can be
adjusted depending on the requirements:

- Symbol size
- Generation size
- Data redundancy
- Feedback probability
- Generation window size
- Send rate

All of these parameters can be controlled by a custom controller which can
adjust the parameter based on available state information and the priority of
the specific application.

Symbol and Generation Size
..........................

The symbol size defines the size (in bytes) of the data chunks that the score
protocol operates on.
In general, this symbol size should be as big as possible, while
staying below the network MTU. E.g. for WiFi networks with an MTU of 1500 bytes,
a symbol size of roughly 1400 bytes is recommended.
For low bandwidth streams that require a low delay, it may be beneficial to
lower the symbol size. This lowers the data delivery delay, as
data packets are sent more frequently from the sender, as well as the repair
process is triggered more often.

The generation size defines the number of symbols grouped together by score
and processed for repair. A larger generation size generally means more
efficient operation (slightly less data pushed to the network), while a smaller
generation size generally means lower latency between transmission and delivery
of data.

Data Redundancy
...............

The data redundancy parameter is used to pro-actively introduce repair data
to counteract packet loss on the network. A parameter value of ``0.0`` means
that only the original data is transmitted initially, and then the repair phase
must handle any loss that may occur. Increasing the value to e.g. ``0.25``
will add 25% repair data in addition to the original data. The stream will then
be able to pro-actively repair packet loss of up to 20% without the need for a
repair phase. As packet loss on a link (especially wireless multicast) is
difficult to predict, this approach will generally decrease the efficiency of
the transmission. However, the data delivery delay will generally be reduced,
as data is readily available without the need for repair phases.

Feedback Probability
....................

Internally, score schedules repair data based on feedback received from
receivers. Feedback messages are generated at specific feedback events during
transmission. For multicast scenarios with a lot of receivers
(e.g. more than 20), feedback from every receiver is not needed. In fact, it
may cause problems as these feedback messages take up wireless capacity.
To reduce the feedback to a sensible amount, the feedback probability parameter
can be adjusted. This parameter describes the probability that a receiver
generates feedback at a feedback event. Setting the value to ``1.0`` (default)
causes a receiver to send feedback at every feedback event. Reducing the value
to e.g. ``0.5`` causes the receiver to generate feedback with a 50% chance.
When reducing this parameter, only a subset of all receivers will generate
feedback for each feedback event, reducing the network load induced by feedback.
As the information in the feedback messages mostly overlap between receivers,
the transmission performance is not reduced as long as enough feedback messages
are generated. Generally the original performance should be preserved if roughly
10 feedback messages are generated at each feedback event. For example in a
multicast scenario with approximately 100 receivers, a feedback probability of
``0.1`` should not reduce score transmission performance.
The feedback probability can also be set to ``0.0`` to obtain a "best effort"
mode of operation, where no feedback will be sent at all, and the recovery of
packet loss fully relies on the data redundancy parameter.

Generation Window Size
......................

The sender temporarily stores previously transmitted data in an internal buffer
in case a receiver needs repair data at a later point in time. The size of this
internal buffer denotes how far back in the data stream repair data can be
requested.
When a repair is needed for a segment in the data stream, all successfully
received subsequent segments will be held back until this segment is repaired.
The receivers are aware of the internal buffer size of the sender. If the
segment is not repaired before it is discarded (overwritten) at the sender,
the receiver will discard this data as well, and proceed to the following
data segments. That is, the maximum period of time that subsequent data is held
back is implicitly defined by the size of this internal buffer.
If the application requires a low transmission latency
(e.g. live video streaming), it is recommended to reduce this buffer size.

Consider for example a live video stream with an average bitrate of 4 Mbps.
If a target latency between transmission and presentation should be below one
second, the maximum internal buffer size should not exceed 0.5 MB, as this
(on average) corresponds to one second worth of video. The buffer size is
defined in 'number of generations', and the resulting size in bytes is thus
implicitly declared through parameters ``symbol size`` and ``generation size``.
For a symbol size of 1000 and a generation size of 10, the generation window
size parameter should be set to 50 in order to get a resulting internal buffer
size of 500 kB (= 0.5 MB).

Send Rate
.........

It is possible to limit the send rate to a desired max rate, either to make room
for other network traffic or to prevent packet loss due to congestion.
Since score uses UDP traffic, it does not implement any sort of congestion
control algorithm. The send rate does not force the data stream to be sent out
with a certain rate. That is, sending a stream that is generated by the
application at rate ``X`` will also be sent at roughly rate ``X``,
as long as the specified send rate ``Y`` is higher than ``X``.
The send rate is a limit, and only guarantees that this limit is not exceeded.
The actual send rate may be lower than the specified limit.


Platform Support
----------------

Score is portable to a wide range of platforms (both hardware platforms and
operating systems).

We ensure compatibility with the supported platforms through a suite of unit
tests, the current status can be checked at the `Steinwurf Buildbot`_ page.
At the bottom of the main page, you can find detailed information
about which platforms and compilers are currently tested by Steinwurf.

.. _Steinwurf Buildbot: http://buildbot.steinwurf.com

.. note:: The Buildbot is used for several different libraries. The
  score library can be found in the overview on the main page.

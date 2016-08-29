.. _score_parameters

Score Parameters
================

The score protocol provides a set of parameters that can be tuned to accommodate
the needs of an application.
The two sender types (stream and object senders) sets these parameters to
default values adjusted towards stream or object use cases respectively.
For most usage scenarios choosing a sender is adequate. A stream sender should
be chosen for scenarios where timely delivery is more important than
reliability. This could be audio or video streaming. An object sender should be
chosen in scenarios where data integrity (reliable transmission) is important,
e.g. file delivery.

Should the default stream and object senders not provide the needed performance,
a set of parameters can be adjusted depending on the requirements:

- Symbol size
- Generation size
- Data redundancy
- Feedback probability
- Generation window size
- Send rate

These parameters and their function is covered in the following sections.

Symbol and Generation Size
--------------------------

The symbol size defines the size (in bytes) of the data chunks that the score
protocol operates on. These chunks are denoted symbols because they are treated
as mathematical entities within score.
In general, this symbol size should be as big as possible, while
staying below the network MTU. E.g. for WiFi networks with an MTU of 1500 bytes,
a symbol size of roughly 1400 bytes is recommended.
For low bandwidth streams that requires a low delay, it may be beneficial to
lower the symbol size to e.g. 400 bytes. This lowers the data delivery delay, as
data packets are sent more frequently from the sender, as well as the repair
process is triggered more often.

The generation size defines the number of symbols grouped together by score
and processed for repair. A larger generation size generally means more
efficient operation (slightly less data pushed to the network), while a smaller
generation size generally means lower latency between transmission and delivery
of data.

Data Redundancy
---------------
The data redundancy parameter is used to pro-actively introduce repair data
to counteract packet loss on the network. A parameter value of ``0.0`` means
that only the original is transmitted initially, and then the repair phase
must handle any loss that may occur. Increasing the value to e.g. ``0.25``
will add 25% repair data in addition to the original data. The stream will then
be able to pro-actively repair packet loss of up to 20% without the need for a
repair phase. As packet loss on a link (especially wireless multicast) is
difficult to predict, this approach will generally decrease the efficiency of
the transmission. However, the data delivery will generally be reduced, as data
is readily available without the need for repair phases.

Feedback Probability
--------------------
Internally, score schedules repair data based on feedback received from
receivers. Feedback messages are generated at specific feedback events during
transmission. For multicast scenarios with a lot of receivers
(e.g. more than 20), feedback from every receiver is not needed. In fact, it
may cause problems as these feedback messages take up wireless capacity.
To reduce the feedback to a sensible amount, the feedback probability parameter
can be adjusted. This parameter describes the probability that a receiver
generates feedback at a feedback event. Setting the value to ``1.0`` (default)
causes a receiver to send feedback at every feedback event. Reducing the value
to e.g. ``0.5`` causes the receiver to generate feedback with a 50 % chance.
When reducing this parameter, only a subset of all receivers will generate
feedback for each feedback event, reducing the network load induced by feedback.
As the information in the feedback messages mostly overlap between receivers,
the transmission performance is not reduced as long as enough feedback messages
are generated. Generally the original performance should be preserved if roughly
10 feedback messages are generated at each feedback event. For example in a
multicast scenario with approximately 100 receivers, a feedback probability of
``0.1`` should not reduce score transmission performance.
The feedback probability can also be set to ``0.0`` to obtain a "best effort"
mode of operation, where no feedback will be sent at all, and fully recovery of
packet loss relies on the data redundancy parameter.

Generation Window Size
----------------------
The sender temporarily stores previously transmitted data in an internal buffer
in case a receiver needs repair data at a later point in time. The size of this
internal buffer denotes how far back in the data stream repair data can be
requested.
When a repair is needed for a segment in the data stream, all successfully
received subsequent is held back until this segment is repaired. The receivers
are aware of the internal buffer size of the sender. If the segment is not
repaired before it is discarded (overwritten) at the sender, the receiver will
discard this data as well, and proceed to the following data segments. That is,
the maximum period of time that subsequent data is held back is implicitly
defined by this size of this internal buffer.
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
size of 500kB (=0.5MB).

Send Rate
---------
It is possible to limit the send rate to a desired max rate, either to make room
for other network traffic or to prevent packet loss due to congestion.
As the score uses UDP traffic it does not implement any sort of congestion
control algorithm. The send rate does not force the data stream to be sent out
with a certain rate. That is, sending a stream that is generated by the
application with rate ``X`` at the sender is also sent with roughly rate ``X``,
as long as specified send rate ``Ỳ`` is higher than ``X``. The send rate is a
limit, and only guarantees that this limit is not exceeded. The actual send rate
may be lower than the specified limit.

.. _score:

Score
=====

The score library implements the Simple COded REliability (SCORE) protocol
for reliable UDP unicast and multicast communication. The protocol is designed
for distribution of data from a sender to one or more receivers. It is
primarily intended for reliable transmission, but it also supports best-effort
delivery, e.g. for cases where no feedback channel is available. Reliability
is ensured using Random Linear Network Coding.

Score is only available under a commercial license.

The score repository: https://gitlab.com/steinwurf/score

.. toctree::
   :maxdepth: 2

   quick_start_score

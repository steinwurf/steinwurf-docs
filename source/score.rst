.. _score:

Score
-----

The score library implements the Simple Coded Reliable protocol for reliable
unicast and multicast communication over UDP. The protocol makes it easy to
efficiently transmit data to many devices simultaneously over a shared
medium, e.g. WiFi.

The library is available on a wide range of platforms, and it is designed for
easy integration with existing software. It exposes a simple API to allow the
programmer to take advantage of Reliable Multicast in a custom application.

score: https://steinwurf.gitlab.io/score/index.html
    The score library implements the Simple Coded Reliable protocol and
    the basic score objects in a network-agnostic fashion.

score-udp: http://docs.steinwurf.com/score-udp/master/index.html
    This library is a high-level C++ wrapper for score to implement unicast
    and multicast communication using UDP sockets. These wrappers provide
    access to the functionality of score without exposing any implementation
    details to the user.

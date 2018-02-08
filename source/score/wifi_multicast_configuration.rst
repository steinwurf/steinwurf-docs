============================
WiFi Multicast Configuration
============================

Configuring and selecting the right access point is a crucial part of
setting up a functional multicast solution. In this section we will provide
advice on how we deal with various WiFi issues and how we configure our WiFi
access points to get the best possible performance.

If you have additional advice on how to improve WiFi multicast please
get in touch - we would love to talk with you: :ref:`contact_us`.


WiFi Multicast Issue
===================================

Performance of WiFi multicast suffers from several different issues. These
issues make it hard for multicast services to get decent performance over
WiFi networks.

Most of the issues have been described in the following two IETF RFCs:

1. `Multicast Wifi Problem Statement
<https://datatracker.ietf.org/doc/draft-mcbride-mboned-wifi-mcast-problem-statement/>`_

2. `Multicast Considerations over IEEE 802 Wireless Media
<https://datatracker.ietf.org/doc/draft-perkins-intarea-multicast-ieee802/>`_


Access Point Configuration
==========================

Given the outlined WiFi multicast issues here are some configuration
options that can be adjusted on the WiFi access point to get better
multicast performance.

Reducing the Beacon Interval & DTIM Period
------------------------------------------

WiFi access points announce their presence by sending out *beacons*,
however beacons are also used to announce whether it has traffic queued up
for power saving clients. This information is delivered inside a bitmap
in the beacon called the Traffic Indication Map (TIM).

The AP uses a special type of Traffic Indication Map (TIM) to to announce
that the it's about to transmit all buffered broadcast and multicast frames
called the Delivery Traffic Indication Map (DTIM). Since all clients are
expected to receive broadcast/multicast traffic - all clients are expected
to wake up and listen for the traffic. How often a beacon includes a DTIM
is controlled by the DTIM period.

For these reasons you should consider the following configurations:

* Setting the **DTIM period to 1** will make every beacon a DTIM beacon.
  Multicast/broadcast traffic will be sent after each beacon.
* Set a low **beacon interval e.g. 15ms** (most access points use per
  default 100ms)

Reducing Max Listen Interval (OpenWrt)
--------------------------------------

The OpenWrt option `max_listen_int` states the maximum number of beacons a
station (e.g. mobile device) may sleep before checking if data is pending.
Reducing this may keep devices awake to receive the broadcast packets more
often. If the option is set too low, the devices can not associate with the
access point. For some Huawei tablets the threshold seems to be `5`, while
the Samsung galaxy s6 does not connect to the network if the value is below
`10`. Either way, in practice this option does not make devices stay awake
for more broadcast packets than usual.

Force Physical Layer Data Rate - PHY Rate (OpenWrt)
---------------------------------------------------

Default multicast PHY rate varies from access point to access point. But,
the WiFi standard mandates that it be at least 1 Mbps for 2.4 Ghz and 6
Mbps for 5 Ghz. This is typically not enough for e.g. HD video streaming.
We therefore typically have to increase it. With OpenWrt we can do this
using the following approach:

When logged onto the access point e.g. via SSH the physical layer data rate
can be configured with the following command::

    iw dev wlan0 set bitrates legacy-5 24 36 48

This will set the minimum data rate for the 5 GHz network to 24 Mbps.

Which Access Point to Buy
=========================

We have tested a few access points and had reasonable results with
following consumer grade equipment.

.. attention:: We are in no way affiliated with any of these brands. We
   we take no responsibility for the performance you may experience.

D-Link DIR-860L (H/W Ver.: B1)
------------------------------

* SoC: MT7621AT
* Wireless 5GHz: MT7612E 802.11an+ac
* Wireless 2.4GHz: MT7602E 802.11bgn

We tested with newest OpenWrt (at the time):

* OpenWrt commit 3a1dac546ac4a1498c89f2c95c668cdfb569cd8e
* 2.4GHz wifi disabled.
* htmode ‘HT20’

Using a 24 Mbps PHY rate the access point now runs stable. However, it does
not seem possible to increase the data rate to above ~7.2 Mbps (application
layer) before a major packet loss occur, even when forcing bitrates above
24 Mbps.

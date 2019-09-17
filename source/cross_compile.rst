.. _cross_compile:

Cross-compilation and Tool Options
==================================

This section describes the waf configuration options that are used to
cross-compile Kodo for different platforms and to change some properties
of your builds.

.. contents:: Table of Contents
   :local:

Changing the compiler
---------------------

You can select a specific compiler with an mkspec (explained below) or
you can set the ``CXX`` variable to your preferred compiler.
For example, if you want to use clang++, just add ``CXX=clang++`` in front of
``python waf configure``::

    CXX=clang++ python waf configure

.. note:: ``clang++`` is currently the default compiler on Mac OSX, therefore
          this customization step is not needed on that operating system.

Generic tool options
--------------------

cxx_debug
    By default, our build system will remove all debugging info from the
    generated binaries. You can enable the debugging symbols with the
    ``cxx_debug`` option::

        python waf configure --cxx_debug

    .. note:: Using this option will add a ``_debug`` postfix to the waf build
              output path. For example, your binaries will be built in
              ``build\linux_debug`` or ``build\win32_debug``.

run_tests
    You can use this option to run the unit tests after your build is
    completed::

        python waf build --run_tests

run_benchmark
    You can use this option to run a specific benchmark after your build is
    completed::

        python waf build --run_benchmark=my_benchmark

enable_codecs
    You can configure kodo-c to only enable some desired codecs and disable
    all others. For example::

        python waf configure --enable_codecs=full_vector

    Run ``python waf --help`` to list the available codecs. You can even
    select multiple codecs with a comma-separated list::

        python waf configure --enable_codecs=full_vector,seed,sparse_seed


Cross-compilation options
-------------------------

We use "mkspecs" (short for "make specifications") to instruct ``waf`` to select
a specific compiler based on its version number (e.g. ``4.8``) and binary name
(e.g. ``g++-4.8`` or ``arm-linux-androideabi-g++``). Some mkspecs also
include compiler and linker flags to select a CPU architecture or
change some other characteristics of the build process. You can select an
mkspec with the ``cxx_mkspec`` tool option, see various examples below.

By using an mkspec, we can easily select a toolchain that can compile binaries
for different platforms. First, you have to install the appropriate toolchain,
then you can configure Kodo with the corresponding mkspec.

Different mkspecs are available on different operating systems. You can
get the list of the currently supported mkspecs with the ``config.py`` helper
script located in the Kodo root folder::

    python config.py

This helper script automatically updates itself when you run it. You can use
this script to go through the common configuration options without typing
too much.

Android
.......
You need a standalone Android toolchain to compile for Android. You can follow
the instructions in this `Android guide`_ to quickly create a toolchain using
the latest Android NDK.

You can also download a toolchain for your platform from this page:
http://files.steinwurf.com/toolchains

You also need the Android SDK, because we need to find the ``adb`` tool
during the configure step. If you do not have it already the `Android
guide`_ describes both where to download the Android SDK and how to get the
``adb`` tool. To ensure our build system will pick up the dependencies, the
easiest solution is to add the path to ``adb`` and the ``bin`` folder of
the standalone toolchain to your PATH. For example, you can add the
following lines to your ``~/.profile`` (please adjust the paths to match
your folder names and locations)::

    PATH="$PATH:$HOME/toolchains/android-sdk-linux/platform-tools"
    PATH="$PATH:$HOME/toolchains/arm-linux-androideabi-r18b/bin"

You need to log in again or open a new terminal to get the updated PATH.
You can check that the required binaries are really in your PATH with these
commands::

    adb version
    arm-linux-androideabi-clang++ --version

Once you have everything in your PATH, use the following mkspec when you
configure (you may also select another Android mkspec if available
in the list provided by ``config.py``)::

    python waf configure --cxx_mkspec=cxx_android5_clang70_armv7

Note that the ``android5`` designation in the mkspec indicates that a
position independent executable (PIE) will be generated. This is required
on Android 5 and above, but Android 4.1+ can also run a PIE binary.

The configure command should find your toolchain and the necessary binaries,
and you can build the codebase as usual after this::

    python waf build

You can find the generated Android binaries in the
``build/cxx_android5_clang70_armv7`` folder. You can transfer these binaries to
your Android device with adb (you can use ``/data/local/tmp/`` as a target
folder).

If you don't want to add the Android toolchains to your PATH, then we also
provide explicit options to specify these folders during the configure step.
Here is an example for that::

    python waf configure --cxx_mkspec=cxx_android5_clang70_armv7 \
    --android_sdk_dir=~/toolchains/android-sdk-linux \
    --android_ndk_dir=~/toolchains/arm-linux-androideabi-r18b

.. note:: If you want to use the generated static libraries with ``ndk-build``,
          then make sure that you process at least one C++ source file (.cpp)
          with ``ndk-build`` (this can be a dummy cpp file). Otherwise you
          will get a lot of linkage issues, because ``ndk-build`` does not link
          with the C++ standard library by default.

.. _Android guide: https://developer.android.com/ndk/guides/standalone_toolchain


iOS
...
You need to install the latest XCode to compile for iOS. Please make sure
that you also have the Apple command-line tools in your PATH by executing
the following command on OSX Mavericks::

    xcode-select --install

Open a Terminal, and use this command to check if you have the Apple LLVM
compiler in your PATH::

    clang++ --version

XCode installs the iOS SDK to a standard location, so you only need to specify
the iOS mkspec when you configure (please note that the version numbers in
the name of the mkspec may change, so use ``config.py`` to list the currently
available versions)::

    python waf configure --cxx_mkspec=cxx_ios70_apple_llvm_armv7

Then you can build Kodo as usual::

    python waf build

You can find the generated iOS binaries in the
``build/cxx_ios70_apple_llvm_armv7`` folder. You can transfer these binaries
to your iOS device with any tool you like. Please note that these are
command-line binaries, so you will need a terminal application to run them.


Raspberry Pi
............
Sometimes the easiest solution is compiling our libraries on the Raspberry Pi
itself. Raspbian 9 (Stretch) provides g++ 6.3 that fully supports the C++14
standard. Note that the compilation on the Raspberry can be slow, since it has
a limited amount of RAM. If you experience any memory-related issues, then
try to limit the waf build process to a single job::

    python waf build -j1

If you have a Raspberry Pi 2 (or newer) running Raspbian 9 (Stretch), then
you can also use the Linaro gcc 6.3 toolchain to cross-compile for your
device. You can find the pre-built toolchain archives here:
https://releases.linaro.org/components/toolchain/binaries/6.3-2017.02/arm-linux-gnueabihf/

If your host machine is running 64-bit Linux, then you need to download this
archive: https://releases.linaro.org/components/toolchain/binaries/6.3-2017.02/arm-linux-gnueabihf/gcc-linaro-6.3.1-2017.02-x86_64_arm-linux-gnueabihf.tar.xz

Then extract the archive to a folder of your liking (we will use
``~/toolchains`` as a target folder in this guide)::

    cd ~/toolchains
    tar -xf gcc-linaro-6.3.1-2017.02-x86_64_arm-linux-gnueabihf.tar.xz

You also need to add the ``bin`` folder of the Linaro toolchain to your PATH.
You can modify your PATH temporarily using a shell script. For a permanent
change, you can add the following lines to your ``~/.profile``
(please adjust the paths to match your folder names and locations)::

    PATH="$PATH:$HOME/toolchains/gcc-linaro-6.3.1-2017.02-x86_64_arm-linux-gnueabihf/bin/"

You need to log in again or open a new terminal to get the updated PATH.
You can check that the required binaries are in your PATH with this command::

    arm-linux-gnueabihf-g++ --version

Now you can configure our libraries using the following mkspec::

    python waf configure --cxx_mkspec=cxx_gxx63_armv7

The configure command should find your toolchain binaries,
and you can build the codebase as usual after this::

    python waf build

You can find the generated binaries in the ``build/cxx_gxx63_armv7`` folder.
You can transfer these binaries to your Raspberry Pi with any tool you like
(e.g. SCP).


OpenWrt
.......
You should build a compatible OpenWrt toolchain for your target device.
Here we explain how to do that for a device with an ARM CPU.

First, you should install the required packages to build the toolchain (this
list works for Ubuntu and Debian)::

    sudo apt-get install gcc g++ subversion git-core build-essential gawk libncurses5-dev zlib1g-dev libssl1.0-dev unzip

Then clone the standard OpenWrt toolchain (you change the target path if
you prefer)::

    cd ~/toolchains
    git clone https://github.com/openwrt/openwrt.git
    cd openwrt

This guide was written using OpenWrt 18.06, and it is recommended
to check out the same branch::

    git checkout openwrt-18.06

This command will pop up a menuconfig window::

    make package/symlinks

Here you should select a Target System and a Target Profile that are
compatible with your OpenWrt device.

Save this initial menuconfig, and then open the full menuconfig::

    make menuconfig

Make sure that GCC 7.x is selected in the Toolchain Options::

    [*] Advanced configuration options (for developers)  --->
     Toolchain Options  --->
      GCC compiler Version (gcc 7.x)  --->
       (X) gcc 7.x

Save the configuration and build the OpenWrt toolchain (``-j4`` uses 4 cores to
speed up the process)::

    make -j4

After the toolchain is built, you need to add the ``bin`` folder of the
generated toolchain to your PATH (the toolchain is created in the
``staging_dir`` folder). You should also set the ``STAGING_DIR`` variable
to point to the ``staging_dir`` folder. For example, you can add the following
lines to your ``~/.profile`` (please adjust the paths to match your folder
names and locations if necessary)::

    PATH="$PATH:$HOME/toolchains/openwrt/staging_dir/toolchain-arm_cortex-a15+neon-vfpv4_gcc-7.3.0_musl_eabi/bin"
    STAGING_DIR="$HOME/toolchains/openwrt/staging_dir/"
    export STAGING_DIR

You need to log in again or open a new terminal to get the updated PATH.
You can check that the required binaries are in your PATH with this command::

    arm-openwrt-linux-g++ --version

Go to your Kodo folder, and configure Kodo with the following mkspec::

    python waf configure --cxx_mkspec=cxx_openwrt_gxx73_armv7

The configure command should find your toolchain binaries,
and you can build the codebase as usual after this::

    python waf build

You can find the generated binaries in the ``build/cxx_openwrt_gxx73_armv7``
folder. You can transfer these binaries to your OpenWrt device with any tool
you like (e.g. SCP). The binaries can be a bit large, because the mkspec embeds
the C++ standard library (with the ``-static-libstdc++`` linker flag).
The ``libstdcpp`` package is usually not installed on OpenWrt devices, or it
might be incompatible with the GCC 7.x compiler.

Note that the following packages are required on your OpenWrt device to
run the generated binaries, you can run these commands on your device if it
has Internet connectivity::

    opkg install libpthread
    opkg install librt
    opkg install libatomic

Alternatively, you can activate these packages in ``menuconfig`` and deploy
the generated ``*.ipk`` files manually on the device (with SCP and opkg)::

    Base system  --->
        <*> libatomic
        <*> libpthread
        <*> librt


Other toolchains
................
Other toolchains might also work if you specify your custom compiler with
the CXX variable when you configure Kodo::

    CXX=/path/to/custom/compiler/g++ python waf configure

This compiler must have a recognizable name (e.g. it contains the ``g++``
string) and waf must be able to determine its version to accept it.

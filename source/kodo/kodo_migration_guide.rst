.. _kodo_migration_guide:

Kodo Migration Guide
====================

The top-level API of the various kodo projects is very similar, therefore
migrating from one API to another is a straightforward task. This migration
guide shows the pseudo-code of the same basic example using the API of each
kodo project. The pseudo-code does not cover the input and output buffers,
but you can find the detailed examples in the specific projects. If you
started using one project and you want to migrate to another one, then this
guide should give you an overview about the API differences.

kodo-cpp
--------

.. code-block:: cpp

    #include <kodocpp/kodocpp.hpp>

    int main()
    {
        uint32_t symbols = 10;
        uint32_t symbol_size = 1000;
        kodocpp::codec codec = kodocpp::codec::full_vector;
        kodocpp::field field = kodocpp::field::binary8,

        kodocpp::encoder_factory encoder_factory(
            codec, field, symbols, symbol_size);

        kodocpp::decoder_factory decoder_factory(
            codec, field, symbols, symbol_size);

        kodocpp::encoder encoder = encoder_factory.build();
        kodocpp::decoder decoder = decoder_factory.build();

        encoder.set_const_symbols(..., encoder.block_size());
        decoder.set_mutable_symbols(..., decoder.block_size());

        while (!decoder.is_complete())
        {
            encoder.write_payload(...);
            decoder.read_payload(...);
        }
    }

kodo-c
------

.. code-block:: c

    #include <kodoc/kodoc.h>

    int main()
    {
        uint32_t symbols = 10;
        uint32_t symbol_size = 1000;
        int32_t codec = kodoc_full_vector;
        int32_t field = kodoc_binary8;

        kodoc_factory_t encoder_factory =
            kodoc_new_encoder_factory(codec, field, symbols, symbol_size);

        kodoc_factory_t decoder_factory =
            kodoc_new_decoder_factory(codec, field, symbols, symbol_size);

        kodoc_coder_t encoder = kodoc_factory_build_coder(encoder_factory);
        kodoc_coder_t decoder = kodoc_factory_build_coder(decoder_factory);

        uint32_t block_size = kodoc_block_size(encoder);
        kodoc_set_const_symbols(encoder, ..., block_size);
        kodoc_set_mutable_symbols(decoder, ..., block_size);

        while (!kodoc_is_complete(decoder))
        {
            kodoc_write_payload(encoder, ...);
            kodoc_read_payload(decoder, ...);
        }
    }

kodo-rlnc
---------

.. code-block:: cpp

    #include <kodo_rlnc/full_vector_codes.hpp>

    int main()
    {
        uint32_t symbols = 10;
        uint32_t symbol_size = 1000;
        fifi::api::field field = fifi::api::field::binary8;

        using rlnc_encoder = kodo_rlnc::full_vector_encoder;
        using rlnc_decoder = kodo_rlnc::full_vector_decoder;

        rlnc_encoder::factory encoder_factory(field, symbols, symbol_size);
        rlnc_decoder::factory decoder_factory(field, symbols, symbol_size);

        auto encoder = encoder_factory.build();
        auto decoder = decoder_factory.build();

        encoder->set_const_symbols(storage::storage(...));
        decoder->set_mutable_symbols(storage::storage(...));

        while (!decoder->is_complete())
        {
            encoder->write_payload(...);
            decoder->read_payload(...);
        }
    }

kodo-python
-----------

.. code-block:: python

    import kodo

    def main():

        symbols = 10
        symbol_size = 1000

        encoder_factory = kodo.FullVectorEncoderFactoryBinary8(symbols, symbol_size)
        decoder_factory = kodo.FullVectorDecoderFactoryBinary8(symbols, symbol_size)

        encoder = encoder_factory.build()
        decoder = decoder_factory.build()

        data_in = os.urandom(encoder.block_size())
        encoder.set_const_symbols(data_in)

        while not decoder.is_complete():
            payload = encoder.write_payload()
            decoder.read_payload(payload)

        data_out = decoder.copy_from_symbols()

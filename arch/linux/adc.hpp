/* ADC BUFFER */

#include <ATcommon/DataStore/Buffer.hpp>
#include <ATcommon/DataStore/AtomicBuffer.hpp>

DataStore::AtomicBuffer<uint16_t> raw_adc_inputBuffers[ADC_CHANNEL_COUNT];
DataStore::ArrayBuffer<DataStore::AtomicBuffer<uint16_t>, uint8_t> adc_inputBuffers(raw_adc_inputBuffers, ADC_CHANNEL_COUNT);


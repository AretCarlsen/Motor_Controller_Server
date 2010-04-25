/* ADC BUFFER / INTERRUPT and SYSTEM TIMER */

// ADC input buffer capacity
#define ADC_INPUT_BUFFER_CAPACITY 3
// ADC channel count
#define ADC_CHANNEL_COUNT 2
// Number of raw readings that are averaged before sinking into the input buffers.
// About 12,019 readings occur per second (20MHz, /128 prescaler, 13 cycles per measurement),
// or one every 83.2us. Averaging 20 improves accuracy and cuts down to 601 measurements
// that must be processed each second. At a 5ms processing frequency, that's 3 measurements
// per processing tick.
#define ADC_AVERAGED_READINGS 120

AnalogEncoder::RawMeasurement_t raw1_adc_inputBuffer[ADC_CHANNEL_COUNT][ADC_INPUT_BUFFER_CAPACITY];
DataStore::RingBuffer<AnalogEncoder::RawMeasurement_t, uint8_t> raw2_adc_inputBuffers[ADC_CHANNEL_COUNT] = {
  DataStore::RingBuffer<AnalogEncoder::RawMeasurement_t, uint8_t>(raw1_adc_inputBuffer[0], ADC_INPUT_BUFFER_CAPACITY),
  DataStore::RingBuffer<AnalogEncoder::RawMeasurement_t, uint8_t>(raw1_adc_inputBuffer[1], ADC_INPUT_BUFFER_CAPACITY)
};
DataStore::RingBuffer<AnalogEncoder::RawMeasurement_t, uint8_t>* raw3_adc_inputBuffers[ADC_CHANNEL_COUNT] = {
  raw2_adc_inputBuffers,
  raw2_adc_inputBuffers + 1
};
DataStore::ArrayBuffer<DataStore::RingBuffer<AnalogEncoder::RawMeasurement_t, uint8_t>*, uint8_t> adc_inputBuffers(raw3_adc_inputBuffers, ADC_CHANNEL_COUNT, ADC_CHANNEL_COUNT);


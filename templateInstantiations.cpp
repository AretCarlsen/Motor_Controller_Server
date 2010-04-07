typedef FixedPoint<int16_t, 12> PIDFpType;
// Template instantiations
  // PID engine/server
template class PID::PIDEngine<PIDFpType, PIDFpType>;
template class PID::PIDEngineInputServer<PIDFpType, PIDFpType>;
template class PID::PIDEngineTargetServer<PIDFpType, PIDFpType>;
  // For MAPPackets et al
template class DataStore::DynamicArrayBuffer<uint8_t,uint8_t>;


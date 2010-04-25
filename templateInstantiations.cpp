typedef FixedPoint<int16_t, 14> PIDFpType;
// Template instantiations
  // PID engine/server
template class PID::PIDEngine<PIDFpType, PIDFpType>;
template class PID::PIDEngineInputServer<PIDFpType, PIDFpType>;
template class PID::PIDEngineTargetServer<PIDFpType, PIDFpType>;
template class PID::PIDEngineParameterServer<PIDFpType, PIDFpType>;
//template PIDFpType abs(PIDFpType);


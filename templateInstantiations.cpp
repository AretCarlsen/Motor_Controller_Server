// Copyright (C) 2010, Aret N Carlsen (aretcarlsen@autonomoustools.com).
// Motor Controller Server running under MapOS.
// Licensed under GPLv3 and later versions. See license.txt or <http://www.gnu.org/licenses/>.

// Template instantiations.


#include "main.hpp"

#include <MapOS/templateInstantiations.cpp>

// Template instantiations
  // PID engine/server
template class PID::PIDEngine<PIDFpType, PIDFpType>;
template class PID::PIDEngineInputServer<PIDFpType, PIDFpType>;
template class PID::PIDEngineTargetServer<PIDFpType, PIDFpType>;
template class PID::PIDEngineParameterServer<PIDFpType, PIDFpType>;


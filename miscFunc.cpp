// Snap a process period to the nearest SystemTimer value.
SystemTimer_t snapTo(SystemTimer_t value, SystemTimer_t period){
  if(value % period != 0)
    value += period - (value % period);

  return value;
}


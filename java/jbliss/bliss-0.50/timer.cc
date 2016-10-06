#include <unistd.h>
#include <sys/times.h>
#include "timer.hh"

/*
 * Copyright (c) Tommi Junttila
 * Released under the GNU General Public License version 2.
 */

namespace bliss {

static const double numTicksPerSec = (double)(sysconf(_SC_CLK_TCK));

Timer::Timer()
{
  reset();
}

void Timer::reset()
{
  struct tms clkticks;

  times(&clkticks);
  start_time =
    ((double) clkticks.tms_utime + (double) clkticks.tms_stime) /
    numTicksPerSec;
}


double Timer::get_duration()
{
  struct tms clkticks;

  times(&clkticks);
  double intermediate = 
    ((double) clkticks.tms_utime + (double) clkticks.tms_stime) /
    numTicksPerSec;
  return intermediate - start_time;
}

} // namespace bliss

#strict
#include HLS_

Activate:
  if(!ActIdle())
    return(1);
  Sound("Connect");
  ChangeDef(HLS_);
  ShiftContents(Contained(), 0, HLS_);
  return(1);

DeathLaser:
  return(1);
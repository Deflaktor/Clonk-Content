#strict
/* Indicator */

local waitTime, timePassed;

public func Trigger(int wait) {
  if(wait>0) {
    waitTime=wait;
    SetAction("TimerWait");
	SetPhase(0);
	return(1);
  }
  SetAction("Execution");
}

protected func Timer() {
  if(!(GetAction()S="TimerWait"))
    return(1);
  timePassed++;
  SetPhase(8*timePassed/waitTime);
  if(timePassed>=waitTime) {
    SetAction("Execution");
  }
}

protected func Remove() {
  RemoveObject();
}
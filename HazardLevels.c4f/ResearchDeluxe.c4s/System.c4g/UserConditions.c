#strict
#appendto TC1_

public func Condition1() {
  return(GBackLiquid());
}

public func Condition2() {
  return(GetAction(Local(0)) S= Local(1));
}

public func Condition3() {
  actuator=FindObject(Local(0),-Local(1),-Local(1),Local(1)*2,Local(1)*2);
  return(actuator);
}

public func Condition4() { // Unused
  return(Local(Local(1), Local(0)));
}

public func Condition5() {
  actuator=Contained(Local(0));
  return(actuator);
}

public func Condition6() {
  return(GameCall("MainEnergySupply",Local(0)));
}
/*-- Fleisch --*/

#strict

public func Activate(object pClonk)
{
  [$TxtEat$]
  Eat(pClonk);
  return(1);
}

public func Eat(object pClonk)
{
  pClonk->~Feed(10);
  RemoveObject();
  return(1);
}

public func Bake() {
  ChangeDef(MEAC);
  return(1);
}

// Kann im Backtrog gemixt und im Ofen gebacken werden
public func IsDough() { return(1); }
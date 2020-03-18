/*-- Grünzeug --*/

#include TREE

#strict

protected func Initialize()
  {
  SetAction(Format("Green%d", Random(4)));
  SetR(Random(80)-40);
  return(1);
  }
  
protected func Damage() {
  if (GetDamage() < 15) return(0);
  DestroyIt();
  return(1);
}

private func DestroyIt() {
  if(GetAction() S= "Remove")
    return(1);
  if(GetAction() S= "Green2")
    CastObjects(WOOD, 2, 5, 0, 5);
  else
    CastObjects(WOOD, 1, 5, 0, 5);
  SetCategory(C4D_Vehicle);
  SetAction("Remove");
}

private func Remove() {
  RemoveObject();
}

public func ChopDown() {
  var obj=FindObject(0,0,0,0,0,OCF_CrewMember,0,this());
  if(obj) {
    obj->FinishCommand(0,1,0);
	obj->SetAction("Walk");
	obj->Explode(10);
  }
  DestroyIt();
}


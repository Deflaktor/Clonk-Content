#strict
#appendto _CHP

// Make Chippie not move after Script-Rage to ensure it will stay the same 
// position each time and not walk away from the position it is supposed to be.

Rage:
  Local(1)=true;
  return(SetLocal(0,Local(0)+1));
  
private JumpDrop:
  if(Local(1)) return(1);
  if (SEqual(GetAction(),"Hangle")) return(SetAction("Jump"));
  Jump();
  return(1);

  
private ChangeDir:
  if(Local(1)) return(1);
  if (SEqual(GetAction(),"Hangle")) return(ChgDirHangle());
  SetVar(0,COMD_Left());
  if (Random(2)) SetVar(0,COMD_Right());
  SetComDir(Var(0));
  return(1);
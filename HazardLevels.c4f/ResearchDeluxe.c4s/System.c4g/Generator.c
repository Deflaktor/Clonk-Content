#strict
#appendto _GEN

Transfer:
  if(Global(6)) {
    ObjectCall(Local(1), "Trigger", Local(4));
    Local(1)=0;
    if(Local(2))
      Local(3)++;
    if(Local(2)&&Local(3)>=12) {
      ObjectCall(Local(2), "Trigger", Local(4));
      Local(2)=0;
      Local(3)=0;
      ControlDownSingle();
      Local(3)=1;
    }
  }
  return(_inherited());

ControlDownSingle:
  [Herunterfahren]
  if(Local(3)) return(0);
  return(_inherited());

ControlUpSingle:
  [Anfahren]
  Local(4)=Par(0);
  if( Local(3) ) 
    if( Var(0)=FindContents(_COM,Par(0)) ) {
      Sound("Connect");
      RemoveObject(Var(0));
      SetLocal(3);
    }
  if(Local(3)) return(0);
  return(_inherited());

Activate:
  if(Equal(Local(3),1))  if(SetVar(0,1))  Message("Pfeilsicht deaktiviert.",this()); 
  if(Equal(Local(3),0))  if(SetVar(0,2))  Message("Pfeilsicht ein.",this());
  SetLocal(3,Sub(Var(0),1));
  return(1);



ControlThrow: 
  SetLocal(9,Par(0)); 
  if (SEqual( GetAction(Par(0)),"AimBow" )) return(1,Fire());  
  if (Not(ObjectCall( Par(0), "ReadyToFire" )))    return(0);
  if (And( ObjectSetAction(Par(0),"AimBow"), SetPhase(3,Par(0)) )) return(1);      
  return(0);

ControlUp:
  if (SEqual(GetAction(Par(0)),"AimBow"))   if (GreaterThan(GetPhase(Par(0)),0))   return(SetPhase( Sum(GetPhase(Par(0)),-1), Par(0) ));
  return(0);
ControlDown:
  if (SEqual(GetAction(Par(0)),"AimBow"))   if (LessThan(GetPhase(Par(0)),5))   return(SetPhase( Sum(GetPhase(Par(0)),+1), Par(0) ));
  return(0);
ControlLeft:
  if (SEqual(GetAction(Par(0)),"AimBow"))    return(SetDir(DIR_Left(),Par(0)));
  return(0);
ControlRight:
  if (SEqual(GetAction(Par(0)),"AimBow"))    return(SetDir(DIR_Right(),Par(0)));
  return(0);
ControlRightDouble:
  if (IsAiming())    And( ObjectCall( Par(0), "StopAiming" ), SetComDir(COMD_Right(),Par(0)) );
  return(0);
ControlLeftDouble:
  if (IsAiming())    And( ObjectCall( Par(0), "StopAiming" ), SetComDir(COMD_Left(),Par(0)) );
  return(0);

IsAiming:
  return (SEqual( GetAction(Contained()),"AimBow" ));

/* Local (0)  =  Köcher
   Local (1)  =  ID des Pfeils
   Local (2)  =  Pfeil selbst 
   Local (3)  =  1, wenn die Sicht verfolgt werden soll, sonst 0
   Local (9)  =  Der schiessende Clonk   */

IstdaeinKoecher:
  SetLocal(0, FindContents(KO3A, Contained()));
  if(Not(Local(0))) Message("Ich habe gar keinen Köcher!",this());
  if(Local(0)) return(1);
  return(0);

SchnappDenPfeil:
  SetLocal(1,Local(1,Local(0)));        //ID merken
  SetLocal(2,FindContents(Local(1),Local(0)));       //Pfeil statt ID merken
  Exit(Local(2));                   //Pfeil aus dem Köcher werfen
  Enter(this(),Local(2));           //Pfeil in den Bogen tun
  return(Local(2));            //Dem Befehl Fire den Pfeil mitteilen

Fire:
  if (SEqual(GetAction(),"Reload")) return(0);
  if (Not(Call("IstdaeinKoecher"))) return(0);

  if (Not(SetVar(0,Call("SchnappDenPfeil")))) ObjectCall(Local(0),"Ammochange");
  if(Not(Var(0))) return(0);

  SetLocal(2,2,Var(0));
  while ( Not(Equal(GetID(Contents(0,Contained())),BO3B)) )  if (Not(ShiftContents(Contained())))   return(0);
  SetVar(4,Sum(Mul(GetPhase(Contained()),2),3));
  if ( Equal(GetDir(Contained()),DIR_Left()) ) SetVar(4, Mul(Var(4),-1) );
  SetVar(5,Sum(GetPhase(Contained()),1));
  SetVar(7, Mul( Var(4), 13) );
  SetVar(3, Sum( Div( Mul( GetPhase(Contained()), 30), 2), 2 ) );
  if ( Equal(GetDir(Contained()),DIR_Left()) ) SetVar(3, Mul(Var(3),-1) );
  SetVar(2, Div( Mul( Sum(GetPhase(Contained()),-3), 30), 2) );
  if (Equal(GetPhase(Contained()),5)) SetVar(2,10);
  SetVar(6, +3);
  if ( Equal(GetDir(Contained()),DIR_Left()) ) SetVar(6, Mul(Var(6),-1) );
  SetOwner( GetOwner(Contained()), Var(0) );
  Exit(Var(0), Var(4),Var(5),Var(7), Var(3),Var(2),Var(6) );
  ObjectCall(Var(0),"Start",Contained());

// Sicht verfolgen
  if(Equal(Local(3),1)) if (Not(Equal(GetPlrView(GetController(Contained())),2)))  SetPlrView(GetController(Contained()),Var(0));


  Sound("Bow");  
  SetAction("Reload");
  return(1);


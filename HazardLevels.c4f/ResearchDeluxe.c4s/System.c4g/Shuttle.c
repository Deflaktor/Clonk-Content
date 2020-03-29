#strict
#appendto SHT1

ExecuteHomebaseAutomatic:
  // HomebaseAutomatic nicht aktiv
  if (Not(HomebaseAutomaticEnabled())) return(0);
  // Kein Kommando, Rückkehr zur Basis (Orbit), vorher Mannschaft rauswerfen
  if (Not(GetCommand())) {
    if (Global(340)) {
      SetCommand(this(),"MoveTo",0,GetX(),-80);
      AppendCommand(this(),"Call",this(),0,0,0,0,"GiveCrewExp");
      return(1);
    } 
    if (Not(DispatchCrew()))
      SetCommand(this(),"MoveTo",0,GetX(),-80);
  }
return(1);

GiveCrewExp:
  SetVar(1,-1);
  SetVar(2,0);
  while ( SetVar(0,Contents(SetVar(1,Sum(Var(1),+1)))) ) {
    if(BitAnd(GetOCF(Var(0)),OCF_CrewMember())) {
      if(GetAlive(Var(0))) {
        var baseEXP = 500;
        var difficultyBonusEXP = 200*Global(3)+100*Global(3)*Global(3);
        var growthBonusEXP = (200-Global(5))*3;
        var enemyStrengthEXPPercentage = 50+Global(4)/2;
        DoCrewExp((baseEXP + difficultyBonusEXP + growthBonusEXP)*enemyStrengthEXPPercentage/100,Var(0));
        SetAlive(0,Var(0));
        ObjectSetAction(Var(0),"Dead");
        ChangeDef(DUMY,Var(0));
      }
    }
  }
  ChangeDef(DUMY);
return(1);

DispatchCrew:
  // Mannschaft und Sender auswerfen
  SetVar(1,-1); SetVar(2,0);
  while ( SetVar(0,Contents(SetVar(1,Sum(Var(1),+1)))) ) {
    if(BitAnd(GetOCF(Var(0)),OCF_CrewMember())) {
      Var(0)->SetEnabled(1);
      SetCursor(GetOwner(Var(0)),Var(0));
      ActivateEntrance();
      SetCommand(Var(0),"Exit");
      SetVar(2,1);
    }
    if(Equal(GetID(Var(0)),_RDO)) {
      ActivateEntrance();
      SetCommand(Var(0),"Exit");
      SetVar(2,1);
    }
  }
  return(Var(2));
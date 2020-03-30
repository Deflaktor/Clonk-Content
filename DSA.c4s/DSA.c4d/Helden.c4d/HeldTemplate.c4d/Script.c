#strict

protected ControlThrow:
  if ( GetPlrDownDouble(GetOwner()) ) return(0); 
  if ( Control2Contents("ControlThrow") ) return(1);
  return(0);

Timer:
  SetLocal(11,Local(11)+1);
  return(1);

Nahkampf:
  if(SEqual(GetAction(),"Walk"))
    while(SetVar(0,FindObject(0,-16,-15,32,30,OCF_Alive(),0,0,NoContainer(), Var(0))))
      if(GetOwner(Var(0))==-1) 
        return(Fight(Var(0)));
  return(1);

Fight:
  SetAction("Fight",Par(0));
  ObjectSetAction(Par(0),"Fight",this());
  return(1);

VerbessernMenu:
  CreateMenu(GetID(),0,0,3,"Attribute verbessern",GetNumberPointsLeft(),1,0);
  if(GetHP()<200)
    AddMenuItem("HP","Verbessern",_M04,0,GetHP(),0,"Erhöht die Lebensenergie.");
  else
    AddMenuItem("HP (Max)","VerbessernMenu",_M04,0,GetHP(),0,"Erhöht die Lebensenergie.");

  if(GetStr()<200)
    AddMenuItem("Str","Verbessern",_M04,0,GetStr(),1,"Erhöht die Kampfkraft.");
  else
    AddMenuItem("Str (Max)","VerbessernMenu",_M04,0,GetStr(),1,"Erhöht die Kampfkraft.");

  if(GetSpd()<20)
    AddMenuItem("Spd","Verbessern",_M04,0,GetSpd(),2,"Erhöht die Geschwindigkeit.");
  else
    AddMenuItem("Spd (Max)","VerbessernMenu",_M04,0,GetSpd(),2,"Erhöht die Geschwindigkeit.");

  if(GetID()!=KR3A&&GetID()!=KRRA) {
    if(GetInt()<200)
      AddMenuItem("Int","Verbessern",_M04,0,GetInt(),3,"Erhöht die Magiepunkte.");
    else
      AddMenuItem("Int (Max)","VerbessernMenu",_M04,0,GetInt(),3,"Erhöht die Magiepunkte.");
  }
  SelectMenuItem(Par(1));
  return(1);

GetHP:
  return(GetPhysical("Walk",1) % 500);
AddHP:
  return(SetPhysical("Walk",GetPhysical("Walk",1)+1,1));
GetStr:
  return(GetPhysical("Jump",1) % 500);
AddStr:
  return(SetPhysical("Jump",GetPhysical("Jump",1)+1,1));
GetSpd:
  return(GetPhysical("Dig",1) % 500);
AddSpd:
  return(SetPhysical("Dig",GetPhysical("Dig",1)+1,1));
GetInt:
  return(GetPhysical("Throw",1) % 500);
AddInt:
  return(SetPhysical("Throw",GetPhysical("Throw",1)+1,1));

Verbessern:
  if(Par(2))
    return(VerbessernMenu(0,Par(1)));
  if(GetNumberPointsLeft()==0)
    return(VerbessernMenu(0,Par(1)));
  SetPhysical("Push",GetPhysical("Push",1)+1,1);
  if(Par(1)==0)
    AddHP();
  if(Par(1)==1)
    AddStr();
  if(Par(1)==2)
    AddSpd();
  if(Par(1)==3)
    AddInt();
  Redefine();
  VerbessernMenu(0,Par(1));
  return(1);  

GetNumberPointsLeft:
  // Am Anfang hat mat 15 Verteilungspunkte
  SetVar(0,15);
  // Ist man Durarug, kriegt man 50 extra Verteilungspunkte
  if(Min(GetRank(),47)==47)
    SetVar(0,Var(0)+15);
  return(Min(GetRank(),47)*5+Var(0)-GetPhysical("Push",1) % 1000);

protected ControlUp:
  if ( Control2Contents("ControlUp") ) return(1);
  return(0);
protected ControlDown:
  if ( Control2Contents("ControlDown") ) return(1);
  return(0);
protected ControlLeftDouble:
  if ( Control2Contents("ControlLeftDouble") ) return(1);
  return(0);
protected ControlRightDouble:
  if ( Control2Contents("ControlRightDouble") ) return(1);
  return(0);
protected ControlDigDouble:
  if ( Control2Contents("ControlDigDouble") ) return(1);
  return(0);
protected ControlDig:
  if ( Control2Contents("ControlDig") ) return(1);
  return(0);

Control2Contents:
  if ( ObjectCall(Contents(),Par(0),this()) ) return(1);
  return(0);

Info:
  if (SEqual(GetAction(),"Push")) return(Message("%s",this(),GetName(GetActionTarget())));
  if (Contents()) Message("%s:, %s",this(),GetName(Contents()),GetDesc(Contents()));
  return(1);

/* ---------Inventar---------*/
GetArrowCount:
  SetVar(1,Sum(ContentsCount(P13A),ContentsCount(P33A),ContentsCount(P53A),ContentsCount(P73A)));
  SetVar(2,Sum(ContentsCount(P23A),ContentsCount(P43A),ContentsCount(P63A),ContentsCount(P83A)));
  return(Sum(Var(1),Var(2)));

GetStuffCount:
  SetVar(0,Sum(ContentsCount(GD3A),ContentsCount(GS3A)));

  SetVar(1,ContentsCount(GL3A));
  if(GreaterThan(Var(1),3)) SetVar(1,3);

  SetVar(2,Sum(ContentsCount(P13A),ContentsCount(P33A),ContentsCount(P53A),ContentsCount(P73A)));
  SetVar(3,Sum(ContentsCount(P23A),ContentsCount(P43A),ContentsCount(P63A),ContentsCount(P83A)));
  SetVar(4,Sum(Var(2),Var(3)));
  if(GreaterThan(Var(4),50)) SetVar(4,50);
  
  SetVar(5,Sum(ContentsCount(WK3A),ContentsCount(AL3A),ContentsCount(EB3A),ContentsCount(KI3A)));
  if(GreaterThan(Var(5),10)) SetVar(5,10);
  return(Sum(Var(0),Var(1),Var(4),Var(5)));

GetKruetliCount:
  SetVar(1,Sum(ContentsCount(WK3A),ContentsCount(AL3A),ContentsCount(EB3A),ContentsCount(KI3A)));
  return(Var(1));

GetRolleCount:
  SetVar(1,Sum(ContentsCount(_SFE),ContentsCount(_SFM),ContentsCount(_SFG),ContentsCount(_SFS)));
  return(Var(1));

protected RejectCollect:
 // Wenn weniger als 6 Objekte getragen werden, alles aufnehmen
   if (LessThan(Sub(ContentsCount(),GetStuffCount()) ,6)) return(0);
 //Maximal 50 Pfeile
   if(Equal(Par(0),P13A))  if(LessThan(GetArrowCount(),50))  return(0);
   if(Equal(Par(0),P23A))  if(LessThan(GetArrowCount(),50))  return(0);
   if(Equal(Par(0),P33A))  if(LessThan(GetArrowCount(),50))  return(0);
   if(Equal(Par(0),P43A))  if(LessThan(GetArrowCount(),50))  return(0);
   if(Equal(Par(0),P53A))  if(LessThan(GetArrowCount(),50))  return(0);
   if(Equal(Par(0),P63A))  if(LessThan(GetArrowCount(),50))  return(0);
   if(Equal(Par(0),P73A))  if(LessThan(GetArrowCount(),50))  return(0);
   if(Equal(Par(0),P83A))  if(LessThan(GetArrowCount(),50))  return(0);
   if(Equal(Par(0),P93A))  if(LessThan(GetArrowCount(),50))  return(0);
 //Unbegrenzt Geld
   if(Equal(Par(0),GD3A))  return(0);
   if(Equal(Par(0),GS3A))  return(0);
 //Maximal 10 Kräuter
   if(Equal(Par(0),WK3A))  if(LessThan(GetKruetliCount(),10))  return(0);
   if(Equal(Par(0),EB3A))  if(LessThan(GetKruetliCount(),10))  return(0);
   if(Equal(Par(0),AL3A))  if(LessThan(GetKruetliCount(),10))  return(0);
   if(Equal(Par(0),KI3A))  if(LessThan(GetKruetliCount(),10))  return(0);
 //Höchstens 3 Glasflaschen
   if(Equal(Par(0),GL3A))  if(LessThan(ContentsCount(GL3A),3))  return(0);
 //Höchstens 4 Schriftrollen
   if(Equal(Par(0),_SFE))  if(LessThan(GetRolleCount(),4))  return(0);
   if(Equal(Par(0),_SFM))  if(LessThan(GetRolleCount(),4))  return(0);
   if(Equal(Par(0),_SFS))  if(LessThan(GetRolleCount(),4))  return(0);
   if(Equal(Par(0),_SFG))  if(LessThan(GetRolleCount(),4))  return(0);
   return (1);

IchLebeHierInFrieden:
  SetLocal(7,0);
  return(1);

/* Während des Kämpfens */
Fighting:
   SetLocal(7,1);

   if (FindContents(EX3A)&&(GetID()==KR3A||GetID()==KRRA)) {
     SetLocal(8,8);
     SetLocal(9,FindContents(EX3A));
     return(SetAction("ExcaliburFight",Par(0)));
   }
   if (FindContents(SWOR)&&(GetID()==KR3A||GetID()==KRRA)) {
     SetLocal(8,7);
     SetLocal(9,FindContents(SWOR));
     return(SetAction("SwordFight",Par(0)));
   }
   if (FindContents(AXE1)&&(GetID()==KR3A||GetID()==KRRA)) {
     SetLocal(8,6);
     SetLocal(9,FindContents(AXE1));
     return(SetAction("AxeFight",Par(0)));
   }
   if (FindContents(SK3A)&&(GetID()==KR3A||GetID()==KRRA)) {
     SetLocal(8,5);
     SetLocal(9,FindContents(SK3A));
     return(SetAction("StreitkolbenFight",Par(0)));
   }
   if (FindContents(RA3A)&&GetID()!=MA3A) {
     SetLocal(8,4);
     SetLocal(9,FindContents(SK3A));
     return(SetAction("RapierFight",Par(0)));
   }
   if (FindContents(ZS3A)&&GetID()==MA3A) {
     SetLocal(8,3);
     SetLocal(9,FindContents(ZS3A));
     return(SetAction("ZauberstabFight",Par(0)));
   }
   if (FindContents(MT3A)&&GetID()==MA3A) {
     SetLocal(8,2);
     SetLocal(9,FindContents(MT3A));
     return(SetAction("MagierflorettFight",Par(0)));
   }
   if (FindContents(KP3A)) {
     SetLocal(8,1);
     SetLocal(9,FindContents(KP3A));
     return(SetAction("KampfstabFight",Par(0)));
   }

  SetLocal(8,0);
  return(1);  

/*----Trefferchancen-------*/

protected ControlLeft:
  if ( Control2Contents("ControlLeft") ) return(1);
  if (GetDir()!=DIR_Left())
    return(0);
  Attack();
  return(0);

protected ControlRight:
  if ( Control2Contents("ControlRight") ) return(1);
  if (GetDir()!=DIR_Right())
    return(0);
  Attack();
  return(0);

Attack:
  if(!SEqual(GetActMapVal("Procedure",GetAction()),"FIGHT"))
    return(0);
  // Verhindere, dass man einfach auf dem Knopf bleibt
  // Button-Bashing ist angesagt :)
  if (Local(11)<5) {
    SetLocal(11,0);
    return(0);
  }
  SetLocal(11,0);

  SetVar(0,ObjectCall(Local(9),"Speed"));
  if(Local(8)==0)
    SetVar(0,5);

  SetLocal(10,Local(10)+1);
  if ( Local(10) < Var(0) ) {
    return(0);
  }
  if(SEqual(GetAction(),"Magierflorett")) MagierflorettHit();
  if(SEqual(GetAction(),"Zauberstab")) ZauberstabHit();
  if(SEqual(GetAction(),"ExcaliburFight")) ExcaliburHit();
  if(SEqual(GetAction(),"SwordFight")) SwordHit();
  if(SEqual(GetAction(),"StreitkolbenFight")) StreitkolbenHit();
  if(SEqual(GetAction(),"AxeFight")) AxeHit();
  if(SEqual(GetAction(),"RapierFight")) RapierHit();
  if(SEqual(GetAction(),"KampfstabFight")) KampfstabHit();
  if(SEqual(GetAction(),"DolchFight")) DolchHit();
  if(SEqual(GetAction(),"Fight")) SetAction("Punch");
  return(1);

MagierflorettHit:
  return(SetAction("MagierflorettThrust"));
ZauberstabHit:
  if (Random(2)) return(SetAction("ZauberstabStrikeoben"));
  return(SetAction("ZauberstabStrikeunten"));
ExcaliburHit:
  if(Local(15)) return(SetAction("ExcaliburVernichtung"));
  return(SetAction("ExcaliburStrike"));
SwordHit:
  if(Local(15)) return(SetAction("SwordVernichtung"));
  if (Random(2)) return(SetAction("SwordStrike"));
  return(SetAction("SwordThrust"));
StreitkolbenHit:
  if(Local(15)) return(SetAction("StreitkolbenVernichtung"));
  return(SetAction("StreitkolbenStrike"));
AxeHit:
  if(Local(15)) return(SetAction("AxeVernichtung"));
  return(SetAction("AxeStrike"));
RapierHit:
  if(Local(15)) return(SetAction("RapierVernichtung"));
  return(SetAction("RapierThrust"));
KampfstabHit:
  if(Local(15)) return(SetAction("KampfstabVernichtung"));
  if (Random(2)) return(SetAction("KampfstabStrikeoben"));
  return(SetAction("KampfstabStrikeunten"));
DolchHit:
  return(SetAction("DolchThrust"));

/*-----Schaden------*/
Strike:
  //if(Random(2)) {
    if(Local(8)==1||Local(8)==3) Sound("StaffHit");
    if(Local(8)==2||Local(8)==4||Local(8)==7||Local(8)==8) Sound("SwordHit*");
    if(Local(8)==5||Local(8)==6) Sound("AxeHit*");
  //}
  SetLocal(13,10);
  // Schadensberechnung
  SetVar(0,ObjectCall(Local(9),"Power"));
  SetVar(0,Var(0)*(GetPhysical("Fight",0)/5000+1)+GetPhysical("Fight",0)/5000);
  if(SetVar(2,ObjectCall(GetActionTarget(),"Abwehr")))
  SetVar(0,Var(0)/Var(2));
  SetVar(0,ZusatzSchaden(Var(0)));
  SetLocal(10);
  if(Local(8)==0)
    SetVar(0,1);
  SetVar(1,0);
  if(Random(100)<ObjectCall(Local(9),"CritRate"))
    SetVar(1,1);
  if(Var(1))
    SetVar(0,Var(0)*2);
  if(Var(1)||Local(15)) {
    if(Local(15)) {
      SetVar(0,Var(0)*3);
      Punch(GetActionTarget(),Max(Var(0),1));
      Fling(GetActionTarget(), -5+10*GetDir(), -4);
      SetLocal(15,0);
    } else {
      Punch(GetActionTarget(),Max(Var(0),1));
    }
  } else {
    DoEnergy(-Max(Var(0),1),GetActionTarget());
  }
  ObjectCall(GetActionTarget(),"TakeDamage",Max(Var(0),1));
  return(Max(Var(0),1));

ZusatzSchaden:
  return(Par(0));

Damage:
  TakeDamage(Par(0));
  return(1);

TakeDamage:
  SetLocal(0,Max(Par(0),1),CreateObject(__SA));
  return(1);

/*-----Schild-------*/
HasShield:
  SetVar(0,1);
  if(FindObject(SHIA,0,0,0,0,0,"Shield",Par(0)))
    SetVar(0,Var(0)*2);
  if(FindObject(AR3A,0,0,0,0,0,"Klaaskleber",Par(0)))
    SetVar(0,Var(0)*2);
  return (Var(0));

/*Mit Excalibur Zauber abwehren */
Abwehr:
  if(LessThan(Local(0,Local(1)),30)) SetAction("Walk");
  if(Equal(GetDir(),DIR_Left())) Call("LinkeDefens");
  if(Equal(GetDir(),DIR_Right())) Call("RechteDefens");
  return(1);

LinkeDefens:
  if(SetLocal(7,FindObject(BF3A,-75,-45,75,90))) ObjectCall(Local(1),"Destroy",Local(7));
  if(SetLocal(7,FindObject(FM3A,-75,-45,75,90))) ObjectCall(Local(1),"Destroy",Local(7));
  if(SetLocal(7,FindObject(GV3A,-75,-45,75,90))) ObjectCall(Local(1),"Destroy",Local(7));
  if(SetLocal(7,FindObject(IG3A,-75,-45,75,90))) ObjectCall(Local(1),"Destroy",Local(7));
  if(SetLocal(7,FindObject(BF3A,-75,-45,75,90))) ObjectCall(Local(1),"Destroy",Local(7));
  return(1);
RechteDefens:
  if(SetLocal(7,FindObject(BF3A,0,-45,75,90))) ObjectCall(Local(1),"Destroy",Local(7));
  if(SetLocal(7,FindObject(FM3A,0,-45,75,90))) ObjectCall(Local(1),"Destroy",Local(7));
  if(SetLocal(7,FindObject(GV3A,0,-45,75,90))) ObjectCall(Local(1),"Destroy",Local(7));
  if(SetLocal(7,FindObject(IG3A,0,-45,75,90))) ObjectCall(Local(1),"Destroy",Local(7));
  if(SetLocal(7,FindObject(BF3A,0,-45,75,90))) ObjectCall(Local(1),"Destroy",Local(7));
  return(1);

ExitSpear:
  if (Not(SetVar(6,FindContents(SPER)))) return(0);
  SetVar(0,+1);
  SetVar(1,+150);
  if ( Equal(GetDir(),DIR_Left()) )  SetVar(0,-1);
  if ( Equal(GetDir(),DIR_Left()) )  SetVar(1,+30);
  SetVar(2,Mul(Var(0),10));
  SetVar(3,Mul(Var(0),5));
  SetVar(4,Mul(Var(0),4));
  Exit(Var(6),Var(2),-5,Var(1),Var(3),-2,Var(4));
  return(1);
  
Feed:
  DoEnergy(Par(0));
  Sound("KnightMunch");
	return(1);  
  
Initialize:
  SetAction("Walk");
  SetDir(Random(2));
  SetLocal(5,3);
  SetLocal(4,GetRank());
  return(1);

CatchBlow:
  if (SEqual(GetAction(),"Dead")) return(0);
  if(Not(Random(5))) Call("Hurt");
  return(1);
 
Hurt:
  Sound("Hurt*");
  return(1);
Chop:
  Sound("Chop*");
  return(1);
Build:
  if(Not(Random(2))) Sound("Build*");
  return(1);
Dig:
  Sound("Dig*");
  return(1);
Grab:
  Sound("Grab");
  return(1);
Get:
  Sound("Grab");
  return(1);
Put:
  Sound("Grab");
  return(1);
DeepBreath:
  Sound("Breath");
  return(1);
   
Death:
  Sound("Die");
  DeathAnnounce();
  // Letztes Mannschaftsmitglied tot: neuer Einsatz
  if (Not(GetCrew(GetOwner())))
    GameCall("Relaunch",GetOwner(),this());
  return(1);

Redefine:
  SetAction("Walk");
  ResetPhysical();

  SetPhysical("Energy",GetHP()*5000,2);
  SetPhysical("Fight",GetStr()*5000,2);
  SetVar(0,GetSpd());
  SetPhysical("Breath",10000*Var(0),2);
  SetPhysical("Scale",5000*Var(0),2);
  SetPhysical("Hangle",5000*Var(0),2);
  SetPhysical("Swim",5000*Var(0),2);
  SetPhysical("Dig",3000*Var(0)+10000,2);
  SetPhysical("Walk",1500*Var(0)+60000,2);
  SetPhysical("Magic",GetInt()*1000,2);

  return(1);

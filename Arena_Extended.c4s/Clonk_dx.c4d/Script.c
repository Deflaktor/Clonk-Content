#strict

local godMode, epicMode;

IsEpicMode:
  return(epicMode);

/*-- Clonk DX --*/
IsGodMode:
 return(godMode);

/* Initialisierung */

Initialize:
  ResetPhysical();
  SetPhysical("Energy",90000+GetRank()*1000,2);
  if(FindObject(SRKR))
    SetPhysical("Energy",GetPhysical("Energy",0)*4,2);
  DoEnergy(+2000);
  SetVisibility(VIS_All());
  SetAction("Walk");
  SetDir(Random(2));
  // Anzahl Tragbare Objekte:
  SetLocal(2,5);
  // Hat Schuhe an:
  SetLocal(3,0);
  // Hat Equipment an:
  SetLocal(4,0);
  //SetMagic(100);
  return(1);

Respawn:
  SetCrewEnabled(1);
  SetCategory(1);
  SetCategory(2056);
  SetAction("Walk");
  SetLocal(2,5);
  SetLocal(3,0);
  SetLocal(4,0);
  ResetPhysical();
  SetPhysical("Energy",90000+GetRank()*1000,2);
  if(FindObject(SRKR))
    SetPhysical("Energy",GetPhysical("Energy",0)*4,2);
  DoEnergy(+2000);
  SetVisibility(VIS_All());
  SetDir(Random(2));
  SetXDir(0);
  SetYDir(0);
  SetRDir(0);
  Fling();
  SetPosition(Random(LandscapeWidth()),0);
  SetAlive(1);
  //MakeCrewMember(this(),GetOwner());
  return(1);

Flare:
if (GetPhysical("Walk",0)>95000)
ObjectCall(CreateObject(3QHS,0,10),"SetPicture",GetAction(),GetPhase(),GetDir());
return(1);

/* Magie... (erstmal nur mit DoMagicEnergy) */
SetMagic:
  DoMagicEnergy(Par(0));
  return(1);
/*


/* Aufnahme-Überprüfung */
public RejectCollect:
  // fünf Sachen kann man immer tragen
  if(AnzahlObjekte()<Local(2))
    return(0);
  // Geld immer aufheben aber maximal eins
  if(IstGeld(Par(0)))
    if(AnzahlGeldObjekte()==0)
      return(0);
  // Schatztrue immer aufheben aber maximal eine
  if(Par(0)==CHST)
    if(ContentsCount(CHST)==0)
      return(0);
  return(1);

IstGeld:
  return(Par(0)==ST58||Par(0)==S582||Par(0)==S658);

AnzahlGeldObjekte:
  SetVar(0,ContentsCount(ST58));
  SetVar(0,Var(0)+ContentsCount(S582));
  SetVar(0,Var(0)+ContentsCount(S658));
  return(Var(0));

AnzahlObjekte:
  SetVar(0,ContentsCount(0));
  if(AnzahlGeldObjekte()>0)
    SetVar(0,Var(0)-1);
  if(ContentsCount(CHST)>0)
    SetVar(0,Var(0)-1);
  return(Var(0));

Bluten:
  if(epicMode)
    return(1);
  SetVar(0,Max(Par(0),16));
  CastObjects(BLUT, Var(0)/4, Var(0)/2);
  SetVar(2,Min(GetXDir(),100)/20);
  SetVar(3,Min(GetYDir(),100)/20);
  for(var i = 0;i<Var(0)/4;i++) {
    SetVar(1,CreateContents(BLUT));
    SetOwner(GetOwner(),Var(1));
    Exit(Var(1),-5+Random(10),-5+Random(10),0, (Var(2)-5+Random(10)), (Var(3)-5+Random(10)), 0);
  }
  return(1);

Damaged:
  if(Par(0)<=0) return(0);
  if (SEqual(GetAction(),"Dead")) return(0);
  Bluten(Par(0));
  if (Not(Random(5))) Hurt();
  if( Par(1) == GetOwner() )
    return(0);

  if(GetEnergy()<=Par(0)) {
    if(Local(9)==0) {
      SetLocal(9,1);
      SetWealth(Par(1),GetWealth(Par(1))+5);
      while(SetVar(1,FindObject(SDCL,0,0,0,0,0,0,0,0,Var(1))))
        if(GetOwner(Var(1))==Par(1))
          SetLocal(0,Local(0,Var(1))+1,Var(1));
      if(FindObject(SRKR))
        SetWealth(Par(1),GetWealth(Par(1))+GetWealth()/2);
    }
    Kill();
    return(1);
  }
  DoEnergy(-Par(0));
  return(1);
  
CatchBlow:
  if (SEqual(GetAction(),"Dead")) return(0);
  Bluten(Par(0));
  if (Not(Random(5))) Hurt();
  if( GetOwner(Par(1)) != GetOwner() )
    if(Not(GreaterThan(GetEnergy(),Par(0)))) {
      if(Local(9)==0) {
        SetLocal(9,1);
        while(SetVar(1,FindObject(SDCL,0,0,0,0,0,0,0,0,Var(1))))
          if(GetOwner(Var(1))==GetOwner(Par(1)))
            SetLocal(0,Local(0,Var(1))+1,Var(1));
        if(FindObject(SRKR))
          SetWealth(Par(1),GetWealth(Par(1))+GetWealth()/2);
      }
      Kill();
    } else {
      DoEnergy(Mul(-1,Par(0)));
    }
  return(1);
/*
public Damage:
  if (SEqual(GetAction(),"Dead")) return(0);
  Bluten(Par(0));
  if (Not(Random(5))) Hurt();
  if( Par(1) != GetOwner() )
    if(Not(GreaterThan(GetEnergy(),Par(0)))) {
      if(Local(9)==0) {
        SetLocal(9,1);
        while(SetVar(1,FindObject(SDCL,0,0,0,0,0,0,0,0,Var(1))))
          if(GetOwner(Var(1))==Par(1))
            SetLocal(0,Local(0,Var(1))+1,Var(1));
        if(FindObject(SRKR))
          SetWealth(Par(1),GetWealth(Par(1))+GetWealth()/2);
      }
      Kill();
    } else {
      DoEnergy(Mul(-1,Par(0)));
    }
  return(1);
*/
/* Kaufmenü */

MakeMenu:
  CreateMenu(CHST);
  if(!FindObject(SRKR))
    AddMenuItem("Lebensenergie auffrischen (4)","ReloadLife",_ROE);
  else
    AddMenuItem("Feuer löschen (4)","ReloadLife",_ROE);
  AddMenuItem("Zaubersprüche","Spells",_ROL);
  AddMenuItem("Know How","Know",_ROK);
  if(Var(0)=FindObject(MNTK))
  if(GetWealth(GetOwner())>=Var(0)->GetGodModeCost()&&!godMode&&!Var(0)->GetCurrentGod())
    AddMenuItem(Format("Gott Modus Kaufen (%d)", Var(0)->GetGodModeCost()),"BuyGodMode",MNTK);
  if(godMode)
    AddMenuItem("Gott Modus","GodMode",_ROM);
  return(1);
  
BuyGodMode:
  Var(0)=FindObject(MNTK);
  if(!Var(0))
    return(0);
  Var(0) = Var(0)->GetGodModeCost();
  if(GetWealth(GetOwner())<Var(0)) 
    return(0);
  SetWealth(GetOwner(),GetWealth(GetOwner())-Var(0));
  Sound("Cash");
  godMode=1;
  ObjectCall(FindObject(MNTK),"GodModeActivated", this());
  return(1);

GodMode:
  CreateMenu(CHST,0,0,3,0,GetMagicEnergy(),0,1);
  GameCall("MakeGodMenu",this(),20);
  return(1);

StartEvent:
  if(!DoMagicEnergy(-20))
    return(Sound("Error", 0, this(), 100, GetOwner()+1));
  ObjectCall(FindObject(EVT_),"ResetTimer");
  if(Par(1)==-1)
    GameCall("LandschaftWiederherstellen");
  else
    GameCall(Format("Event%d",Par(1)));
  return(1);

ReloadLife:
  if(LessThan(GetWealth(GetOwner(this())),4)) Message("Du hast nicht genügend Geld!",this());
  if(LessThan(GetWealth(GetOwner(this())),4)) Sound("Error");
  if(LessThan(GetWealth(GetOwner(this())),4)) return(1);
  if(!FindObject(SRKR))
    DoEnergy(2000);
  else if(!OnFire()) {
    Message("Du brennst nicht!",this());
    Sound("Error");
    return(1);
  }
  Sound("Heal");
  Extinguish();
  CastObjects(_PRR,15,20);
  Money(4);
  return(1);

/*ReloadMagic:
    if(LessThan(GetWealth(GetOwner(this())),5)) Message("Du hast nicht genügend Geld!",this());
    if(LessThan(GetWealth(GetOwner(this())),5)) Sound("Error");
    if(LessThan(GetWealth(GetOwner(this())),5)) return(1);
    Sound("Electric");
    SetMagic(100);
    CastObjects(_PRK,5,20);
    Money(5);
    return(1); */

Know:
  CreateMenu(_ROK);
  AddMenuItem("Schleuderbedienung (5)","Schleuder",_SHL);
  AddMenuItem("Pegasus Schuh (5)","CHL",_CG1);
  AddMenuItem("Luftschiff zaubern (10)","Blimp",_BMP);
  AddMenuItem("KamiKaze Etui (5)","Kaze",_SH2);
 // AddMenuItem("Panzer (15)","Panzer",CG10);
 /*if (Not(FindObject(RJTA,0,0,-1,-1)))
  AddMenuItem("Jetpack (25)","Jetpack",_CG2);
 if (FindObject(RJTA,0,0,-1,-1))
  AddMenuItem("Jetpack auffüllen (10)","JetpackF",CG2F);*/
  return(1);

Spells:
  CreateMenu(_ROL);
  AddMenuItem("Himmelfall (5)","Falling",_UPH); 
  if(ContentsCount()+1 <= MaxFlints())
  AddMenuItem("Zufälligen Flint zaubern (2)","RandomFlint",_RFL);
  if(ContentsCount()+2 <= MaxFlints())
  AddMenuItem("Viele Zufällige Flints zaubern (2n)","Flints",_RF2);
  if(ContentsCount()+2 <= MaxFlints())
  AddMenuItem("Zufälligen starken Flint Zaubern (10)","RandomFlint3",RFL3);
  if(ContentsCount()+2 <= MaxFlints())
  AddMenuItem("Viele Zufällige starke Flints Zaubern (10n)","Flints2",RFL4);
  return(1);

Flints:
  CreateMenu(_RF2);
  AddMenuItem("2 Stück (4)","RandomFlint2",_I15,0,0,2);
  if(ContentsCount()+4 <= MaxFlints())
  AddMenuItem("4 Stück (8)","RandomFlint2",_I17,0,0,4);
  if(ContentsCount()+6 <= MaxFlints())
  AddMenuItem("6 Stück (12)","RandomFlint2",_I18,0,0,6);
  if(ContentsCount()+50 <= MaxFlints())
  AddMenuItem("50 Stück (100)","RandomFlint2",_I05,0,0,50);
  if(ContentsCount()+90 <= MaxFlints())
  AddMenuItem("90 Stück (180)","RandomFlint2",_I06,0,0,90);
  return(1);

Flints2:
  CreateMenu(_RF2);
  if(ContentsCount()+2 <= MaxFlints())
  AddMenuItem("2 Stück (20)","RandomFlint4",_I15,0,0,2); 
  if(ContentsCount()+4 <= MaxFlints())
  AddMenuItem("4 Stück (40)","RandomFlint4",_I17,0,0,4);
  if(ContentsCount()+6 <= MaxFlints())
  AddMenuItem("6 Stück (60)","RandomFlint4",_I18,0,0,6);
  if(ContentsCount()+50 <= MaxFlints())
  AddMenuItem("50 Stück (500)","RandomFlint4",_I05,0,0,50);
  return(1);

MaxFlints:
  if(FindObject(RBEG))
    return(181);
  return(2000);

CHL:
  if(LessThan(GetWealth(GetOwner(this())),5)) Message("Du hast nicht genügend Geld!",this());
  if(LessThan(GetWealth(GetOwner(this())),5)) Sound("Error");
  if(LessThan(GetWealth(GetOwner(this())),5)) return(1);
  Sound("Cash");
  CastObjects(_PRG,15,20);
  SetOwner(GetOwner(this()),CreateContents(_POW));
  Money(5);
  return(1); 
  
Jetpack:
  if(LessThan(GetWealth(GetOwner(this())),10)) Message("Du hast nicht genügend Geld!",this());
  if(LessThan(GetWealth(GetOwner(this())),10)) Sound("Error");
  if(LessThan(GetWealth(GetOwner(this())),10)) return(1);
  Sound("Cash");
  CastObjects(_PRG,15,20);
  SetLocal(7,CreateContents(RJET));
  SetOwner(GetOwner(this()),Var(0));
  ObjectCall(Var(0),"Activate");
  Money(10);
  return(1); 

JetpackF:
  if(LessThan(GetWealth(GetOwner(this())),5)) Message("Du hast nicht genügend Geld!",this());
  if(LessThan(GetWealth(GetOwner(this())),5)) Sound("Error");
  if(LessThan(GetWealth(GetOwner(this())),5)) return(1);
  Sound("Cash");
  CastObjects(_PRG,15,20);
  ObjectCall(Local(7),"Fillup");
  Money(5);
  return(1); 

Kaze:
  if(LessThan(GetWealth(GetOwner(this())),5)) Message("Du hast nicht genügend Geld!",this());
  if(LessThan(GetWealth(GetOwner(this())),5)) Sound("Error");
  if(LessThan(GetWealth(GetOwner(this())),5)) return(1);
  Sound("Cash");
  CastObjects(_PRG,15,20);
  Redefine(CLSK);
  Money(5);
  return(1); 

Schleuder:
  if(LessThan(GetWealth(GetOwner(this())),5)) Message("Du hast nicht genügend Geld!",this());
  if(LessThan(GetWealth(GetOwner(this())),5)) Sound("Error");
  if(LessThan(GetWealth(GetOwner(this())),5)) return(1);
  Sound("Cash");
  CastObjects(_PRG,15,20);
  Redefine(CLSH);
  Money(5);
  return(1); 

Falling:
  if(LessThan(GetWealth(GetOwner(this())),5)) Message("Du hast nicht genügend Geld!",this());
  if(LessThan(GetWealth(GetOwner(this())),5)) Sound("Error");
  if(LessThan(GetWealth(GetOwner(this())),5)) return(1);
  Sound("Electric");
  ForcePosition(this(),Random(LandscapeWidth()),0);
  CastObjects(_PRK,15,20);
  Money(5);
  return(1);  

Blimp:
  if(LessThan(GetWealth(GetOwner(this())),10)) Message("Du hast nicht genügend Geld!",this());
  if(LessThan(GetWealth(GetOwner(this())),10))  Sound("Error");
  if(LessThan(GetWealth(GetOwner(this())),10)) return(1);
  Sound("Electric");
  CreateObject(BLMP,0,5,GetOwner());
  CastObjects(_PRK,15,20);
  Money(10);
  return(1); 

Panzer:
  if(LessThan(GetWealth(GetOwner(this())),15)) Message("Du hast nicht genügend Geld!",this());
  if(LessThan(GetWealth(GetOwner(this())),15))  Sound("Error");
  if(LessThan(GetWealth(GetOwner(this())),15)) return(1);
  Sound("Electric");
  CreateObject(PM7K,0,0,GetOwner());
  CastObjects(_PRK,15,20);
  Money(15);
  return(1); 

Zufallsflint:
/*  SetVar(0,Random(21));
  if(Equal(Var(0),0)) return(CreateContents(MARI));
  if(Equal(Var(0),1)) return(CreateContents(WBOB));
  if(Equal(Var(0),2)) return(CreateContents(MBOM));
  if(Equal(Var(0),3)) return(CreateContents(_CGM));
  if(Equal(Var(0),4)) return(CreateContents(FLNT));
  if(Equal(Var(0),5)) return(CreateContents(FF4V));
  if(Equal(Var(0),6)) return(CreateContents(_AUS));
  if(Equal(Var(0),7)) return(CreateContents(JU58));
  if(Equal(Var(0),8)) return(CreateContents(JU59));
  if(Equal(Var(0),9)) return(CreateContents(SBOM));
  if(Equal(Var(0),10)) return(CreateContents(HNTF));
  if(Equal(Var(0),11)) return(CreateContents(MSFL));
  if(Equal(Var(0),12)) return(CreateContents(SFLN));
  if(Equal(Var(0),13)) return(CreateContents(_SFN));
  if(Equal(Var(0),14)) return(CreateContents(J102));
  if(Equal(Var(0),15)) return(CreateContents(TFLN));
  if(Equal(Var(0),16)) return(CreateContents(SHFT));
  if(Equal(Var(0),17)) return(CreateContents(EFLN));
  if(Equal(Var(0),18)) return(CreateContents(_RND));
  if(Equal(Var(0),19)) return(CreateContents(BALL));
  if(Equal(Var(0),20)) return(CreateContents(KREI));*/
return(CreateContents(GameCall("Zufallsflint")));

Zufallsflint2:
/*  SetVar(0,Random(11));
  if(Equal(Var(0),0)) SetOwner(GetOwner(),CreateContents(ATOM));
  if(Equal(Var(0),1)) SetOwner(GetOwner(),CreateContents(SBOM));
  if(Equal(Var(0),2)) SetOwner(GetOwner(),CreateContents(_MFF));
  if(Equal(Var(0),3)) SetOwner(GetOwner(),CreateContents(MSHF));
  if(Equal(Var(0),4)) SetOwner(GetOwner(),CreateContents(P57M));
  if(Equal(Var(0),5)) SetOwner(GetOwner(),CreateContents(SHF2));
  if(Equal(Var(0),6)) SetOwner(GetOwner(),CreateContents(SHF3));
  if(Equal(Var(0),7)) SetOwner(GetOwner(),CreateContents(SLGR));
  if(Equal(Var(0),8)) SetOwner(GetOwner(),CreateContents(QT12));
  if(Equal(Var(0),9)) SetOwner(GetOwner(),CreateContents(ZBOM));
  if(Equal(Var(0),10)) SetOwner(GetOwner(),CreateContents(CHS2));*/
return(CreateContents(GameCall("Zufallsflint2")));

RandomFlint:
  if(LessThan(GetWealth(GetOwner(this())),2)) Message("Du hast nicht genügend Geld!",this());
  if(LessThan(GetWealth(GetOwner(this())),2)) Sound("Error");
  if(LessThan(GetWealth(GetOwner(this())),2)) return(1);
  Sound("Electric");
  Zufallsflint();
  CastObjects(_PRK,15,20);
  Money(2);
  return(1); 

RandomFlint2:
  if(LessThan(GetWealth(GetOwner(this())),Mul(Par(1),2))) Message("Du hast nicht genügend Geld!",this());
  if(LessThan(GetWealth(GetOwner(this())),Mul(Par(1),2))) Sound("Error");
  if(LessThan(GetWealth(GetOwner(this())),Mul(Par(1),2))) return(1);
  Sound("Electric");
  if(!Random(30)) {
    if(Par(1)>9)
      Message(Format("Wie? %d Mal das Gleiche?",Par(1)),this());
    var id = GetID(Zufallsflint());
	for(var i = 1; i<Par(1); i++)
	  CreateContents(id);
  } else {
    for(var i = 0; i<Par(1); i++)
      Zufallsflint();
  }
  CastObjects(_PRK,15,20);
  Money(Mul(Par(1),2));
  return(1); 

RandomFlint4:
  if(LessThan(GetWealth(GetOwner(this())),Mul(Par(1),10))) Message("Du hast nicht genügend Geld!",this());
  if(LessThan(GetWealth(GetOwner(this())),Mul(Par(1),10))) Sound("Error");
  if(LessThan(GetWealth(GetOwner(this())),Mul(Par(1),10))) return(1);
  Sound("Electric");
      for(var i = 0; i<Par(1); i++)
  Zufallsflint2();
  CastObjects(_PRK,15,20);
  Money(Mul(Par(1),10));
  return(1); 

RandomFlint3:
  if(LessThan(GetWealth(GetOwner(this())),10)) Message("Du hast nicht genügend Geld!",this());
  if(LessThan(GetWealth(GetOwner(this())),10)) Sound("Error");
  if(LessThan(GetWealth(GetOwner(this())),10)) return(1);
  Sound("Electric");
  Zufallsflint2();
  CastObjects(_PRK,15,20);
  Money(10);
  return(1); 

//Geld
Money:
  SetWealth(GetOwner(Contained()),Sub(GetWealth(GetOwner(Contained())),Par(0)));
  return(1);

/* Steuerung */

protected ControlLeft:
  // Steuerung an Pferd weiterleiten
  if (IsRiding()) return(ObjectCall(GetActionTarget(),"ControlLeft",this()));
  // Im Sprung drehen
  if(SEqual(GetAction(),"Jump")) SetComDir(COMD_Left());
  if(SEqual(GetAction(),"Jump")) SetDir(DIR_Left());
  // Keine überladene Steuerung
  //if(IsFlying())
   // return(SetComDir(COMD_Left()));
  return(0);

protected ControlRight:
  // Steuerung an Pferd weiterleiten
  if (IsRiding()) return(ObjectCall(GetActionTarget(),"ControlRight",this()));
  // Im Sprung drehen
  if(SEqual(GetAction(),"Jump"))SetComDir(COMD_Right());
  if(SEqual(GetAction(),"Jump"))SetDir(DIR_Right());
  // Keine überladene Steuerung
  if(IsFlying())
    SetComDir(COMD_Right());
  return(0);

protected ControlUpDouble:
  if(Not(SEqual(GetAction(this()),"Zielen"))) if(Not(SEqual(GetAction(this()),"Tumble"))) if(Not(SEqual(GetAction(this()),"Push"))) if(SetVar(0,FindContents(CG1K))) ObjectCall(Var(0),"Activate",this());
  return(1);

protected ControlUp:
  //Fliegen :::: Jetzt mit Climbinghooklauncher
//  if(Equal(GetDir(),DIR_Left())) if(Not(SEqual(GetAction(this()),"Tumble"))) if(GreaterThan(GetMagicEnergy(),1)) if(SEqual(GetAction(this()),"Jump")) MagicJumpLeft();
//  if(Equal(GetDir(),DIR_Right())) if(Not(SEqual(GetAction(this()),"Tumble"))) if(GreaterThan(GetMagicEnergy(),1)) if(SEqual(GetAction(this()),"Jump")) MagicJumpRight();
  // Steuerung an Pferd weiterleiten
  if (IsRiding()) return(ObjectCall(GetActionTarget(),"ControlUp",this()));
  // Keine überladene Steuerung
  if(IsFlying())
    SetComDir(COMD_Up());
  return(0);

protected ControlDownSingle:
  // Steuerung an Pferd weiterleiten
  if (IsRiding()) return(ObjectCall(GetActionTarget(),"ControlDownSingle",this()));
  // Keine überladene Steuerung
  if(IsFlying())
    SetComDir(COMD_Down());
  return(0);

protected ControlDownDouble:
  // Steuerung an Pferd weiterleiten
  if (IsRiding()) return(ObjectCall(GetActionTarget(),"ControlDownDouble",this()));
  if(IsFlying())
    ContactBottom();
  return(0);

protected ControlThrow:
  // Reiten und Werfen
  if (IsRiding())
    if (Contents(0))
      return(SetAction("RideThrow"));
  if ( GetPlrDownDouble(GetOwner()) ) return(0);
  if(Contents()) if(SEqual(GetAction(this()),"Walk")) ObjectCall(Contents(0),"Check", this());
  return(0);
  
//ControlSpecial2:
//  if (Contents()) Message("%s: %s",this(),GetName(Contents()),GetDesc(Contents()));
//  return(1);

protected ControlCommand:
  // Kommando MoveTo an Pferd weiterleiten
  if (SEqual(Par(0),"MoveTo"))
    if (IsRiding())
      return(ObjectCall(GetActionTarget(),"ControlCommand",Par(0),Par(1),Par(2),Par(3)));
  // Anderes Kommando beim Reiten: absteigen
  if (IsRiding())
    And( SetComDir(COMD_Stop(),GetActionTarget()),
         ObjectCall(GetActionTarget(),"ControlDownDouble",this()) );
  // Kein überladenes Kommando
  return(0);

Fly:
  if(Not(GetMagicEnergy()))
      SetAction("Jump");
  DoMagicEnergy(-1);
  return(1);

/* Landung */
ContactBottom:
  if(IsFlying())
    SetAction("Walk");
  return(1);
ContactLeft:
  if(IsFlying())
    SetAction("Scale");
  return(1);
ContactRight:
  if(IsFlying())
    SetAction("Scale");
  return(1);

IsFlying:
  return(GetAction()=="Flight");

//protected Activate:
//  return(1);

Splitter:
  if(Equal(GetDir(),DIR_Left())) SplitterLeft();
  if(Equal(GetDir(),DIR_Right())) SplitterRight();
  return(1);

SplitterLeft:
 Exit(CreateContents(SP58),-12,-1,0,-30,3,0);
 Exit(CreateContents(SP58),-12,-1,0,-30,2,0);
 Exit(CreateContents(SP58),-12,-1,0,-30,2,0);
 Exit(CreateContents(SP58),-12,-1,0,-30,1,0);
 Exit(CreateContents(SP58),-12,-1,0,-30,0,0);
 Exit(CreateContents(SP58),-12,-1,0,-30,0,0);
 Exit(CreateContents(SP58),-12,-1,0,-30,-1,0);
 Exit(CreateContents(SP58),-12,-1,0,-30,-2,0);
 Exit(CreateContents(SP58),-12,-1,0,-30,-2,0);
 Exit(CreateContents(SP58),-12,-1,0,-30,-3,0);
 return(1);

SplitterRight:
 Exit(CreateContents(SP58),+12,-1,0,+30,3,0);
 Exit(CreateContents(SP58),+12,-1,0,+30,2,0);
 Exit(CreateContents(SP58),+12,-1,0,+30,2,0);
 Exit(CreateContents(SP58),+12,-1,0,+30,1,0);
 Exit(CreateContents(SP58),+12,-1,0,+30,0,0);
 Exit(CreateContents(SP58),+12,-1,0,+30,0,0);
 Exit(CreateContents(SP58),+12,-1,0,+30,-1,0);
 Exit(CreateContents(SP58),+12,-1,0,+30,-2,0);
 Exit(CreateContents(SP58),+12,-1,0,+30,-2,0);
 Exit(CreateContents(SP58),+12,-1,0,+30,-3,0);
 return(1);

/* Verwandlung */

public Redefine:
  ChangeDef(Par(0));
  SetAction("Walk");
  return(1);

/* Essen (wird vom Lebensmittel aufgerufen) */  
public Feed:
  DoEnergy(Par(0));
  Sound("ClonkMunch");
    return(1);  

/* Aktionen */

private Riding:
  // Richtung an die des Pferdes anpassen
  SetDir(GetDir(GetActionTarget()));
  // Pferd steht still: Clonk soll auch still sitzen
  if (SetVar(0,ObjectCall(GetActionTarget(),"IsStill")))
    if (Not(SEqual(GetAction(),"RideStill")))
      SetAction("RideStill");
  // Pferd steht nicht still: Clonk soll auch nicht still sitzen
  if (Not(Var(0)))
    if (Not(SEqual(GetAction(),"Ride")))
      SetAction("Ride");
  return(1);


private Throwing:
  // Erstes Inhaltsobjekt werfen
  SetVar(0,Contents(0));
  // X-Austritt
  SetVar(1,0); if (Not(GetDir())) SetVar(1,Mul(Var(1),-1));
  // Y-Austritt
  SetVar(2,-10);
  // R-Austritt
  SetVar(3,Random(360));
  // XDir (plus XDir des ActionTarget)
  SetVar(4,Div(GetPhysical("Throw"),25000)); if (Not(GetDir())) SetVar(4,Mul(Var(4),-1));
  if (GetActionTarget()) SetVar(4,Sum(Var(4),Div(GetXDir(GetActionTarget()),10)));
  // YDir (plus YDir des ActionTarget)
  SetVar(5,Div(GetPhysical("Throw"),25000)); SetVar(5,Mul(Var(5),-1));
  if (GetActionTarget()) SetVar(5,Sum(Var(5),Div(GetYDir(GetActionTarget()),10)));
  // RDir
  SetVar(6,Sum(-20,Random(40)));
  // Objekt auswerfen
  Exit(Var(0),Var(1),Var(2),Var(3),Var(4),Var(5),Var(6));
  // Fertig
  return(1);  

private Fighting:
  if (Not(Random(2))) SetAction("Punch");
  return(1);

private Punching:
  if (Not(Random(3))) Sound("Kime*");
  if (Not(Random(5))) Sound("Punch*");
  if (Not(Random(2))) return(1);
  Punch(GetActionTarget());
  return(1);
  
private Chopping:
  Sound("Chop*");
  CastObjects(SDST,Random(4),5,Sum(-8,Mul(16,GetDir())),+1);
  return(1);
  
private Building:
  if (Not(Random(2))) Sound("Build*");
  return(1);

private Digging:
  Sound("Dig*");
  return(1);

SetEpicMode:
  epicMode = 1;
  SetAlive(0);
  DoEnergy(-10000);
  return(1);
  
Checking:
  // Exp
  if(epicMode) {
    CastObjects(SPRK, 2, 20);
    //CastParticles("PSpark", 2, 20, AbsX(GetX()-5+Random(10)), AbsY(GetY()-10+Random(20)), 20*10, 25*10, RGBa(196, 196, 0, 170), RGBa(255, 255, 127, 170));
    CastParticles("Fire", 2, 20, AbsX(GetX()-5+Random(10)), AbsY(GetY()-10+Random(20)), 30*10, 35*10, RGBa(196, 196, 0, 200), RGBa(255, 255, 127, 200));
    SetVar(2,Random(360));
    var xoff = Sin(Var(2),15);
    var yoff = Cos(Var(2),15);
    if(!Random(10))
      LaunchLightning(GetX()+xoff,GetY()+yoff,xoff,15,yoff,15);
    // Brenn alles in der Nähe nieder
    /*while(Var(0)=FindObject(0,-20,-20,40,40,OCF_Inflammable()|OCF_Collectible(),0,0,NoContainer(), Var(0)))
      if(GetOwner()!=GetOwner(Var(0)))
        Incinerate(Var(0));*/
    Extinguish();
    // Springt nach oben? -> Graben
    if(GetYDir()<0&&GetAction() S= "Jump")
      DigFree (GetX(),GetY()-10,20);
    // Schleuder ihn nicht mehr weit weg
    if(GetYDir()<-100)
      SetYDir(-100);
    // Leuchte
    //SetObjectBlitMode(5);
    //SetClrModulation(RGB(0, 255, 255));
    Var(0)=FindObjectOwner(CHST, GetOwner());
    if(!Var(0)) {
      CreateContents(CHST);
    } else if(Contained(Var(0))!=this()) {
      Enter(this(), Var(0));
    }
    if(!GetCursor(GetOwner())) {
      SetAlive(1);
      SetCursor(GetOwner(), this());
      SetAlive(0);
    }
    DoMagicEnergy(+1);
  }
  if(godMode) {
    CastParticles("PSpark", 2, 20, AbsX(GetX()-5+Random(10)), AbsY(GetY()-10+Random(20)), 10*10, 15*10, RGBa(196, 196, 0, 140), RGBa(255, 255, 127, 140));
    godMode++;
    if(godMode>10) {
      godMode=1;
      DoMagicEnergy(+1);
    }
  }
  if(FindObject(SRKR)) {
    if(Local(6)<0) {
      SetLocal(6,5);
      DoEnergy(1);
    }
    Local(6)--;
  }
  Flare();
//  if(Equal(GetComDir(this()),COMD_Stop())) if(SEqual(GetAction(this()),"Walk")) if(Not(Random(2))) SetMagic(+1);
  return(1);

/* Ereignisse */
  
protected Hurt:
  Sound("Hurt*");
  return(1);
  
protected Grab:
  Sound("Grab");
  return(1);

protected Get:
  Sound("Grab");
  return(1);

protected Put:
  Sound("Grab");
  return(1);

Zerfetzen:
  Bluten(100);
  CastObjects(MEAT, 1, 20);
  return(1);

Death:
  ObjectCall(FindObject(MNTK),"GodModeDeactivated", this());
  while(Contained())
    Exit();
  if(FindObject(WEAL))
    SetWealth(GetOwner(),GetWealth(GetOwner())-5);
  if(FindObject(SRKR))
    SetWealth(GetOwner(),GetWealth(GetOwner())/2);
  Sound("Die");
  Zerfetzen();
  var threattype = Random(11);
  if(threattype == 10)
  CreateObject(S582,0,0,GetOwner(this()));
  if(threattype < 10)
  CreateObject(ST58,0,0,GetOwner(this()));
  SetVar(1,Sub(Random(40),20));
  SetVar(2,Sub(Random(41),21));
  while(SetVar(0,FindOtherContents(CHST))) Exit(Var(0),0,0,Random(360),Var(1),Var(2));
  ChangeDef(__DV);
  MakeCrewMember(this(),GetOwner());
  ObjectCall(this(),"Init",GetOwner());
  return(1);

protected DeepBreath:
  Sound("Breath");
  return(1);

/* Zusatzereignisse */

ControlSpecial:
  ShiftContents();
  return(1);
  
ControlSpecial2:
  ShiftContents(0, 1);
  return(1);

MagicJumpLeft:
  SetMagic(-2);
  SetXDir(-20);
  SetYDir(-45);
  return(1);

MagicJumpRight:
  SetMagic(-2);
  SetXDir(20);
  SetYDir(-45);
  return(1);

Destroy:
  // Wenn EpicMode an, dann nicht löschbar durch Remover/Schwarzes Loch
  if(epicMode)
    return(1);
  if(Par(0) != GetOwner())
    SetWealth(Par(0),GetWealth(Par(0))+5);
  if(Par(0) != GetOwner())
    while(SetVar(1,FindObject(SDCL,0,0,0,0,0,0,0,0,Var(1))))
      if(GetOwner(Var(1))==Par(0)) {
        SetLocal(0,Local(0,Var(1))+1,Var(1));
        SetLocal(1,Var(1));
      }
  if(FindObject(WEAL))
    SetWealth(GetOwner(),GetWealth(GetOwner())-5);
  if(FindObject(SRKR))
    SetWealth(GetOwner(),GetWealth(GetOwner())/2);
  ChangeDef(__DV);
  //MakeCrewMember(this(),GetOwner());
  ObjectCall(this(),"Init",GetOwner());
  return(1);

/* Status */

public IsRiding:
  // Reitet der Clonk?
  return(Or(SEqual(GetAction(),"Ride"),SEqual(GetAction(),"RideStill")));    

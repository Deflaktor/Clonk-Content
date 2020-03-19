/*-- Neues Script --*/

#strict
#appendto HZCK
#appendto HCK2
#appendto HCK3
#appendto HCK4

private DoMoney:
  SetWealth(GetOwner (), Sum (GetWealth (GetOwner ()), Par ()));
  return(1);

public func ContextBoss(pCaller)
{
  [Endgegner]
  var obj=CreateObject(HK01,50,0,-1);
  CreateContents(DR1D,obj);
  //for(var i=0;i<10;i++)  
    CreateContents(_MED,obj);
  CreateContents(RWP1,obj);
  CreateContents(_AP7,obj);
  // CreateContents(MINI,obj);
  /*CreateContents(_PP6,obj);
  CreateContents(_PP6,obj);
  CreateContents(_PP6,obj);
  CreateContents(_PP6,obj);*/
  CreateContents(RWP2,obj);
  CreateContents(_LGP,obj);
  CreateContents(_AP0,obj);
  CreateContents(_WP0,obj);
  return(1);
}

/* Taste zum Kaufen von Sachen */

protected ControlSpecial2:
  [Kaufen]
  CreateMenu();
  AddMenuItem("Waffen","WaffenKaufen",_WP1);
  AddMenuItem("Munition","MuntionKaufen",_AP8);
  AddMenuItem("Sonstiges","Sonstiges",_FFG);
  if(Local(6))
    AddMenuItem("Silo einstellen","Silo",INVT);
  if(Local(3)+5<100||Local(4)<50||Local(5)<5||Local(6)<4)
    AddMenuItem("Upgrades","Upgrades",HZCK);
  return(1);

WaffenKaufen:
  return(KaufenMenu("IsWeapon", Par(0)));
  
MuntionKaufen:
  return(KaufenMenu("IsAmmo", Par(0)));

func KaufenMenu(string callFunction, id icon) {
  CreateMenu(icon,0,0,2,0,0,0,1);
  var i, j, idDef;
  var array = CreateObject(WOOD);
  while(idDef = GetDefinition(i++, C4D_Object()))
    if(DefinitionCall(idDef, callFunction))
	  QuicksortAdd(array, j++, idDef);
  Quicksort(array, this(), "Funktionswert");
  i=0;
  while(idDef=QuicksortResult(array, i++))
	AddMenuItem("%s","Kaufen",idDef);
  RemoveObject(array);
}

Funktionswert:
  return(GetValue(0, Par(0)));

Silo:
  CreateMenu(INVT,0,0,4);
  var i, obj;
  while(obj=Contents(i)) {
    if(SiloGesetzt(i)) {
      AddMenuItem("%s","SiloEntfernen",GetID(obj),0,1,i,"Silo entfernen");
	} else {
	  AddMenuItem("%s","SiloSetzen",GetID(obj),0,0,i,"Silo setzen");
	}
	i++;
  }
  var k;
  for(var j=7; j<7+Local(6); j++) {
    if(Local(j))
	  if(Contained(Local(j))!=this())
	    AddMenuItem("%s","SiloEntfernen",GetID(Local(j)),0,1,-j,"Silo entfernen");
  }
  SelectMenuItem(Par(1));
  return(1);

SiloSetzen:
  for(var i=7; i<7+Local(6); i++) {
    if(!Local(i)) {
	  Local(i)=Contents(Par(1));
	  return(Silo(0,Par(1)));
	}
  }
  Sound("Error");
  Message("Mehr Silos werden benötigt.", this());
  return(Silo(0,Par(1)));
  
SiloEntfernen:
  if(Par(1)<0) {
    Local(-Par(1))=0;
	return(Silo(0, 0));
  }
  for(var i=7; i<7+Local(6); i++) {
    if(Local(i)==Contents(Par(1)))
	  Local(i)=0;
  }
  return(Silo(0,Par(1)));
  
SiloGesetzt:
  for(var i=7; i<7+Local(6); i++) {
    if(Local(i)==Contents(Par(0)))
	  return(1);
  }
  return(0);
  
Kaufen:
  if(Zahlen(GetValue(0,Par(0),0,GetOwner())))
    return(CreateContents(Par(0)));
  return(1);
  
Zahlen:
  var iValue = Par(0);
  if(GetWealth(GetOwner())<iValue) {
    Sound("Error");
    return(0);
  }
  DoMoney(-iValue);
  Sound("Cash");
  return(1);
  
Sonstiges:
  CreateMenu(_FFG,0,0,2,0,0,0,1);  
  AddMenuItem("%s","Kaufen",_MED);
  AddMenuItem("%s","Kaufen",_POW);
  AddMenuItem("%s","Kaufen",POW2);
  AddMenuItem("%s","Kaufen",_TLP);
  AddMenuItem("%s","Kaufen",_RDC);
  AddMenuItem("%s","Kaufen",_FFG);
  AddMenuItem("%s","Kaufen",_BMR);
  return(1);

Upgrades:
  CreateMenu(HZCK,0,0,2,0,0,0,0);  
  var kosten = Local(3)*Local(3)/2+5;
  if(Local(3)+5<100)
    AddMenuItem(Format("Gold+%d", Local(3)+1+5),"MehrGold",_GVK,0,0,kosten,"Permanentes Extra Gold pro eingesammeltes Stück",128,0,kosten);
  kosten = 100*Local(17)*Local(17)+200*Local(17)+100;
  if(Local(17)<10)
    AddMenuItem(Format("Gold*%d%%", 100+(1+Local(17))*20),"MehrGold2",_GVK,0,0,kosten,"Permanentes Extra Gold pro eingesammeltes Stück",128,0,kosten);
  kosten = Local(4)*Local(4)+Local(4)+5;
  if(Local(4)<50)
    AddMenuItem(Format("Hp+%d", Local(4)+1),"MehrHP",_MED,0,0,kosten,"Permanenter Gesundheits Upgrade",128,0,kosten);
  kosten = 2*(Local(5)+10)*(Local(5)+10)*(Local(5)+10)*(Local(5)+1);
  if(Local(5)<5)
    AddMenuItem(Format("Regeneration+%d", Local(5)+1),"MehrRegen",RG3V,0,0,kosten,"Permanenter Regenerations Upgrade",128,0,kosten);
  kosten = 50*10**Local(6);
  if(Local(6)<4)
    AddMenuItem(Format("%d. Silo kaufen", Local(6)+1),"MehrSilo",INVT,0,0,kosten,"Behalte deine wertvollsten Gegenstände nach dem Tod",128,0,kosten);
  kosten = 500;
  if(!Local(18))
    AddMenuItem("Automatisch Munition nachkaufen","AutoAmmo",_AP8,0,0,kosten,"Kauft automatisch die zuletzt verwendete Munition nach wenn nicht vorhanden",128,0,kosten);
  // floor((5*2^x+20*x^2+300*x)/100)*100-100
  kosten = (5*2*(Local(19)+1) + 20*(Local(19)+1)*(Local(19)+1)+300*(Local(19)+1))/100*100-100;
  if(Local(19)<9)
    AddMenuItem(Format("Nachladezeit-%d%%",(1+Local(19))*10),"FasterShot",_WP8,0,0,kosten,"Senkt die Nachladezeit",128,0,kosten);
  SelectMenuItem(Par(1));
  return(1);

MehrGold:
  if(Zahlen(Par(1)))
    Local(3)++;
  return(Upgrades(0,0));

MehrGold2:
  if(Zahlen(Par(1)))
    Local(17)++;
  return(Upgrades(0,1));

MehrHP:
  if(Zahlen(Par(1))) {
    Local(4)++;
	SetPhysical( "Energy", GetPhysical("Energy")+1*1000, 2 );
    DoEnergy(1);
  }
  return(Upgrades(0,2));
  
MehrRegen:
  if(Zahlen(Par(1)))
    Local(5)++;
  return(Upgrades(0,3));
  
MehrSilo:
  if(Zahlen(Par(1)))
    Local(6)++;
  return(Upgrades(0,4));

AutoAmmo:
  if(Zahlen(Par(1)))
    Local(18)++;
  return(Upgrades(0,5));

NeedAmmoPacket:
  if(!Local(18))
    return(0);
  if(!Par(0))
    return(0);
  return(Kaufen(Par(0)));

FasterShot:
  if(Zahlen(Par(1)))
    Local(19)++;
  return(Upgrades(0,6));
  
ReloadDelay:
  if(Local(19))
    return(Par(0)*(100-Local(19)*10)/100);
  return(Par(0));

/* Landung */
ContactBottom:
  if(Or(SEqual(GetAction(),"ArmedFlight"),SEqual(GetAction(),"Flight")))
    And(SetAction("Walk"),CheckArmed());
  return(_inherited());
ContactLeft:
  if(Or(SEqual(GetAction(),"ArmedFlight"),SEqual(GetAction(),"Flight")))
    And(SetAction("Scale"));
  return(_inherited());
ContactRight:
  if(Or(SEqual(GetAction(),"ArmedFlight"),SEqual(GetAction(),"Flight")))
    And(SetAction("Scale"));
  return(_inherited());

/* Fliegend? */
IsFlying:
 if(Or(SEqual(GetAction(),"ArmedFlight"),SEqual(GetAction(),"Flight")))
  return(1);
 return(0);

/* Bewaffnung prüfen */
private CheckArmed:
  _inherited();
  if (SEqual(GetAction(),"Flight")) if (IsArmed()) return(SetAction("ArmedFlight"));
  if (SEqual(GetAction(),"ArmedFlight")) if (Not(IsArmed())) return(SetAction("Flight"));
  return(1);
  
/* Kann der Clonk aus der aktuellen Aktion feuern? */
public ReadyToFire:
   return(_inherited()||SEqual(GetAction(),"ArmedFlight"));

/* Steuerung Richtung (an Inhalt weitergeben, sonst internen Befehl ausführen) */
protected ControlUp:
  if(_inherited())
    return(1);
  if(IsFlying())
    SetComDir(COMD_Up());
  return(0);
protected ControlUpDouble:
  if(_inherited())
    return(1);
  if(Local(1))
    SetAction("Flight");
  return(0);
protected ControlDown:
  if(_inherited())
    return(1);
  if(IsFlying())
    SetComDir(COMD_Down());
  return(0);
protected ControlDownDouble:
  if(_inherited())
    return(1);
  if(IsFlying())
    ContactBottom();
  return(0);
protected ControlLeft:
  if(_inherited())
    return(1);
  if(IsFlying())
    SetComDir(COMD_Left());
  return(0);
protected ControlRight:
  if(_inherited())
    return(1);
  if(IsFlying())
    SetComDir(COMD_Right());
  return(0);
protected ControlLeftDouble:
  if(_inherited())
    return(1);
  if(IsFlying())
    SetDir(DIR_Left());
  return(0);
protected ControlRightDouble:
  if(_inherited())
    return(1);
  if(IsFlying())
    SetDir(DIR_Right());
  return(0);
  
/* Steuerung Werfen */
protected ControlThrow:
  // Bei vorherigem Doppel-Stop nur Ablegen  
  if ( GetPlrDownDouble(GetOwner()) )
    if(Not(IsFlying()))
     return(0); 
  // Steuerung an Inhalt weitergeben
  if ( Control2Contents("ControlThrow") ) return(1);
  // Sonst internen Throw-Befehl ausführen
  return(0);

Death:
  CreateObject(_GVK);
  return(_inherited());
  
Activity:
  _inherited();
  DoEnergy(+Local(5));
  if(IsFlying()) {
    Local(1)-=10;
	if(!Local(1)) {
      SetAction("Jump");
	  if(Local(2))
        RemoveObject(Local(2));
	} else {
	  if(!Local(2))
	    Local(2)=CreateObject(_LIV);
	  if(Local(1)<=200)
        Message("LOW FUEL|WARNING",this());
	}
  } else {
  	if(Local(2))
      RemoveObject(Local(2));
  }
  return(1);
  
Init:
  _inherited();
  SetPhysical( "Energy", GetPhysical("Energy")+Local(4)*1000, 2 );
  DoEnergy(Local(4));
  for(var i=7; i<7+Local(6); i++) {
    if(Local(i))
	  Enter(this(), Local(i));
  }
  return(1);

/*---- HazardClonk-KI ----*/
// Local(0) Aktuelles Ziel
// Local(1) Aktuelle Waffe
// Local(2) Anzulaufender Waypoint

#strict
#include HZCK

Debug: return(0);

// Nick-Nack

Initialize:
  SetAction("Walk");
  SetDir(Random(2));
  SetEntrance(1);
  SetOwner(-1);
  return(1);

/* TimerCall */
protected Activity:
  // Wenn er nicht mehr lebt, abbrechen
  if(Not(GetAlive())) return(0);

  // WayPoints auf Waffen, die man schon eingesammelt hat, löschen
  while(SetVar(0,FindObject(WP00,0,0,0,0,0,0,this(),0,Var(0))))
    if(ObjectCall(GetActionTarget(0,Var(0)), "IsWeapon")&&FindContents(GetID(GetActionTarget(0,Var(0)))))
      RemoveObject(Var(0));

  // WayPoints auf Waffen, die man nicht mehr kriegen kann, löschen
  while(SetVar(0,FindObject(WP00,0,0,0,0,0,0,this(),0,Var(0))))
    if(ObjectCall(GetActionTarget(0,Var(0)), "IsWeapon")&&!WeaponFree(GetActionTarget(0,Var(0))))
      RemoveObject(Var(0));

  if(Not(Local(2))) SetLocal(2,FindObject(WP00,0,0,0,0,0,"WP1",this()));

  // Je nach Schwierigkeitsgrad abbrechen
  if(Not(Difficulty())) return(0);

  // Bei allen CrewMembers, die sich mit der KI vom Ort
  // überschneiden, überprüfen, ob sie kämpfen, und wenn nicht,
  // nach Zufall Nahmkampf starten
 /* while(SetVar(0,FindObject(0,0,0,16,20,OCF_CrewMember(),0,0,0,Var(0))))
    if(Not(Equal(ID(Var(0)),ID())))
      if(And(Not(IsFighting()),Not(IsFighting(Var(0)))))
        And(SetAction("Fight",Var(0)),ObjectSetAction(Var(0),"Fight",this()));*/

  SetEnemy(); // Gegner bestimmen

  if(Debug()) if(Local(0)) Log("Gegner: %s",GetName(Local(0)));
  if(Debug())  if(Not(Local(0))) Log("Kein Gegner");

  if(Debug())  if(Local(1)) Log("Waffe: %s",GetName(0,ID(Local(1))));
  if(Debug())  if(Not(Local(1))) Log("Waffe: Nahkampf");

  // Waffe anwählen (oder Objekt gleicher ID, da bei ShiftContents() immer einige Objekte
  // gleicher ID übersprungen werden)
  if(Local(1)) Help1();

  CheckArmed(); // Grafik anpassen

  // Wenn er keine Waffe oder keinen Gegner hat, nach einer Waffe suchen
  if(Not(And(Local(0),Local(1)))) Check4Weapons();

  // Wenn er einen Gegner hat, und entweder kein Medipack da ist oder seine Energie größer
  // 10 ist, angreifen
  if(And(Local(0),Not(CheckEnergy()))) AttackEnemy();

  return(WaySearch()); // Wegroutine aufrufen

Help1:
while(Not(Equal(ID(Local(1)),ID(Contents(0))))) ShiftContents();
return(1);

// Hallifax
TeamPlayEnemy:
  SetVar(0,2);
  SetVar(1,1);
  while(And(Var(0),SetVar(IncVar(1),FindObject(HK00,0,0,-1,-1))))
    DecVar(0);
  if(Not(Var(2))) return(0);

  // KI mit wenigsten HitPoints ermitteln
  SetVar(0,LowEnergyEnemy(this(),Var(2)));
  if(Var(3)) SetVar(0,LowEnergyEnemy(this(),Var(2),Var(3)));

  if(Equal(Var(0),this()))
    return(0);
  if(Not(Local(0,Var(0))))
    return(0);
  if(Not(LessThan(ObjectDistance(Var(0),this()),1500)))
    return(0); // Wenn die KI zu weit weg ist, sich erst um den eigenen Gegner kümmern
  return(Local(0,Var(0)));

// Nick-Nack
// Die Gegnerauswahlroutine
SetEnemy:
  if(TeamPlayEnabled())
    if(SetLocal(0,TeamPlayEnemy()))
      return(1); // Wenn Teamplay gefordert ist, Feind durch TeamPlayEnemy() bestimmen lassen

  if(IsFighting()) return(1,SetLocal(0,GetActionTarget())); // Wenn man kämpft, Gegner behalten

  SetVar(0,FindEnemy());
  SetVar(1,FindEnemy(Var(0)));
  SetVar(2,FindEnemy(Var(1))); // die drei nahesten Gegner bestimmen

  if(OnFire())
    return(And(1,SetLocal(0,Var(0)))); // Wenn man brennt, nahesten Gegner angreifen (anzünden)

  // Wenn der naheste Gegner zu weit weg ist, Verschnaufpause
  if(GreaterThan(ObjectDistance(this(),Var(0)),1000))
    return(SetLocal(0,0)); // Gegner zu weit weg

  if(GreaterThan(ObjectDistance(Var(0),Var(1)),200))
    SetVar(1,0); // Gegner zu weit weg
  if(GreaterThan(ObjectDistance(Var(0),Var(2)),200))
    SetVar(2,0); // Gegner zu weit weg

/* Wenn der Clonk eine andere Waffe ausser Raketen- und Granatenwerfen und Flammenwerfer,
  oder gar keine Waffe hat, den Gegner mit der geringsten Energie angreifen*/
  if(Or(
        FindContents(_WP1),
        FindContents(_WP4),
        FindContents(_WP6),
        FindContents(_WP7),
        FindContents(_WP9),
        Not(
            Or(FindContents(_WP2),FindContents(_WP3),FindContents(_WP5))
           )
       )
    )
    return(1,SetLocal(0,LowEnergyEnemy(Var(0),Var(1),Var(2))));

  // Wenn die KI keinen Flammenwerfer hat, den Gegner angreifen, der am entferntesten ist
  if(Not(FindContents(_WP3))) return(1,SetLocal(0,Var(2)));
  
  // Gegner angreifen, der am nahesten ist
  return(1,SetLocal(0,Var(0)));

LowEnergyEnemy: //Par(0) C4Object, Par(1) C4Object, Par(2) C4Object
  // Bei nur einem Übergabeparameter
  if(Not(Par(1))) return(Par(0));

  // Bei nur zwei Übergabeparametern das Objekt, mit der geringsten Energie zurückgeben
  if(Not(Par(2))) if(LessThan(GetEnergy(Par(1)),GetEnergy(Par(0)))) return(Par(1));
  if(Not(Par(2))) return(Par(0));

  // Bei drei Übergabeparametern, ein Objekt, das nicht die geringste Energie hat, aussortieren,
  // und LowEnergyEnemy mit den beiden anderen Parametern aufrufen
  if(GreaterThan(GetEnergy(Par(0)),GetEnergy(Par(1)))) return(LowEnergyEnemy(Par(1),Par(2)));
  if(GreaterThan(GetEnergy(Par(1)),GetEnergy(Par(2)))) return(LowEnergyEnemy(Par(0),Par(2)));
  return(LowEnergyEnemy(Par(0),Par(1)));

// Hallifax
// Die Waffenauswahlroutine
ChooseWeapon:
  if(Not(Local(0))) return();
  if(OnFire()) return(SetLocal(1,0)); // Wenn man brennt, Nahkampf (Gegner anzünden)
  SetVar(0,-1);
  Var(0)=ObjectXDistance(Local(0),this());
  if(Var(0)<100)
    Var(1)=ShortRangeWeapon();
  else if(Var(0)<300)
    Var(1)=MiddleRangeWeapon();
  else 
    Var(1)=LongRangeWeapon();
  var mostValuedWeapon = 0;
  Var(0)=0;
  Var(2)=0;
  while(Var(0)=Contents(Var(2)++)) {
    if(ObjectCall(Var(0), "IsWeapon")==Var(1)||ObjectCall(Var(0), "IsThrowWeapon"))
	  if(ObjectCall(Var(0), "MaxAmmo")==-1||ObjectCall(Var(0), "Ammo")>0)
	    if(!mostValuedWeapon||(mostValuedWeapon&&GetValue(mostValuedWeapon)<GetValue(Var(0))))
		  mostValuedWeapon = Var(0);
  }
  return(SetLocal(1,mostValuedWeapon));

// Nick-Nack
/* Die Routine zum Gefahrausweichen */
private AvoidDanger:
  // Wenn die KI feststeckt, freigraben
  if(Stuck(this())) AddCommand(this(),"Dig",0,GetX(),GetY());

  // Wenn die KI springen kann und ein Geschoss auf sie zu fliegt, springen
  if(ReadyToJump())
    while(SetVar(1,FindObject(0,-100,-10,200,20,0,0,0,0,Var(1))))
      if(GetAction(Var(1))S="Travel")
        if(Not(Equal(GreaterThan(GetXDir(Var(1)),0),GetHeading(Var(1)))))
          Jump();

  // Wenn die KI nach links oder rechts geht, AvoidDanger-Rückgabewert zurückgeben
  if(Or(Equal(SetVar(1,GetComDir()),COMD_Left()),Equal(Var(1),COMD_Right())))
    return(AvoidDangerWalk());

  return(1); // Gefahr überwunden, 1 zurück geben

private AvoidDangerWalk:
  SetVar(0,1);
  // Minen überspringen
  if(FindObject(_AM8,Sub(Mul(GetDir(),20),20),-12,20,24)) Jump();

  // Lava und Säure überspringen
  if(FindObject(0,Sub(Mul(GetDir(),20),20),-10,20,20,OCF_OnFire()))
    return(0,SetCommand(this(),"Jump"));
  if(FindMaterial("DuroLava",Sub(Mul(GetDir(),30),15),20))
    Jump();
  if(FindMaterial("Lava",Sub(Mul(GetDir(),30),15),20))
    Jump();
  if(FindMaterial("Acid",Sub(Mul(GetDir(),30),15),20))
    Jump();
  return(Var(0));

FireWeaponFailed:
return(FireWeapon());

/* Die Angriffsroutine */
private AttackEnemy:
  if(Not(Local(0))) return(0);
  // Wenn der Gegner 40 Punkte mehr Energie hat, flüchten
  /*if(GreaterThan(Sub(GetEnergy(Local(0)),GetEnergy()),40))
    return(GoBack());*/

  if(Not(Random(100))) SaySaying();

  if(Debug()) Log("Keine Flucht");

  // Wenn man einen aktivierten Schildgenerator trägt, ihn abschalten
  if(SetVar(0,FindObject(_FFG,0,0,0,0,0,"Target",0,this())))
    ObjectCall(Var(0),"Activate",this());

  if(Not(GetAlive(Local(0)))) return(SetLocal(0,0));  // Ziel tot

  if(Not(AvoidDanger())) return(1); // Keine Aktion bei Gefahr

  ChooseWeapon();

  if(Not(Local(1)) ) return(CloseCombat());
  if(Equal(ID(Local(1)),_WP3)) return(ThrowFlames());
  if(Or(Equal(ID(Local(1)),_AM8),Equal(ID(Local(1)),_AP8))) return(ThrowMines());
  if(Or(Equal(ID(Local(1)),_AM5),Equal(ID(Local(1)),_AP5))) return(ThrowGrenades());
  if(Equal(ID(Local(1)),_WP2)) return(RocketStrike());
  if(Equal(ID(Local(1)),_WP5)) return(GrenadeStrike());
  return(StraightStrike()); // Standardangriff

ThrowGrenades:
  if(Not(FindContents(_AM5)))
    if(Not(ObjectCall(FindContents(_AP5),"Activate",this())))
      return(0);
  while(Not(Equal(ID(Contents(0)),_AM5))) ShiftContents();
  SetVar(0,Contents(0));
  AppendCommand(this(),"Throw",0,GetX(Local(0)),GetY(Local(0)));
  AppendCommand(this(),"Call",Var(0),0,0,0,0,"Activate");
  return(1);

GrenadeStrike:
  if(Not(FindContents(GetAmmoID(ID(Local(1))),Local(1))))
    if(Not(FindContents(GetAmmoPacketID(ID(Local(1))))))
      return(0);
  if ( LessThan( Abs(Sub(GetX(),GetX(Local(0)))), 30) ) 
    return(GoBack());  // Ziel zu nah: Flüchten
  if(Inside(GetY(Local(0)),Sub(GetY(),10),Sum(GetY(),10)))
    if(ShotFree(GetX(),GetY(),GetX(Local(0)),GetY(Local(0))))
      return(SetAction("AimGrenade"),WhereToAim(Local(0))); //Zielen
  if(Inside(GetY(Local(0)),Sum(GetY(),50),Sum(GetY(),11)))
    if(SEqual(GetAction(),"ArmedJump"))
      return(0);

  // Kein Schuss möglich, geeigneten Punkt für Angriff bestimmen
  if(Not(Difficulty())) return(0);
  return(ApproachTarget(GetX(Local(0)),GetY(Local(0)))); 

// Hallifax
private RocketStrike:
  if(Not(Or(FindContents(GetAmmoID2(ID(Local(1))),Local(1)),FindContents(GetAmmoID(ID(Local(1))),Local(1)))))
    if(Not(Or(
              ObjectCall(FindContents(GetAmmoPacketID(ID(Local(1)))),"Activate",this()),
              ObjectCall(FindContents(GetAmmoPacketID2(ID(Local(1)))),"Activate",this())
           )))
      return(0);
  if ( LessThan( Abs(Sub(GetX(),GetX(Local(0)))), 30) ) 
    return(GoBack());  // Ziel zu nah: Flüchten
  if(Inside(GetY(Local(0)),Sub(GetY(),10),Sum(GetY(),10)))
    if(ShotFree(GetX(),GetY(),GetX(Local(0)),GetY(Local(0))))
      return(SetAction("AimRocket"),WhereToAim(Local(0))); //Zielen
  if(Inside(GetY(Local(0)),Sum(GetY(),50),Sum(GetY(),11)))
    if(SEqual(GetAction(),"ArmedJump"))
      return(0);

  // Kein Schuss möglich, geeigneten Punkt für Angriff bestimmen
  if(Not(Difficulty())) return(0);
  return(ApproachTarget(GetX(Local(0)),GetY(Local(0)))); 

// Nick-Nack
private ThrowMines:
  if(Not(FindContents(_AM8))) if(Not(ObjectCall(FindContents(_AP8),"Activate",this()))) return(0);
  if(Not(Difficulty())) return(0);
  return(AppendCommand(this(),"Throw",FindContents(_AM8),GetX(Local(0)),GetY(Local(0))));

private ThrowFlames:
  if(Not(FindContents(GetAmmoID(ID(Local(1))),Local(1))))
    if(Not(FindContents(GetAmmoPacketID(ID(Local(1))))))
      return(0);
  if(Or(
     And(Equal(GetDir(),DIR_Left()),Equal(GetComDir(),COMD_Right())),
     And(Equal(GetDir(),DIR_Right()),Equal(GetComDir(),COMD_Left()))
     ))
    if(LessThan(Abs(GetYDir()),5))
      if(SEqual(GetAction(),"ArmedJump"))
        return(FireWeapon());
  if ( LessThan( Abs(Sub(GetX(),GetX(Local(0)))), 10) )
    return(FlamesJumpAttack());  // Ziel nah genug: Sprungangriff
  if ( LessThan( Abs(Sub(GetX(),GetX(Local(0)))), 50) )
    return(SetComDir(COMD_Stop()),FireWeapon()); // Ziel immer noch nahe genug, normaler Angriff
  if(LessThan(GetY(),GetY(Local(0)))) if(SEqual(GetAction(),"ArmedJump")) return(0);
  if(LessThan(GetY(),GetY(Local(0))))
    if(ShotFree(GetX(),GetY(),GetX(Local(0)),GetY(Local(0))))
      return(FireWeapon(),SetComDir(COMD_Stop()),SetCommand(this(),"None")); //Alle Befehle löschen
  return(ApproachTarget(GetX(Local(0)),GetY(Local(0))));

FlamesJumpAttack:
  if(GetHeading(Local(0)))    // Wenn der Gegner rechts ist,
    return(FlamesJumpLeft()); // FlamesJumpLeft() aufrufen und Funktion beenden
  if(Not(Difficulty())) return(0);
  SetDir(DIR_Right());     // Sonst nach rechts drehen,
  SetComDir(COMD_Right()); // nach rechts gehen,
  Jump();                  // springen und
  SetDir(DIR_Left());      // nach links drehen
  return(1);               // Simuliert das Rückwärtsspringen

FlamesJumpLeft:
  if(Not(Difficulty())) return(0);
  SetDir(DIR_Left());     // Nach links drehen,
  SetComDir(COMD_Left()); // nach links gehen,
  Jump();                 // springen und
  SetDir(DIR_Right());    // nach rechts drehen
  return(1);              // Simuliert das Rückwärtsspringen

private CloseCombat:
  if ( GreaterThan( Abs(Sub(GetX(),GetX(Local(0)))), 4000) )
    if(Not(PathFree(GetX(),GetY(),GetX(Local(0)),GetY(Local(0)))))
      return(Check4Weapons());
  if(Not(Difficulty())) return(0);
  return(ApproachTarget(GetX(Local(0)),GetY(Local(0))));

private StraightStrike:
  if(Equal(ID(Local(1)),_WP6))
    if(Not(Or(FindContents(_AP6),FindContents(_AM6,Local(1)))))
      if(Not(ObjectCall(FindContents(_PP6),"Activate",this())))
        return(0);
  if(ObjectCall(Local(1), "MaxAmmo")!=-1)
    if(Not(FindContents(GetAmmoID(ID(Local(1))),Local(1))))
      if(Not(FindContents(GetAmmoPacketID(ID(Local(1))))))
        return(0);
  if(ObjectCall(Local(1), "MaxAmmo")==-1)
    if ( GreaterThan( Abs(Sub(GetX(),GetX(Local(0)))), 353) )
      return( ApproachTarget(GetX(Local(0)),GetY(Local(0))));  // Ziel zu weit weg: Hinlaufen
  if ( LessThan( Abs(Sub(GetX(),GetX(Local(0)))), 10) )
    return(ToClose());  // Ziel zu nah: wegspringen
  if(Inside(GetY(Local(0)),Sub(GetY(),10),Sum(GetY(),10)))
    if(ShotFree(GetX(),GetY(),GetX(Local(0)),GetY(Local(0))))
      return(FireWeapon());
  if(Inside(GetY(Local(0)),Sub(GetY(),50),Sub(GetY(),11)))
    if(ShotFree(GetX(),Sub(GetY(),40),GetX(Local(0)),GetY(Local(0))))
      return(JumpAttack());
  if(Inside(GetY(Local(0)),Sum(GetY(),50),Sum(GetY(),11)))
    if(SEqual(GetAction(),"ArmedJump"))
      return(0);
  if(Not(Difficulty())) return(0);
  return(ApproachTarget(GetX(Local(0)),GetY(Local(0)))); // Zum Gegner laufen

private ToClose:
  if(GreaterThan(Sub(GetEnergy(),GetEnergy(Local(0))),10))
    return(AppendCommand(this(),"Attack",Local(0)));
  if(And(IsFighting(),Equal(GetActionTarget(),Local(0))))
    And(SetAction("Walk"),ObjectSetAction(Local(0),"Walk"));
  if(Or(SEqual(GetAction(),"Jump"),Not(ReadyToFire()))) return(0);
  SetComDir(COMD_Right());
  SetDir(DIR_Right());
  if(GetHeading(Local(0))) And(SetComDir(COMD_Left()),SetDir(DIR_Left()));
  AppendCommand(this(),"Jump");

  if(Not(Difficulty())) return(0);
  AppendCommand(this(),"Call",this(),0,0,0,0,"FireWeapon");
  return(1);

private JumpAttack:
  AppendCommand( this(), "Jump", 0,
      Sum(GetX(),Mul(40,Sub(Mul(2,GetHeading(Local(0))),1))),
      Sum(GetY(),40) );

  if(Not(Difficulty())) return(0);
  AppendCommand( this(), "Call", this(), 0,0,0,0, "FireWeapon" );
  return(1);

private ApproachTarget:  // Par(0) X-Koordinate, Par(1) Y-Koordinate
  SetWayPoint(Par(0),Par(1),Local(0));
  return(1);

// Nick-Nack
/* Waffe abfeuern */
public FireWeapon:
  // Ist nicht bewaffnet
  if (Not(IsArmed())) return(0);
  // Kann zur Zeit nicht feuern
  if (Not(ReadyToFire())) return(0);
  // Müsste sich zum Feuern im Sprung umdrehen
  if ( And(Not(Equal(GetHeading(Local(0)),GetDir())),SEqual(GetAction(),"ArmedJump")) )
     return(0);
  // Feuer-Funktion der Waffe aufrufen
  SetDir(GetHeading(Local(0)));
  SetComDir(Sum(Mul(GetHeading(Local(0)),6),2));
  ObjectCall(Local(1),"Fire");
  return(1);

/* Ist der Clonk im Nahkampf? */
IsFighting:
  return(Or(
           SEqual(GetAction(Par(0)),"Fight"),
           SEqual(GetAction(Par(0)),"Punch"),
           SEqual(GetAction(Par(0)),"GetPunched")
          ));

/* Gedeathmatcht */

protected Death:
  Sound("Die");
  Message("Wieder ein Bot weniger...",this());
  SetLocal(0,0); // Die zweite 0 könnte man weglassen, ich weiß, aber so find ichs übersichtlicher
  SetLocal(1,0); // Siehe Kommentar oben
  if (Not(GetCrew(GetOwner())))
    GameCall("RelaunchBot",GetOwner());
  ChangeDef(HD00);
  return(1);



/* Punkteauswertung */

protected Damage:
  if (Not(GetAlive())) return(0);
  // Jeder Treffer auf einen anderen Spieler bringt Punkte
  if (Not(Equal( Par(1), -1 )))
    DoScore( Par(1), Par(0) );
  return(1);

protected Incineration:
  // Anzünden bringt 100 Punkte
  if (Not(Equal( Par(0), -1)))
    DoScore( Par(0), +100 );
  // Meldung
  if (GetPlayerName(Par(0)))
    if (GameCall("HazardLogs"))
      Log("%s fackelt 'nen Bot ab.",GetPlayerName(Par(0)));
  return(1);

public Shrink:
  DoCon(-25);
  Sound("Teleport");
  // Schrumpfen bringt 10 Punkte
  if (Not(Equal( Par(0), -1 )))
    DoScore( Par(0), +10 );
  // Meldung
  if (GetPlayerName(Par(0)))
    if (Not(Equal( Par(0), -1 )))
      if (GameCall("HazardLogs"))
        Log("%s schrumpft 'nen Bot.",GetPlayerName(Par(0))); 
  return(1);  

protected CatchBlow:
  if (SEqual(GetAction(),"Dead")) return(0);
  if (Not(Random(5))) Hurt();
  // Schlagen bringt Punkte
  if (Not(Equal( GetOwner(Par(1)), -1 )))
    DoScore( GetOwner(Par(1)), +2 );
  return(1);

// Clonk-Karl

/* Die Wegsuchroutine */

private WaySearch:
  if(Not(Difficulty())) return(0);
  if(Not(AvoidDanger())) return(NoWay());
  // Schrumpfen bei zu kleinem Gang
  //if(Not(GetWayHeight()))
  //  if(Not(ObjectCall(FindContents(_WP9),"Activate")))
  //    return(NoWay());

  // WayPoints entfernen, wenn er bei einem steht
  // Var[0]: WayPoint am Ort der KI, damit sie diesen löschen kann und zum nächsten WayPoint gehen kann
  if(SetVar(0,FindObject(WP00,-7,-35,14,70,0,"WP1",this() )) )
    RemoveObject(Var(0));
  // Eventuell Medikits holen
  if(CheckEnergy())
  // Weiterer Verlauf hier abbrechen, wenn ein Medikit zu holen ist
    return(1);
  // Munition prüfen
  CheckAmmo();

  // NoWay();
  // Bewegung zum nächstgelegenen WayPoint
  // Var[0]: Anzulaufender WayPoint (WayPoint, zu dem die KI laufen soll)
  // Var[1]: Durchschaltende WayPointAction-Nummer
  while(SetVar(0,FindObject(WP00,0,0,-1,-1,0,Format("WP%d",IncVar(1)),this())))
   if(Not(Or(SEqual(GetCommand(),"MoveTo"),SEqual(GetCommand(),"Follow"))))
    return(AddCommand(this(),"Follow", Var(0),0,0,0,0,0,0,2));
  Var(1)=0;
  // Wartungskanäle benutzen
  while(SetVar(1,FindObject(_MH1,-150,-150,300,300,0,0,0,0,Var(1) )) )
    // Ist der Ausgang des Kanals näher am Zielobjekt als die KI selbst?
    if(LessThan(
                ObjectDistance(Local(0,Var(1)),Var(0) ),
                ObjectDistance(Var(0) )
  ))
      And(
          AddCommand(this(),"Wait",0,0,0,0,50),
          AddCommand(this(),"Enter",Var(1)) );
  // Pipelines benutzen
  if(SEqual(GetAction(),"Swim"))
    while(SetVar(1,FindObject(_PI1,-150,-150,300,300,0,0,0,0,Var(1) )) )
    // Ist der Ausgang des Kanals näher am Zielobjekt als die KI selbst?
    if(LessThan(
                ObjectDistance(Local(0,Var(1)),Var(0) ),
                ObjectDistance(Var(0) )
  ))
        And(
            AddCommand(this(),"Wait",0,0,0,0,50),
            AddCommand(this(),"Enter",Var(1)) );
  // Luken öffnen
  while(SetVar(1,FindObject(_HAC,-100,-100,200,200,0,0,0,0,Var(1) )) )
    if(Not(FindMaterial("DuroLava",GetX(Var(1)),Sum(GetY(Var(1)),100) )))
      if(Not(FindMaterial("Lava",GetX(Var(1)),Sum(GetY(Var(1)),100) )))
        if(Not(FindMaterial("Acid",GetX(Var(1)),Sum(GetY(Var(1)),100) )))
          if(LessThan(GetY(Var(0)),GetY()))
            if(GreaterThan(GetY(Var(1)),GetY() ))
              if(LessThan(
                ObjectDistance(Local(0,Var(1)),Var(0) ),
                ObjectDistance(Var(0) )
                ))
              And(
		  AddCommand(this(),"Grab",Var(1)),
		  ObjectCall(Var(1),"ControlUp")
		  );
  // Hangeln
  if(SEqual(GetAction(),"Hangle"))
    if(GetHeading(Var(0)))
      SetComDir(COMD_Right());
  if(SEqual(GetAction(),"Hangle"))
    if(Not(GetHeading(Var(0))))
      SetComDir(COMD_Left());
  // Klettern
  if(SEqual(GetAction(),"Scale"))
    if(GreaterThan(GetY(Var(0)),GetY()))
      SetComDir(COMD_Up());
  if(SEqual(GetAction(),"Scale"))
   if(LessThan(GetY(Var(0)),GetY()))
     SetComDir(COMD_Down());
  if(Debug()) Log("WaySearch Ende");
  return(1);

//Clonk Nukem
Check4Weapons:
  // Nächstgelegene Waffen.
  // Entfernung ist egal (Weil Waffen UNBEDINGT notwendig sind).
  if(Debug()) Log("Nach Waffen suchen");
  while(SetVar(0,FindObject(0,0,0,-1,-1,0,0,0,0,Var(0))))
    if(ObjectCall(Var(0), "IsWeapon"))
      if(WeaponFree(Var(0)))
        return(PointToWeapon(Var(0)));
  if(Debug()) Log("Keine Waffe gefunden");
  SetVar(0,0);
  while(SetVar(0,FindObject(_SPW,0,0,-1,-1,0,"Set",0,0,Var(0))))
    if(DefinitionCall(Local(0,Var(0)),"IsWeapon"))
      if(SpawnPointFree(Var(0)))
        return(SetWayPoint(GetX(Par(0)),GetY(Par(0)),Par(0)));
  if(Debug()) Log("Kein SpawnPoint gefunden");
  return(0);

// Nick-Nack

PointToWeapon:
  // Wenn schon ein SpawnPoint auf der Waffe liegt, aufhören,
  // sonst WayPoint setzen
  while(SetVar(0,FindObject(WP00,0,0,0,0,0,0,Par(0),0,Var(0))))
    if(Equal(GetActionTarget(1,Var(0)),this()))
      return(0);
  // WayPoint setzen
  return(SetWayPoint(GetX(Par(0)),GetY(Par(0)),Par(0)));

// Gibt 1 zurück, wenn die Waffe/Munition vom Spawnpoint nicht mehr existiert
SpawnPointFree: return(And(1,Local(1,Par(0))));

// Clonk Nukem
WeaponFree:
  if(Debug()) Log("Waffe gefunden: %s",GetName(0,ID(Par(0))));

  // Waffe wird schon getragen
  if(Contained(Par(0))&&( GetOCF(Contained(Par(0))) & OCF_CrewMember() ))
    return(0);
  // KI hat schon so eine Waffe
  if(Not(FindContents(ID(Par(0)))))
      // Okay
      return(1);
  // Kein Erfolg.
  return(0);

// Clonk-Karl


// Den WayPoint und den Command löschen (Die KI wird sie in den meisten Fällen zwar gleich wieder setzten, aber besser wie nix :(

private NoWay:
  SetCommand(this(),"None");
  if(Local(2)) RemoveObject(Local(2));
  return(1);

/* Energie prüfen, Medikit abholen, abhauen */
private CheckEnergy:
  // Wieviel Energie noch?
  if(GreaterThan(GetEnergy(),10))
    return(0);  // Alles i.O.

  // Ist auf dem Weg zu einem Medikit
  while(SetVar(0,FindObject(WP00,0,0,0,0,0,0,this(),0,Var(0))))
    if(GetID(GetActionTarget(0,Var(0)))==_MED)
	  return(0); // Auch in Ordnung
  // Medikit im Inventar?
  if(ObjectCall(FindContents(_MED),"Activate",this()))
    return(0);  // Energie auffrischen: Medikit benutzen

  // Var[0]: Medikit, zu dem die KI laufen soll
  // Medikit suchen
  if(SetVar(0,FindObject(_MED,-400,-200,800,400)))
    return(SetWayPoint(GetX(Var(0)),GetY(Var(0)),Var(0)));  // Waypoint setzten

  // Ansonsten: Weiterkämpfen
  return(0);
	
  // Ansonsten: Abhauen!
  //return(GoBack());

/* Prüfen, ob er noch Munition hat, wenn nicht, holen gehen */
private CheckAmmo:
  // Var[0]: Munition der Waffe
  // Var[1]: Munitionspack der Waffe
  // Var[2]: Zweite Munition der Waffe (Zielsuchrakete beim Raketenwerfer)
  // Var[3]: Zweites Munitionspack der Waffe
  // Var[9]: WayPoint mit Muni als ActionTarget

  // Zuerst: Bei Phaser oder Schallpistole keine Ammo vonnöten
  if(ObjectCall(Local(1), "MaxAmmo")==-1)
    return(0);

  SetVar(0,GetAmmoID(ID(Local(1))));
  SetVar(1,GetAmmoPacketID(ID(Local(1))));

  // AmmoID2 für Raketenwerfer
  SetVar(2,GetAmmoID2(ID(Local(1))));
  SetVar(3,GetAmmoPacketID2(ID(Local(1))));

  // Bei einer MG als ausgewählten Waffe MGCheck aufrufen
  if(Equal(ID(Local(1)),_WP6))
    SetVar(1,MGCheck());

  // Ist schon auf dem Weg zu Muni
  while(SetVar(9,FindObject(WP00,0,0,-1,-1,0,0,Var(1),0,Var(9))))
    if(Equal(GetActionTarget(1,Var(9)),this()))
      return(0);  // Braucht nicht mehr weiter zu suchen
  SetVar(9);
  while(SetVar(9,FindObject(WP00,0,0,-1,-1,0,0,Var(3),0,Var(9))))
    if(Equal(GetActionTarget(1,Var(9)),this()))
      return(0);  // Braucht nicht mehr weiter zu suchen
    
  // Keine Muni mehr da?
  if(And(And(
         Not(FindContents(Var(0),Local(1))),
         Not(FindContents(Var(2),Local(1)))),
     And(Not(FindContents(Var(1))),
         Not(FindContents(Var(3))))
         ))
    return(LookForAmmo(Var(1),Var(3)));

  // Noch Muni vorhanden
  return(0);

/*
  Wenn eine MG vorhanden ist, Munition auspacken und Var(1) in CheckAmmo nicht auf
  GetAmmoPacketID legen, da dies der Munitionsstreifen ist, und nicht der Kasten
*/
MGCheck:
  if(SetVar(0,FindContents(_PP6)))
    ObjectCall(Var(0),"Activate");
  // _PP6 (MG-Muni-Kiste) zurückgeben
  return(_PP6);

/* Munition suchen */

private LookForAmmo:
  // Par[0]: Passende Munition
  // Par[1]: Zweite Munition (Zielsuchraketen beim Raketenwerfer)
  // Var[0]: Die Munition, die es zu holen gilt
  // Var[9]: Hilfsvarable zum kurzen speichern von dem zu holenden Objekt
  if(Not(Par(0)))
    return();
  if(Not(Par(1)))
    if(Or( Not(FindObject(Par(0),0,0,-1,-1)), Not(FindObject(Par(1),0,0,-1,-1)) ))
      return(0);
  // Munition suchen
  while(SetVar(9,FindObject(Par(0),0,0,-1,-1,0,0,0,0,Var(9) )) )
    // Nicht in Lava
    if(Not(FindMaterial("DuroLava",GetX(Var(9)),GetY(Var(9)) )))
    // Nicht im Besitz eines anderen Clonks
      if(Not(ContentsCheck(Var(9))))
        SetVar(0,Var(9));
  // Wenn ein gültiger Par(1)-Wert übergeben wurde (Nicht 0), Zielsuchraketen ODER Mini-Raketen holen (Das, was am nähesten ist)
  if(Par(1))
    SetVar(0,LookForMissiles());
  // Keine Muni gefunden? Scheiße war's!
  if(Not(Var(0)))
    return();
  SetPosition(GetX(Var(0)),GetY(Var(0)),SetVar(2,CreateObject(WP00)));
  ObjectCall(Var(2),"SetOne",Var(0),this());
  return(1);


/* Raketen für den Raketenwerfer suchen */

private LookForMissiles:
  // Var[0]: Mini- oder Zielsuchraketenpack, welches am nähesten ist und gefunden wird
  // Sehr rechenintensiv, da die ganze Karte abgesucht wird (bzw. werden muss)
  while(SetVar(0,FindObject(0,0,0,-1,-1,0,0,0,0,Var(0) )) )
    if(Or(
          Equal(ID(Var(0)),_AP2),
          Equal(ID(Var(0)),_HMP)
          ))
        // Nicht in Lava
        if(Not(FindMaterial("DuroLava",GetX(Var(0)),GetY(Var(0)) )))
          // Nicht in einem Lebewesen enthalten
          if(Not(ContentsCheck(Var(0))))
            // Gefundenes Pack zurückgeben
            return(Var(0));
  // Keine Raketenpacks da (sollte nicht vorkommen)
  return(0);

/* Eine weniger rechenintensive Variante */
private LookForMissiles2:
  // Var[0]: Miniraketenpack, welches am nähesten ist und gefunden wird
  // Var[1]: Zielsuchraketenpack, welches am nähesten ist und gefunden wird
  // Var[2]: Indikator, um anzuzeigen, dass die Suche beendet werden kann
  while(And(Not(Var(2)),Var(0)))
    if(SetVar(0,FindObject(_HMP,0,0,-1,-1,0,0,0,0,Var(0))))
      if(Var(0))
        // Nicht in Lava
        if(Not(FindMaterial("DuroLava",GetX(Var(0)),GetY(Var(0)) )))
          // Nicht in einem Lebewesen enthalten
          if(Not(ContentsCheck(Var(0))))
            SetVar(2,1);
  SetVar(2);
  while(And(Not(Var(2)),Var(1)))
    if(SetVar(1,FindObject(_AP2,0,0,-1,-1,0,0,0,0,Var(1))))
      if(Var(1))
        // Nicht in Lava
        if(Not(FindMaterial("DuroLava",GetX(Var(0)),GetY(Var(0)) )))
          // Nicht in einem Lebewesen enthalten
          if(Not(ContentsCheck(Var(0))))
            SetVar(2,1);
  if(Not(Var(1))) return(Var(0));
  if(GreaterThan(ObjectDistance(this(),Var(1)),ObjectDistance(this(),Var(0)))) return(Var(0));
  return(Var(1));  

ContentsCheck:
  // Überprüft, ob Par[0] sich in einem Lebewesen befindet und gibt 1 zurück, wenn dem so ist
  // Par[0]: Zu prüfendes Objekt
  if(Contained(Par(0)))
    if(BitAnd(GetOCF(Contained(Par(0))),OCF_Living() ))
      return(1);
  // Befindet sich in keinem Lebewesen
  return(0);

/* Flüchten */

private GoBack:
/* Andere Befehle löschen, um nicht wieder zum Gegner zurückzuwollen,
   wenn dort Munition für die Waffe ist. Abhauen ist wichtiger */
  if(SetVar(0,FindContents(_FFG))) ObjectCall(Var(0),"Activate",this());
  SetCommand(this(),"None");
  // Rechts von der KI: Nach links abhauen!
  if(GetHeading(Local(0)))
    return(SetComDir(COMD_Left()));
  // Ansonsten nach rechts verschwinden
  return(SetComDir(COMD_Right()));

/* DANK AN HALLIFAX!!!!!!! Er lieferte mir das Grundgerüst dieser Funktion, die Pathfree-Abfragen. */

GetWayHeight:
  // Klappt noch nicht ganz
  // Var[0]: Richtung 1 für rechts, -1 für links
  // Var[1]: Mittelpunkt (Offset)
  // Var[2]: Oberkante des Clonks (variiert mit aktueller Größe)
  // Var[3]: Y-Vertex 1 (Oberkante, CNAT_Top)
  // Var[4]: Hilfsvariable (Y-Vertex 2, Unterkante, CNAT_Bottom)
  // Var[5]: Objektgröße (Positive Var(3) + Var(4))
  SetVar(0,1);
  if(Equal(GetDir(),DIR_Left()))
    SetVar(0,-1);
  SetVar(3,GetVertex(1,1,0));
  SetVar(4,GetVertex(2,1,0));
  SetVar(5,Sum(Mul(Var(3),-1),Var(4) ));

  //Gang ist 10 Pixel entfernt
  if(Not(PathFree(
      SetVar(1,GetX()),
      SetVar(2,Sub(GetY(),Var(3))),
      Sum(Mul(Var(),10),Var(1)),
      Var(2)
  )))
    if(Not(PathFree(
        Var(1),
        Sub(Var(2),Var(5)),
        Sum(Mul(Var(),10),Var(1)),
        Sub(Var(2),Var(5))
    )))
      return(1);
  SetVar(6,1);
  while(LessThan(SetVar(6,Sum(Var(6),4)),18))
    if(GBackSolid(Mul(Var(0),10),Sub(Var(3),Var(6))))
      return(0);
  // Nicht jedes Pixel abfragen, da ein-Pixel-Gänge auch mit Schrumpfen nicht begehbar sind
  return(1);

/* Hilfsfunktionen */

/* Nick-Nack
   1 SetWayPoint (int iX, int iY, C4Object *pObj)
   Setzt einen Waypoint für this() an den Koordinaten ix/iy auf das Objekt pObj. Gibt immer 1
   zurück. */
SetWayPoint:
  while(SetVar(0,FindObject(WP00,0,0,0,0,0,"WP1",this(),0,Var(0))))
    if(Equal(GetActionTarget(0,Var(0)),Par(2)))
       return(SetPosition(Par(0),Par(1),Var(0)),SetLocal(2,Var(0)));
  SetPosition(Par(0),Par(1),SetVar(1,CreateObject(WP00)));
  ObjectCall(Var(1),"SetOne",Par(2),this());
  return(1);

/* Schuss von Punkt A nach B möglich? */
// Par(0) X des Startpunktes, Par(1) Y des Startpunktes, Par(2) X des Zielpunktes, Par(3) Y des Zielpunktes
private ShotFree:
  if ( Not( PathFree(Par(0),Par(1),Par(2),Par(3)) ) )  return(0); // Hindernis im Schussfeld
 // if ( FriendBetween(Par(2)) ) return(0);  // andere KI im Schussfeld
  return(1);

/* Überprüft, ob eine andere KI zwischen this() und dem X-Punkt Par(0) ist. Als Y wird das Y
   dieser KI angenommen. Das Suchrechteck ist so breit wie der X-Abstand zwischen KI und Ziel,
   und 30 hoch. Gibt 1 oder 0 zurück.
*/
private FriendBetween:  //X-Koordinate des Zielpunkts
  if(Not(TeamPlayEnabled())) return(0);
  if(LessThan( Par(0), Par(1)))
    if(FindObject( ID(), 0, -15, Sub(GetX(),Par(0)), 30,0,0,0, NoContainer()))
      return(1);  // Ziel ist rechts von der KI
  if(FindObject( ID(), Sub(GetX(),Par(0)), -5, Sub(Par(0),GetX()), 30,0,0,0, NoContainer()))
    return(1); // Ziel ist links von der KI
  return(0);  

// Kurzschreibweise für GetID()
public ID: // C4Object *pObj
  return(GetID(Par(0)));

// Gibt zufällig einen Spruch wieder
SaySaying:
  SetVar(0,Random(10));
  if(Equal(Var(0),0)) Message("Mal sehen, wie lange du überlebst!",this());
  if(Equal(Var(0),1)) Message("%s, du bist zu erst dran!",this(),GetPlayerName(0));
  if(Equal(Var(0),2)) Message("Wenn das kein Fest wird...",this());
  if(Equal(Var(0),3)) Message("Tja, DU hast keine Zeit, solche Sprüche ab zu lassen, %s!",this(),GetPlayerName(0));
  if(Equal(Var(0),4)) if(GetPlayerName(1)) Message("Also an deiner Stelle, %s, würde ich sofort aufgeben!",this(),GetPlayerName(1));
  if(Equal(Var(0),5)) if(GetPlayerName(2)) Message("Da kann ja selbst meine Oma besser kämpfen, %s!",this(),GetPlayerName(2));
  if(Equal(Var(0),6)) Message("Hübsche Waffe, nehm' ich mir!",this());
  if(Equal(Var(0),7)) Message("Lange niemand mehr getötet!",this());
  if(Equal(Var(0),8)) Message("Hey, sag' bloss nicht, ich wäre schlecht, weil ich ein Bot bin!",this());
  if(Equal(Var(0),9)) Message("Also, wenn du mich fragst,|du bist schon so gut wie tot!",this());
  return(1);

// Die Ammo-IDs aller Waffen
GetAmmoID:
  if(Equal(Par(0),_WP2)) return(_AM2);
  if(Equal(Par(0),_WP3)) return(_AM3);
  if(Equal(Par(0),_WP5)) return(_AM5);
  if(Equal(Par(0),_WP6)) return(_AM6);
  if(Equal(Par(0),_WP7)) return(_AM7);
  if(Equal(Par(0),_WP9)) return(_AM9);
  return(0);

GetAmmoPacketID:
  if(Equal(Par(0),_WP2)) return(_AP2);
  if(Equal(Par(0),_WP3)) return(_AP3);
  if(Equal(Par(0),_WP5)) return(_AP5);
  if(Equal(Par(0),_WP6)) return(_AP6);
  if(Equal(Par(0),_WP7)) return(_AP7);
  if(Equal(Par(0),_WP9)) return(_AP9);
  return(0);

GetAmmoID2:
  if(Equal(Par(0),_WP2)) return(_HMS);
  return(0);

GetAmmoPacketID2:
  if(Equal(Par(0),_WP2)) return(_HMP);
  return(0);

// Gibt 1 zurück, wenn pObj1 rechts von pObj2 ist, sonst 0.
private GetHeading:  // C4Object *pObj1, C4Object *pObj2
  return(GreaterThan(GetX(Par(0)),GetX(Par(1))));

// Sucht den nächststehenden Gegner
private FindEnemy: // C4Object *NextObj
  SetVar(0,Par(0));
  while(SetVar(0,FindObject(0,0,0,-1,-1,OCF_CrewMember(),0,0,0,Var(0))))
    if( Or(Not(TeamPlayEnabled()),Not(Equal( ID(Var(0)), ID(this()) )) ))
      if(GetAlive(Var(0)))
        return(Var(0));
  return(0);

// Gibt 1 zurück, wenn die KI aus der aktuellen Aktion springen kann,
// also wenn sie gerade läuft
ReadyToJump:
  return(Or(SEqual(GetAction(),"Walk"),SEqual(GetAction(),"ArmedWalk")));

// Gibt 1 oder 0 zurück, je nach Zufall: Je größer der Schwierigkeitsgrad, desto seltener 0
Difficulty:
  SetVar(0,10);
  if(LessThan(Var(0),5)) return(0);
  return(1);

TeamPlayEnabled:
  return(1);

IsKI:
  return(1);

// Clonk-Karl
// BOOL FindMaterial (const char *szMaterial, int iX, int iY);
// Überprüft, ob an angegebener Stelle das angegebene Material
// vorhanden ist und liefert 1 zurück, wenn das Material dort ist, ansonsten 0.
private FindMaterial:
  if (Not(Equal(SetVar(0,GetMaterial(Par(1),Par(2))),-1)))
    if (Equal( Var(0), Material(Par(0)) ))
      return(1);
  return(0);

// Hallifax
WhereToAim: //Par(0) *pObject ZielObjekt, Par(1) int iPhasen 
  SetVar(0,Angle(GetX(),GetY(),GetX(Par()),GetY(Par())));
  if (GreaterThan(Var(),180)) 
    And(SetPhase(Div(Sub(Var(),180),Par(1))),SetDir(DIR_Right()),SetComDir(COMD_Right()));
  if ( Or(LessThan(Var(),90),GreaterThan(Var(),270)) )
    And(SetDir(DIR_Left()),SetComDir(COMD_Left()),SetPhase(Div(Var(), Par(1))));
  return(1);

// Überarbeitet von Nick-Nack
ObjectXDistance:
  return(Abs(Sub(GetX(Par(0)),GetX(this()))));

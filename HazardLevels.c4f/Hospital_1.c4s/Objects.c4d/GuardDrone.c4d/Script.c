/*--- Wachdrone ---*/

// Locals
// 0 Clonk             - object
// 1 Folgen            - bool
// 2 Energie abgeben   - bool
// 3 Monster angreifen - bool

/* Initialisierung */

protected Initialize:
  SetAction("Travel");
  SetLocal(1,1);
  SetLocal(2,0);
  SetLocal(3,1);
  return(1);
  
/* TimerCall */

protected Activity:
  SetAlive(1);
  // Feinde
  if(Local(3))
    CheckTarget();
  // Flugrichtung
  CheckDirection();
  // Clonk folgen
  if(Local(1))
    if(Local(0))
      SetCommand(0,"Follow",Local(0));
  if(Not(Local(1)))
    // Anhalten und langsam nach unten fliegen
    And(
      SetCommand(0,"None"),
      SetComDir(COMD_Stop()),
      SetXDir(0), 
      SetYDir(1)
    );
  // Blitzableiter in der der Nähe?
  if(Local(2))
    if(SetVar(0,FindObject(_LNR,-35,-55,70,90)))
      if(Random(3))
        if(PathFree(GetX(),GetY(),GetX(Var(0)),GetY(Var(0))))
          // Dann unechten Blitz erzeugen
          And(
            LaunchLight(GetX(),GetY(),-5,11,-5,11),
            // Sound
            Sound("LaserShot1")
          );
  // Clonk nicht mehr da?
  if(Not(GetAlive(Local(0))))
    RemoveObject(this());
  return(1);  

/* Flugsteuerung */

private CheckDirection:
  if (GreaterThan(GetXDir())) 
    if (Equal(GetDir(),DIR_Left()))
      SetAction("Turn",0,0,0,SetDir(DIR_Right()));
  if(LessThan(GetXDir())) 
    if(Equal(GetDir(),DIR_Right()))
      SetAction("Turn",0,0,0,SetDir(DIR_Left()));
  return(1);     
  
public Reset:
  SetCommand(this(),"None");
  return(1);
  
private CheckTarget:
  // Monster suchen, Laser abfeuern
  if(SetVar(0,FindObject(OZRK,-100,-100,200,200,0,0,0,NoContainer())))
    if(GetAlive(Var(0)))
      if(Random(2))
        ObjectCall(CreateObject(LSR1,0,0,-1),"Launch",this(),Var(0));
  if(SetVar(0,FindObject(_ICH,-100,-100,200,200,0,0,0,NoContainer())))
    if(GetAlive(Var(0)))
      if(Random(2))
        ObjectCall(CreateObject(LSR1,0,0,-1),"Launch",this(),Var(0));
  return(1);

protected Damage:
  // Zerstörung
  if (LessThan(GetDamage(),120)) return(0);
  Explode(30);
  CastObjects(_DFR,3,40,0,0);
  CastObjects(_DFS,6,40,0,0);
  Log("Der Drone von %s wurde zerstört.",GetPlayerName(GetOwner(Local(0))));
  return(1);

LightningStrike:
  // Abweisen
  return(1);

LaunchLight:
  ObjectCall(CreateObject(FXL1),"Activate",Par(0),Par(1),Par(2),Par(3),Par(4),Par(5));
  return(1);
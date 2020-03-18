#strict

/* Locals:
Local[0] : Räder (wir--
*/

local Buffer;  // Luftwiderstand und Reibung
local OldXPos; // Procedure=ATTACH -Objekte
local OldYPos; // müssen ihre Geschwindigkeit
local CurrentXPos; // selbst ausrechnen.
local CurrentYPos;
local OldSpeed;
//local SpeedBuffer; // ungenauer, dafür aber exakter :)
local CurrentSpeed;
local ShootDelayCounter; // Damit man nicht ununterbrochen ballern kann
local ShootSoundNumber;
local XEntrance;
local DriverFlag;


/* Konstanten */
constMaxRDifference:return(15); // Maximaler Rotationsunterschied von den Rädern und dem Rumpf
constPhlegm:        return( 5); // Trägheit
constBufferValue:   return( 1); // Stoßdämpfer. Je weniger um so mehr Federung
constLaunchSpeed:   return( 7); // Abschussgeschwindigkeit eines Projektils
constShootDelay:    return(40); // Minimale Zeit zwischen zwei Schüssen
constBackBlow:    return( 8); // Rückstoß

//constSpeedBufferMax:return( 1);

/* Szenariobedingte Einstellungen */

SetEndlessAmmo: // ID oder 0
  return(1);

Damage:
  if(GetDamage()>600)
    Incinerate();
  return(1);

Destroy:
while (Contents()) Exit(Contents());
return(0);

Initialize:
  if(Random(2)) ChangeDef(PN7K);

  Local() = CreateObject(PW7K,0,0,GetOwner());
  SetAction("Exist",Local());

  ObjectCall(Local(),"SetMainPart",this());

  XEntrance = CreateObject(PE7K,0,0,GetOwner());
  ObjectSetAction(XEntrance,"Exist",this());
  SetLocal(0,this(),XEntrance);  


  OldXPos = GetX();
  OldYPos = GetY();
  CurrentXPos = GetX();
  CurrentYPos = GetY();

  return(1);

protected Incineration:
//  SetAction("Destroyed");
  Explode(20,CreateObject(PB7K));
//  CastObjects(_DFR,6,100,0,0);
//  CastObjects(_DFS,5,100,0,0);
  while (Contents()) Exit(Contents());
  if(DriverFlag) RemoveObject(DriverFlag);
  ObjectCall(Local(),"MainPartDestroyed");
  RemoveObject( XEntrance ); // Eingangsobjekt löschen
  ChangeDef(PB7K);
  SetAction("Destroyed");
  return(1);

/* Rotationsberechnung */

Stopp:
  ClearCommand();
//  Sound("Click");
  SetComDir(COMD_Stop(),Local());
//  CloseAirlock();
  SetCommand(Par(),"None");
  return(1);


AdaptRotation:
 if(Not(FindContents(CLON))&&Not(FindContents(CLSK))&&Not(FindContents(CLSH)))
  Stopp();

  if(!Local()) return(RemoveObject());

  var AngleDifference = GetR() - GetR(Local());

  if(GetCommand(Local()) S= "MoveTo")
    {
      if(GetXDir(Local()) > 0 && GetID() != PM7K )
        TurnRight();
      if(GetXDir(Local()) < 0 && GetID() != PN7K )
        TurnLeft();
    }


/*  SpeedBuffer++;
  if( SpeedBuffer > constSpeedBufferMax() )
    SpeedBuffer = 0 ;

  if( SpeedBuffer == constSpeedBufferMax() )*/

  if( ShootDelayCounter > 0 )
    ShootDelayCounter--;

  // Trägheitsbezogene Rotation festlegen
  CalculateSpeedCausedRotation();

  // Stoßdämpfer des Panzers

  Buffer++;
  if(Buffer > constBufferValue() ) Buffer = 0 ;


  if( AngleDifference > constMaxRDifference() )
    {
//      Sound("ShuttleHit");
      SetR( GetR(Local()) + constMaxRDifference() );
      SetRDir( Min( 0, GetRDir() ) );
    }

  if( AngleDifference < -constMaxRDifference() )
    {
//      Sound("ShuttleHit");
      SetR( GetR(Local()) - constMaxRDifference() );
      SetRDir( Max( 0, GetRDir() ) );
    }


  if( GetR() > GetR(Local()) )
    {
      SetRDir( GetRDir() - AngleDifference/2 );
      if( Buffer == constBufferValue() )
        {
          SetR( GetR() - 1 ) ;
//          Local(1) = 0 ;
        }
//      return(1);
    }

  if( GetR() < GetR(Local()) )
    {
      SetRDir( GetRDir() - AngleDifference/2 ); // +1
      if( Buffer == constBufferValue() )
        {
          SetR( GetR() + 1 ) ;
//          Local(1) = 0 ;
        }
//      return(1);
    }

  if( GetR() == GetR(Local()) )
    SetRDir( (Abs(GetRDir()) - 1) * ( GetRDir() / Abs(GetRDir()) ) );

  if( LiquidStatus() == 2 )
    SetRDir(0);/*    {
      if(GetRDir() < 0)
        SetRDir( GetRDir() +1 );
      if(GetRDir() > 0)
        SetRDir( GetRDir() -1 );
    }*/

  CheckDriver();

  return(1);

CheckDriver:
  var Driver = FindDriver();

  if(Driver && !DriverFlag )
    {
      DriverFlag = CreateObject(PF7K,0,0,-1);
      ObjectSetAction(DriverFlag,"FlyTank",this());
    }

  if(!Driver && DriverFlag )
    RemoveObject(DriverFlag);


  if(DriverFlag)
    {
      ObjectCall(DriverFlag,"CalculateManyStuff");
      SetColor(GetColor(Driver),DriverFlag);
    }

  return(1);

FindDriver:
  return(FindObject(0, 0,0,0,0, OCF_CrewMember(),0,0,this()));


CalculateSpeedCausedRotation:

  var WaypointAngle ;
  var DrivenDistance ;

  OldXPos = CurrentXPos ;
  OldYPos = CurrentYPos ;

  OldSpeed = CurrentSpeed;

  CurrentXPos = GetX() ;
  CurrentYPos = GetY() ;

  WaypointAngle = Angle( OldXPos, OldYPos, CurrentXPos, CurrentYPos );

  // Winkel in einen Bereich von -179 bis 180 umrechen
  while( WaypointAngle > 180 ) WaypointAngle -= 360 ;

  DrivenDistance = Distance( OldXPos, OldYPos, CurrentXPos, CurrentYPos );  

  CurrentSpeed = Sin( (WaypointAngle - GetR(Local())), DrivenDistance );

//  Message("%d",this(),CurrentSpeed);

  SetRDir( GetRDir() + ( ( OldSpeed - CurrentSpeed ) * constPhlegm() ) );

//  Message(
//    "Streckenwinkel: %d|Weg: %d|Geschwindigkeit: %d",this(),
//    WaypointAngle,DrivenDistance,CurrentSpeed
//  );
//  Log("Streckenwinkel: %d|",WaypointAngle);

  return(1);


/* Steuerung */

public ContainedLeft:
  [Fahrt links]

  TurnLeft();

  SetCommand(Local(),"None");
  SetComDir(COMD_Left(),Local());

  return(1);


TurnLeft:
  if( GetID() == PM7K )
    {
      Sound("Click");
      ChangeDef(PN7K);
      SetAction("Exist",Local());
    }

  return(1);

public ContainedRight:
  [Fahrt rechts]

  TurnRight();

  SetComDir(COMD_Right(),Local());
  SetCommand(Local(),"None");


  return(1);

TurnRight:
  if( GetID() == PN7K )
    {
      ChangeDef(PM7K);
      Sound("Click");
      SetAction("Exist",Local());
    }

  return(1);

protected ContainedDown:
  [Stop]
  ClearCommand();
//  Sound("Click");
  SetComDir(COMD_Stop(),Local());
//  CloseAirlock();
  SetCommand(Par(),"None");
  return(1);

ContainedThrow:

  if( ShootDelayCounter > 0 ) return();

  if( !Contents(0,Contents()) ) return();

  for(var i=0;i<=ContentsCount(0,Contents());i++) {
    SetVar(0,Contents(0,Contents()));
    if(GetID()!=CHST)
      break;
  }
  
  if( !Var(0) ) return();

  if(GetID(Var(0))==CHST) return();

 // Exit(Var(0));
  Enter(this(),Var(0));

  if( ShootSoundNumber == 2 ) ShootSoundNumber = 0 ;

  ShootDelayCounter = constShootDelay() ;

  ObjectCall(Var(0),"Check");
  ObjectCall(Var(0),"ActivateBomb");

  if( GetID() == PM7K ) return(ShootRight( Var(0) ));
  if( GetID() == PN7K ) return(ShootLeft( Var(0) ));
  return(0,Sound("Error"));

ContainedDig:

  if( ShootDelayCounter > 0 ) return();

  if( ShootSoundNumber == 2 ) ShootSoundNumber = 0 ;

  ShootDelayCounter = constShootDelay() ;

  if( GetID() == PM7K ) return(ShootRight( CreateContents(PP7K) ));
  if( GetID() == PN7K ) return(ShootLeft( CreateContents(PP7K) ));
  return(0,Sound("Error"));


// 17,17
ShootRight:
  var Projectile;

  // Endlose Munition
  Projectile = Par(0);

  if(!Projectile) Projectile = FindProjectile();

  if(!Projectile) return(Sound("NoAmmo"));

  SetOwner(GetOwner(), Projectile);

  // Ab hier wird scharf geschossen

  DoRDir(-constBackBlow());  // Rückstoß

/*  Smoke( Cos( GetR() - 40 , 49), Sin( GetR() - 45 , 24) , 5 + Random(7) ); // left: 50 statt 40
  Smoke( Cos( GetR() - 45 , 24), Sin( GetR() - 45 , 24) , 10 + Random(10) );*/

  // Mündungsfeuer
  SetR(
    GetR() + 90 ,
    CreateObject(PX7K,Cos( GetR() - 45 , 25),Sin( GetR() - 45 , 25) + 3, -1)
  );

  Sound( Format("TTaFir00%d",ShootSoundNumber) );
  ShootSoundNumber++;

  Exit(
    Projectile,

    Cos( GetR() - 45 , 24),
    Sin( GetR() - 45 , 24) + 3,

    GetR() + 90,

    Sin(GetR() + 90 , constLaunchSpeed()),
   -Cos(GetR() + 90 , constLaunchSpeed())
  );

  return(1);


ShootLeft:
  var Projectile;

  // Endlose Munition
  Projectile = Par(0);

  if(!Projectile) Projectile = FindProjectile();

  if(!Projectile) return(Sound("NoAmmo"));

  // Ab hier wird scharf geschossen

  SetOwner(GetOwner(), Projectile);

  DoRDir(constBackBlow());  // Rückstoß

/*  Smoke( -Cos( GetR() + 45 , 24), -Sin( GetR() + 45 , 24) , 10 + Random(10) );
  Smoke( Cos( GetR() - 40 , 49), Sin( GetR() - 45 , 24) , 10 + Random(10) ); // left: 50 statt 40
  Smoke( Cos( GetR() - 45 , 24), Sin( GetR() - 45 , 24) , 10 + Random(10) );*/

  // Mündungsfeuer
  SetR(
    GetR() - 90 ,
    CreateObject(PX7K,-Cos( GetR() + 45 , 25),-Sin( GetR() + 45 , 25) + 3, -1)
  );

  Sound(Format("TTaFir00%d",ShootSoundNumber));
  ShootSoundNumber++;

  Exit(
    Projectile,

   -Cos( GetR() + 45 , 24),
   -Sin( GetR() + 45 , 24) + 3,

    GetR() - 90,

   -Sin(GetR() + 90 , constLaunchSpeed()),
    Cos(GetR() + 90 , constLaunchSpeed())
  );

  return(1);


FindProjectile: // Findet ein Geeignetes Geschoss
  while(Var(1)=Contents(Var()++))
    if(BitAnd( GetCategory(Var(1)), C4D_Object() ))
      return(Var(1));
  return();


protected ContainedUpDouble:
  if(GameCall("NoTankDeparture"))
    {
      Message("Man kann in diesem|Szenario den Panzer|nicht verlassen!",this());
      return();
    }
//  OpenAirlock();
  Exit(Par(0));
  Sound("Airlock1");
  SetComDir(COMD_Stop(),Local()); 
//  SetXDir(0); SetYDir(0);
  return(1);

protected ControlCommand:
  // Bewegungskommando
  if (Par(0)S="MoveTo")
    return(SetCommand(this(),Par(0),Par(1),Par(2),Par(3)+10));
  return(0);

private ClearCommand:
  SetCommand(this(),"None");
  return(1);



global DoRDir: // iChange, *pObject
  return(SetRDir(GetRDir(Par(1)) + Par(),Par(1)));


LiquidStatus:
  return(ObjectCall(Local(),"LiquidStatus"));

RejectCollect:
  if (Contained(Par(1))) return(1);
  if( Sqrt( Pow(GetXDir(Par(1)),2), Pow(GetYDir(Par(1)),2) ) >= 15 )
    ObjectCall(Par(1),"Hit");
  return(1);


/*
NormalR:
  */

ControlCommand:
  // Bewegungskommando
  if (Par(0)S="MoveTo")
    return(SetCommand(Local(),Par(0),Par(1),Par(2),Par(3) + 5));
  return(0);


Pow:
  if(LessThan( Par(1),0 )) IncVar(2);
  IncVar();
  while(LessThan( Var(1),Abs(Par(1)) ))
    And(
      SetVar(0,Mul( Var(),Par() )),
      IncVar(1)
    );
  if(Var(2)) return(Div( 1,Var() ));
  return(Var());


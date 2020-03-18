/*--- Räder ---*/

#strict

local MainPart, XEntrance;


constPhysicalWalk: return(100000);
constMaxSpeedInLiquid: return( 10 );

/* Initialisierung */

protected Initialize:
  SetAction("Walk");
  SetComDir(COMD_Stop());

//  MainPart = CreateObject(PM7K,0,0,GetOwner());
//  ObjectSetAction(MainPart,"Exist",this());
//  SetLocal(0,this(),MainPart);


//  ResortObjects("TankPartResort",C4D_Vehicle());

  return(1);

SetMainPart:
  MainPart = Par();
  return(1);

/*TankPartResort:
  //if( Par() == this() && Par(1) == MainPart )
    return(1);

  return(-1);
*/


//12,11
/* TimerCall */

AdaptRotation:

  // Bodenhaftung (NICHT Ausrichtung)
  AttachAdjust();

  // Physical Anpassen
  PhysicalAdjust();

/*  if(
    Inside( Abs(GetR()), -1, 1 )
 && (
      (!LeftWheelStuck() && !RightWheelStuck() )
    ||( LeftWheelStuck() &&  RightWheelStuck() )
    )
  )
    SetR(0);
 */
  //var NewRDir

//  CreateObject(_FLR,LeftWheelX(),LeftWheelY(),-1);
//  CreateObject(_FLR,RightWheelX(),RightWheelY(),-1);

  while(  LeftWheelStuck() && !RightWheelStuck() )
    {
      SetR( GetR() + 1 );
      Var()++;
    }
      
  while( !LeftWheelStuck() &&  RightWheelStuck() )
    {
      SetR( GetR() - 1 ) ;
      Var()-- ;
    }


  if(
    GetAction() S= "Jump"
  &&(
      ( !LeftWheelStuck() && !RightWheelStuck() )
    ||(  LeftWheelStuck() &&  RightWheelStuck() )
    )
  )
    DoRDir(MaxAbs( Var() / 4, Var() / Abs(Var()) ));

/*
  if( !LeftWheelStuck() && !RightWheelStuck() && !( GetAction(Local()) S= "Jump" ) )
    {
      if( GetR() < 0 )
        SetRDir( GetRDir() - 1 );

      if( GetR() > 0 )
        SetRDir( GetRDir() - 1 );
    }
*/

  if( GetAction() S= "Walk" )
    SetRDir();

  // Geschwindigkeit anpassen
  if( LiquidStatus() == 2 )
    {
      SetXDir(BoundBy(
        GetXDir()-(GetXDir()/Abs(GetXDir())),
        -constMaxSpeedInLiquid(),
        constMaxSpeedInLiquid()
      ));
      SetYDir(BoundBy(GetYDir(),-constMaxSpeedInLiquid(),constMaxSpeedInLiquid()));
    }


  return(1);


// Wenn Objekte verdreht aufkommen setzen sie nicht automatisch die Action "Walk"
AttachAdjust:
  //Wenn fester Boden drunter ist
  if(
    GBackSolid( GetVertex(1,0), GetVertex(1,1) + 1 )
 && GetAction() S= "Jump"
  )
    SetAction("Walk");

  return(1);


/* 
In Flüssigkeiten fährt der Panzer nur 1/2x so schnell.
Außerdem gibt "Walk" nur die horizontale Geschwindigkeit an,
bergauf/ab sind also Objekte normalerweise schneller.
Das hier kompensiert es:
*/
PhysicalAdjust:
  SetPhysical("Walk",Abs(Cos( GetR(), constPhysicalWalk() )) / LiquidStatus(), 2);

//  if(InLiquid()) SetPhysical("Walk",GetPhysical("Walk")/10,2); Da reicht schon ein Pixel :(

  // Im Wasser ist er langsamer
//  if(GBackLiquid(TankCenterX(),TankCenterY())) SetPhysical("Walk",GetPhysical("Walk")/2,2);

//  CreateObject(_FLR,TankCenterX(),TankCenterY(),-1);

//  Message("Walk: %d",this(),GetPhysical("Walk"));

  return(1);



LeftWheelStuck:
//  if(GBackSolid( LeftWheelX(), LeftWheelY() )) Message("Links",this());
  return(GBackSolid( LeftWheelX(), LeftWheelY() ));

RightWheelStuck:
//  if(GBackSolid( RightWheelX(), RightWheelY() )) Message("Rechts");
  return(GBackSolid( RightWheelX(), RightWheelY() ));


LeftWheelX:
  return( Cos( GetR() + 4 * ( GetR() / Abs(GetR()) ) , -12 ) );

LeftWheelY:
  return( Sin( GetR() + 4 * ( GetR() / Abs(GetR()) ) , -12 ) );

RightWheelX:
  return( Cos( GetR() + 4 * ( GetR() / Abs(GetR()) ) , 12 ) );

RightWheelY:
  return( Sin( GetR() + 4 * ( GetR() / Abs(GetR()) ) , 12 ) );

LiquidStatus:
  if( GBackLiquid(TankCenterX(),TankCenterY()) ) return(2);
  return(1);

TankCenterX:
  return(Sin(GetR(),10));

TankCenterY:
  return(-Cos(GetR(),10));  

// Gibt die Zahl mit dem größeren Betrag zurück
MaxAbs: // iZahl1, iZahl2
  if( Abs(Par()) > Abs(Par(1)) ) return(Par());
  return(Par(1));


// Wenn der Hauptteil kaputt geht:
MainPartDestroyed:

  RemoveObject() ; // sich selbst löschen
  return(1);
/*-- Splitter-Rakete --*/

#strict
#include _POV

Dmg: return(DefinitionCall(_SPL, "Dmg")*9);

// Local 0: XDir
// Local 1: YDir

/* Status */
public IsMissile: return(1);

/* Wird abgefeuert */
public Launch:  
  // Schußrichtung
  SetLocal(0,Div(Par(0),2));
  SetLocal(1,Div(Par(1),2));
  SetAction("Travel");
  // Sicht verfolgen
  SetPlrView(GetOwner(),this());
  return(1);
  
/* Fliegt */
private Travel:
  // Treffer-Überprüfung
  if(CheckHit(-5,-5,10,10))
    return(Hit());
  // Bewegung
  SetXDir(Local(0));
  SetYDir(Local(1));
  Smoke( 0, 0, 5 );
  return(1);
  
/* Treffer */
public Hit:
  CastObjects(_SPL,9,20,0,0);
  RemoveObject();
  return(1);

/*-- Splitter-Rakete --*/

#strict
#include _POV

Dmg: return(20);

// Local 0: XDir
// Local 1: YDir

/* Status */
public IsMissile: return(1);

/* Wird abgefeuert */
public Launch:  
  // Schuﬂrichtung
  SetLocal(0,Div(Par(0),2));
  SetLocal(1,Div(Par(1),2));
  SetAction("Travel");
  // Sicht verfolgen
  SetPlrView(GetOwner(),this());
  return(1);
  
/* Fliegt */
private Travel:
  // Bewegung
  if(GetActTime()<100) {
    SetXDir(Local(0));
    SetYDir(Local(1));
  }
  if(GetActTime()>2) {
    SetVar(0,CreateObject(_SPL));
    SetXDir(GetXDir()/8,Var(0));
    SetYDir(GetYDir()/8,Var(0));
  }
  Smoke( 0, 0, 5 );
  return(1);
  
/* Treffer */
public Hit:
  ObjectCall(CreateObject(EXPL),"Launch",Dmg());
  RemoveObject();
  return(1);

/*-- Blitz --*/

#strict

/* Locals */

// 0: Bewegung X
// 1: Abweichung X
// 2: Bewegung Y
// 3: Abweichung Y


/* Aktivierung */

public Activate: // int iStartX, int iStartY, int iAdvanceX, int iRandomX, int iAdvanceY, int iRandomY
  // Startposition
  AddVertex(Par(0),Par(1));
  // Bewegungsverhalten
  Local(0)=Par(2); Local(1)=Par(3); Local(2)=Par(4); Local(3)=Par(5);
  // Aktion setzen
  SetAction("Advance");
  // Geräusch
  if (!Random(5)) Sound("Thunder*");
  return(1);

/* Bewegung */


private Advance:
  // Einschlag
  Var(0)=GetVertexNum()-1;
  if (GBackSemiSolid( GetVertex(Var(0),0)-GetX(), GetVertex(Var(0),1)-GetY() ))
    return(Remove());

  // Objektschaden
  if (Var()>5) BlastObjects( GetVertex(Var(0),0), GetVertex(Var(0),1), 5);

  // Verzweigung
  if (!Random(35))
    LaunchLightning( GetVertex(Var(0),0), GetVertex(Var(0),1), Local(0),Local(1),Local(2),Local(3) );

  // Neuen Eckpunkt
  if (!AddVertex( GetVertex(Var(0),0)+Local(0)+Random(Local(1)),
                  GetVertex(Var(0),1)+Local(2)+Random(Local(3))) )  return(Remove());

  // Objektanziehung
  Var(0)=GetVertexNum()-1;  
  if (Var(0)>7)
    if (Var(1)=FindObject( 0, GetVertex(Var(0),0)-GetX()-50,GetVertex(Var(0),1)-GetY()-50,100,100,OCF_AttractLightning() ) )
      Attraction(Var(1));

  // Weiter	
  return(1);


/* Effekte */

private Sparkle:
  Var()=GetVertexNum()-1;
  CastObjects(SPRK,1,20,GetVertex(Var(0),0)-GetX(), GetVertex(Var(0),1)-GetY());
  return(1);


/* Anziehung */

private Attraction:
  // Einschlag in Objekt
  AddVertex( GetVertex(0,0,Par(0))+GetX(Par(0)),
             GetVertex(0,1,Par(0))+GetY(Par(0)) );
  ObjectCall(Par(0),"LightningStrike");
  SetAction("Connect");
  return(1);


/* Ende */

private Remove:
  RemoveObject();
  return(1);
	
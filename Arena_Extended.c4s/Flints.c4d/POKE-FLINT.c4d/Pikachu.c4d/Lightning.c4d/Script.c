/*-- Blitz --*/

/* Locals */

// 0: Bewegung X
// 1: Abweichung X
// 2: Bewegung Y
// 3: Abweichung Y

/* Aktivierung */
public Activate: // int iStartX, int iStartY, int iAdvanceX, int iRandomX, int iAdvanceY, int iRandomY
  SetPosition(0,0);
  // Startposition
  AddVertex(Par(0),Par(1));
  // Bewegungsverhalten
  SetLocal(0,Par(2));
  SetLocal(1,Par(3));
  SetLocal(2,Par(4));
  SetLocal(3,Par(5));
  // Aktion setzen
  SetAction("Advance");
  // Geräusch
  if (Not(Random(5))) Sound("Thunder*");
  return(1);

/* Bewegung */
private Advance:
  // Einschlag
  SetVar(0,Sum(GetVertexNum(),-1));
  if (GBackSemiSolid( Sub(GetVertex(Var(0),0),GetX()), Sub(GetVertex(Var(0),1),GetY()) ))
  return(Remove());
  // Objektschaden
  if (GreaterThan(Var(0),1))
    while(SetVar(2,FindObject(0,GetVertex(Var(0),0)-10,GetVertex(Var(0),1)-10,GetVertex(Var(0),0)+20,GetVertex(Var(0),1)+20,OCF_Alive(),0,0,NoContainer(),Var(2))))
      if(GetOwner(Var(2))!=GetOwner())
        DoEnergy(-1,Var(2));
  // Verzweigung
  // Neuen Eckpunkt
  if (Not( AddVertex( Sum( GetVertex(Var(0),0), Local(0), Random(Local(1)) ),
  Sum( GetVertex(Var(0),1), Local(2), Random(Local(3)) ) ) ))
  return(Remove());
  // Objektanziehung
  SetVar(0,Sum(GetVertexNum(),-1));
  if (GreaterThan(Var(0),7))
  if (SetVar(1, FindObject( 0,
  Sub(GetVertex(Var(0),0),GetX(),50),
  Sub(GetVertex(Var(0),1),GetY(),50),
  100,
  100,
  OCF_AttractLightning() ) ))
  Attraction(Var(1));
  // Weiter	
  return(1);

/* Effekte */
private Sparkle:
  SetVar(0,Sum(GetVertexNum(),-1));
  CastObjects(SPRK,1,20,Sub(GetVertex(Var(0),0),GetX()), Sub(GetVertex(Var(0),1),GetY()));
  return(1);

/* Anziehung */
private Attraction:
  // Einschlag in Objekt
  AddVertex( Sum(GetVertex(0,0,Par(0)),GetX(Par(0))),
  Sum(GetVertex(0,1,Par(0)),GetY(Par(0))) );
  ObjectCall(Par(0),"LightningStrike");
  SetAction("Connect");
  return(1);

/* Ende */
private Remove: return(RemoveObject());
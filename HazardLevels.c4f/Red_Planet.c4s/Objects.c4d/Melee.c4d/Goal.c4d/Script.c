/*-- Spielzielsteuerung --*/

#strict

// Bei allen C4D_Goal-Objekten zu importieren
// �berladbare Funktionen:
// int IsFullfilled(); - Ist das Ziel erf�llt?
// Statt Initialize InitGoal benutzen!

// Local0: Aktives GameGoal-Pr�fobjekt

// Initialisierung
protected Initialize:
  // Bei GOAL selber nur Warteaktion
  if(GetID()==GOAL) return(SetAction("Init"));
  // Objekt mit Timer erstellen
  if(!FindObject(GOAL)) CreateObject(GOAL,0,0,-1);
  // Fertig
  return(1);

// Nachinitialisierung f�r GOAL
protected PostInit:
  // Ein CheckFullfilled-Broadcast an alle
  while(Var(0)= FindObject(0, 0,0,0,0, 0, 0,0, 0, Var(0)))
    if(GetCategory(Var(0))&C4D_Goal())
      ObjectCall(Var(0), "IsFulfilled");
  return(1);

// Timer
protected CheckTime:
  // Momentanes Zielobjekt pr�fen
  if(Local(0)) if(!ObjectCall(Local(0), "IsFulfilled")) return(1);
  // Zielpr�fung aktiv?
  if(!ActIdle()) return(1);
  // Jetzt in der Schleife suchen
  Local()=0;
  while(Local()=FindObject(0, 0,0,0,0, 0, 0,0, 0, Local(0)))
    if(GetCategory(Local(0))&C4D_Goal())
      {
      Var()++;
      if(!ObjectCall(Local(0), "IsFulfilled")) return(1);
      }
  // Kein Zielobjekt? Wir sind �berfl�ssig :(
  if (!Var()) return(RemoveObject());
  // Ziel erf�llt: Vom Szenario abgefangen?
  if (GameCall("OnGoalsFulfilled")) return(RemoveObject());
  // Tja, jetzt ist das Spiel vorbei. Erstmal die Belohnung
  Sound("Trumpet",1);
  // Jetzt ein wenig warten, und dann GameOver
  SetAction("Wait4End");
  return(1);

protected RoundOver:
  // Das wars ;(
  GameOver();
  return(RemoveObject());

// default
public IsFulfilled: return(1);

protected Activate: // Defaultnachrichten
  if (IsFulfilled()) return(MessageWindow("Spielziel erf�llt",Par()));
  return(MessageWindow(GetDesc(),Par()));

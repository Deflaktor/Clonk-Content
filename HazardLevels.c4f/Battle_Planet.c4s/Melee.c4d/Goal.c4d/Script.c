/*-- Spielzielsteuerung --*/

#strict

// Bei allen C4D_Goal-Objekten zu importieren
// Überladbare Funktionen:
// int IsFullfilled(); - Ist das Ziel erfüllt?
// Statt Initialize InitGoal benutzen!

// Local0: Aktives GameGoal-Prüfobjekt

// Initialisierung
protected Initialize:
  // Bei GOAL selber nur Warteaktion
  if(GetID()==GOAL) return(SetAction("Init"));
  // Objekt mit Timer erstellen
  if(!FindObject(GOAL)) CreateObject(GOAL,0,0,-1);
  // Fertig
  return(1);

// Nachinitialisierung für GOAL
protected PostInit:
  // Ein CheckFullfilled-Broadcast an alle
  while(Var(0)= FindObject(0, 0,0,0,0, 0, 0,0, 0, Var(0)))
    if(GetCategory(Var(0))&C4D_Goal())
      ObjectCall(Var(0), "IsFulfilled");
  return(1);

// Timer
protected CheckTime:
  // Momentanes Zielobjekt prüfen
  if(Local(0)) if(!ObjectCall(Local(0), "IsFulfilled")) return(1);
  // Zielprüfung aktiv?
  if(!ActIdle()) return(1);
  // Jetzt in der Schleife suchen
  Local()=0;
  while(Local()=FindObject(0, 0,0,0,0, 0, 0,0, 0, Local(0)))
    if(GetCategory(Local(0))&C4D_Goal())
      {
      Var()++;
      if(!ObjectCall(Local(0), "IsFulfilled")) return(1);
      }
  // Kein Zielobjekt? Wir sind überflüssig :(
  if (!Var()) return(RemoveObject());
  // Ziel erfüllt: Vom Szenario abgefangen?
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
  if (IsFulfilled()) return(MessageWindow("Spielziel erfüllt",Par()));
  return(MessageWindow(GetDesc(),Par()));

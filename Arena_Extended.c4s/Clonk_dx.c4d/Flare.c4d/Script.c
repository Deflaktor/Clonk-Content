/*---- Schweif ----*/

// Par 0: Action
// Par 1: Phase
// Par 2: Richtung

SetPicture:
  SetAction(Par(0));
  SetPhase(Par(1));
  SetDir(Par(2));
  SetLocal(0,Par(3));
  SetAction("Hold");
  return(1);

Remove: return(RemoveObject());
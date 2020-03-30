#strict

/*Initialize:
if(!IsNewgfx()&&Random(2))
RemoveObject();
return(1);
*/

protected Process:
  if (Random(10)+10 < GetActTime()) DoCon(-25);
  return(1);

protected Completion:
  DoCon(Random(100));
  SetAction("Sparkle");
  return(1);

protected Hit: return(DoCon(-50));

/* Globaler Funktionsaufruf */
global Sparkle: // int iAmount, int iX, int iY
  CastObjects(_TRS, Par()/3 +2, Par(), Par(1), Par(2));
  return(1);

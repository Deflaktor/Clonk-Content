#strict
//Global(0): 1 = Marathonlauf 2 = Punkterennen

Initialize:
  return(1);

MenuQueryCancel:
return(1);

Menu1:
  CreateMenu(MEN1,GetHiRank(),0,0,"Regel-Einstellung",0,1);
  SetMenuSize(2,1,GetHiRank());
  AddMenuItem("Marathonlauf (Einzelspieler empfohlen)","Marathon",MEN1,GetHiRank(),0,0,"Zeitrennen. Der erste Spieler der die komplette Strecke schafft gewinnt.");
  AddMenuItem("Punkterennen (Mehrspieler empfohlen)","Punkte",MEN1,GetHiRank(),0,0,"Derjenige der die meisten Teilstrecken gewonnen hat gewinnt.");
  return(1);

Marathon:
  while(Var(0)=FindObject(_CP1,0,0,0,0,0,"Goal")) {
    ObjectSetAction(Var(0),"Los");
    SetPosition(GetX(Var(0)), GetY(Var(0))-20, Var(0));
  }
  SetGlobal(0,1);
  return(Start());

Punkte:
  SetGlobal(0,2);
  return(Start());

Start:
  ChangeDef(CLNK);
  this()->SetAction("Walk");
  while(Contents())
    Exit(Contents());
  ScriptGo(1);
  return(1);

/*-- Spielercontainer --*/

#strict

#appendto STAR

/* Initialisierung */

protected Initialize:
  // Zufallsposition und leuchten
  SetPosition(Random(LandscapeWidth()), Random(LandscapeHeight()));
  SetAction("Shine");
  return(1);


/* Warteobjekt */

protected ContainedUp:
  [Wartezeit/Men�]
  if (Local()>0) return(StartMenu());
  if (Local()==-1) return(QueryPlrSide());
  if (!Local(1)) return();
  return(PlrMessage("Verbleibende Wartezeit: %d:%02d", GetOwner(), Local(1)/60, Local(1)%60));


/* Men�steuerung */

protected MenuQueryCancel: // Abbruch im Men�
  // Permanentes Men� soll geschlossen werden?
  if (Local()==2) return();
  // Seitenauswahl: Kein Abbruch
  if (Local()==-1) return(1, Sound("Error"));
  // Hostmen�: Zur�ck zum Hauptmen�
  return(1, StartMenu());

PlrClnk: // Spieler f�rs Men� suchen
  var o=GetOwner();
  if (GetCursor(o)) return(GetCursor(o));
  return(GetHiRank(o));

SelItem: // ID f�rs Men�
  if (Par()) return(FLNT);
  return(ROCK);


/* Hostmen� */

public StartMenu:
  // flag setzen, dass ein Abbruch wieder ins Hostmen� f�hrt
  Local()=1;
  CreateMenu(_DS2, PlrClnk(), this(), 0, "Optionen",0,1);
  AddMenuItem("Burgauswahl...", "PlrPlc", CST3, PlrClnk(), 0, -1, "Spielerplazierung");
  AddMenuItem("Rejoins...", "PlrRej", KNIG, PlrClnk(), 0, 0, "Anzahl der Rejoins festlegen");
  AddMenuItem("Rejoindelay", "DelayRej", TIME, PlrClnk(), 0, 0, "Wartezeit zwischen den Rejoins");
  AddMenuItem("Kein LZB", "DoToggleFlag", SelItem(GetFlag(GF_NoJoin())), PlrClnk(), 0, GF_NoJoin(), "Joinen nach dem Start");
  AddMenuItem("Ein Konto", "DoToggleFlag", SelItem(GetFlag(GF_OneAcc())), PlrClnk(), 0, GF_OneAcc(), "Ein Gemeinschaftskonto f�r alle Spieler");
  AddMenuItem("Feste Krone", "DoToggleFlag", SelItem(GetFlag(GF_SensCr())), PlrClnk(), 0, GF_SensCr(), "Die Krone ist nur f� Feinde einsammelbar");
  AddMenuItem("K�nig erlauben", "DoToggleFlag", SelItem(GetFlag(GF_King())), PlrClnk(), 0, GF_King(), "Man kann einen K�nig kaufen");
  AddMenuItem("Start!", "ActionGo", _CRN, PlrClnk(), 0, -1, "Das Spiel starten");
  return(1);

protected ActionGo:
  SetLocal();
  return(GameCall("StartGame"));

protected DoToggleFlag:
  Sound("Connect");
  ToggleFlag(Par(1));
  return(StartMenu());

protected PlrPlc:
  Sound("Click");
  CreateMenu(CST3, PlrClnk(), this(), 0,"Teamwahl",0,1);
  AddMenuItem("Auswahl", "PlrPlc2", SelItem(plrplc==PLC_User()), PlrClnk(), 0, PLC_User(), "Die Spieler entscheiden selber");
  AddMenuItem("Zuf�llig", "PlrPlc2", SelItem(plrplc==PLC_Random()), PlrClnk(), 0, PLC_Random(), "Der Zufall entscheidet");
  AddMenuItem("Gleichm��ig", "PlrPlc2", SelItem(plrplc==PLC_RndEq()), PlrClnk(), 0, PLC_RndEq(), "Der Zufall entscheidet gerecht");
  AddMenuItem("zur�ck", "StartMenu", LMM1, PlrClnk(), 0, -1, "Hauptmen�");
  return(1);

protected PlrRej:
  Sound("Click");
  PlrMessage("Rejoins: %d", GetOwner(), rejoincnt-1);
  if (Par()) Local()=2;
  CreateMenu(KNIG, PlrClnk(), this(), 0,"Teamwahl",0,1,1);
  AddMenuItem("keine", "PlrRejZ", ZAP1, PlrClnk(), 0, 0, "Nur der Startjoin");
  AddMenuItem("+1", "PlrRejS", LMM3, PlrClnk(), 0, 1, "Ein Rejoin mehr");
  if (rejoincnt>1) AddMenuItem("-1", "PlrRejS", MONS, PlrClnk(), 0, -1, "Ein Rejoin weniger");
  AddMenuItem("+10", "PlrRejS", LMM3, PlrClnk(), 0, 10, "Zehn Rejoins mehr");
  if (rejoincnt>10) AddMenuItem("-10", "PlrRejS", FMNS, PlrClnk(), 0, -10, "Zehn Rejoins weniger");
  AddMenuItem("zur�ck", "PlrRejE", LMM1, PlrClnk(), 0, -1, "Hauptmen�");
  Local()=1;
  return(1);

protected PlrRejS:
  Sound("ArrowHit");
  rejoincnt+=Par(1);
  PlrMessage("Rejoins: %d", GetOwner(), rejoincnt-1);
  if (rejoincnt==1) { PlrRej(1); SelectMenuItem(1, PlrClnk()); return(1); }
  if (rejoincnt<=10 && rejoincnt-Par(1)>10 && Par(1)<0) { PlrRej(1); SelectMenuItem(2, PlrClnk()); return(1); }
  if (Par(1)>0 && (rejoincnt==Par(1)+1 || (rejoincnt<=Par(1)+10 && rejoincnt>10)))
    {
    PlrRej(1);
    if (Par(1)==1) SelectMenuItem(1, PlrClnk());
    if (Par(1)==10) SelectMenuItem(3, PlrClnk());
    return(1);
    }
  return(1);

protected PlrRejZ:
  Sound("Connect");
  rejoincnt=1;
  return(CloseMenu(PlrClnk()));

protected PlrRejE: return(CloseMenu(PlrClnk()));

protected DelayRej:
  Sound("Click");
  PlrMessage("Rejoinzeit: %d:%02d", GetOwner(), rejointime/60, rejointime%60);
  if (Par()) Local()=2;
  CreateMenu(KNIG, PlrClnk(), this(), 0,"Teamwahl",0,1,1);
  AddMenuItem("sofort", "DelayRejZ", ZAP1, PlrClnk(), 0, 0, "Sofortiger Neubeitritt");
  AddMenuItem("+0:10", "DelayRejS", LMM3, PlrClnk(), 0, 10, "Zehn Sekunden l�nger");
  if (rejointime>=10) AddMenuItem("-0:10", "DelayRejS", MONS, PlrClnk(), 0, -10, "Zehn Sekunden k�rzer");
  AddMenuItem("+1:00", "DelayRejS", LMM3, PlrClnk(), 0, 60, "Eine Minute l�nger");
  if (rejointime>=60) AddMenuItem("-1:00", "DelayRejS", FMNS, PlrClnk(), 0, -60, "Eine Minute k�rzer");
  AddMenuItem("zur�ck", "DelayRejE", LMM1, PlrClnk(), 0, -1, "Hauptmen�");
  Local()=1;
  return(1);

protected DelayRejS:
  Sound("ArrowHit");
  rejointime+=Par(1);
  PlrMessage("Rejoinzeit: %d:%02d", GetOwner(), rejointime/60, rejointime%60);
  if (!rejointime) { DelayRej(1); SelectMenuItem(1, PlrClnk()); return(1); }
  if (rejointime<60 && rejointime-Par(1)>=60 && Par(1)<0) { DelayRej(1); SelectMenuItem(2, PlrClnk()); return(1); }
  if (Par(1)>0 && (rejointime==Par(1) || (rejointime<Par(1)+60 && rejointime>=60)))
    {
    DelayRej(1);
    if (Par(1)==10) SelectMenuItem(1, PlrClnk());
    if (Par(1)==60) SelectMenuItem(3, PlrClnk());
    return(1);
    }
  return(1);

protected DelayRejZ:
  Sound("Connect");
  rejointime=0;
  return(CloseMenu(PlrClnk()));

protected DelayRejE: return(CloseMenu(PlrClnk()));


PlrPlc2:
  Sound("Connect");
  plrplc=Par(1);
  return(StartMenu());

/* Spielerplazierungsmen� */

public QueryPlrSide:
  // Men� zur Seitenauswahl �ffnen
  Local()=-1;
  CloseMenu(PlrClnk()); CreateMenu(_CRN, PlrClnk(), this());
  AddMenuItem("Linke Burg", "PlrSide", LMM1, PlrClnk(), 0, -1, "Der linken Burg beitreten");
  AddMenuItem("Rechte Burg", "PlrSide", LMM5, PlrClnk(), 0, 1, "Der rechten Burg beitreten");
  return(1);

PlrSide:
  SetPlrSide(GetOwner(), Par(1));
  return(GameCall("DoPlrJoin", GetOwner()));

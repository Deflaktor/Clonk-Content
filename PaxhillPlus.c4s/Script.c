/* --- Paxhill - Krone der Ewigkeit --- */

#strict

/* -- Variablen -- */

// Teamvariablen: 0=keine, -1=links, +1=rechts

static winner;    // Seite, die gewonnen hat
static rejoincnt; // Anzahl erlaubter Rejoins-1
static rejointime;// Wartezeit bis zum Rejoin
static plrplc;    // Spielerplazierung:
  global PLC_User:   return(0); // Der Spieler entscheidet
  global PLC_Random: return(1); // Zufällig
  global PLC_RndEq:  return(2); // Zufällig mit in etwa gleichen Spielerzahlen in den Burgen
static flags;     // Spielflags
  global GF_Running:   return(1<<0); // Das Spiel läuft
  global GF_NoJoin:    return(1<<1); // Spielerbeitritt zur Laufzeit gesperrt?
  global GF_LeftCst:   return(1<<2); // Linke Burg zugewiesen?
  global GF_RightCst:  return(1<<3); // Rechte Burg zugewiesen?
  global GF_OneAcc:    return(1<<4); // Gemeinschaftskonto
  global GF_SensCr:    return(1<<5); // Schlaue Krone
  global GF_King:      return(1<<6); // Man kann einen König kaufen

// Global(n) - Rejoinzähler für Spieler n
//  Positiv: Rechte Burg
//  Negativ: Linke Burg


/* -- Hilfsfunktionen -- */

global ToggleFlag: return((flags=flags ^ Par())&Par());    // ToggleFlag  - Flag an/ausschalten; zurückgeben, ob es gesetzt ist
global GetFlag:    return(flags&Par());                    // GetFlag     - Zurückgeben, ob ein Flag gesetzt ist
global Sgn: if (!Par()) return(); return(Par()/Abs(Par()));// Sgn         - Vorzeichenfunktion
global GetPlrSide: return(Sgn(Global(Par())));             // GetPlrSide  - Heimatburg von Spieler Par() ermitteln
global SetPlrSide: return(Global(Par())=Par(1)*rejoincnt); // SetPlrSide  - Spieler Par() für Burg Par(1) setzen
global DoRejoin:                                           // DoRejoin    - Gibt zurück, ob Spieler Par() rejoinen kann, und erniedrigt den Rejoinzähler
  var r=Global(Par()); if (Abs(r)<=1) return();
  Global(Par())=(Abs(r)-1)*Sgn(r); return(1);
global NoPlrJoin:                                          // NoPlrJoin   - Darf gerade kein Spieler beitreten?
  return(flags&GF_Running() && flags&GF_NoJoin() || winner);
global SetRejoins: rejoincnt=Par(); var i,j,r;             // SetRejoins  - Rejoinzahl neu setzen; Spielerrejoins aktualisieren
  for (j=GetPlayerCount(); j; i++) if (GetPlayerName(i))
    { r=Global(i); Global(i)=(Abs(r)+1)*Sgn(r); j--; }
  return(1);

/* -- Spielinitialisierung -- */

protected Initialize:
  // Defaultwerte setzen
  rejoincnt=1;
  rejointime=0;
  plrplc=PLC_RndEq();
  // Fahrstuhlschächte bohren
  while(SetVar(0, FindObject(CPEL, 0, 0, 0, 0, 0, 0, 0, 0, Var())))
    ObjectCall(Var(), "CreateShaft", 250);
  return(1);


/* -- Spielerinitialisierung -- */

protected InitializePlayer:
  // Baupläne
  DefinitionCall(WPPL, "SetKnowledge", Par());
  DefinitionCall(CPPL, "SetKnowledge", Par());
  // Konto erzeugen - nicht mehr nötig im neuen Teamkonto
  //if (flags&GF_OneAcc()) ObjectCall(FindObject(_OAC), "InitializePlayer", Par());
  // Spielerflags zurücksetzen
  SetGlobal(Par());
  // Beitritt erlaubt?
  if (NoPlrJoin()) return(EliminatePlayer(Par()));
  // Spiel läuft schon: Direkter Spielbeitritt
  if (flags&GF_Running()) return(DoPlrJoin(Par()));
  // Anfangsmodus: Spieler fangen
  var obj, crw, i;
  obj=CreateObject(STAR, 0,0, Par());
  while (crw=GetCrew(Par(), i++)) Enter(obj, crw);
  // Spieler 0: Menü
  if (!Par()) ObjectCall(obj, "StartMenu");
  // Andere Spieler: Nachricht
  if (Par()) Message("Bitte warten,|der Host stellt das Spiel ein...");
  // Jo, das war's erstmal
  return(1);

private DoPlrJoin: // int iPlr, bool fRejoin
  // Spielerseite ermitteln
  var sd=GetPlrSide(Par());
  // Keine? Ermitteln.
  if (!sd) sd=QueryPlrSide(Par());
  // Immer noch keine? Dann dauert es wohl noch
  if (!sd) return(0);
  // Weg mit dem Spielerobjekt
  var obj=Contained(GetCrew(Par()));
  if (obj) RemoveObject(obj, 1);
  // Rejoinnachricht
  if (Par(1))
    {
    Log("%s hat noch %d Rejoin(s)", GetPlayerName(Par()), Abs(Global(Par()))-1);
    Sound("Ding");
    }
  // Spieler in der Burg plazieren: Linke Burg
  if (sd == -1)
    {
    // Linke Burg noch nicht zugewiesen?
    if (~flags & GF_LeftCst()) { AquireBase(Par(),    0, 0, 550, 550);  flags=flags|GF_LeftCst(); }
    // Plazieren
    PlacePlr(Par(),   40, 190);
    }
  // Rechte Burg
  if (sd == 1)
    {
    // Rechte Burg noch nicht zugewiesen?
    if (~flags & GF_RightCst()) { AquireBase(Par(), 1370, 0, 550, 550); flags=flags|GF_RightCst(); }
    // Plazieren
    PlacePlr(Par(), 1820, 180);
    }
  // Verfeindung
  var i,j;
  if (!Par(1))
    for (j=GetPlayerCount(); j>1; i++) if (GetPlayerName(i) && i != Par())
      {
      SetHostility(Par(), i, GetPlrSide(Par())!=GetPlrSide(i), true);
      SetHostility(i, Par(), GetPlrSide(Par())!=GetPlrSide(i), true);
      j--;
      }
  // Feddich
  return(1);

private AquireBase: // int iPlr, int ix, int iy, int iwidth, int iheight
  // Alles im Zielrechteck...
  while(SetVar(0, FindObject(0, Par(1), Par(2), Par(3), Par(4), 0, 0, 0, 0, Var()))) {
    // ...wenn es nicht lebt...
    if(Not(BitAnd(GetOCF(Var()), OCF_Living())))
      // ...und noch keinem gehört...
      if(Equal(GetOwner(Var()), -1))
	    if(GetMaterial(GetX(Var()),GetY(Var())) != Material("Earth"))
          // ...in Besitz nehmen
          SetOwner(Par(), Var());
  }
  // Fertig =)
  return(1);

private PlacePlr: // int iPlr, int iX, int iY
  // Alle Clonks des Spielers...
  SetVar(1, -1);
  while(SetVar(0, GetCrew(Par(), IncVar(1))))
    // ...in etwa an der Zielposition plazieren
    SetPosition(Sum(Par(1), -19, Random(40)), Par(2), Var());
  // Eine Flagge gibts auch gleich noch
  Enter(GetHiRank(Par()), CreateObject(FLAG, Par(1), Par(2), Par()));
  // OK, fertig
  return(1);

private QueryPlrSide:
  // Benutzermodus?
  if (plrplc == PLC_User())
    {
    // ggf. in den Stern versetzen
    if (!Contained(GetCrew(Par())))
      {
      var obj, crw, i;
      obj=CreateObject(STAR, 0,0, Par());
      while (crw=GetCrew(Par(), i++)) Enter(obj, crw);
      }
    // Benutzer abfragen
    ObjectCall(Contained(GetCrew(Par())), "QueryPlrSide");
    // Noch keine Entscheidung
    return(0);
    }
  var sd;
  // Ausgeglichener Zufallsmodus?
  if (plrplc == PLC_RndEq())
    {
    // Spielerzahlen links und rechts ermitteln
    var i,j,pl,pr;
    for (j=GetPlayerCount(); j; i++) if (GetPlayerName(i)) { Var(GetPlrSide(i)+1)++; j--; }
    pl=Var(); pr=Var(2);
    // Eine Seite hat zu wenig?
    if (pl<pr) sd=-1;
    if (pl>pr) sd=1;
    }
  // Zufallsmodus/noch keine Entscheidung?
  if (!sd) sd=Random(2)*2-1;
  return(sd, SetPlrSide(Par(), sd));

public StartGame:
  // Alle Spieler beitreten lassen
  var i,j;
  for (j=GetPlayerCount(); j; i++) if (GetPlayerName(i)) { 
    DoPlrJoin(i); 
	if(GetFlag(GF_King())) 
	  DoHomebaseMaterial(i, KING, 1);
	j--;
  }
  // Gemeinschaftskonto?
  if (flags&GF_OneAcc()) CreateObject(TACC,0,0,-1);
  // Scriptablauf starten (rejoins)
  ScriptGo(1);
  return(1);

public RelaunchPlayer:
  // Spieler gestorben: Rejoin abziehen
  if (!DoRejoin(Par())) return();
  // Neuen Clonk erzeugen
  var crw,obj;
  MakeCrewMember(crw=CreateObject(KNIG,0,0,Par()),Par());
  SetCursor(Par(), crw);
  SelectCrew(Par(), crw, 1);
  // Sofortiger Rejoin?
  if (!rejointime) return(DoPlrJoin(Par(),1));
  // Spieler warten lassen
  Enter(obj=CreateObject(STAR,0,0,Par()), crw);
  SetPosition(LandscapeWidth()/2+LandscapeWidth()/4*GetPlrSide(Par()), 100, obj);
  Local(1,obj)=rejointime;
  ScriptGo(1);
  PlrMessage("%d:%02d bis zum Rejoin...", Par(), rejointime/60, rejointime%60);
  // Feddich
  return(1);

/* -- Szenarienablauf -- */

Script1:
  // Rejoin-Zeitzähler
  var obj;
  while (obj=FindObject(STAR,0,0,0,0,0,0,0,0,obj))
    if (!--Local(1,obj))
      DoPlrJoin(GetOwner(obj),1);
  // Alle drin, kein Kontozeug?
  if (!ObjectCount(STAR)) ScriptGo();
  // Start markieren
  flags |= GF_Running();
  return(goto());


/* Spielziel */

CrownLost: // pObj *pCrown
  // Spiel schon vorbei?
  if(winner) return(1);
  // Besitzer ermitteln
  winner=-Local(0, Par());
  // Endsequenz
  return(ScriptGo(1), goto(1000));

DoKillClonk: // pObj *pClonk
  // ein paar Übrigbleibsel erzeugen
  Smoke(GetX(Par()), GetY(Par()), Sum(20, Random(10)));
  CastObjects(SPRK, 5, 10, GetX(Par()), GetY(Par()));
  CastPXS("Sand", 10, 20, GetX(Par()), GetY(Par()));
  // Clonk entfernen
  RemoveObject(Par());
return(1);

DoKillPlayer: // int iPlr
  // Crew entfernen
  while(SetVar(0, GetHiRank(Par()))) DoKillClonk(Var());
  // Spieler zur Sicherheit noch eliminieren
  EliminatePlayer(Par());
  return(1);

Script1001:
  // Versager eliminieren
  var i,j;
  for (j=GetPlayerCount(); j; i++) if (GetPlayerName(i))
    {
    if(GetPlrSide(i)!=winner) DoKillPlayer(i);
    j--;
    }
  // Sound dazu
  Sound("Dragons");
  if(!(currentBattleMusic S= "@ifYouCanUseADoorKnob.ogg")) {
	importantBattleMusicEndFrame=0;
	Music("@ifYouCanUseADoorKnob.ogg",0,2);
	PeaceMusic();
	return();
  }
  return(1);

Script1020:
  // Spiel mit Fanfare beenden
  GameOver();
  return(ScriptGo());

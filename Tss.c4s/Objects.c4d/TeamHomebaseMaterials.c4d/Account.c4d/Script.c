/*-- Konto --*/

#strict

local value; // Geld auf dem Konto
local tick;  // Z�hler
local lastA; // Gr��te Spielernummer der Verb�ndeten
local cnt;   // Anzahl Verb�ndeter

// Local(n): Konto von Spieler n, wenn befreundet

/* Zerst�rung */

private func GetKonto(iPlr) {
  var obj;
  while(obj=FindObject(HBK_, 0,0,0,0, 0, 0 ,0,0, obj))
    if(Local(0,obj)==iPlr) {
	  obj->SetAction("Idle");
	  return(obj);
	}
  obj=CreateObject(HBK_, 0,0, iPlr);
  SetLocal(0,iPlr,obj);
  return(obj);
}

protected func Destruction()
{
  // Befreundete Accounts benachrichtigen
  var i,acc;
  while (i<=lastA)
    if (acc=Local(i++))
      acc->AllianceDie(this() );
}

/* Initialisierung */

protected func Initialize()
{
  SetAction("Delay");
}

public func Init()
{
  // Anfangsgeldwert
  value=GetKonto(GetOwner());

  // Z�hler initialisieren
  tick=35;
  lastA=-1;
}

/* �berpr�fung */

private func Execute()
{
  if(!ActIdle())
    return(1);
  // Geh�rt niemandem (Spieler eliminiert?) - l�schen
  if (GetOwner() < 0) return(RemoveObject() );

  // Geldwert�nderung?
  value->Check(this());
  if (!value->EqualTo(this()))
  {
    value->SubtractInv(this(), this());
    value->Add(this());
    // �nderung auf verb�ndete Konten anrechnen
    var i,acc;
    while (i<=lastA) if (acc=Local(i++)) acc->UpdateValue(this());
  }
  // Alle 35 Aufrufe CheckAlliances durchf�hren
  if (!--tick) AllChk();
}

/* Kontobestand �ndern */

public func UpdateValue(iByAmount)
{
  // �nderung auf value und Wealth getrennt anrechnen, da beide verschieden sein k�nnen,
  // wenn zwei Konten im gleichen Frame ge�ndert wurden
  value->Add(iByAmount);
  value->ResetForPlayer(GetOwner());
}

public func UpdateToValue(iToAmount)
{
  // �nderung auf value und Wealth getrennt anrechnen, da beide verschieden sein k�nnen,
  // wenn zwei Konten im gleichen Frame ge�ndert wurden
  value->MaxWith(iToAmount);
  value->ResetForPlayer(GetOwner());
}

/* Allianz�nderungen pr�fen und Konten entsprechend umkonfigurieren */

private func AllChk()
{
  // Z�hler zur�cksetzen
  tick=35;
  // Pr�fen, ob Allianzen gebrochen wurden
  var i,o = GetOwner();
  // Alle Konten der Teammitglieder durchgehen
  for (;i<=lastA;i++)
    // Konto vorhanden und verfeindet?
    if(Local(i) && Hostile(o,i))
      // Konto l�schen
      BreakAlliance(i);

  // Pr�fen, ob neue Allianzen geschlossen wurden
  for(i = 0; i < GetPlayerCount(); ++ i)
  {
    // Spieler ermitteln
    var plr = GetPlayerByIndex(i);
    // Nicht verfeindet und noch kein Konto reserviert?
    if(!Hostile(o,plr) && !Local(plr))
      // Neues Konto erstellen
      CreateAlliance(plr);
  }
}

/* Konto aus den Teamkonten l�schen */

private func BreakAlliance(iPlr)
{
  // Alle Allianzen brechen
  var o = GetOwner();

  // Alle Konten durchgehen
  for (var i = 0;i<=lastA;i++) if (Local(i))
  {
    // Und diesen Spieler aus der Allianz l�schen
    Local(i)->RemoveAlliance(o);
    // Uns selbst nat�rlich auch l�schen :)
    RemoveAlliance(i);
  }

  cnt=0;
  lastA=-1;
}

/* Neuen Spieler in die Allianz aufnehmen */

private func CreateAlliance(iWithPlr)
{
  // Verb�ndete Spieler �berpr�fen: Alle m�ssen verb�ndet sein
  var acc=FindObjectOwner(GetID(),iWithPlr);
  if(!acc) return(0);
  if (!CheckAlliances(acc)) return(0);
  // Neuen letzten Verb�ndeten berechnen
  lastA=Max(lastA, iWithPlr);
  // Allianz hinzuf�gen; Locals setzen
  var v2 = ObjectCall(acc,"AddAlliances",this(),value); //acc->AddAlliances(this(), value);
  //v2->Subtract(value,this());
  value->MaxWith(v2,this());
  AddAlliances(acc, this());

  return(1);
}

/* Pr�fen, ob dieser Spieler mit der Allianzgruppe pWith verb�ndet ist */

private func CheckAlliances(pWith)
{
  // Allianzen f�r alle verb�ndeten Konten pr�fen...
  for (var i = 0;i<=lastA;i++) if (Local(i))
    if (!CheckAlliance(Local(i), pWith)) return(0);
  // ...und f�r sich selbst
  return(CheckAlliance(this(), pWith));
}

/* Pr�fen, ob der Account pAcc mit pWith verb�ndet ist */

public func CheckAlliance(pAcc, pWith)
{
  // Besitzer von pAcc ermitteln 
  var o = GetOwner(pAcc);
  // Jeden Spieler durchgehn
  for(var i = 0; i < GetPlayerCount(); ++ i)
  {
    // Spielernummer ermitteln
    var plr = GetPlayerByIndex(i);
    // Konto f�r diesen Spieler in pWith vorhanden?
    if(Local(plr, pWith) )
      // Verfeindet?
      if(Hostile(o, plr) )
        // Dann war's wohl nix.
        return(0);
  }
  // Zuletzt noch pr�fen, ob der Spieler mit pWith selbst verb�ndet ist.
  return(!Hostile(o, GetOwner(pWith)) );
}

public func AddAlliances(pGroup, iToValue)
{
  // Bei Verb�ndeten hinzuf�gen...
  for (var i = 0;i<=lastA;i++)
    // Verb�ndet?
    if (Local(i))
      // Jo, also hinzuf�gen
      Local(i)->AddAlliance(pGroup, iToValue);
  // ...und bei sich selbst
  AddAlliance(pGroup, iToValue);
  return(value);
}

public func AddAlliance(pGroup, iToValue)
{
  // Locals setzen
  var o = GetOwner(pGroup);
  // Jeden SPieler durchgehn
  for(var i = 0; i < GetPlayerCount(); ++ i)
  {
    // Spielernummer ermitteln
    var plr = GetPlayerByIndex(i);
    // Verb�ndet?
    if(Local(plr, pGroup) )
    {
      // Sind wie das selbst?
      if(Local(plr) || plr == GetOwner() ) continue;
      // Konto hinzuf�gen
      Local(plr) = Local(plr, pGroup);
      // Neue h�chste Spielernummer in diesem Team ermitteln
      lastA = Max(lastA, plr);
      // Diese Allianz hat ein Mitglied mehr
      ++cnt;
    }
  }
  
  // Auch hier neue Allianz hinzuf�gen
  Local(o)=pGroup;
  // Und neue h�chste Spielernummer setzen
  lastA=Max(lastA, o);
  ++cnt;
  // Geldwert anpassen
  UpdateToValue(iToValue);
}

/*  Allianz stirbt: Geldwert belassen und Z�hler verringern */

public func AllianceDie()
{
  return(--cnt);
}

public func RemoveAlliance(iAlliance)
{
  // Allianz entfernen; Z�hler verringern
  if (!Local(iAlliance)) return(0);
  Local(iAlliance) = 0;
  --cnt;
  while (!Local(lastA) && lastA) --lastA;
  return(1);
}


/* Info */

public func GetTeam()
{
  // Kein Team? :'(
  if (!cnt) return();
  // Alle Allianzmitglieder speichern
  var j,k;
  for (var i = 0; i <= lastA; i++)
    if (Local(i))
      Var(j++) = GetPlayerName(i);

  // Erstes Mitglied holen
  var rs = Var(0);

  // Und alle weiteren mit Komma getrennt dranh�ngen
  while (++k < j)
    if (Var(k))
      rs = Format("%s, %s", rs, Var(k));
      
  return(rs);
}

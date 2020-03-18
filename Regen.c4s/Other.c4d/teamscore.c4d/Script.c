/*-- Gemeinschafts-Siedlungspunkte --*/

/* Kurzinfo
 * Autor: Christian Harnisch (Nachtschatten)
 * Version: 1.0 (18.02.2008)
 */

#strict

local originalPlayerValues, playerScores;

protected func Initialize() {
	originalPlayerValues = [];
	playerScores = [];
}

protected func Activate( int player) {
	var team = GetTeamMateNames( player);
	// Nachricht vorbereiten, je nachdem, ob andere Spieler im Team sind oder nicht
	if( team S= "")
		team = "$NoTeamScore$";
	else
		team = Format( "$TeamScoreWith$", team);
	MessageWindow( team, player);
}

/* Initialisierung eines Spielers */

protected func InitializePlayer( int playerNumber) {
	// Punkte auf Null setzen
	SetScore( playerNumber, 0);
	// Ursprüngliche Gesamtpunktzahl des Spielers speichern
	SetOriginalPlayerValue( playerNumber, GetPlayerValue( playerNumber));
}

/* Timer call */

protected func Activity() {
	// Alle Spieler durchgehen
	for( var i = 0; i < GetPlayerCount(); ++i) {
		var currentPlayer = GetPlayerByIndex( i);
		SetDisplayedScore( currentPlayer, GetTeamValueGain( GetTeamPlayers( currentPlayer)));
	}
}

/*-- Hilfsfunktionen --*/

private func SetDisplayedScore( int playerNumber, int newScore) {
	//Log( "Set player %d score to %d", playerNumber, newScore);
	DoScore( playerNumber, newScore - GetPlrValueGain( playerNumber), true);

}

/*- Score -*/

private func SetScore( playerNumber, int newScore) {
	playerScores[ playerNumber] = newScore;
}

global func DoScore( int playerNumber, int scoreChange) {
	var teamScoreRule = FindObject2( Find_Func( "IsTeamScoreRule"));
	// Aufruf in der Team Score-Spielregel, sofern vorhanden
	if( teamScoreRule)
		if( this() != teamScoreRule)
			return teamScoreRule->DoScore( playerNumber, scoreChange);
	// Ansonsten Aufruf der geerbten Funktion
	return _inherited( playerNumber, scoreChange);
}

public func DoScore( int playerNumber, int scoreChange, bool isForDisplay) {
	if( isForDisplay)
		// ... Punkte für Anzeige berechnen, mit _inherited Engine-Funktion aufrufen
		_inherited( playerNumber, scoreChange);
	else
		playerScores[ playerNumber] += scoreChange;
}

global func GetScore( int playerNumber) {
	var teamScoreRule = FindObject2( Find_Func( "IsTeamScoreRule"));
	// Aufruf in der Team Score-Spielregel, sofern vorhanden
	if( teamScoreRule)
		if( this() != teamScoreRule)
			return teamScoreRule->GetScore( playerNumber);
	// Ansonsten Aufruf der geerbten Funktion
	return _inherited( playerNumber);
}

public func GetScore( int playerNumber, bool isEngineValueRequested) {
	if( isEngineValueRequested)
		return _inherited( playerNumber);
	return playerScores[ playerNumber];
}

/*global func Test() {
	if( this())
		if( !(this()->~IsTeamScoreRule()))
			Log( "abc");
	_inherited();
}
public func Test() { Log( "def"); _inherited(); }
public func Test2() { Test(); }*/

/*- Spieler-Punkte -*/

/* Punkte eines einzelnen Spielers */
private func GetPlayerValue( int playerNumber) {
	return( GetPlayerObjectsValue( playerNumber) + GetWealth( playerNumber) + GetScore( playerNumber));
}
private func GetPlayerValueGain( int playerNumber) {
	return GetPlayerValue( playerNumber) - GetOriginalPlayerValue( playerNumber);
}

/* Punkte eines Teams */
private func GetTeamValue( array teamPlayerNumbers) {
	var teamValue = 0;
	for( var playerNumber in teamPlayerNumbers)
		teamValue += GetPlayerValue( playerNumber);
	return teamValue;
}
private func GetTeamValueGain( array teamPlayerNumbers) {
	var teamGain = 0;
	for( var playerNumber in teamPlayerNumbers)
		teamGain += GetPlayerValueGain( playerNumber);
	return teamGain;
}

/* Berechnet den Wert, den alle Objekte eines Spielers insgesamt haben */
private func GetPlayerObjectsValue( int playerNumber) {
	var objectsValue;
	for( var object in FindObjects( Find_Owner( playerNumber)))
		objectsValue += object->GetValue();
	return objectsValue;
}

/* Ursprüngliche PlayerValue */
private func GetOriginalPlayerValue( int playerNumber) {
	return( originalPlayerValues[ playerNumber]);
}
private func SetOriginalPlayerValue( int playerNumber, int value) {
	originalPlayerValues[ playerNumber] = value;
}

/*- Spielerteams -*/

/* Liefert einen String zurück, der die Namen der Spieler im selben Team enthält, aber ohne den angegebenen Spieler */
public func GetTeamMateNames( int playerNumber) {
	// Nummern der Spieler, die im selben Team sind
	var team = GetTeamPlayers( playerNumber);
	var count = GetLength( team);
	// Ersten Namen in die Liste schreiben...
	var i, foundIndex;
	var list = "";
	for( i = 0; i < count; ++i)
		if( playerNumber != team[ i]) {
			list = GetPlayerName( team[ i]);
			foundIndex = i;
			break;
		}
	// ... und die Namen der anderen anhängen, jeweils mit einem Komma getrennt
	for( i = 0; i < count; ++i) {
		if( playerNumber != team[ i] && i != foundIndex)
			list = Format( "%s, %s", list, GetPlayerName(  team[ i]));
	}
	return list;
}

/* Liefert ein Array von Spielernummern, die allesamt befreundet sind */
global func GetTeamPlayers( int playerNumber) {
	var team = [];
	var i, j;
	// Alle Spieler durchgehen, und die speichern, die befreundet sind
	for( i = 0; i < GetPlayerCount(); ++i) {
		var otherPlayer = GetPlayerByIndex( i);
		if( !Hostile( playerNumber, otherPlayer))
			team[ j++] = otherPlayer;
	}
	return team;
}

public func IsTeamScoreRule() { return true; }
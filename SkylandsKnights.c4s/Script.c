/* Himmelsinseln */

#strict
static timeTillWar;

/* Initialisierung */

protected func Initialize()
{
    SetGamma(RGB(10,9,10), RGB(161,157,159), RGB(255,254,255) );
    timeTillWar=10*60;
    ScriptGo(1);
}

protected func InitializePlayer(int iPlr) {
    var i=0;
    var obj;
    while(obj=FindObjectOwner(0,iPlr,0,0,0,0,OCF_Collectible(),0,0,obj)) {
        i=(i+1)%GetCrewCount(iPlr);
        Enter(GetCrew(iPlr,i),obj);
    }
    obj=0;
    while(obj=FindObjectOwner(0,iPlr,0,0,0,0,0,0,0,obj)) if(GetCategory(obj) & C4D_Vehicle()) {
        for(var i=0;i<=GetCrewCount(iPlr);i++)
            SetPosition(GetX(obj),GetY(obj), GetCrew(iPlr, i));
    }
}

Script2:
 // if(GetPlayerCount()<2)
 //   return(goto(1));
    if(timeTillWar==0) {
        CreateObject(MELE,0,0,-1);
        // Mit allen Spielern verfeinden
        var i,j,k,l;
        for (j = GetPlayerCount(); j > 1; i++) {
        if(GetPlayerName(i))
            j--;
        for (k = GetPlayerCount(); k > 1; l++) {
            if(GetPlayerName(l))
                k--;
            if (GetPlayerName(i) && GetPlayerName(l) && i!=l) {
                SetHostility(i, l, 1, 1);
                SetHostility(l, i, 1, 1);
            }
        }
    }
        ScriptGo(0);
        return(goto(1));
    }
    var seconds;
    var minutes;
    // Die Zeit läuft noch
    seconds = timeTillWar;
    --timeTillWar;
    while(seconds>=60) {
        seconds-=60;
        minutes++;
    }
    if(seconds<10)
        seconds = Format("0%d",seconds);
    if(GetType(seconds)!=C4V_String())
        if(seconds>=10)
            seconds = Format("%d",seconds);
    // Globale Meldung ausgeben;
    if(minutes<1||minutes>=1&&seconds==0)
    Message("Krieg in:|%d:%s",0,minutes,seconds);
    return(goto(1));
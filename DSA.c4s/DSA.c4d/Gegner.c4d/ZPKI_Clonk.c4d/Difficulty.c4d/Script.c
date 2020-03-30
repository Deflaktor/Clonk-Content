#strict

static ZPKI_dif,ZPKI_rndzahl;

private func go()
{
ZPKI_dif=ObjectCount(_ZPK)+1;
Log("Zauberpack KI Schwierigkeitsgrad: %d",ZPKI_dif);
ZPKI_rndzahl=7-ZPKI_dif;
if(ZPKI_rndzahl<0)
	ZPKI_rndzahl=0;
while(Var()=FindObject(_ZPK))
	RemoveObject(Var());

  return(1);
}

protected func Initialize()
{SetAction("go");}


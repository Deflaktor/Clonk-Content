#strict

func check()
{
if(!FindObject(ZPKI))
	{
	Sound("Trumpet");
	Log("Super!");
	Message("Gute Arbeit. Alle Gegner wurden vernichtet!");
	GameOver();
	}

}
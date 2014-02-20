#pragma strict

var MenuSkin : GUISkin;

var toggleTxt : boolean;
var toolbarInt : int = 0;
var toolbarStrings : String[] = ["Toolbar1", "Toolbar2", "Toolbar3"];
var selGridInt : int = 0;
var selStrings : String[] = ["Grid 1", "Grid 2", "Grid 3", "Grid 4"];
var hSliderValue : float = 0.0;
var hSbarValue : float;


function OnGUI() 
{

	GUI.skin = MenuSkin;
	
    GUI.BeginGroup(new Rect(Screen.width/2-150,Screen.height/2-150,300,300));
        GUI.Box(Rect(0,0,300,300),"This is the title of a box");
		GUI.Button(Rect(0,25,100,20),"I am a button");
	GUI.EndGroup ();

}
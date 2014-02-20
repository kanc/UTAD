using UnityEngine;
using System.Collections;

public class Menu : MonoBehaviour {

	public GUISkin MenuSkin;

	void OnGUI() 
	{
		GUI.skin = MenuSkin;
	
		GUI.BeginGroup(new Rect(Screen.width/2 - 200,Screen.height/2 - 200,400,400));
			GUI.Box(new Rect(0,0,400,400),"");
			GUI.Button(new Rect(60,50,275,74),"Jugar");
			GUI.Button(new Rect(60,150,275,74),"Salir");
		GUI.EndGroup ();
	}
}

using UnityEngine;
using System.Collections;

public class cloudMovement : MonoBehaviour {

	public float speed = 10;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {

		transform.position= new Vector3(transform.position.x + speed * Time.deltaTime, transform.position.y,transform.position.z);

		Collider rSceneCol = GameObject.Find("SceneRightBound").collider;

		if (!renderer.bounds.Intersects(rSceneCol.bounds ))
		{
			Collider lSceneCol = GameObject.Find("SceneLeftBound").collider;
			transform.position = new Vector3(lSceneCol.transform.position.x, transform.position.y, transform.position.z);
		}
	
	}
}

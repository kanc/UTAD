using UnityEngine;
using System.Collections;

public class EggSettings : MonoBehaviour {

	public float score;
	public bool isGrouded;
	public float timeToDissapear = 1;
	float timeGrounded = 0;
	float elapsedTimeGrounded;
	
	// Use this for initialization
	void Start () 
	{	
		float eggType = Random.value;

		if (eggType > 0.7f)
		{	score = 5;
			rigidbody.mass = 5;
		}
		else
			score = 1;

	}
	
	// Update is called once per frame
	void Update () 
	{
		if (isGrouded)
		{
			if (timeGrounded == 0)
				timeGrounded = Time.time;

			elapsedTimeGrounded = Time.time - timeGrounded;

			if (elapsedTimeGrounded >= timeToDissapear)
				Destroy(gameObject);
		}

	}
	void OnTriggerEnter (Collider other) 
	{
		if (other.gameObject.name == "ground")
			isGrouded = true;
	}
}

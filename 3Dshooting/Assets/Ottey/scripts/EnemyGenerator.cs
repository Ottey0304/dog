using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyGenerator : MonoBehaviour
{
    [SerializeField] GameObject enemyPrefab;


    const int GENERATE_INTERVAL_F = 120;


    void Start()
    {
        
    }


    void Update()
    {
        StartCoroutine("ManageInterval");
    }


    IEnumerator ManageInterval()
    {
        for (int i = 0; i < GENERATE_INTERVAL_F; i ++)
        {
            GenerateEnemy();
            yield return null;
        }
    }


    void GenerateEnemy()
    {
        Instantiate(enemyPrefab);
    }
}

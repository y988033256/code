using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Playerstats : MonoBehaviour
{
    public Button Reset;

    // local characters manager
    private CharacterManagerScript charactersManager;

    // -----------------------------MaxHp----------------------------- //

    public Button MaxHpLevelIncrease;       // + button for MaxHp
    public Button MaxHpLevelDecrease;       // - button for MaxHp

    public Text MaxHpLevelDisplay;              // UI text for CurrentMaxHpLevel ' 0 '/10
    public int MaxHpLevel { get; set; }

    public Text MaxHpStatsDisplay;     // UI text for MaxHP stats ??? <<<
    public int CurrentMaxHpStats { get; set; }


    // -----------------------------Ammunition Size----------------------------- //

    public Button MaxAmmoSizeIncrease;    // + button for Ammunitionsize
    public Button MaxAmmoSizeDecrease;    // - button for Ammunitionsize

    public Text MaxAmmoSizeLevelDisplay;              // UI text for Current Ammunition Size Level ' 0 '/10
    public int MaxAmmoSizeLevel { get; set; }

    public Text MaxAmmoSizeStatsDisplay;     // UI text for Max Ammunition Size Stats ??? <<<
    public int CurrentMaxAmmoSizeStats { get; set; }


    // ----------------------------------MaxEnergy-------------------------------------- //

    public Button MaxEnergyIncrease;    // + button for MaxEnergy
    public Button MaxEnergyDecrease;    // - button for MaxEnergy

    public Text MaxEnergyLevelDisplay;              // UI text for Current Max Energy Level ' 0 '/10
    public int MaxEnergyLevel { get; set; }

    public Text MaxEnergyStatsDisplay;     // UI text for Max Max Energy Level Stats ??? <<<
    public int MaxEnergyStats { get; set; }

    // ----------------------------------ReloadSpeed-------------------------------------- //

    public Button ReloadSpeedIncrease;    // + button for ReloadSpeed
    public Button ReloadSpeedDecrease;    // - button for ReloadSpeed

    public Text ReloadSpeedLevelDisplay;              // UI text for Current Reload Speed Level ' 0 '/10
    public int ReloadSpeedLevel { get; set; }

    public Text ReloadSpeedStatsDisplay;     // UI text for Max Energy Level Stats ??? <<<
    public float CurrentReloadSpeedStats { get; set; }

    // ----------------------------------MoveSpeed-------------------------------------- //

    public Button MoveSpeedIncrease;    // + button for Movespeed
    public Button MoveSpeedDecrease;    // - button for Movespeed

    public Text MoveSpeedLevelDisplay;              // UI text for Current Move Speed Level ' 0 '/10
    public int MoveSpeedLevel { get; set; }

    public Text MoveSpeedStatsDisplay;     // UI text for Move Speed Stats ??? <<<
    public int CurrentMoveSpeedStats { get; set; }

    // ----------------------------------Skill CDR-------------------------------------- //

    public Button SkillCDRIncrease;    // + button for Skill CDR
    public Button SkillCDRDecrease;    // - button for Skill CDR

    public Text SkillCDRLevelDisplay;              // UI text for Current Skill CDR Level ' 0 '/10
    public int SkillCDRLevel { get; set; }

    public Text SkillCDRStatsDisplay;     // UI text for Skill CDR Stats ??? <<<
    public float CurrentSkillCDRStats { get; set; }

    // ----------------------------------Fire rate-------------------------------------- //

    public Button FireRateIncrease;    // + button for FireRate
    public Button FireRateDecrease;    // - button for FireRate

    public Text FireRateLevelDisplay;              // UI text for Current Skill FireRate Level ' 0 '/10
    public int FireRateLevel { get; set; }

    public Text FireRateStatsDisplay;     // UI text for Skill CDR Stats ??? <<<
    public float CurrentFireRateStats { get; set; }

    // ----------------------------------Grenade Damage Area-------------------------------------- //

    public Button GrenadeDamageAreaIncrease;    // + button for Grenade Damage Area
    public Button GrenadeDamageAreaDecrease;    // - button for Grenade Damage Area

    public Text GrenadeDamageAreaLevelDisplay;              // UI text for Current skill Grenade Damage Area Level ' 0 '/10
    public int GrenadeDamageAreaLevel { get; set; }

    public Text GrenadeDamageAreaStatsDisplay;     // UI text for Skill Grenade Damage Area Stats ??? <<<
    public float CurrentGrenadeDamageAreaStats { get; set; }

    // ----------------------------------Gun Damage Increase-------------------------------------- //

    public Button GunDamageIncrease;    // + button for Grenade Damage Area
    public Button GunDamageDecrease;    // - button for Grenade Damage Area

    public Text GunDamageLevelDisplay;              // UI text for Current skill Grenade Damage Area Level ' 0 '/10
    public int GunDamageLevel { get; set; }

    public Text GunDamageStatsDisplay;     // UI text for Skill Grenade Damage Area Stats ??? <<<
    public float CurrentGunDamageStats { get; set; }

    // ----------------------------------Grenade Damage Increase-------------------------------------- //

    public Button GrenadeDamageIncrease;    // + button for Grenade Damage Area
    public Button GrenadeDamageDecrease;    // - button for Grenade Damage Area

    public Text GrenadeDamageLevelDisplay;              // UI text for Current skill Grenade Damage Area Level ' 0 '/10
    public int GrenadeDamageLevel { get; set; }

    public Text GrenadeDamageStatsDisplay;     // UI text for Skill Grenade Damage Area Stats ??? <<<
    public float CurrentGrenadeDamageStats { get; set; }






    public Text MaxHp;
    public Text CurrentHp;
    public Text MaxExpText;
    public Text CurrentExpText;
    public Text LevelText;
    public Text CurrentGeneralSkillPoint;
    public Text CurrentCharacterSkillPoint;

    public int MaxHealth { get; set; }
    public int CurrentHealth { get; set; }
    public int MaxExp { get; set; }
    public int CurrentExp { get; set; }

    public int Level { get; set; }

    public int Skillpoint { get; set; }

    public Slider healthbar;
    public Slider expbar;


    // Start is called before the first frame update
    void Start()
    {
        //Button MaxHpLevelIncrease = GetComponent<Button>();
        // Button MaxHpLevelDecrease = GetComponent<Button>();

        // look up on the list of objects and get CharacterManagerScript component for the object tagged as CharacterManager
        charactersManager = GameObject.FindGameObjectWithTag("CharacterManager").GetComponent<CharacterManagerScript>();

        Skillpoint = 100;
        Level = 1;

        // -----------------------------MaxHp------------------------------//
        CurrentMaxHpStats = 0;
        MaxHpLevel = 0;

        // -----------------------------Ammunition Size--------------------//
        MaxAmmoSizeLevel = 0;
        CurrentMaxAmmoSizeStats = 0;

        // -----------------------------MaxEnergy--------------------------//
        MaxEnergyLevel = 0;
        MaxEnergyStats = 0;

        // -----------------------------ReloadSpeed------------------------//
        ReloadSpeedLevel = 0;
        CurrentReloadSpeedStats = 0;

        // -----------------------------MoveSpeed--------------------------//
        MoveSpeedLevel = 0;
        CurrentMoveSpeedStats = 0;

        // -----------------------------Skill CDR--------------------------//
        SkillCDRLevel = 0;
        CurrentSkillCDRStats = 0;

        // ----------------------------------Fire rate-------------------------------------- //
        FireRateLevel = 0;
        CurrentFireRateStats = 0;

        // ----------------------------------Grenade Damage Area-------------------------------------- //
        GrenadeDamageAreaLevel = 0;
        CurrentGrenadeDamageAreaStats = 0;

        // ----------------------------------Gun Damage Increase-------------------------------------- //  
        GunDamageLevel = 0;
        CurrentGunDamageStats = 0;

        // ----------------------------------Grenade Damage Increase-------------------------------------- //
        GrenadeDamageLevel = 0;
        CurrentGrenadeDamageStats = 0;

        // MaxHealth = 100;
        //  CurrentHealth = MaxHealth;
        // healthbar.value = CalculateHealth();


        //   MaxExp = 100;
        //   CurrentExp = 0;
        //   expbar.value = CalculateExp();


    }




    // Update is called once per frame
    void Update()
    {
        CurrentGeneralSkillPoint.text = Skillpoint.ToString();
        CurrentCharacterSkillPoint.text = Skillpoint.ToString();

        // -----------------------------MaxHp----------------------------- //
        MaxHpLevelDisplay.text = MaxHpLevel.ToString() + "/30";
        MaxHpStatsDisplay.text = "+" + CurrentMaxHpStats.ToString();

        // -----------------------------Ammunition Size----------------------------- //
        MaxAmmoSizeLevelDisplay.text = MaxAmmoSizeLevel.ToString() + "/10";
        MaxAmmoSizeStatsDisplay.text = "+" + CurrentMaxAmmoSizeStats.ToString();

        // ----------------------------------MaxEnergy-------------------------------------- //
        MaxEnergyLevelDisplay.text = MaxEnergyLevel.ToString() + "/20";
        MaxEnergyStatsDisplay.text = "+" + MaxEnergyStats.ToString();

        // ----------------------------------ReloadSpeed-------------------------------------- // 这里需要确定 怎么表达 属性
        ReloadSpeedLevelDisplay.text = ReloadSpeedLevel.ToString() + "/10";
        ReloadSpeedStatsDisplay.text = "-" + CurrentReloadSpeedStats.ToString() + "s";

        // ----------------------------------MoveSpeed-------------------------------------- //  这里需要确定 怎么表达 属性
        MoveSpeedLevelDisplay.text = MoveSpeedLevel.ToString() + "/10";
        MoveSpeedStatsDisplay.text = "+" + CurrentMoveSpeedStats.ToString();

        // ----------------------------------Skill CDR-------------------------------------- // 这里需要确定 怎么表达 属性
        SkillCDRLevelDisplay.text = SkillCDRLevel.ToString() + "/10";
        SkillCDRStatsDisplay.text = "-" + CurrentSkillCDRStats.ToString() + "s";

        // ----------------------------------Fire rate-------------------------------------- //  这里需要确定 怎么表达 属性
        FireRateLevelDisplay.text = FireRateLevel.ToString() + "/10";
        FireRateStatsDisplay.text = "+" + CurrentFireRateStats.ToString();

        // ----------------------------------Grenade Damage Area-------------------------------------- //  这里需要确定 怎么表达 属性
        GrenadeDamageAreaLevelDisplay.text = GrenadeDamageAreaLevel.ToString() + "/10";
        GrenadeDamageAreaStatsDisplay.text = "+" + CurrentGrenadeDamageAreaStats.ToString();

        // ----------------------------------Gun Damage Increase-------------------------------------- // 这里需要确定 怎么表达 属性
        GunDamageLevelDisplay.text = GunDamageLevel.ToString() + "/10";
        GunDamageStatsDisplay.text = "+" + CurrentGunDamageStats.ToString();

        // ----------------------------------Grenade Damage Increase-------------------------------------- // 这里需要确定 怎么表达 属性
        GrenadeDamageLevelDisplay.text = GrenadeDamageLevel.ToString() + "/10";
        GrenadeDamageStatsDisplay.text = "+" + CurrentGrenadeDamageStats.ToString();







        /*
               LevelText.text = Level.ToString();

              MaxHp.text = MaxHealth.ToString();
              CurrentHp.text = CurrentHealth.ToString();

              MaxExpText.text = MaxExp.ToString();
              CurrentExpText.text = CurrentExp.ToString();

              if (CurrentHealth != 0)
               {
                   if (Input.GetKeyDown(KeyCode.A))
                   {
                       TakeDamage(10);
                   }
               }
               if (Input.GetKeyDown(KeyCode.B))
               {
                   addmaxhp(10);
               }
               if (Input.GetKeyDown(KeyCode.C))
                   Addexp(10);

         */


    }
    /*
   void IncreaseMaxHpLevelonClick()
   {
       IncreaseMaxHpLevel(1);
   }
   void DecreaseMaxHpLevelonClick()
   {
       DecreaseMaxHpLevel(1);
   }
 */
    // -----------------------------MaxHp----------------------------- //
    public void IncreaseMaxHpLevel(int amount)
    {
        if (Skillpoint >0)
        {
            if (MaxHpLevel < 30)
            {
                charactersManager.IncrementPlayerHealth(10.0f);
                charactersManager.IncrementPlayerMaxHealth(10.0f);
                MaxHpLevel += amount;
                CurrentMaxHpStats += 10;
                Skillpoint -= 1;
            }
        }
    }

    public void DecreaseMaxHpLevel(int amount)
    {
        if (Skillpoint > 0)
        {
            if (MaxHpLevel > 0)
            {
                MaxHpLevel -= amount;
                CurrentMaxHpStats -= 10;
                Skillpoint += 1;
            }
        }
    }
    // -----------------------------MaxHp----------------------------- //


    // -----------------------------Ammunition Size----------------------------- //
    public void IncreaseMaxAmmoSizeLevel(int amount)
    {
        if (Skillpoint > 0)
        {
            if (MaxAmmoSizeLevel < 10)
            {
                MaxAmmoSizeLevel += amount;
                CurrentMaxAmmoSizeStats += 2;
                Skillpoint -= 2;
            }
        }
    }

    public void DecreaseMaxAmmoSizeLevel(int amount)
    {
        if (Skillpoint > 0)
        {
            if (MaxAmmoSizeLevel > 0)
            {
                MaxAmmoSizeLevel -= amount;
                CurrentMaxAmmoSizeStats -= 2;
                Skillpoint += 2;
            }
        }
    }
    // -----------------------------Ammunition Size----------------------------- //


    // ----------------------------------MaxEnergy-------------------------------------- //
    public void IncreaseMaxEnergyLevel(int amount)
    {
        if (Skillpoint > 0)
        {
            if (MaxEnergyLevel < 20)
            {
                MaxEnergyLevel += amount;
                MaxEnergyStats += 10;
                Skillpoint -= 1;
            }
        }
    }
    public void DecreaseMaxEnergyLevel(int amount)
    {
        if (Skillpoint > 0)
        {
            if (MaxEnergyLevel > 0)
            {
                MaxEnergyLevel -= amount;
                MaxEnergyStats -= 10;
                Skillpoint += 1;
            }
        }
    }
    // ----------------------------------MaxEnergy-------------------------------------- //

    // ----------------------------------ReloadSpeed-------------------------------------- //
    public void IncreaseReloadSpeedLevel(int amount)
    {
        if (Skillpoint > 0)
        {
            if (ReloadSpeedLevel < 10)
            {
                ReloadSpeedLevel += amount;
                CurrentReloadSpeedStats += 0.1f;
                Skillpoint -= 1;
            }
        }
    }

    public void DecreaseReloadSpeedLevel(int amount)
    {
        if (Skillpoint > 0)
        {
            if (ReloadSpeedLevel > 0)
            {
                ReloadSpeedLevel -= amount;
                CurrentReloadSpeedStats -= 0.1f;
                Skillpoint += 1;
            }
        }
    }
    // ----------------------------------ReloadSpeed-------------------------------------- //


    // ----------------------------------MoveSpeed-------------------------------------- //
    public void IncreaseMoveSpeedLevel(int amount)
    {
        if (Skillpoint > 0)
        {
            if (MoveSpeedLevel < 10)
            {
                MoveSpeedLevel += amount;
                CurrentMoveSpeedStats += 10;
                Skillpoint -= 1;
            }
        }
    }

    public void DecreaseMoveSpeedLevel(int amount)
    {
        if (Skillpoint > 0)
        {
            if (MoveSpeedLevel > 0)
            {
                MoveSpeedLevel -= amount;
                CurrentMoveSpeedStats -= 10;
                Skillpoint += 1;
            }
        }
    }
    // ----------------------------------MoveSpeed-------------------------------------- //


    // ----------------------------------Skill CDR-------------------------------------- //
    public void IncreaseSkillCDRLevel(int amount)
    {
        if (Skillpoint > 0)
        {
            if (SkillCDRLevel < 10)
            {
                SkillCDRLevel += amount;
                CurrentSkillCDRStats += 0.1f;
                Skillpoint -= 1;
            }
        }
    }
    public void DecreaseSkillCDRLevel(int amount)
    {
        if (Skillpoint > 0)
        {
            if (SkillCDRLevel > 0)
            {
                SkillCDRLevel -= amount;
                CurrentSkillCDRStats -= 0.1f;
                Skillpoint += 1;
            }
        }
    }
    // ----------------------------------Skill CDR-------------------------------------- //


    // ----------------------------------Fire rate-------------------------------------- //
    public void IncreaseFireRateLevel(int amount)
    {
        if (Skillpoint > 0)
        {
            if (FireRateLevel < 10)
            {
                FireRateLevel += amount;
                CurrentFireRateStats += 10;
                Skillpoint -= 1;
            }
        }
    }
    public void DecreaseFireRateLevel(int amount)
    {
        if (Skillpoint > 0)
        {
            if (FireRateLevel > 0)
            {
                FireRateLevel -= amount;
                CurrentFireRateStats -= 10;
                Skillpoint += 1;
            }
        }
    }
    // ----------------------------------Fire rate-------------------------------------- //

    // ----------------------------------Grenade Damage Area-------------------------------------- //
    public void IncreaseGrenadeDamageAreaLevel(int amount)
    {
        if (Skillpoint > 0)
        {
            if (GrenadeDamageAreaLevel < 10)
            {
                GrenadeDamageAreaLevel += amount;
                CurrentGrenadeDamageAreaStats += 10;
                Skillpoint -= 3;
            }
        }
    }

    public void DecreaseGrenadeDamageAreaLevel(int amount)
    {
        if (Skillpoint > 0)
        {
            if (GrenadeDamageAreaLevel > 0)
            {
                GrenadeDamageAreaLevel -= amount;
                CurrentGrenadeDamageAreaStats -= 10;
                Skillpoint += 3;
            }
        }
    }
    // ----------------------------------Grenade Damage Area-------------------------------------- //

    // ----------------------------------Gun Damage Increase-------------------------------------- //
    public void IncreaseGunDamageLevel(int amount)
    {
        if (Skillpoint > 0)
        {
            if (GunDamageLevel < 10)
            {
                GunDamageLevel += amount;
                CurrentGunDamageStats += 10;
                Skillpoint -= 3;
            }
        }
    }
    public void DecreaseGunDamageLevel(int amount)
    {
        if (Skillpoint > 0)
        {
            if (GunDamageLevel > 0)
            {
                GunDamageLevel -= amount;
                CurrentGunDamageStats -= 10;
                Skillpoint += 3;
            }
        }
    }
    // ----------------------------------Gun Damage Increase-------------------------------------- //

    // ----------------------------------Grenade Damage Increase-------------------------------------- //
    public void IncreaseGrenadeDamageLevel(int amount)
    {
        if (Skillpoint > 0)
        {
            if (GrenadeDamageLevel < 10)
            {
                GrenadeDamageLevel += amount;
                CurrentGrenadeDamageStats += 10;
                Skillpoint -= 3;
            }
        }
    }
    public void DecreaseGrenadeDamageLevel(int amount)
    {
        if (Skillpoint > 0)
        {
            if (GrenadeDamageLevel > 0)
            {
                GrenadeDamageLevel -= amount;
                CurrentGrenadeDamageStats -= 10;
                Skillpoint += 3;
            }
        }
    }
    // ----------------------------------Grenade Damage Increase-------------------------------------- //


    public void ResetAllskill()
    {
        Skillpoint = 100;   

        // -----------------------------MaxHp------------------------------//
        CurrentMaxHpStats = 0;
        MaxHpLevel = 0;

        // -----------------------------Ammunition Size--------------------//
        MaxAmmoSizeLevel = 0;
        CurrentMaxAmmoSizeStats = 0;

        // -----------------------------MaxEnergy--------------------------//
        MaxEnergyLevel = 0;
        MaxEnergyStats = 0;

        // -----------------------------ReloadSpeed------------------------//
        ReloadSpeedLevel = 0;
        CurrentReloadSpeedStats = 0;

        // -----------------------------MoveSpeed--------------------------//
        MoveSpeedLevel = 0;
        CurrentMoveSpeedStats = 0;

        // -----------------------------Skill CDR--------------------------//
        SkillCDRLevel = 0;
        CurrentSkillCDRStats = 0;

        // ----------------------------------Fire rate-------------------------------------- //
        FireRateLevel = 0;
        CurrentFireRateStats = 0;

        // ----------------------------------Grenade Damage Area-------------------------------------- //
        GrenadeDamageAreaLevel = 0;
        CurrentGrenadeDamageAreaStats = 0;

        // ----------------------------------Gun Damage Increase-------------------------------------- //  
        GunDamageLevel = 0;
        CurrentGunDamageStats = 0;

        // ----------------------------------Grenade Damage Increase-------------------------------------- //
        GrenadeDamageLevel = 0;
        CurrentGrenadeDamageStats = 0;
    }


    /*
                void addmaxhp(int amount)
                {
                    MaxHealth += amount;
                }

                void TakeDamage(int amount)
                {
                    CurrentHealth -= amount;

                    healthbar.value = CalculateHealth();
                    Debug.Log(CurrentHealth);
                    if (CurrentHealth <= 0)
                        Die();
                }

                float CalculateHealth()
                {
                    return CurrentHealth / MaxHealth;
                }


                void Die()
                {
                    CurrentHealth = 0;
                    Debug.Log("You are dead");

                }
                void Addexp(int amountexp)
                {
                    CurrentExp += amountexp;
                    expbar.value = CalculateExp();
                    if (CurrentExp == 100)
                        LevelUp();
                }
                int CalculateExp()
                {
                    return CurrentExp / MaxExp;
                }
                void LevelUp()
                {
                    Level += 1;
                    CurrentExp = 0;
                    MaxExp += 10;
                    CurrentHealth = MaxHealth;
                    Debug.Log("You Leveled Up");
                }
                 */
}

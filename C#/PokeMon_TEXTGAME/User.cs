using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//유저 플레이어 객체 관리

namespace PoketMonsterGame
{
    class User
    {
        private List<Monster> HaveMonster;
        private List<Item> HaveItem;
        private Monster UseMon;
        private char Key = (char)0;
        private int Gold = 0;
        bool shilde = true;
        int MonIndex = 0;

        public User()
        {
            HaveMonster = new List<Monster>();
            HaveItem = new List<Item>();
            UseMon = null;
        }
        public User(bool n)
        {
            HaveMonster = new List<Monster>();
            HaveItem = new List<Item>();
            HaveItem.Add(new Item("몬스터 볼", 1, 200));
            UseMon = null;
        }

        public bool Get_Shilde()
        {
            return shilde;
        }
        public int Get_MonIndex()
        {
            return MonIndex;
        }
        public char Get_Key()   //입력 받은 유저의 키를 반환
        {
            return Key;
        }
        public string Get_HaveMonName(int index)
        {
            return HaveMonster[index].GetName();
        }
        public void GetOtherMon(Monster Other)
        {
            HaveMonster.Add(new Monster(Other));
        }
        //######################################################################
        public void Set_Key()   //유저의 키입력을 받음
        {
            Key = (char)Console.Read();
            Console.ReadLine();
            Console.WriteLine();
        }
        public void Set_MonIndex(int index)
        {
            MonIndex = index;
        }
        //#######################################################################

        public void ShileON_OFF()
        {
            if (shilde) shilde = false;
            else shilde = true;
        }
        //가지고 있는 몬스터를 제거
        public void DelMyMon(int index) 
        {
            HaveMonster.Remove(HaveMonster[index]);
        }
       
        //가지고 있는 몬스터의 정보를 반환
        public void MonShow()
        {
            Console.WriteLine("#################################");
            for (int count = 1; count - 1 < HaveMonster.Count(); count++)
            {
                Console.WriteLine();
                Console.Write(string.Format($"<{count}번>\n" +
                    $"이름 : {HaveMonster[count - 1].GetName()}\n체력 : {HaveMonster[count - 1].GetHP()}\n힘 : {HaveMonster[count - 1].GetPower()}"));

            }
            Console.WriteLine();
            Console.WriteLine("#################################");
            Console.WriteLine();
        }

        //전투에 사용할 몬스터 선택
        public void ChoiceMon()
        {
            if (UseMon == null)
            {
                UseMon = HaveMonster[0];
            }
        }
        public string Get_UseMonName()
        {
            return UseMon.GetName();
        }
        public void Show_UseMon()
        {
            UseMon.Show();
        }
        public void UseMonAtk(ref Monster OtherMon, int index)
        {
            Random Rand = new Random();
            int damage;
            damage = Rand.Next(1, 3);
            if (damage > 1) Console.WriteLine("[공격이 생각보다 효과가 컸습니다.]");
            OtherMon.SetHp(OtherMon.GetHP() - (UseMon.GetPower() * damage * UseMon.HaveSkill[index].Get_SkillDamage()));
        }

        public void Set_UseMonHP(int _HP)
        {
            UseMon.SetHp(_HP);
        }
        public int Get_UseMonHP()
        {
            return UseMon.GetHP();
        }
        
        public int HaveMonCount()
        {
            return HaveMonster.Count();
        }
        public int Get_HaveMonHP(int index)
        {
            return HaveMonster[index].GetHP();
        }
        
        public Monster Get_HaveMon(int index)
        {
            return HaveMonster[index];
        }

        public void Get_HaveMon_ref(ref Monster temp, int index)
        {
            temp = HaveMonster[index];
        }

        public void Set_HaveMonHP(int index, Monster temp)
        {
            HaveMonster[index].SetHp(temp.GetHP());
        }

        public void UseMonSkill()
        {
            UseMon.SkillShow();
        }
        public string UseMonSkillName(int index)
        {
            return UseMon.HaveSkill[index].Get_SkillName();
        }
        public void TrunEnd()
        {
            UseMon.SkillCoolDown();
        }
        public void BattleEnd()
        {
            for(int i = 0; i<HaveMonster.Count; i++)
                HaveMonster[i].init_cool();
        }
        public void Skill_Show()
        {
            for(int i = 0; i<HaveMonster.Count(); i++)
            {
                HaveMonster[i].SkillNameShow();
            }
        }
        public void Set_Gold(int _Gold)
        {
            Gold = _Gold;
        }
        public int Get_Gold()
        {
            return Gold;
        }

        public void Add_Item(Item temp)
        {
            for (int i = 0; i < HaveItem.Count(); i++)
            {
                if (HaveItem[i].Get_Name() == temp.Get_Name())
                {
                    HaveItem[i].Up_count();
                }
            }
            if(Serch_Item(temp))
            {
                temp.Up_count();
                HaveItem.Add(temp);
            }
                
        }
        public bool UseItem_Show()
        {
            if(HaveItem.Count() == 0)
            {
                Console.WriteLine("[사용할 수 있는 아이템이 없습니다.]");
                return false;
            }
            else
            {
                Console.WriteLine("#################################");
                for (int i = 0; i < HaveItem.Count(); i++)
                {
                    Console.Write($"{i + 1}. {HaveItem[i].Get_Name()} : {HaveItem[i].Get_Count()}\n");
                }
                Console.WriteLine("#################################");
                return true;
            }
        }

        public bool Serch_Item(Item temp)
        {
            for (int i = 0; i < HaveItem.Count(); i++)
            {
                if (HaveItem[i].Get_Name() == temp.Get_Name())
                {
                    return false;
                }
            }
            return true;
        }
        
        public void Item_Use(ref GM GameManager, ref User Player, Monster Other)
        {
            if(HaveItem[Key - 49].Get_Name() == "몬스터 볼" && HaveItem[Key - 49].Get_Count()>0)
            {
                if (Other.GetHP() <= 30)
                {
                    HaveMonster.Add(new Monster(Other));
                    Console.WriteLine("[몬스터를 잡는데 성공했습니다.]");
                    Player.MonShow();
                    Other.SetHp(0);
                }
                else
                    Console.WriteLine("[몬스터를 잡는데 실패 했습니다.]");
                HaveItem[Key - 49].Down_count();
            }
            else if(HaveItem[Key - 49].Get_Name() == "상처약" && HaveItem[Key - 49].Get_Count() > 0)
            {
                if(UseMon.GetHP()<100)
                {
                    HaveItem[Key - 49].Down_count();
                    UseMon.SetHp(100);
                }
                else
                {
                    Console.WriteLine("[이미 체력이 최대치입니다.]");
                }
            }
        }

        public void UseMon_change()
        {
            if(HaveMonster[Key-49].GetHP() > 0)
            {
                UseMon = HaveMonster[Key - 49];
                Console.WriteLine("[몬스터가 변경되었습니다.]");
            }
            else
            {
                Console.WriteLine("[선택하신 몬스터는 체력이 없어 출전할 수 없습니다.]");
            }
        }

        public void AllMonHill()
        {
            for(int i = 0; i<HaveMonster.Count(); i++)
            {
                HaveMonster[i].SetHp(100);
            }
        }
    }
}

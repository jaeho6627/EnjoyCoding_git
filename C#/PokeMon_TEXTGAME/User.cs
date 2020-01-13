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
        private int MonsterBall = 0;
        private char Key = (char)0;
        bool shilde = true;
        int MonIndex = 0;

        public User()
        {
            HaveMonster = new List<Monster>();
            UseMon = null;
            MonsterBall = 3;
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
        public int Get_MonsterBall()    //유저가 가지고 있는 몬스터 볼을 반환
        {
            return MonsterBall;
        }
        public void GetOtherMon(Monster OtherMonster)   //다른 몬스터를 잡음
        {
            HaveMonster.Add(new Monster(OtherMonster));
        }
        public string Get_HaveMonName(int index)
        {
            return HaveMonster[index].GetName();
        }
        //######################################################################

        public void Set_MonsterBall(int nBall) //몬스터 볼을 저장
        {
            MonsterBall = nBall;
        }
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
        public void ChoiceMon(int index)
        {

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
    }
}

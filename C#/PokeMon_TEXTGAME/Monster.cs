using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//몬스터 클래스
namespace PoketMonsterGame
{
    class Monster
    {

        private string SponPoint;
        private string MonName;
        private int MonHP;
        private int MonPower;

        public List<Skill> HaveSkill;

        
        public Monster(string Point, string name, int hp, int power, Skill _Skill)
        {
            SponPoint = Point;
            MonName = name;
            MonHP = hp;
            MonPower = power;
            HaveSkill = new List<Skill>();
            HaveSkill.Add(_Skill);
        }
        public Monster() { }
        public Monster(Monster temp)
        {
            MonName = temp.GetName();
            MonHP = temp.GetHP();
            MonPower = temp.GetPower();
            HaveSkill = new List<Skill>();
            HaveSkill.Add(temp.HaveSkill[0]);
        }
        public string GetName()
        {
            return MonName;
        }
        public int GetHP()
        {
            return MonHP;
        }
        public int GetPower()
        {
            return MonPower;
        }
        public string GetSponPoint()
        {
            return SponPoint;
        }
        public void SetHp(int _HP)
        {
            MonHP = _HP;
        }
        public void Show()
        {
            Console.WriteLine("#################################");
            Console.WriteLine("{0}\n{1}\n{2}", MonName, MonHP, MonPower);
            Console.WriteLine("#################################");
        }
        
        public void AtkMon(ref User Player, int damage)
        {
            if (damage > 1) Console.WriteLine("[공격이 생각보다 효과가 컸습니다.]");
            Player.Set_UseMonHP(Player.Get_UseMonHP() - (MonPower * damage * HaveSkill[0].Get_SkillDamage()));
        }

        public void SkillShow()
        {
            Console.WriteLine("###############################");
            for(int i = 0; i<HaveSkill.Count(); i++)
            {
                Console.Write("{0}. ", i+1);
                HaveSkill[i].CoolShow();
            }
            Console.WriteLine("###############################");
        }
        public void SkillCoolDown()
        {
            for(int i = 0; i<HaveSkill.Count(); i++)
            {
                HaveSkill[i].CoolDown();
            }
        }
        public void init_cool()
        {
            for (int i = 0; i < HaveSkill.Count(); i++)
            {
                HaveSkill[i].Set_Cool(0);
            }
        }

        public void Add_Skill(Skill _skill)
        {
            HaveSkill.Add(_skill);
        }

        public void SkillNameShow()
        {
            Console.WriteLine("###############################");
            for (int i = 0; i < HaveSkill.Count(); i++)
            {
                Console.Write("{0}. ", i + 1);
                Console.WriteLine($"{HaveSkill[i].Get_Name()}");
            }
            Console.WriteLine("###############################");
        }
    }
}

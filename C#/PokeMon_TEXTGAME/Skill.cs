using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
/*
 * 스킬을 몬스터가 최대 4개까지 가질 수 있도록 함
 * 스킬의 효과가 상대 또는 자신에게 영향을 주어야 함
 * 몬스터는 기본적으로 스킬을 하나 가지고 생성된다.
 * 기본 스킬은 몸통 박치기로 기본공격이라 생각하면 된다.
 * 
 * 스킬의 속성
 * - 스킬이름
 * - 데미지
 * - 쿨타임 ( 대기 턴 )
 * 
 * 기능 
 * - 스킬을 사용하면 스킬 데미지를 몬스터의 기본 공격력에 곱을 한 만큼 상대 몬스터에게 데미지를 준다.
 * - 스킬을 사용할 때 화면에 스킬의 쿨타임을 표시한다.
 * - 쿨타임이 있는 스킬의 경우 턴이 지날 때 마다 쿨타임을 1 감소 시킨다.
 **/
namespace PoketMonsterGame
{
    class Skill
    {
        private string SkillName;
        private int damage;
        private int SkillCool;
        private int Cool;
        public Skill() { }
        public Skill(string _name, int _damage, int _MaxCool)
        {
            SkillName = _name;
            damage = _damage;
            SkillCool = _MaxCool;
            Cool = 0;
        }
        public Skill(Skill temp)
        {
            SkillName = temp.SkillName;
            damage = temp.damage;
            SkillCool = temp.SkillCool;
            Cool = 0;
        }
        public void CoolDown()
        {
            if (Cool > 0)
                SkillCool--;
        }

        public void CoolShow()
        {
            Console.WriteLine("{0} : {1}", SkillName, SkillCool);
        }

        public int Get_SkillDamage()
        {
            if (Cool >= 1)
            {
                Console.WriteLine("[선택하신 스킬은 현재 쿨타임 입니다.]\n[자동으로 '몸통박치기'를 시전합니다.]");
                return 1;
            }
            Cool = SkillCool;
            return damage;
        }

        public string Get_SkillName()
        {
            return SkillName;
        }
        public void Set_Cool(int set)
        {
            Cool = set;
        }
        public string Get_Name()
        {
            return SkillName;
        }
        public int Get_Damage()
        {
            return damage;
        }
        public int Get_Cool()
        {
            return SkillCool;
        }
    }
}

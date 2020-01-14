using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PoketMonsterGame
{
    class GM
    {
        public List<Monster> GrassMon;
        public List<Monster> MountMon;
        public List<Monster> RiverMon;
        public List<Skill> lm_Skill;
        public List<Item> lm_ITEM;

        public GM()
        {
            init_Skill();
            init_MonGrass();
            init_MonMount();
            init_MonRiver();
            init_Item();
        }

        private void init_MonGrass()
        {
            GrassMon = new List<Monster>();
            GrassMon.Add(new Monster("grass", "피카츄", 100, 20, lm_Skill[0]));
            GrassMon.Add(new Monster("grass", "이상해씨", 100, 20, lm_Skill[0]));
            GrassMon.Add(new Monster("grass", "캐터피", 100, 10, lm_Skill[0]));
        }

        private void init_MonMount()
        {
            MountMon = new List<Monster>();
            MountMon.Add(new Monster("Mount", "파이리", 100, 20, lm_Skill[0]));
            MountMon.Add(new Monster("Mount", "구구", 100, 10, lm_Skill[0]));
            MountMon.Add(new Monster("Mount", "깨비참", 100, 10, lm_Skill[0]));
        }

        private void init_MonRiver()
        {
            RiverMon = new List<Monster>();
            RiverMon.Add(new Monster("River", "꼬부기", 100, 20, lm_Skill[0]));
            RiverMon.Add(new Monster("River", "모래두지", 100, 10, lm_Skill[0]));
            RiverMon.Add(new Monster("River", "꼬렛", 100, 10, lm_Skill[0]));
        }

        private void init_Skill()
        {
            lm_Skill = new List<Skill>();
            lm_Skill.Add(new Skill("몸통박치기", 1, 0));
            lm_Skill.Add(new Skill("화염 방사", 4, 3));
            lm_Skill.Add(new Skill("풀잎 날리기", 3, 2));
            lm_Skill.Add(new Skill("물 대포", 5, 4));
            lm_Skill.Add(new Skill("백만 볼트", 4, 3));
        }

        private void init_Item()
        {
            lm_ITEM = new List<Item>();
            lm_ITEM.Add(new Item("몬스터 볼", 0, 200));
            lm_ITEM.Add(new Item("상처약", 0, 100));
        }

        public void ShowMonsterList()
        {
            for (int i = 0; i < GrassMon.Count(); i++)
                GrassMon[i].Show();
            for (int i = 0; i < MountMon.Count(); i++)
                MountMon[i].Show();
            for (int i = 0; i < RiverMon.Count(); i++)
                RiverMon[i].Show();
        }

        public void partner(ref User Player)
        {
            if (Player.Get_Key() == '1') Player.GetOtherMon(GrassMon[1]);
            else if (Player.Get_Key() == '2') Player.GetOtherMon(MountMon[0]);
            else Player.GetOtherMon(RiverMon[0]);
        }

        public void ProdMon(string area, ref Monster Mon)
        {
            Random Rand = new Random();
            int RandMon = Rand.Next(0, 3);


            if (area == "Grass") Mon = new Monster(GrassMon[RandMon]);
            else if (area == "Mount") Mon = new Monster(MountMon[RandMon]);
            else Mon = new Monster(RiverMon[RandMon]);
        }
        public void BattleResult(ref User Player, ref Monster OtherMon)
        {
            //공격 결과 출력
            Console.WriteLine("<전투결과>\n[나의 몬스터]");
            Player.Show_UseMon();
            Console.WriteLine("[상대 몬스터]");
            OtherMon.Show();
        }
        //몬스터 검색
        public int SelectMon(Monster MainMon)
        {
            switch (MainMon.GetSponPoint())
            {
                case "grass":
                    for (int i = 0; i < GrassMon.Count(); i++)
                        if (MainMon.GetName() == GrassMon[i].GetName())
                            return GrassMon[i].GetHP();
                    break;
                case "Mount":
                    for (int i = 0; i < MountMon.Count(); i++)
                        if (MainMon.GetName() == MountMon[i].GetName())
                            return MountMon[i].GetHP();
                    break;
                case "River":
                    for (int i = 0; i < RiverMon.Count(); i++)
                        if (MainMon.GetName() == RiverMon[i].GetName())
                            return RiverMon[i].GetHP();
                    break;
            }
            return 0;
        }

        public void SkillShow()
        {
            Console.WriteLine("#################################");
            for (int count = 0; count < lm_Skill.Count(); count++)
            {
                Console.WriteLine();
                Console.Write(string.Format($"<{count+1}번>\n" +
                    $"이름 : {lm_Skill[count].Get_Name()}\n데미지 배수 : {lm_Skill[count].Get_Damage()}\n쿨 : {lm_Skill[count].Get_Cool()}"));
            }
            Console.WriteLine();
            Console.WriteLine("#################################");
            Console.WriteLine();
        }

        public void Give_Price(ref User Player)
        {
            Console.WriteLine("[전투 보상으로 '100'원을 획득하셨습니다.]");
            Player.Set_Gold(Player.Get_Gold() + 100);
        }

        public void Show_Shop()
        {
            Console.WriteLine("#################################");
            for (int i = 0; i<lm_ITEM.Count(); i++)
            {
                Console.Write($"{i + 1}. {lm_ITEM[i].Get_Name()} : {lm_ITEM[i].Get_Price()}\n");
            }
            Console.WriteLine("#################################");
        }
        public void Get_ShopItem(ref User Player)
        {
            if (Player.Get_Key()<'3')
            {
                if (Player.Get_Gold() >= lm_ITEM[Player.Get_Key() - 49].Get_Price())
                {
                    Player.Set_Gold(Player.Get_Gold() - lm_ITEM[Player.Get_Key() - 49].Get_Price());
                    Console.Write($"['{lm_ITEM[Player.Get_Key() - 49].Get_Name()}'을 구매 하였습니다.]\n");
                    Player.Add_Item(lm_ITEM[Player.Get_Key() - 49]);
                }
                else
                {
                    Console.Write($"[골드가 부족해 아이템을 구매하지 못하였습니다.]\n");
                }
            }
        }
        //static void MonHill(ref User Player)
        //{

        //    for (int i = 0; i < Player.HaveMonCount(); i++)
        //        if (Player.Get_HaveMonHP(i) <= 0)
        //            Player.Set_HaveMonHP(i, SelectMon(Player.Get_HaveMon(i)));
        //    Console.WriteLine("[치료가 완료 되었습니다.]");
        //    Console.WriteLine();
        //}
    }
}

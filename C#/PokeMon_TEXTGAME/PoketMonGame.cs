using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//포켓몬 게임 전반적인 시스템 관리
namespace PoketMonsterGame
{
    class PoketMonGame
    {
        private GM GameManager = new GM();
        private User Player = new User();

        public void PoketMon()
        {
            
            Console.WriteLine("GAME_START~~");
            Console.WriteLine();
            Console.Write("[안녕하십니까. 포켓몬 세계에 오신 것을 환영합니다.]\n[파트너로 삼을 포켓몬을 선택해주세요.]\n");
            Console.Write("[1. 이상해씨 2. 파이리 3. 꼬북이]\n유저 : ");
            Player.Set_Key();
            GameManager.partner(ref Player);

            Console.Write(string.Format($"[\"{Player.Get_HaveMonName(0)}\"을(를) 가졌습니다.]\n[게임을 시작합니다.]\n\n\n"));

            while (true)
            {
                Console.Write("[마을에 입장했습니다.]\n" +
                    "['상점'에서 몬스터볼을 구매하실 수 있습니다.]\n" +
                    "['여관'에서 소지하고 있는 몬스터의 체력을 회복할 수 있습니다.]\n" +
                    "['던전'에서 몬스터와 대결하고 몬스터를 잡을 수 있습니다.]\n" +
                    "['병원'에서 당신이 소지한 몬스터의 상태를 확인할 수 있습니다.]\n" +
                    "[1. 던전 2. 병원 3. 상점 4. 훈련장]\n유저 : ");
                Player.Set_Key();
                switch (Player.Get_Key())
                {
                    case '1':
                        ChoiceDon(ref Player, ref GameManager);
                        break;
                    case '2':
                        //Hospital(ref Player);
                        break;
                    case '3': //상점
                        break;
                    case '4': //훈련장
                        Training(ref Player, ref GameManager);
                        break;
                    default:
                        GameManager.ShowMonsterList();
                        break;
                }
            }
        }

        //몬스터 랜덤 생성 //생성 = produce
        
        static void ChoiceDon(ref User Player, ref GM GameManager)
        {
            Console.Write("[던전에 입장했습니다.]\n[어디로 이동하시겠습니까?]\n[1. 초원 2. 산 3. 강]\n유저 : ");
            Player.Set_Key();
            switch (Player.Get_Key())
            {
                case '1':
                    Console.WriteLine("[초원으로 이동했습니다.]");
                    MoveDon("Grass", ref Player, ref GameManager);
                    break;
                case '2':
                    Console.WriteLine("[산으로 이동했습니다.]");
                    MoveDon("Mount", ref Player, ref GameManager);
                    break;
                case '3':
                    Console.WriteLine("[강으로 이동했습니다.]");
                    MoveDon("River", ref Player, ref GameManager);
                    break;
            }
        }
        static void MoveDon(string area, ref User Player, ref GM GameManager)
        {
            Random Rand = new Random();
            int RandEvent;

            while (true)
            {
                Console.Write("[행동을 선택해주세요.]\n[1. 이동 2. 돌아가기]\n유저 : ");
                Player.Set_Key();

                if (Player.Get_Key() == '1')
                {
                    Console.WriteLine("[앞으로 한걸음 이동했습니다.]");
                    RandEvent = Rand.Next(0, 3);
                    if (RandEvent > 0)//몬스터와 조우
                    {
                        Monster Mon = new Monster();
                        GameManager.ProdMon(area, ref Mon);
                        Console.WriteLine(string.Format($"[\"{Mon.GetName()}\"이(가) 등장했습니다.]"));
                        Console.Write(string.Format($"[\"{Mon.GetName()}\"와 전투배틀을 진행하시 겠습니까?]\n[1. 예 2. 아니오]\n유저 : "));
                        Player.Set_Key();
                        if (Player.Get_Key() == '1')
                            BattleMon(ref Mon, ref Player, ref GameManager);
                        else
                            Console.WriteLine("[전투를 진행하지 않습니다.]");
                    }
                    else
                        Console.WriteLine("[아무일도 일어나지 않았습니다.]");
                    Console.WriteLine();
                }
                else
                {
                    Console.WriteLine("[마을로 돌아 갑니다.]");
                    Console.WriteLine();
                    break;
                }
            }
        }
        static void BattleMon(ref Monster Mon, ref User Player, ref GM GameManager)
        {
            
            Console.WriteLine("[전투가 시작되었습니다.]");
            Console.WriteLine("[전투의 시작은 최근에 사용된 몬스터를 소환해 진행됩니다.]\n[처음에는 첫번째 몬스터가 소환됩니다.]");
            Player.ChoiceMon();
            Console.WriteLine("['{0}' 이(가) 필드에 소환되었습니다.]\n", Player.Get_UseMonName());
            Player.Show_UseMon();
            while (true)
            {
                Console.Write("[행동을 선택해주세요.]\n[1. 공격 2. 막기 3. 몬스터 변경 4. 도망]\n유저 : ");
                Player.Set_Key();

                if (Player.Get_Key() == '1')
                {
                    Console.WriteLine("[사용할 스킬을 선택해주세요.]");
                    Player.UseMonSkill();
                    Console.Write("유저 : ");
                    Player.Set_Key();                    
                    Console.WriteLine($"[나의 '{Player.Get_UseMonName()}'이(가) {Player.UseMonSkillName(Player.Get_Key() - 49)}(으)로 공격했습니다.]");
                    Player.UseMonAtk(ref Mon, Player.Get_Key()- 49);

                }
                else if (Player.Get_Key() == '2')
                {
                    Console.WriteLine("[나의 '{0}'이(가 막기를 시전했습니다.)]", Player.Get_UseMonName());
                    Player.ShileON_OFF();
                }
                else if (Player.Get_Key() == '3')
                {
                    Console.WriteLine("[몬스터를 변경합니다.]");
                    //몬스터 변경 함수 ( HP를 확인하고 0과 같은 경우 변경이 불가능 하도록 )
                }
                else
                {
                    Console.WriteLine("[도망치는데 성공했습니다.]");
                    break;
                }

                if (Mon.GetHP() <= 0)
                {
                    Console.WriteLine("[상대몬스터를 처치하는데 성공했습니다.]\n");
                    GetOtherMon(Mon, ref Player);
                    Player.BattleEnd();
                    break;
                }

                if (Player.Get_Shilde())
                {
                    Console.WriteLine("[상대 '{0}'이(가) 공격했습니다.]", Mon.GetName());
                    Mon.AtkMon(ref Player, 1);
                }
                else
                {
                    Console.WriteLine("[막기에 성공했습니다.]");
                    Player.ShileON_OFF();
                }

                Player.TrunEnd();

                if (Player.Get_UseMonHP() <= 0)
                {
                    Console.WriteLine("[나의 '{0}'이(가) 공격 받아 HP가 0이 되었습니다.]", Player.Get_UseMonName());
                    Console.Write("[몬스터를 변경하시겠습니까?]\n[1. 예 2. 아니오 도망갈래요]\n 유저 : ");
                    Player.Set_Key();
                    if (Player.Get_Key() == '2')
                    {
                        Console.WriteLine("[전투를 종료합니다.]");
                        break;
                    }
                    else
                    {
                        Console.Write("[사용할 몬스터를 선택해주세요.]\n유저 : ");
                        //몬스터 변경 함수
                    }
                }
                GameManager.BattleResult(ref Player, ref Mon);
            }
        }
        static void GetOtherMon(Monster OtherMon, ref User Player)
        {
            Console.Write("[처치한 몬스터를 잡으시겠습니까?]\n[소지하고 있는 몬스터 볼 : {0}]\n[1. 예 2. 아니오]", Player.Get_MonsterBall());
            Player.Set_Key();
            if (Player.Get_Key() == '1'&&Player.Get_MonsterBall()>0)
            {
                Player.Set_MonsterBall(Player.Get_MonsterBall() - 1);
                Player.GetOtherMon(OtherMon);
                Console.WriteLine("[몬스터를 잡는데 성공했습니다.]");
                Player.MonShow();
            }
            else if(Player.Get_MonsterBall() <= 0)
            {
                Console.WriteLine("[몬스터 볼이 없어 잡을 수 없습니다.]");
            }
        }
        static void Training(ref User Player, ref GM GameManager)
        {
            Console.Write("[훈련장에 입장했습니다.]\n[원하시는 스킬을 몬스터에게 학습시키거나 잊게 만들 수 있습니다.]\n");
            Console.Write("[훈련을 원하시는 포켓몬을 선택해주세요.]\n");
            Player.MonShow();
            Console.Write("유저 : ");
            Player.Set_Key();
            Monster TrainMon = null;
            Player.Get_HaveMon_ref(ref TrainMon, Player.Get_Key() - 49);
            Console.Write($"['{TrainMon.GetName()}'이(가) 선택 되었습니다.]\n[원하시는 행위를 선택해주세요.]\n[1. 학습 2. 망각]\n유저 : ");
            Player.Set_Key();
            if(Player.Get_Key() == '1')
            {
                Console.Write("[학습시키고 싶으신 기술을 선택해주세요.]\n");
                GameManager.SkillShow();
                Console.Write("유저 : ");
                Player.Set_Key();
                TrainMon.Add_Skill(GameManager.lm_Skill[Player.Get_Key() - 49]);
                Console.Write($"['{TrainMon.GetName()}'이(가) '{GameManager.lm_Skill[Player.Get_Key() - 49].Get_SkillName()}'을(를) 배우는데 성공했습니다.\n]");
            }
            else
            {
                Console.Write("[지우실 기술을 선택해주세요.]\n");
                TrainMon.SkillNameShow();
                Console.Write("유저 : ");
                Player.Set_Key();
                TrainMon.HaveSkill.Remove(TrainMon.HaveSkill[Player.Get_Key()-49]);
                Console.Write($"['{TrainMon.GetName()}'이(가) 스킬을 완벽하게 잊었습니다.]\n\n");
            }
            
        }

        //static void Hospital(ref User Player)
        //{
        //    Console.Write("[병원에 입장하셨습니다.]\n[소지하고 계신 몬스터는 다음과 같습니다.]");
        //    do
        //    {
        //        Player.MonShow();
        //        Console.WriteLine();
        //        Console.WriteLine();

        //        Console.Write("[1. 치료한다 2. 다시 확인한다 3. 돌아간다]\n유저 : ");
        //        Player.Set_Key();
        //        if (Player.Get_Key() == '1')
        //            MonHill(ref Player);

        //    } while (Player.Get_Key() == '2');
        //    Console.WriteLine("[마을로 이동합니다.]");
        //    Console.WriteLine();
        //}
    }
}

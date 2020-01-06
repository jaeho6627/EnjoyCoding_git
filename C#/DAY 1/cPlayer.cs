using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C샵_수업_1
{
    class cPlayer
    {
        //몬스터/플레이어 공통
        private int HP; //체력
        private int Power; //공격력
        private int EXP;//경험치
        //플레이어 전용
        private int MP; //마나
        private bool Shilde = false; //막기 상태 값 (0.1)
        //몬스터 전용
        private bool Attack = false; //공격 상태 값 (0.1)
        //기능
        public cPlayer(int _HP, int _Power, int _EXP, int _MP)
        {
            HP = _HP;
            Power = _Power;
            EXP = _EXP;
            MP = _MP;
        }
        public void Set_HP(int _HP) { HP = _HP; }
        public void Set_Power(int _Power) { Power = _Power; }
        public void Set_EXP(int _EXP) { EXP += _EXP; }
        public void Set_MP(int _MP) { MP = _MP; }
        public void Set_Shilde()
        {
            if (Shilde == true) Shilde = false;
            else Shilde = true;
        }
        public void Set_Attack()
        {
            if (Attack == true) Attack = false;
            else Attack = true;
        }

        public int Get_HP() { return HP; }
        public int Get_Power() { return Power; }
        public int Get_EXP() { return EXP; }
        public int Get_MP() { return MP; }
        public bool Get_Shilde() { return Shilde; }

        public void fc_Attack(ref cPlayer Them, bool Skill)
        {
            if (Skill == true) //일반 공격 시 
            {
                int Temp_HP = Them.Get_HP() - Power;
                Them.Set_HP(Temp_HP);
            }
            else //스킬 공격
            {
                int Temp_HP = Them.Get_HP() - (int)(Power * 1.5);
                Them.Set_HP(Temp_HP);
            }
        }
    }
    class GameManager
    {
        /*//문제 2 : 반복문
         * 플레이어와 몬스터가 둘중 한명이 사망할 때까지 전투를 한다.
         * 플레이어는 일반공격과 스킬공격, 막기를 할 수 있다.
         * 몬스터는 50%확률로 공격을 한다.
         * 플레이어는 공격력과 체력, 마나를 가진다.
         * 마나는 한턴에 10씩 회복된다.
         * 몬스터를 처치하면 경험치를 획득한다.
         * *******************************************
         * 플레이어의 상태값(변수) : 공격력, 체력, 마나, 막기 상태, 경험치
         * 몬스터의 상태값 : 공력력, 체력, 공격 상태값, 경험치
         * 시스템 상태값 : 랜덤 변수, 문자열 변수
         * ********************************************
         * 플레이어 기능(함수) : 공격, 스킬공격, 막기
         * 몬스터의 기능 : 공격(랜덤확률)
         * 시스템 기능 : 자동 반복(턴 체크, 유저 마나 회복, 전투 종료 조건 확인, 전투결과 출력)
        */
        static void Display(ref cPlayer user)
        {
            Console.WriteLine("##########################################################");
            Console.WriteLine("<Player state>");
            Console.WriteLine("HP : " + user.Get_HP());
            Console.WriteLine("MP : " + user.Get_MP());
            Console.WriteLine("Power : " + user.Get_Power());
            Console.WriteLine("EXP : " + user.Get_EXP());
            Console.WriteLine("##########################################################");
        }
        static void Battle_show(ref cPlayer User, ref cPlayer Mon)
        {
            Console.WriteLine("##########################################################");
            Console.WriteLine("<Player state>");
            Console.WriteLine("HP : " + User.Get_HP());
            Console.WriteLine("MP : " + User.Get_MP());
            Console.WriteLine("<Monster state>");
            Console.WriteLine("HP : " + Mon.Get_HP());
            Console.WriteLine("##########################################################");
        }
        public void Battle()
        {
            cPlayer User = new cPlayer(100, 10, 0, 50);
            cPlayer Monster = new cPlayer(100, 10, 100, 0);
            Random _Random = new Random();
            int MonAtk = 0;
            Console.WriteLine("##########################################################\n" + "전투를 시작합니다.\n" +
                "당신은 공격과 스킬공격, 막기를 할수 있으며, 몬스터는 50%확률로 공격을 합니다.\n" + "몬스터 또는 당신의 HP가 0이되면 게임은 끝납니다.\n" +
                "몬스터가 당신을 죽이기 전에 먼저 몬스터를 처치하십시오\n" + "##########################################################\n");
            Display(ref User);
            while (true)
            {
                string Choice = "";

                Console.Write("무슨 행동을 하시겠습니까? \n a. 일반 공격 s. 스킬 공격 d. 막기\n(턴을 넘기시려면 아무키나 누르시면 됩니다.)\n - ");
                Choice = Console.ReadLine();
                switch (Choice)
                {
                    case "a":
                        if (User.Get_MP() >= 10)
                        {
                            Console.WriteLine("몬스터를 일반공격합니다.");
                            User.Set_MP(User.Get_MP() - 10);
                            User.fc_Attack(ref Monster, true);
                        }
                        break;
                    case "s":
                        if (User.Get_MP() >= 20)
                        {
                            Console.WriteLine("몬스터를 스킬공격합니다.");
                            User.Set_MP(User.Get_MP() - 20);
                            User.fc_Attack(ref Monster, false);
                        }
                        break;
                    case "d":
                        if (User.Get_MP() >= 10)
                            Console.WriteLine("막기를 시전합니다.");
                        User.Set_MP(User.Get_MP() - 10);
                        User.Set_Shilde();
                        break;
                    default:
                        Console.WriteLine("턴을 넘김니다.");
                        break;
                }

                MonAtk = _Random.Next(0, 3);
                if (MonAtk >= 1)
                {
                    if (User.Get_Shilde() == false)
                    {
                        if (MonAtk == 1)
                        {
                            Console.WriteLine("몬스터가 일반공격을 시전했습니다.");
                            Monster.fc_Attack(ref User, true);
                        }
                        else if (MonAtk == 2)
                        {
                            Console.WriteLine("몬스터가 스킬공격을 시전했습니다.");
                            Monster.fc_Attack(ref User, false);
                        }
                    }
                    else
                    {
                        Console.WriteLine("막기에 성공했습니다.");
                        User.Set_MP(User.Get_MP() + 30);
                    }
                }
                else
                {
                    Console.WriteLine("몬스터가 공격하지 않았습니다.");
                }
                if (User.Get_Shilde() == true)
                    User.Set_Shilde();

                Battle_show(ref User, ref Monster);

                if (User.Get_MP() < 100)
                {
                    Console.WriteLine("마나를 회복합니다. MP +5");
                    User.Set_MP(User.Get_MP() + 5);
                }

                if (User.Get_HP() == 0)
                {
                    Console.Write("You Die~~");
                    break;
                }
                else if (Monster.Get_HP() == 0)
                {
                    Console.Write("You Win!!" + "Get EXP : " + Monster.Get_EXP());
                    break;
                }
            }
        }
    }
}

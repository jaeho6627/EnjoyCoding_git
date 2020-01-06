using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C샵_수업_1
{
    class Program
    {
        //정수 값을 입력 받아 3로 나눈 결과 출력
        static void ValMain()
        {
            int nScore = 0;
            float fAverage = 0.0f;
            string sScore, sAverage;
            Console.WriteLine("Score : " + nScore);
            Console.WriteLine("Average : " + fAverage);
            Console.Write("Please input integer\n: ");
            sScore = Console.ReadLine();
            
            nScore = Convert.ToInt32(sScore);
            fAverage = nScore / 3.0f;
            Console.WriteLine("score : " + nScore + "average : " + fAverage);
            sAverage = Convert.ToString(fAverage);
            Console.WriteLine("string average : " + sAverage);

        }
       
        //랜덤 클래스를 활용해 랜덤 값을 만들고 크리티컬 확률과 조건을 확인해 몬스터에게 데미지를 주는 예제 코드
        static void criticalAttackMain()
        {
            Random cRandom = new Random();
            int nRandom = cRandom.Next(1, 3); //랜덤으로 구한 값.
            Console.WriteLine("Random : " + nRandom); //1~3-1(2) 범위의 값들 중 하나를 랜덤으로 출력함

            int nPlayerPower = 10;
            int nMonsterHP = 100;

            if(nRandom == 1)
            {
                nPlayerPower = (int)(nPlayerPower * 1.5);
                Console.WriteLine("Critical Damage : " + nPlayerPower);
            }
            else
            {
                Console.WriteLine("Player Demage : " + nPlayerPower);
            }

            nMonsterHP -= nPlayerPower;

            Console.WriteLine("Monster HP : " + nMonsterHP);
        }
      
        //switch 문을 활용해 다 분기 조건문을 검사 할 수 있는 예제 코드
        static void MoveHome()
        {
            Console.Write("What do you want : (home, dungeon, store)\n: ");
            string sChoice = Console.ReadLine();

            switch(sChoice)
            {
                case "home":
                case "Home":
                case "HOME":
                    Console.WriteLine("We move \"Home\"");
                    break;
                case "dungeon":
                case "Dungeon":
                case "DUNGEON":
                    Console.WriteLine("We move \"Dungeon\"");
                    break;
                case "store":
                case "Store":
                case "STORE":
                    Console.WriteLine("We move \"Store\"");
                    break;

            }

        }

        //몬스터가 죽을 때까지 반복적으로 공격하는 함수
        static void AttackWhile()
        {
            int nPlayerDemage = 10;
            int nMonsterHP = 10000;

            while(nMonsterHP>0)
            {
                nMonsterHP -= nPlayerDemage;
                string msg = string.Format($"Monster HP is {nMonsterHP}, Player Demage is {nPlayerDemage}.");
                //string 자료형에 정의 되어 있는 Format 함수를 통해 원하는 형태로 문자열을 저장할 수 있다.
                Console.WriteLine(msg);
            }
        }

        //몬스터 리스트 제작
        static void MonsterList()
        {
            List<string> ListMonster = new List<string>();

            ListMonster.Add("슬라임");
            ListMonster.Add("스켈레톤");
            ListMonster.Add("좀비");
            ListMonster.Add("드래곤");
            //c언어와 동일하게 배열의 첫번째 요소의 인덱스 값이 0, 마지막은 배열 요소 개수 -1 이다.
            //Add가 호출될 때마다 저장할 새로운 매모리가 호출된다 ( 가정 )
            Console.WriteLine(ListMonster[0]);
            Console.WriteLine(ListMonster[3]);

            for(int i = 0; i<ListMonster.Count; i++) //List 객체 안에 count라는 변수가 따로 저장되었다.
            {
                //Console.WriteLine(string.Format("Monster [{0}] : {1}", i, ListMonster[i])); //Format 함수를 사용하는 두가지 방법
                Console.WriteLine(string.Format($"Monster [{i}] : {ListMonster[i]}"));
            }
        }

        /*//문제 1 : 변수 
         * 국어, 수학, 영어, 국사의 점수를 입력 받아 평균과 평균에 해당하는 점수를 출력하는 프로그램 출력
         * 국어, 수학, 영어, 국사는 정수형 변수
         * 평군은 실수형 변수
         * 점수는 문자열 변수
        */
        static void Average()
        {
            int Korean;
            int Math;
            int English;
            int History;
            float Average;
            string rating;
            Console.WriteLine("국어, 수학, 영어, 국사의 점수를 차례로 입력해주세요.");
            Console.Write("국어 : ");
            Korean = int.Parse(Console.ReadLine());
            Console.Write("수학 : ");
            Math = int.Parse(Console.ReadLine());
            Console.Write("영어 : ");
            English = int.Parse(Console.ReadLine());
            Console.Write("국사 : ");
            History = int.Parse(Console.ReadLine());

            Average = (Korean + Math + English + History) / 4.0f;
            Console.WriteLine(string.Format($"Average : {Average}"));
            if(Average>90.0f)
            {
                rating = string.Format("A");
                Console.WriteLine("SCORE is : " + rating);
            }
            else if(Average>70.0f)
            {
                rating = string.Format("B");
                Console.WriteLine("SCORE is : " + rating);
            }
            else if(Average>50.0f)
            {
                rating = string.Format("C");
                Console.WriteLine("SCORE is : " + rating);
            }
            else
            {
                rating = string.Format("D");
                Console.WriteLine("SCORE is : " + rating);
            }
        }

        
        static void Main(string[] args)
        {
            {//예제
                //ValMain();
                //criticalAttackMain();
                //MoveHome();
                // AttackWhile();
                //MonsterList();
            }
            {//문제
                //Average();
                GameManager GamePlay;
                GamePlay = new GameManager();
                GamePlay.Battle();
            }
        }
    }
}

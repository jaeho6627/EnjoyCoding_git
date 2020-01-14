using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PoketMonsterGame
{
    class Item
    {
        private string Item_name;
        private int Item_count;
        private int Item_price;
        //
        public Item(string _name, int _count, int _price)
        {
            Item_name = _name;
            Item_count = _count;
            Item_price = _price;
        }
        public Item(){ }
        public Item(Item temp)
        {
            Item_name = temp.Item_name;
            Item_count = temp.Item_count;
            Item_price = temp.Item_price;
        }

        public string Get_Name()
        {
            return Item_name;
        }

        public int Get_Price()
        {
            return Item_price;
        }
        public int Get_Count()
        {
            return Item_count;
        }
        public void Up_count()
        {
            Item_count++;
        }
        public void Down_count()
        {
            Item_count--;
        }
    }
}

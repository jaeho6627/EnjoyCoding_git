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
        //
        public Item(string _name, int _count)
        {
            Item_name = _name;
            Item_count = _count;
        }
        public Item(){ }
    }
}

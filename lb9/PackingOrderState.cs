using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lb9
{
    public class PackingOrderState : IOrderState
    {
        public void Proceed(OrderContext context)
        {
            Console.WriteLine("Order has been shipped.");
            context.SetState(new OrderShippedState());
        }

        public void Cancel(OrderContext context)
        {
            Console.WriteLine("Cannot cancel. Order is being packed.");
        }

        public void PrintStatus()
        {
            Console.WriteLine("Current State: Packing Order.");
        }
    }

}

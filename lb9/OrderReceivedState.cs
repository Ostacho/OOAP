using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lb9
{
    public class OrderReceivedState : IOrderState
    {
        public void Proceed(OrderContext context)
        {
            Console.WriteLine("Order is already completed.");
        }

        public void Cancel(OrderContext context)
        {
            Console.WriteLine("Cannot cancel. Order already completed.");
        }

        public void PrintStatus()
        {
            Console.WriteLine("Current State: Order Received by Customer.");
        }
    }

}

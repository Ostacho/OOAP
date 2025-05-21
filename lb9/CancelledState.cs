using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lb9
{
    public class CancelledState : IOrderState
    {
        public void Proceed(OrderContext context)
        {
            Console.WriteLine("Cannot proceed. Order was cancelled.");
        }

        public void Cancel(OrderContext context)
        {
            Console.WriteLine("Order is already cancelled.");
        }

        public void PrintStatus()
        {
            Console.WriteLine("Current State: Order Cancelled.");
        }
    }

}

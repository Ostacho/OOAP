using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lb9
{
    public class OrderShippedState : IOrderState
    {
        public void Proceed(OrderContext context)
        {
            Console.WriteLine("Order delivered to destination.");
            context.SetState(new OrderDeliveredState());
        }

        public void Cancel(OrderContext context)
        {
            Console.WriteLine("Cannot cancel. Order has been shipped.");
        }

        public void PrintStatus()
        {
            Console.WriteLine("Current State: Order Shipped.");
        }
    }

}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lb9
{
    public class OrderDeliveredState : IOrderState
    {
        public void Proceed(OrderContext context)
        {
            Console.WriteLine("Order received by customer.");
            context.SetState(new OrderReceivedState());
        }

        public void Cancel(OrderContext context)
        {
            Console.WriteLine("Cannot cancel. Order already delivered.");
        }

        public void PrintStatus()
        {
            Console.WriteLine("Current State: Order Delivered.");
        }
    }

}

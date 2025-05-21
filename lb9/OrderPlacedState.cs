using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lb9
{
    public class OrderPlacedState : IOrderState
    {
        public void Proceed(OrderContext context)
        {
            Console.WriteLine("Proceeding to: Waiting for Payment.");
            context.SetState(new WaitingForPaymentState());
        }

        public void Cancel(OrderContext context)
        {
            Console.WriteLine("Order cancelled.");
            context.SetState(new CancelledState());
        }

        public void PrintStatus()
        {
            Console.WriteLine("Current State: Order Placed.");
        }
    }

}

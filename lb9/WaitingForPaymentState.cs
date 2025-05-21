using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lb9
{
    public class WaitingForPaymentState : IOrderState
    {
        public void Proceed(OrderContext context)
        {
            Console.WriteLine("Payment received.");
            context.SetState(new PaymentReceivedState());
        }

        public void Cancel(OrderContext context)
        {
            Console.WriteLine("Order cancelled before payment.");
            context.SetState(new CancelledState());
        }

        public void PrintStatus()
        {
            Console.WriteLine("Current State: Waiting for Payment.");
        }
    }

}

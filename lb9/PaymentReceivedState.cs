using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lb9
{
    public class PaymentReceivedState : IOrderState
    {
        public void Proceed(OrderContext context)
        {
            Console.WriteLine("Packing order.");
            context.SetState(new PackingOrderState());
        }

        public void Cancel(OrderContext context)
        {
            Console.WriteLine("Cannot cancel. Payment already received.");
        }

        public void PrintStatus()
        {
            Console.WriteLine("Current State: Payment Received.");
        }
    }

}
